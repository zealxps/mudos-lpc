#define SUPPRESS_COMPILER_INLINES
#include "std.h"
#include "lpc_incl.h"
#include "efuns_incl.h"
#include "file.h"
#include "file_incl.h"
#include "backend.h"
#include "simul_efun.h"
#include "debug.h"
#include "eoperators.h"
#include "efunctions.h"
#include "lex.h"
#include "sprintf.h"
#include "swap.h"
#include "comm.h"
#include "port.h"
#include "qsort.h"
#include "compiler.h"
#include "regexp.h"

svalue_t* __args;

#ifdef OPCPROF
	#include "opc.h"

	static int opc_eoper[BASE];
#endif 

#ifdef OPCPROF_2D
	/* warning, this is typically 4 * 100 * 100 = 40k */
	static int opc_eoper_2d[BASE + 1][BASE + 1];
	static int last_eop = 0;
#endif 

static char *type_names[] = 
{
	"int", "string", "array", "object", "mapping", "fun", "float", "buffer", "class",
};
#define TYPE_CODES_END 0x400
#define TYPE_CODES_START 0x2

extern int max_cost;
extern int call_origin;

INLINE void push_indexed_lvalue(int);
#ifdef DEBUG
	INLINE_STATIC svalue_t *find_value(int);
#endif 
void break_point(void);
INLINE_STATIC void do_loop_cond_number(void);
INLINE_STATIC void do_loop_cond_local(void);
static void do_catch(char*);
#ifdef DEBUG
	int last_instructions(void);
#endif 
static float _strtof(char *, char **);
#ifdef TRACE_CODE
	static char *get_arg(int, int);
#endif 

#ifdef DEBUG
	int stack_in_use_as_temporary = 0;
#endif 

int inter_sscanf(svalue_t *, svalue_t *, svalue_t *, int);
program_t *current_prog;
short int caller_type;
static int tracedepth;
int num_varargs;

/*
 * Inheritance:
 * An object X can inherit from another object Y. This is done with
 * the statement 'inherit "file";'
 * The inherit statement will clone a copy of that file, call reset
 * in it, and set a pointer to Y from X.
 * Y has to be removed from the linked list of all objects.
 * All variables declared by Y will be copied to X, so that X has access
 * to them.
 *
 * If Y isn't loaded when it is needed, X will be discarded, and Y will be
 * loaded separately. X will then be reloaded again.
 */

/*
 * These are the registers used at runtime.
 * The control stack saves registers to be restored when a fun
 * will return. That means that control_stack[0] will have almost no
 * interesting values, as it will terminate execution.
 */
char *pc; /* Program pointer. */
svalue_t *fp; /* Pointer to first argument. */

svalue_t *sp;

int function_index_offset; /* Needed for inheritance */
int variable_index_offset; /* Needed for inheritance */
int st_num_arg;

static svalue_t start_of_stack[CFG_EVALUATOR_STACK_SIZE];
svalue_t *end_of_stack = start_of_stack + CFG_EVALUATOR_STACK_SIZE - 5;

/* Used to throw an error to a catch */
svalue_t catch_value = 
{
	T_NUMBER, 0, 
	{
		0
	}
};

/* used by routines that want to return a pointer to an svalue */
svalue_t apply_ret_value = 
{
	T_NUMBER, 0, 
	{
		0
	}
};

control_stack_t control_stack[CFG_MAX_CALL_DEPTH];
control_stack_t *csp; /* Points to last element pushed */

int too_deep_error = 0, max_eval_error = 0;
#define STACK_CHECK if (++sp >= end_of_stack) do { \
too_deep_error = 1; error("QTZ_SE:stack overflow\n"); } \
while (0)

void get_version(char *buff)
{
	sprintf(buff, "QTZ_SE %s", "ver 0.01");
}

/*
 * Information about assignments of values:
 *
 * There are three types of l-values: Local variables, global variables
 * and array elements.
 *
 * The local variables are allocated on the stack together with the arguments.
 * the register 'frame_pointer' points to the first argument.
 *
 * The global variables must keep their values between executions, and
 * have space allocated at the creation of the object.
 *
 * Elements in arrays are similar to global variables. There is a reference
 * count to the whole array, that states when to deallocate the array.
 * The elements consists of 'svalue_t's, and will thus have to be freed
 * immediately when over written.
 */

/*
 * Push an object pointer on the stack. Note that the reference count is
 * incremented.
 * A destructed object must never be pushed onto the stack.
 */
void push_object(object_t *ob)
{
	STACK_CHECK;
	sp->type = T_OBJECT;
	sp->u.ob = ob;
	add_ref(ob, "push_object");
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

char *type_name(int c)
{
	int j = 0;
	int limit = TYPE_CODES_START;

	do {
		if (c &limit) {
			return type_names[j];
		}
		j++;
	}while (!( (limit <<= 1) &TYPE_CODES_END) );
	/* Oh crap.  Take some time and figure out what we have. */
	switch (c) {
		case T_INVALID:
			return "*invalid*";
		case T_LVALUE:
			return "*lvalue*";
		case T_LVALUE_BYTE:
			return "*lvalue_byte*";
		case T_LVALUE_RANGE:
			return "*lvalue_range*";
		case T_ERROR_HANDLER:
			return "*error_handler*";
		IF_DEBUG(case T_FREED:
			return "*freed*");
	}
	return "*unknown*";
}

/*
 * May current_object shadow object 'ob' ? We rely heavily on the fact that
 * fun names are pointers to shared strings, which means that equality
 * can be tested simply through pointer comparison.
 */
static program_t *ffbn_recurse(program_t *, char *, int *, int*);
static program_t *ffbn_recurse2(program_t *, char *, int *, int *, int*);

/*
 * Push a number on the value stack.
 */
void push_number(int n)
{
	STACK_CHECK;
	sp->type = T_NUMBER;
	sp->subtype = 0;
	sp->u.number = n;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

void push_real(double n)
{
	STACK_CHECK;
	sp->type = T_REAL;
	sp->u.real = n;
}

/*
 * Push undefined (const0u) onto the value stack.
 */
void push_undefined()
{
	STACK_CHECK;
	*sp = const0u;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

void push_undefineds(int num)
{
	if (sp + num >= end_of_stack) {
		too_deep_error = 1;
		error("stack overflow\n");
	}
	
	while (num--) {
		 *++sp = const0u;
	}
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

void copy_and_push_string(char *p)
{
	STACK_CHECK;
	sp->type = T_STRING;
	sp->subtype = STRING_MALLOC;
	sp->u.string = string_copy(p, "copy_and_push_string");
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

void share_and_push_string(char *p)
{
	STACK_CHECK;
	sp->type = T_STRING;
	sp->subtype = STRING_SHARED;
	sp->u.string = make_shared_string(p);
}

/*
 * Get address to a valid global variable.
 */
#ifdef DEBUG
INLINE_STATIC svalue_t *find_value(int num)
	{
		DEBUG_CHECK2(num >= (int)current_object->prog->num_variables_total, "QTZ_SE:Illegal variable access %d(%d).\n", num, current_object->prog->num_variables_total);
		return  &current_object->variables[num];
	}
#else 
	#define find_value(num) (&current_object->variables[num])
#endif 

void free_string_svalue(svalue_t *v)
{
	char *str = v->u.string;

	if (v->subtype &STRING_COUNTED)
	{
		#ifdef STRING_STATS
			int size = MSTR_SIZE(str);
		#endif 
		if (DEC_COUNTED_REF(str) )
		{
			SUB_STRING(size);
			NDBG(BLOCK(str) );
			if (v->subtype &STRING_HASHED)
			{
				SUB_NEW_STRING(size, sizeof(block_t) );
				deallocate_string(str);
				CHECK_STRING_STATS;
			}
			else
			{
				SUB_NEW_STRING(size, sizeof(malloc_block_t) );
				FREE(MSTR_BLOCK(str) );
				CHECK_STRING_STATS;
			}
		}
		else
		{
			SUB_STRING(size);
			NDBG(BLOCK(str) );
		}
	}
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

void unlink_string_svalue(svalue_t *s)
{
	char *str;

	switch (s->subtype)
	{
		case STRING_MALLOC:
			if (MSTR_REF(s->u.string) > 1)
			{
				s->u.string = string_unlink(s->u.string, "unlink_string_svalue");
			}
			break;
		case STRING_SHARED:
			{
				size_t l = SHARED_STRLEN(s->u.string);

				str = new_string(l, "unlink_string_svalue");
				strncpy(str, s->u.string, l + 1);
				free_string(s->u.string);
				s->subtype = STRING_MALLOC;
				s->u.string = str;
				break;
			}
		case STRING_CONSTANT:
			s->u.string = string_copy(sp->u.string, "unlink_string_svalue");
			s->subtype = STRING_MALLOC;
			break;
	}
}

/*
 * Free the data that an svalue is pointing to. Not the svalue
 * itself.
 * Use the free_svalue() define to call this
 */
#ifdef DEBUG
	inline void int_free_svalue(svalue_t *v, char *tag)
#else 
	INLINE void int_free_svalue(svalue_t *v)
#endif 
{

	if (v->type == T_STRING)
	{
		char *str = v->u.string;

		if (v->subtype &STRING_COUNTED)
		{
			#ifdef STRING_STATS
				int size = MSTR_SIZE(str);
			#endif 
			if (DEC_COUNTED_REF(str) )
			{
				SUB_STRING(size);
				NDBG(BLOCK(str) );
				if (v->subtype &STRING_HASHED)
				{
					SUB_NEW_STRING(size, sizeof(block_t) );
					deallocate_string(str);
					CHECK_STRING_STATS;
				}
				else
				{
					SUB_NEW_STRING(size, sizeof(malloc_block_t) );
					FREE(MSTR_BLOCK(str) );
					CHECK_STRING_STATS;
				}
			}
			else
			{
				SUB_STRING(size);
				NDBG(BLOCK(str) );
			}
		}
	}
	else if (v->type &T_REFED)
	{
		if (!(--v->u.refed->ref) )
		{
			switch (v->type)
			{
			case T_OBJECT:
				dealloc_object(v->u.ob, "free_svalue");
				break;
			case T_CLASS:
				dealloc_class(v->u.arr);
				break;
			case T_ARRAY:
				dealloc_array(v->u.arr);
				break;
			case T_BUFFER:
				if (v->u.buf !=  &null_buf)
				{
					FREE( (char*)v->u.buf);
				}
				break;
			case T_MAPPING:
				dealloc_mapping(v->u.map);
				break;
			case T_FUNCTION:
				dealloc_funp(v->u.fp);
				break;
			}
		}
	}
	else if (v->type == T_ERROR_HANDLER)
	{
		(*v->u.error_handler) ();
	}
	#ifdef DEBUG
		else if (v->type == T_FREED)
		{
			fatal("QTZ_SE:T_FREED svalue freed.  Previously freed by %s.\n", v->u.string);
		}
		v->type = T_FREED;
		v->u.string = tag;
	#endif 
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

void process_efun_callback(int narg, function_to_call_t *ftc, int f)
{
	svalue_t *arg = sp - st_num_arg + 1+narg;

	if (arg->type == T_FUNCTION)
	{
		ftc->f.fp = arg->u.fp;
		ftc->ob = 0;
		ftc->narg = st_num_arg - narg - 1;
		ftc->args = arg + 1;
	}
	else
	{
		ftc->f.str = arg->u.string;
		if (st_num_arg < narg + 2)
		{
			ftc->ob = current_object;
			ftc->narg = 0;
		}
		else
		{
			if ( (arg + 1)->type == T_OBJECT)
			{
				ftc->ob = (arg + 1)->u.ob;
			}
			else
			if ( (arg + 1)->type == T_STRING)
			{
				if (!(ftc->ob = find_object( (arg + 1)->u.string) ) || !object_visible(ftc->ob) )
				{
					bad_argument(arg + 1, T_STRING | T_OBJECT, 3, f);
				}
			} else {
				bad_argument(arg + 1, T_STRING | T_OBJECT, 3, f);
			}

			ftc->narg = st_num_arg - narg - 2;
			ftc->args = arg + 2;

			if (ftc->ob->flags &O_DESTRUCTED) {
				bad_argument(arg + 1, T_STRING | T_OBJECT, 3, f);
			}
		}
	}
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

svalue_t *call_efun_callback(function_to_call_t *ftc, int n)
{
	svalue_t *v;

	if (ftc->narg) {
		push_some_svalues(ftc->args, ftc->narg);
	}
	if (ftc->ob) {
		if (ftc->ob->flags &O_DESTRUCTED) {
			error("QTZ_SE:Object destructed during efun callback.\n");
		}
		v = apply(ftc->f.str, ftc->ob, n + ftc->narg, ORIGIN_EFUN);
	} else {
		v = call_function_pointer(ftc->f.fp, n + ftc->narg);
	}
	return v;
}

/*
 * Free several svalues, and free up the space used by the svalues.
 * The svalues must be sequentially located.
 */
INLINE void free_some_svalues(svalue_t *v, int num)
{
	while (num--) {
		free_svalue(v + num, "free_some_svalues");
	}
	FREE(v);
}

/*
 * Prepend a slash in front of a string.
 */
char *add_slash(char *str)
{
	char *tmp;

	tmp = new_string(strlen(str) + 1, "add_slash");
	*tmp = '/';
	strcpy(tmp + 1, str);
	return tmp;
}

/*
 * Assign to a svalue.
 * This is done either when element in array, or when to an identifier
 * (as all identifiers are kept in a array pointed to by the object).
 */

INLINE void assign_svalue_no_free(svalue_t *to, svalue_t *from)
{
	DEBUG_CHECK(from == 0, "Attempt to assign_svalue() from a null ptr.\n");
	DEBUG_CHECK(to == 0, "Attempt to assign_svalue() to a null ptr.\n");
	*to =  *from;

	if (from->type == T_STRING) {
		if (from->subtype &STRING_COUNTED) {
			INC_COUNTED_REF(to->u.string);
			ADD_STRING(MSTR_SIZE(to->u.string) );
			NDBG(BLOCK(to->u.string) );
		}
	} else if (from->type &T_REFED) {
		from->u.refed->ref++;
	}
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

INLINE void assign_svalue(svalue_t *dest, svalue_t *v)
{
	/* First deallocate the previous value. */
	free_svalue(dest, "assign_svalue");
	assign_svalue_no_free(dest, v);
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

INLINE void push_some_svalues(svalue_t *v, int num)
{
	if (sp + num >= end_of_stack) {
		too_deep_error = 1;
		error("QTZ_SE:stack overflow\n");
	}
	
	while (num--) {
		push_svalue(v++);
	}
}

/*
 * Copies an array of svalues to another location, which should be
 * free space.
 */
INLINE void copy_some_svalues(svalue_t *dest, svalue_t *v, int num)
{
	while (num--) {
		assign_svalue_no_free(dest + num, v + num);
	}
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

void transfer_push_some_svalues(svalue_t *v, int num)
{
	if (sp + num >= end_of_stack) {
		too_deep_error = 1;
		error("stack overflow\n");
	}
	memcpy(sp + 1, v, num *sizeof(svalue_t) );
	sp += num;
}

/*
 * Pop the top-most value of the stack.
 * Don't do this if it is a value that will be used afterwards, as the
 * data may be sent to FREE(), and destroyed.
 */
INLINE void pop_stack()
{
	DEBUG_CHECK(sp < start_of_stack, "Stack underflow.\n");
	free_svalue(sp--, "pop_stack");
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

svalue_t global_lvalue_byte = 
{
	T_LVALUE_BYTE, 0, 
	{
		0
	}
};

/*
 * Compute the address of an array element.
 */
INLINE void push_indexed_lvalue(int code)
{
	int ind;
	svalue_t *lv;

	if (sp->type == T_LVALUE)
	{
		lv = sp->u.lvalue;
		if (!code && lv->type == T_MAPPING)
		{
			sp--;
			if (!(lv = find_for_insert(lv->u.map, sp, 0) ) )
			{
				mapping_too_large();
			}
			free_svalue(sp, "push_indexed_lvalue: 1");
			sp->type = T_LVALUE;
			sp->u.lvalue = lv;
			return ;
		}

		if (!( (--sp)->type == T_NUMBER) )
		{
			error("QTZ_SE:Illegal type of index\n");
		}

		ind = sp->u.number;

		switch (lv->type)
		{
			case T_STRING:
				{
					size_t len = SVALUE_STRLEN(lv);

					if (code)
					{
						ind = len - ind;
					}
					if (ind >= (int)len || ind < 0)
					{
						error("QTZ_SE:Index out of bounds in string index lvalue.\n");
					}
					unlink_string_svalue(lv);
					sp->type = T_LVALUE;
					sp->u.lvalue = &global_lvalue_byte;
					global_lvalue_byte.subtype = 0;
					global_lvalue_byte.u.lvalue_byte = (unsigned char*) &lv->u.string[ind];
					break;
				}

			case T_BUFFER:
				{
					if (code)
					{
						ind = lv->u.buf->size - ind;
					}
					if (ind >= (int)lv->u.buf->size || ind < 0)
					{
						error("Buffer index out of bounds.\n");
					}
					sp->type = T_LVALUE;
					sp->u.lvalue = &global_lvalue_byte;
					global_lvalue_byte.subtype = 1;
					global_lvalue_byte.u.lvalue_byte = &lv->u.buf->item[ind];
					break;
				}

			case T_ARRAY:
				{
					if (code)
					{
						ind = lv->u.arr->size - ind;
					}
					if (ind >= lv->u.arr->size || ind < 0)
					{
						error("QTZ_SE:Array index out of bounds\n");
					}
					set_dirty_arr(lv->u.arr, ind, DIRTY_SET);
					sp->type = T_LVALUE;
					sp->u.lvalue = lv->u.arr->item + ind;
					break;
				}
			case T_CLASS:
				{
					if (code)
					{
						ind = lv->u.arr->size - ind;
					}
					if (ind >= lv->u.arr->size || ind < 0)
					{
						error("QTZ_SE:Class index out of bounds\n");
					}
					sp->type = T_LVALUE;
					sp->u.lvalue = lv->u.arr->item + ind;
					break;
				}
			default:
				if (lv->type == T_NUMBER && !lv->u.number)
				{
					error("QTZ_SE:Value being indexed is zero.\n");
				}
				error("QTZ_SE:Cannot index value of type '%s'.\n", type_name(lv->type) );
		}
	}
	else
	{
		/* It is now coming from (x <assign_type> y)[index]... = rhs */
		/* Where x is a _valid_ lvalue */
		/* Hence the reference to sp is at least 2 :) */

		if (!code && (sp->type == T_MAPPING) )
		{
			if (!(lv = find_for_insert(sp->u.map, sp - 1, 0) ) )
			{
				mapping_too_large();
			}
			sp->u.map->ref--;
			free_svalue(--sp, "push_indexed_lvalue: 2");
			sp->type = T_LVALUE;
			sp->u.lvalue = lv;
			return ;
		}

		if (!( (sp - 1)->type == T_NUMBER) )
		{
			error("QTZ_SE:Illegal type of index\n");
		}

		ind = (sp - 1)->u.number;

		switch (sp->type)
		{
			case T_STRING:
				{
					error("QTZ_SE:Illegal to make char lvalue from assigned string\n");
					break;
				}

			case T_BUFFER:
				{
					if (code)
					{
						ind = sp->u.buf->size - ind;
					}
					if (ind >= (int)sp->u.buf->size || ind < 0)
					{
						error("QTZ_SE:Buffer index out of bounds.\n");
					}
					sp->u.buf->ref--;
					(--sp)->type = T_LVALUE;
					sp->u.lvalue = &global_lvalue_byte;
					global_lvalue_byte.subtype = 1;
					global_lvalue_byte.u.lvalue_byte = (sp + 1)->u.buf->item + ind;
					break;
				}

			case T_ARRAY:
				{
					if (code)
					{
						ind = sp->u.arr->size - ind;
					}
					if (ind >= sp->u.arr->size || ind < 0)
					{
						error("QTZ_SE:Array index out of bounds.\n");
					}
					sp->u.arr->ref--;
					(--sp)->type = T_LVALUE;
					sp->u.lvalue = (sp + 1)->u.arr->item + ind;
					break;
				}

			default:
				if (sp->type == T_NUMBER && !sp->u.number)
				{
					error("QTZ_SE:Value being indexed is zero.\n");
				}
				error("QTZ_SE:Cannot index value of type '%s'.\n", type_name(sp->type) );
		}
	}
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

static struct lvalue_range
{
	int ind1, ind2, size;
	svalue_t *owner;
} global_lvalue_range;

static svalue_t global_lvalue_range_sv = 
{
	T_LVALUE_RANGE, 0, 
	{
		0
	}
};

INLINE void push_lvalue_range(int code)
{
	int ind1, ind2;
	int size = 0;
	svalue_t *lv;

	if (sp->type == T_LVALUE)
	{
		switch ( (lv = global_lvalue_range.owner = sp->u.lvalue)->type)
		{
			case T_ARRAY:
				size = lv->u.arr->size;
				break;
			case T_STRING:
				{
					size = SVALUE_STRLEN(lv);
					unlink_string_svalue(lv);
					break;
				}
			case T_BUFFER:
				size = lv->u.buf->size;
				break;
			default:
				error("QTZ_SE:Range lvalue on illegal type\n");
				IF_DEBUG(size = 0);
		}
	}
	else
	{
		error("QTZ_SE:Range lvalue on illegal type\n");
	}

	if (!( (--sp)->type == T_NUMBER) )
	{
		error("QTZ_SE:Illegal 2nd index type to range lvalue\n");
	}

	ind2 = (code &0x01) ? (size - sp->u.number): sp->u.number;
	if (++ind2 < 0 || (ind2 > size) )
	{
		error("QTZ_SE:The 2nd index to range lvalue must be >= -1 and < sizeof(indexed value)\n");
	}

	if (!( (--sp)->type == T_NUMBER) )
	{
		error("QTZ_SE:Illegal 1st index type to range lvalue\n");
	}
	ind1 = (code &0x10) ? (size - sp->u.number): sp->u.number;

	if (ind1 < 0 || ind1 > size)
	{
		error("QTZ_SE:The 1st index to range lvalue must be >= 0 and <= sizeof(indexed value)\n");
	}

	global_lvalue_range.ind1 = ind1;
	global_lvalue_range.ind2 = ind2;
	global_lvalue_range.size = size;
	sp->type = T_LVALUE;
	sp->u.lvalue = &global_lvalue_range_sv;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

INLINE void copy_lvalue_range(svalue_t *from)
{
	int ind1, ind2, size, fsize;
	svalue_t *owner;

	ind1 = global_lvalue_range.ind1;
	ind2 = global_lvalue_range.ind2;
	size = global_lvalue_range.size;
	owner = global_lvalue_range.owner;

	switch (owner->type)
	{
		case T_ARRAY:
			{
				array_t *fv,  *dv;
				svalue_t *fptr,  *dptr;
				if (from->type != T_ARRAY)
				{
					error("QTZ_SE:Illegal rhs to array range lvalue\n");
				}

				fv = from->u.arr;
				fptr = fv->item;

				if ( (fsize = fv->size) == ind2 - ind1)
				{
					dptr = (owner->u.arr)->item + ind1;

					if (fv->ref == 1)
					{
						/* Transfer the svalues */
						while (fsize--)
						{
							free_svalue(dptr, "copy_lvalue_range : 1");
							*dptr++ =  *fptr++;
						}
						free_empty_array(fv);
					}
					else
					{
						while (fsize--)
						{
							assign_svalue(dptr++, fptr++);
						}
						fv->ref--;
					}
				}
				else
				{
					array_t *old_dv = owner->u.arr;
					svalue_t *old_dptr = old_dv->item;

					/* Need to reallocate the array */
					dv = allocate_empty_array(size - ind2 + ind1 + fsize);
					dptr = dv->item;

					/* ind1 can range from 0 to sizeof(old_dv) */
					while (ind1--)
					{
						assign_svalue_no_free(dptr++, old_dptr++);
					}

					if (fv->ref == 1)
					{
						while (fsize--)
						{
							 *dptr++ =  *fptr++;
						}
						free_empty_array(fv);
					}
					else
					{
						while (fsize--)
						{
							assign_svalue_no_free(dptr++, fptr++);
						}
						fv->ref--;
					}

					/* ind2 can range from 0 to sizeof(old_dv) */
					old_dptr = old_dv->item + ind2;
					size -= ind2;

					while (size--)
					{
						assign_svalue_no_free(dptr++, old_dptr++);
					}
					free_array(old_dv);

					owner->u.arr = dv;
				}
				break;
			}

		case T_STRING:
			{
				if (from->type != T_STRING)
				{
					error("QTZ_SE:Illegal rhs to string range lvalue.\n");
				}

				if ( (fsize = SVALUE_STRLEN(from) ) == ind2 - ind1)
				{
					/* since fsize >= 0, ind2 - ind1 <= strlen(orig string) */
					/* because both of them can only range from 0 to len */

					strncpy(owner->u.string + ind1, from->u.string, fsize);
				}
				else
				{
					char *tmp,  *dstr = owner->u.string;

					owner->u.string = tmp = new_string(size - ind2 + ind1 + fsize, "copy_lvalue_range");
					if (ind1 >= 1)
					{
						strncpy(tmp, dstr, ind1);
						tmp += ind1;
					}
					strcpy(tmp, from->u.string);
					tmp += fsize;

					size -= ind2;
					if (size >= 1)
					{
						strncpy(tmp, dstr + ind2, size);
						*(tmp + size) = 0;
					}
					FREE_MSTR(dstr);
				}
				free_string_svalue(from);
				break;
			}

		case T_BUFFER:
			{
				if (from->type != T_BUFFER)
				{
					error("QTZ_SE:Illegal rhs to buffer range lvalue.\n");
				}

				if ( (fsize = from->u.buf->size) == ind2 - ind1)
				{
					memcpy( (owner->u.buf)->item + ind1, from->u.buf->item, fsize);
				}
				else
				{
					buffer_t *b;
					unsigned char *old_item = (owner->u.buf)->item;
					unsigned char *new_item;

					b = allocate_buffer(size - ind2 + ind1 + fsize);
					new_item = b->item;
					if (ind1 >= 1)
					{
						memcpy(b->item, old_item, ind1);
						new_item += ind1;
					}
					memcpy(new_item, from->u.buf, fsize);
					new_item += fsize;

					if ( (size -= ind2) >= 1)
					{
						memcpy(new_item, old_item + ind2, size);
					}
					free_buffer(owner->u.buf);
					owner->u.buf = b;
				}
				free_buffer(from->u.buf);
				break;
			}
	}
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

INLINE void assign_lvalue_range(svalue_t *from)
{
	int ind1, ind2, size, fsize;
	svalue_t *owner;

	ind1 = global_lvalue_range.ind1;
	ind2 = global_lvalue_range.ind2;
	size = global_lvalue_range.size;
	owner = global_lvalue_range.owner;

	switch (owner->type)
	{
		case T_ARRAY:
			{
				array_t *fv,  *dv;
				svalue_t *fptr,  *dptr;
				if (from->type != T_ARRAY)
				{
					error("QTZ_SE:Illegal rhs to array range lvalue\n");
				}

				fv = from->u.arr;
				fptr = fv->item;

				if ( (fsize = fv->size) == ind2 - ind1)
				{
					dptr = (owner->u.arr)->item + ind1;
					while (fsize--)
					{
						assign_svalue(dptr++, fptr++);
					}
				}
				else
				{
					array_t *old_dv = owner->u.arr;
					svalue_t *old_dptr = old_dv->item;

					/* Need to reallocate the array */
					dv = allocate_empty_array(size - ind2 + ind1 + fsize);
					dptr = dv->item;

					/* ind1 can range from 0 to sizeof(old_dv) */
					while (ind1--)
					{
						assign_svalue_no_free(dptr++, old_dptr++);
					}

					while (fsize--)
					{
						assign_svalue_no_free(dptr++, fptr++);
					}

					/* ind2 can range from 0 to sizeof(old_dv) */
					old_dptr = old_dv->item + ind2;
					size -= ind2;

					while (size--)
					{
						assign_svalue_no_free(dptr++, old_dptr++);
					}
					free_array(old_dv);

					owner->u.arr = dv;
				}
				break;
			}

		case T_STRING:
			{
				if (from->type != T_STRING)
				{
					error("QTZ_SE:Illegal rhs to string range lvalue.\n");
				}

				if ( (fsize = SVALUE_STRLEN(from) ) == ind2 - ind1)
				{
					/* since fsize >= 0, ind2 - ind1 <= strlen(orig string) */
					/* because both of them can only range from 0 to len */

					strncpy(owner->u.string + ind1, from->u.string, fsize);
				}
				else
				{
					char *tmp,  *dstr = owner->u.string;

					owner->u.string = tmp = new_string(size - ind2 + ind1 + fsize, "assign_lvalue_range");
					if (ind1 >= 1)
					{
						strncpy(tmp, dstr, ind1);
						tmp += ind1;
					}
					strcpy(tmp, from->u.string);
					tmp += fsize;

					size -= ind2;
					if (size >= 1)
					{
						strncpy(tmp, dstr + ind2, size);
						*(tmp + size) = 0;
					}
					FREE_MSTR(dstr);
				}
				break;
			}

		case T_BUFFER:
			{
				if (from->type != T_BUFFER)
				{
					error("QTZ_SE:Illegal rhs to buffer range lvalue.\n");
				}

				if ( (fsize = from->u.buf->size) == ind2 - ind1)
				{
					memcpy( (owner->u.buf)->item + ind1, from->u.buf->item, fsize);
				}
				else
				{
					buffer_t *b;
					unsigned char *old_item = (owner->u.buf)->item;
					unsigned char *new_item;

					b = allocate_buffer(size - ind2 + ind1 + fsize);
					new_item = b->item;
					if (ind1 >= 1)
					{
						memcpy(b->item, old_item, ind1);
						new_item += ind1;
					}
					memcpy(new_item, from->u.buf, fsize);
					new_item += fsize;

					if ( (size -= ind2) >= 1)
					{
						memcpy(new_item, old_item + ind2, size);
					}
					free_buffer(owner->u.buf);
					owner->u.buf = b;
				}
				break;
			}
	}
}

/*
 * Deallocate 'n' values from the stack.
 */
INLINE void pop_n_elems(int n)
{
	DEBUG_CHECK1(n < 0, "pop_n_elems: %d elements.\n", n);
	while (n--)	{
		pop_stack();
	}
}

/*
 * Deallocate 2 values from the stack.
 */
INLINE void pop_2_elems()
{
	free_svalue(sp--, "pop_2_elems");
	DEBUG_CHECK(sp < start_of_stack, "Stack underflow.\n");
	free_svalue(sp--, "pop_2_elems");
}

/*
 * Deallocate 3 values from the stack.
 */
INLINE void pop_3_elems()
{
	free_svalue(sp--, "pop_3_elems");
	free_svalue(sp--, "pop_3_elems");
	DEBUG_CHECK(sp < start_of_stack, "Stack underflow.\n");
	free_svalue(sp--, "pop_3_elems");
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

void bad_arg(int arg, int instr)
{
	error("Bad argument %d to %s()\n", arg, get_f_name(instr) );
}

void bad_arg2(int arg, char *funcn)
{
	error("Bad argument %d to %s()\n", arg, funcn);
}


//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

void bad_argument(svalue_t *val, int type, int arg, int instr)
{
	outbuffer_t outbuf;
	int flag = 0;
	int j = TYPE_CODES_START;
	int k = 0;

	outbuf_zero(&outbuf);
	outbuf_addv(&outbuf, "QTZ_SE:Bad argument %d to %s%s\nExpected: ", arg, get_f_name(instr), (instr < BASE ? "" : "()") );

	do {
		if (type &j) {
			if (flag) {
				outbuf_add(&outbuf, " or ");
			} else {
				flag = 1;
			}
			outbuf_add(&outbuf, type_names[k]);
		}
		k++;
	} while (!( (j <<= 1) &TYPE_CODES_END) );

	outbuf_add(&outbuf, " Got: ");
	svalue_to_string(val, &outbuf, 0, 0, 0);
	outbuf_addv(&outbuf, " type: %s", type_name(val->type) );

	outbuf_add(&outbuf, ".\n");
	outbuf_fix(&outbuf);
	error_needs_free(outbuf.buffer);
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

INLINE void push_control_stack(int frkind)
{
	if (csp ==  &control_stack[CFG_MAX_CALL_DEPTH - 1])
	{
		too_deep_error = 1;
		error("QTZ_SE:Too deep recursion.\n");
	}
	csp++;
	csp->caller_type = caller_type;
	csp->ob = current_object;
	csp->framekind = frkind;
	csp->prev_ob = previous_ob;
	csp->fp = fp;
	csp->prog = current_prog;
	csp->pc = pc;
	csp->function_index_offset = function_index_offset;
	csp->variable_index_offset = variable_index_offset;
}

/*
 * Pop the control stack one element, and restore registers.
 * extern_call must not be modified here, as it is used imediately after pop.
 */
void pop_control_stack()
{
	DEBUG_CHECK(csp == (control_stack - 1), "QTZ_SE:Popped out of the control stack\n");
	#ifdef PROFILE_FUNCTIONS
		if ( (csp->framekind &FRAME_MASK) == FRAME_FUNCTION)
		{
			unsigned long secs, usecs, dsecs;
			compiler_function_t *cfp = &current_prog->function_table[csp->fr.table_index];

			get_cpu_times(&secs, &usecs);
			dsecs = ( (secs - csp->entry_secs) *1000000+usecs - csp->entry_usecs);
			cfp->self += dsecs;
			if (csp != control_stack)
			{
				if ( ( (csp - 1)->framekind &FRAME_MASK) == FRAME_FUNCTION)
				{
					csp->prog->function_table[(csp - 1)->fr.table_index].children += dsecs;
				}
			}
		}
	#endif 
	current_object = csp->ob;
	current_prog = csp->prog;
	previous_ob = csp->prev_ob;
	caller_type = csp->caller_type;
	pc = csp->pc;
	fp = csp->fp;
	function_index_offset = csp->function_index_offset;
	variable_index_offset = csp->variable_index_offset;
	csp--;
}

/*
 * Push a pointer to a array on the stack. Note that the reference count
 * is incremented. Newly created arrays normally have a reference count
 * initialized to 1.
 */
void push_array(array_t *v)
{
	v->ref++;
	sp++;
	sp->type = T_ARRAY;
	sp->u.arr = v;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

void push_refed_array(array_t *v)
{
	sp++;
	sp->type = T_ARRAY;
	sp->u.arr = v;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

void push_buffer(buffer_t *b)
{
	b->ref++;
	sp++;
	sp->type = T_BUFFER;
	sp->u.buf = b;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

void push_refed_buffer(buffer_t *b)
{
	sp++;
	sp->type = T_BUFFER;
	sp->u.buf = b;
}

/*
 * Push a mapping on the stack.  See push_array(), above.
 */
void push_mapping(mapping_t *m)
{
	m->ref++;
	sp++;
	sp->type = T_MAPPING;
	sp->u.map = m;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

void push_refed_mapping(mapping_t *m)
{
	sp++;
	sp->type = T_MAPPING;
	sp->u.map = m;
}

/*
 * Push a class on the stack.  See push_array(), above.
 */
INLINE void push_class(array_t *v)
{
	v->ref++;
	sp++;
	sp->type = T_CLASS;
	sp->u.arr = v;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

INLINE void push_refed_class(array_t *v, unsigned char idx)
{
	sp++;
	sp->type = T_CLASS;
	sp->subtype = idx;
	sp->u.arr = v;
}

/*
 * Push a string on the stack that is already malloced.
 */
void push_malloced_string(char *p)
{
	sp++;
	sp->type = T_STRING;
	sp->u.string = p;
	sp->subtype = STRING_MALLOC;
}

/*
 * Pushes a known shared string.  Note that this references, while
 * push_malloced_string doesn't.
 */
INLINE void push_shared_string(char *p)
{
	sp++;
	sp->type = T_STRING;
	sp->u.string = p;
	sp->subtype = STRING_SHARED;
	ref_string(p);
}

/*
 * Push a string on the stack that is already constant.
 */
void push_constant_string(const char *p)
{
	STACK_CHECK;
	sp->type = T_STRING;
	sp->subtype = STRING_CONSTANT;
	sp->u.string = (char *)p;
}


/*
 * Argument is the fun to execute. If it is defined by inheritance,
 * then search for the real definition, and return it.
 * There is a number of arguments on the stack. Normalize them and initialize
 * local variables, so that the called fun is pleased.
 */
INLINE void setup_variables(int actual, int local, int num_arg)
{
	int tmp;

	if ( (tmp = actual - num_arg) > 0) {
		/* Remove excessive arguments */
		pop_n_elems(tmp);
		push_undefineds(local);
	} else {
		/* Correct number of arguments and local variables */
		push_undefineds(local - tmp);
	}
	fp = sp - (csp->num_local_variables = local + num_arg) + 1;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

INLINE void setup_varargs_variables(int actual, int local, int num_arg)
{
	array_t *arr;
	if (actual >= num_arg)
	{
		int n = actual - num_arg + 1;
		/* Aggregate excessive arguments */
		arr = allocate_empty_array(n);
		while (n--)
		{
			arr->item[n] =  *sp--;
		}
	}
	else
	{
		/* Correct number of arguments and local variables */
		push_undefineds(num_arg - 1-actual);
		arr = &the_null_array;
	}
	push_refed_array(arr);
	push_undefineds(local);
	fp = sp - (csp->num_local_variables = local + num_arg) + 1;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

INLINE compiler_function_t *setup_new_frame(int index)
{
	runtime_function_u *func_entry = FIND_FUNC_ENTRY(current_prog, index);
	int findex;

	function_index_offset = variable_index_offset = 0;

	while (current_prog->function_flags[index] &NAME_INHERITED) {
		int offset = func_entry->inh.offset;
		function_index_offset += current_prog->inherit[offset].function_index_offset;
		variable_index_offset += current_prog->inherit[offset].variable_index_offset;
		current_prog = current_prog->inherit[offset].prog;
		index = func_entry->inh.function_index_offset;
		func_entry = FIND_FUNC_ENTRY(current_prog, index);
	}

	findex = func_entry->def.f_index;
	csp->fr.table_index = findex;
#ifdef PROFILE_FUNCTIONS
	get_cpu_times(&(csp->entry_secs), &(csp->entry_usecs) );
	current_prog->function_table[findex].calls++;
#endif 

	/* Remove excessive arguments */
	if (current_prog->function_flags[index] &NAME_TRUE_VARARGS) {
		setup_varargs_variables(csp->num_local_variables, func_entry->def.num_local, func_entry->def.num_arg);
	} else {
		setup_variables(csp->num_local_variables, func_entry->def.num_local, func_entry->def.num_arg);
	}
	return  &current_prog->function_table[findex];
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

INLINE compiler_function_t *setup_inherited_frame(int index)
{
	runtime_function_u *func_entry = FIND_FUNC_ENTRY(current_prog, index);
	int findex;

	while (current_prog->function_flags[index] &NAME_INHERITED)
	{
		int offset = func_entry->inh.offset;
		function_index_offset += current_prog->inherit[offset].function_index_offset;
		variable_index_offset += current_prog->inherit[offset].variable_index_offset;
		current_prog = current_prog->inherit[offset].prog;
		index = func_entry->inh.function_index_offset;
		func_entry = FIND_FUNC_ENTRY(current_prog, index);
	}

	findex = func_entry->def.f_index;
	csp->fr.table_index = findex;
	#ifdef PROFILE_FUNCTIONS
		get_cpu_times(&(csp->entry_secs), &(csp->entry_usecs) );
		current_prog->function_table[findex].calls++;
	#endif 

	/* Remove excessive arguments */
	if (current_prog->function_flags[index] &NAME_TRUE_VARARGS)
	{
		setup_varargs_variables(csp->num_local_variables, func_entry->def.num_local, func_entry->def.num_arg);
	}
	else
	{
		setup_variables(csp->num_local_variables, func_entry->def.num_local, func_entry->def.num_arg);
	}
	return  &current_prog->function_table[findex];
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

#ifdef DEBUG
	/* This fun is called at the end of every complete LPC statement, so
	 * it is a good place to insert debugging code to find out where during
	 * LPC code certain assertions fail, etc
	 */
	void break_point()
	{
		/* The current implementation of foreach leaves some stuff lying on the
		stack */
		if (!stack_in_use_as_temporary && sp - fp - csp->num_local_variables + 1 != 0)
		{
			fatal("QTZ_SE:Bad stack pointer.\n");
		}
	}
#endif 

program_t fake_prog = 
{
	"<fun>",  // char *name;
	0,  // int flags;
	0,  // unsigned short ref 
	0,  // unsigned short func_ref
	#ifdef DEBUG
		0,  // int extra_ref;              /* Used to verify ref count */ 
		0,  // int extra_func_ref;
	#endif 
	0,  // char *program;              /* The binary instructions */   
	0,  // int id_number;              
	0,  // unsigned char *line_info;   /* Line number information */ 
	0,  // unsigned short *file_info; 
	0,  // int line_swap_index;        /* Where line number info is swapped */
	0,  // compiler_function_t *function_table;
	0,  // unsigned short *function_flags; /* separate for alignment reasons */
	0,  // runtime_function_u *function_offsets; 
	#ifdef COMPRESS_FUNCTION_TABLES
		0,  // compressed_offset_table_t *function_compressed;
	#endif 
	0,  // class_def_t *classes;
	0,  // class_member_entry_t *class_members;
	0,  // char **strings;             /* All strings uses by the program */
	0,  // char **variable_table;      /* variables defined by this program */
	0,  // unsigned short *variable_types;     /* variables defined by this program */
	0,  // inherit_t *inherit; /* List of inherited prgms */
	0,  // int total_size;             /* Sum of all data in this struct */
	0,  // int heart_beat;             
	0,  // unsigned short *argument_types;
	0,  // unsigned short *type_start; 
	0,  // unsigned short program_size;/* size of this instruction code */
	0,  // unsigned short num_classes;
	0,  // unsigned short num_functions_total;
	0,  // unsigned short num_functions_defined;
	0,  // unsigned short num_strings; 
	0,  // unsigned short num_variables_total;
	0,  // unsigned short num_variables_defined;
	0  // unsigned short num_inherited;  
};
unsigned char fake_program = F_RETURN;

/*
 * Very similar to push_control_stack() [which see].  The purpose of this is
 * to insert an frame containing the object which defined a fun pointer
 * in cases where it would otherwise not be on the call stack.  This
 * preserves the idea that fun pointers calls happen 'through' the
 * object that define the fun pointer.
 * These frames are the ones that show up as <fun> in error traces.
 */
void setup_fake_frame(funptr_t *fun)
{
	if (csp ==  &control_stack[CFG_MAX_CALL_DEPTH - 1])
	{
		too_deep_error = 1;
		error("QTZ_SE:Too deep recursion.\n");
	}
	csp++;
	csp->caller_type = caller_type;
	csp->framekind = FRAME_FAKE | FRAME_OB_CHANGE;
	csp->fr.funp = fun;
	csp->ob = current_object;
	csp->prev_ob = previous_ob;
	csp->fp = fp;
	csp->prog = current_prog;
	csp->pc = pc;
	pc = (char*) &fake_program;
	csp->function_index_offset = function_index_offset;
	csp->variable_index_offset = variable_index_offset;
	caller_type = ORIGIN_FUNCTION_POINTER;
	csp->num_local_variables = 0;
	current_prog = &fake_prog;
	previous_ob = current_object;
	current_object = fun->hdr.owner;
}

/* Remove a fake frame added by setup_fake_frame().  Basically just a
 * specialized version of pop_control_stack().
 */
void remove_fake_frame()
{
	DEBUG_CHECK(csp == (control_stack - 1), "Popped out of the control stack\n");
	current_object = csp->ob;
	current_prog = csp->prog;
	previous_ob = csp->prev_ob;
	caller_type = csp->caller_type;
	pc = csp->pc;
	fp = csp->fp;
	function_index_offset = csp->function_index_offset;
	variable_index_offset = csp->variable_index_offset;
	csp--;
}

/* num_arg args are on the stack, and the args from the array vec should be
 * put in front of them.  This is so that the order of arguments is logical.
 *
 * evaluate( (: f, a :), b) -> f(a,b) and not f(b, a) which would happen
 * if we simply pushed the args from vec at this point.  (Note that the
 * old fun pointers are broken in this regard)
 */
int merge_arg_lists(int num_arg, array_t *arr, int start)
{
	int num_arr_arg = arr->size - start;
	svalue_t *sptr;

	if (num_arr_arg) {
		sptr = (sp += num_arr_arg);
		if (num_arg) {
			/* We need to do some stack movement so that the order
			of arguments is logical */
			while (num_arg--) {
				*sptr = *(sptr - num_arr_arg);
				sptr--;
			}
		}
		num_arg = arr->size;
		while (--num_arg >= start) {
			assign_svalue_no_free(sptr--, &arr->item[num_arg]);
		}
		/* could just return num_arr_arg if num_arg is 0 but .... -Sym */
		return (sp - sptr);
	}
	return num_arg;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

void cfp_error(char *s)
{
	remove_fake_frame();
	error(s);
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

int check_function_currying(funptr_t *funp, int num_arg)
{
	switch (funp->hdr.type) {
	case FP_SIMUL:
		return 0;
	case FP_EFUN:
		return 0;
	case FP_LOCAL | FP_NOT_BINDABLE: {
		if (current_object->prog->function_flags[funp->f.local.index] &NAME_UNDEFINED) {
			error("QTZ_SE:Undefined fun: %s\n", function_name(current_object->prog, funp->f.local.index) );
		}

		int index = funp->f.local.index;
		// find runtime_function_u
		program_t *prog = funp->hdr.owner->prog;
		runtime_function_u *func_entry = FIND_FUNC_ENTRY(current_prog, index);
		while (current_prog->function_flags[index] &NAME_INHERITED) {
			int offset = func_entry->inh.offset;
			prog = prog->inherit[offset].prog;
			index = func_entry->inh.function_index_offset;
			func_entry = FIND_FUNC_ENTRY(prog, index);
		}
		return 0;

		int arg_remain = func_entry->def.num_arg - num_arg - (funp->hdr.args ? funp->hdr.args->size :0);
		return arg_remain < 0 ? 0 : arg_remain;
	}
	case FP_FUNCTIONAL:
	case FP_FUNCTIONAL | FP_NOT_BINDABLE: {
		int arg_remain = funp->f.functional.num_arg - num_arg - (funp->hdr.args ? funp->hdr.args->size :0);
		return arg_remain < 0 ? 0 : arg_remain;
	}
	default:
		error("QTZ_SE:Unsupported fun pointer type.\n");
	}

	return 0;
}

svalue_t *call_function_pointer(funptr_t *funp, int num_arg)
{
	static func_t *oefun_table = efun_table - BASE;
	if (funp->hdr.owner->flags &O_DESTRUCTED) {
		error("QTZ_SE:Owner (/%s) of fun pointer is destructed.\n", funp->hdr.owner->name);
	}
	/*
	int arg_remain = check_function_currying(funp, num_arg);
	if (arg_remain) {
		printf("function currying %d remain %d\n", num_arg, arg_remain);
		funptr_t *funp = make_functional_currying(funp, num_arg);
		// create the new arg and return
		free_svalue(&apply_ret_value, "call_function_pointer");
		apply_ret_value.type = T_FUNCTION;
		apply_ret_value.u.fp = fp;
		return  &apply_ret_value;
	}
	*/
	setup_fake_frame(funp);
#ifdef _USE_SWAP_H_
	if (current_object->flags &O_SWAPPED) {
		load_ob_from_swap(current_object);
	}
#endif

	switch (funp->hdr.type) {
	case FP_SIMUL:
		if (funp->hdr.args) {
			check_for_destr(funp->hdr.args);
			num_arg = merge_arg_lists(num_arg, funp->hdr.args, 0);
		}
		call_simul_efun(funp->f.simul.index, num_arg);
		break;
	case FP_EFUN: {
		int i, def;

		fp = sp - num_arg + 1;
		if (funp->hdr.args) {
			check_for_destr(funp->hdr.args);
			num_arg = merge_arg_lists(num_arg, funp->hdr.args, 0);
		}
		i = funp->f.efun.index;
		if (num_arg == instrs[i].min_arg - 1 && ( (def = instrs[i].Default) != DEFAULT_NONE) ) {
			if (def == DEFAULT_THIS_OBJECT) {
				if (current_object && !(current_object->flags &O_DESTRUCTED)) {
					push_object(current_object);
				} else {
					*(++sp) = const0;
				}
			} else {
				(++sp)->type = T_NUMBER;
				sp->u.number = def;
			}
			num_arg++;
		} else {
			if (num_arg < instrs[i].min_arg) {
				error("QTZ_SE:Too few arguments to efun %s in efun pointer.\n", instrs[i].name);
			} else if (num_arg > instrs[i].max_arg && instrs[i].max_arg !=  - 1) {
				error("QTZ_SE:Too many arguments to efun %s in efun pointer.\n", instrs[i].name);
			}
		}

		/* possibly we should add TRACE, OPC, etc here;
		   also on eval_cost here, which is ok for just 1 efun */
		{
			int j, n = num_arg;
			st_num_arg = num_arg;

			if (n >= 4 || instrs[i].max_arg ==  - 1) {
				n = instrs[i].min_arg;
			}

			for (j = 0; j < n; j++) {
				CHECK_TYPES(sp - num_arg + j + 1, instrs[i].type[j], j + 1, i);
			}
			(*oefun_table[i]) ();

			free_svalue(&apply_ret_value, "call_function_pointer");
			if (instrs[i].ret_type == TYPE_NOVALUE) {
				apply_ret_value = const0;
			} else {
				apply_ret_value =  *sp--;
			}
			remove_fake_frame();
			return  &apply_ret_value;
		}
	}
	case FP_LOCAL | FP_NOT_BINDABLE: {
		compiler_function_t *func;
		fp = sp - num_arg + 1;

		if (current_object->prog->function_flags[funp->f.local.index] &NAME_UNDEFINED) {
			error("QTZ_SE:Undefined fun: %s\n", function_name(current_object->prog, funp->f.local.index) );
		}

		push_control_stack(FRAME_FUNCTION);
		current_prog = funp->hdr.owner->prog;

		caller_type = ORIGIN_LOCAL;

		/*
		  if (funp->hdr.args) {
		  array_t *v = funp->hdr.args;

		  check_for_destr(v);
		  num_arg = merge_arg_lists(num_arg, v, 0);
		  num_arg = merge_upvalue_lists(num_arg, v);
		  }
		*/
		//error("here");

		csp->num_local_variables = num_arg;
		func = setup_new_frame(funp->f.local.index);
		call_program(current_prog, func->address);
		break;
	}
	case FP_FUNCTIONAL:
	case FP_FUNCTIONAL | FP_NOT_BINDABLE: 
		{
			fp = sp - num_arg + 1;

			push_control_stack(FRAME_FUNP);
			current_prog = funp->f.functional.prog;
			csp->fr.funp = funp;

			caller_type = ORIGIN_FUNCTIONAL;

			/* this is use for upvalue now
			   if (funp->hdr.args)
			   {
			   array_t *v = funp->hdr.args;

			   check_for_destr(v);
			   //num_arg = merge_arg_lists(num_arg, v, 0);
			   num_arg = merge_upvalue_lists(num_arg, v);
			   }
			*/
			//error("here");
				
			setup_variables(num_arg, funp->f.functional.num_local, funp->f.functional.num_arg);
				
			function_index_offset = funp->f.functional.fio;
			variable_index_offset = funp->f.functional.vio;
			call_program(funp->f.functional.prog, funp->f.functional.offset);
			break;
		}
	default:
		error("QTZ_SE:Unsupported fun pointer type.\n");
	}
	free_svalue(&apply_ret_value, "call_function_pointer");
	apply_ret_value =  *sp--;
	remove_fake_frame();
	return  &apply_ret_value;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

svalue_t *safe_call_function_pointer(funptr_t *funp, int num_arg)
{
	error_context_t econ;
	svalue_t *ret;

	if (!save_context(&econ) )
	{
		return 0;
	}
	if (!SETJMP(econ.context) )
	{
		ret = call_function_pointer(funp, num_arg);
	}
	else
	{
		restore_context(&econ);
		/* condition was restored to where it was when we came in */
		pop_n_elems(num_arg);
		ret = 0;
	}
	pop_context(&econ);
	return ret;
}

/*
 * When a array is given as argument to an efun, all items have to be
 * checked if there would be a destructed object.
 * A bad problem currently is that a array can contain another array, so this
 * should be tested too. But, there is currently no prevention against
 * recursive arrays, which means that this can not be tested. Thus, QTZ_SE
 * may crash if a array contains a array that contains a destructed object
 * and this top-most array is used as an argument to an efun.
 */
/* MudOS won't crash when doing simple operations like assign_svalue
 * on a destructed object. You have to watch out, of course, that you don't
 * apply a fun to it.
 * to save space it is preferable that destructed objects are freed soon.
 *   amylaar
 */
void check_for_destr(array_t *v)
{
	int i = v->size;

	while (i--) {
		if ( (v->item[i].type == T_OBJECT) && (v->item[i].u.ob->flags &O_DESTRUCTED) ) {
			free_svalue(&v->item[i], "check_for_destr");
			v->item[i] = const0;
		}
	}
}

/* do_loop_cond() coded by John Garnett, 1993/06/01

Optimizes these four cases (with 'int i'):

1) for (expr0; i < integer_variable; expr2) statement;
2) for (expr0; i < integer_constant; expr2) statement;
3) while (i < integer_variable) statement;
4) while (i < integer_constant) statement;
 */

INLINE_STATIC void do_loop_cond_local()
{
	svalue_t *s1,  *s2;
	int i;

	s1 = fp + EXTRACT_UCHAR(pc++); /* a from (a < b) */
	s2 = fp + EXTRACT_UCHAR(pc++);
	switch (s1->type | s2->type)
	{
		case T_NUMBER:
			i = s1->u.number < s2->u.number;
			break;
		case T_REAL:
			i = s1->u.real < s2->u.real;
			break;
		case T_STRING:
			i = (strcmp(s1->u.string, s2->u.string) < 0);
			break;
			case T_NUMBER | T_REAL: if (s1->type == T_NUMBER)
			{
				i = s1->u.number < s2->u.real;
			}
			else
			{
				i = s1->u.real < s2->u.number;
			}
			break;
		default:
			if (s1->type == T_OBJECT && (s1->u.ob->flags &O_DESTRUCTED) )
			{
				free_object(s1->u.ob, "do_loop_cond:1");
				*s1 = const0;
			}
			if (s2->type == T_OBJECT && (s2->u.ob->flags &O_DESTRUCTED) )
			{
				free_object(s2->u.ob, "do_loop_cond:2");
				*s2 = const0;
			}
			if (s1->type == T_NUMBER && s2->type == T_NUMBER)
			{
				i = s1->u.number < s2->u.number;
				break;
			}
			switch (s1->type)
			{
			case T_NUMBER:
			case T_REAL:
				error("QTZ_SE:2nd argument to < is not numeric when the 1st is.\n");
			case T_STRING:
				error("QTZ_SE:2nd argument to < is not string when the 1st is.\n");
			default:
				error("QTZ_SE:Bad 1st argument to <.\n");
			}
			i = 0;
	}
	if (i)
	{
		unsigned short offset;

		COPY_SHORT(&offset, pc);
		pc -= offset;
	}
	else
	{
		pc += 2;
	}
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

INLINE_STATIC void do_loop_cond_number()
{
	svalue_t *s1;
	int i;

	s1 = fp + EXTRACT_UCHAR(pc++); /* a from (a < b) */
	LOAD_INT(i, pc);
	if (s1->type == T_NUMBER)
	{
		if (s1->u.number < i)
		{
			unsigned short offset;

			COPY_SHORT(&offset, pc);
			pc -= offset;
		}
		else
		{
			pc += 2;
		}
	}
	else if (s1->type == T_REAL)
	{
		if (s1->u.real < i)
		{
			unsigned short offset;

			COPY_SHORT(&offset, pc);
			pc -= offset;
		}
		else
		{
			pc += 2;
		}
	}
	else
	{
		error("QTZ_SE:Right side of < is a number, left side is not.\n");
	}
}

/*
 * Evaluate instructions at address 'p'. All program offsets are
 * to current_prog->program. 'current_prog' must be setup before
 * call of this fun.
 *
 * There must not be destructed objects on the stack. The destruct_object()
 * fun will automatically remove all occurences. The effect is that
 * all called efuns knows that they won't have destructed objects as
 * arguments.
 */
#ifdef TRACE_CODE
	static int previous_instruction[60];
	static int stack_size[60];
	static char *previous_pc[60];
	static int last;
#endif 

void eval_instruction(char *p)
{
	#ifdef DEBUG
		int num_arg;
	#endif 
	int i, n;
	float real;
	svalue_t *lval;
	int instruction;
	#if defined(TRACE_CODE) || defined(OPCPROF) || defined(OPCPROF_2D)
		int real_instruction;
	#endif 
	unsigned short offset;
	static func_t *oefun_table = efun_table - BASE + ONEARG_MAX;
	#ifndef DEBUG
		static func_t *ooefun_table = efun_table - BASE;
	#endif 
	static instr_t *instrs2 = instrs + ONEARG_MAX;

	IF_DEBUG(svalue_t *expected_stack);

	/* Next F_RETURN at this level will return out of eval_instruction() */
	csp->framekind |= FRAME_EXTERNAL;
	pc = p;
	while (1)
	{
		instruction = EXTRACT_UCHAR(pc++);
		#if defined(TRACE_CODE) || defined(OPCPROF) || defined(OPCPROF_2D)
			if (instruction >= F_EFUN0 && instruction <= F_EFUNV)
			{
				real_instruction = EXTRACT_UCHAR(pc) + ONEARG_MAX;
			}
			else
			{
				real_instruction = instruction;
			}
			#ifdef TRACE_CODE
				previous_instruction[last] = real_instruction;
				previous_pc[last] = pc - 1;
				stack_size[last] = sp - fp - csp->num_local_variables;
				last = (last + 1) % (sizeof previous_instruction / sizeof(int) );
			#endif 
			#ifdef OPCPROF
				if (real_instruction < BASE)
				{
					opc_eoper[real_instruction]++;
				}
				else
				{
					opc_efun[real_instruction - BASE].count++;
				}
			#endif 
			#ifdef OPCPROF_2D
				if (real_instruction < BASE)
				{
					if (last_eop)
					{
						opc_eoper_2d[last_eop][real_instruction]++;
					}
					last_eop = real_instruction;
				}
				else
				{
					if (last_eop)
					{
						opc_eoper_2d[last_eop][BASE]++;
					}
					last_eop = BASE;
				}
			#endif 
		#endif 
		if (!--eval_cost)
		{
			debug_message("object /%s: eval_cost too big %d\n", current_object->name, max_cost);
			eval_cost = max_cost;
			max_eval_error = 1;
			error("QTZ_SE:Too long evaluation. Execution aborted.\n");
		}
		/*
		 * Execute current instruction. Note that all functions callable from
		 * LPC must return a value. This does not apply to control
		 * instructions, like F_JUMP.
		 */
		switch (instruction) {
		case F_PUSH:
			/* Push a number of things onto the stack */
			n = EXTRACT_UCHAR(pc++);
			while (n--) {
				i = EXTRACT_UCHAR(pc++);
				switch (i &PUSH_WHAT) {
				case PUSH_STRING:
					DEBUG_CHECK1( (i &PUSH_MASK) >= current_prog->num_strings, "string %d out of range in F_STRING!\n", i &PUSH_MASK);
					push_shared_string(current_prog->strings[i &PUSH_MASK]);
					break;
				case PUSH_LOCAL:
					lval = fp + (i &PUSH_MASK);
					DEBUG_CHECK( (lval - fp) >= csp->num_local_variables, "Tried to push non-existent local\n");
					if ( (lval->type == T_OBJECT) && (lval->u.ob->flags &O_DESTRUCTED) ) {
						*++sp = const0;
						assign_svalue(lval, &const0);
					} else {
						push_svalue(lval);
					}
					
					//printf("%d, %d\n", lval - fp, csp->num_local_variables);
					//printf("PUSH_LOCAL:%d->%s\n", i&PUSH_MASK, string_print_formatted("%O", 1, lval));
					break;
				case PUSH_UPVALUE:{
					funptr_t *funp = csp->fr.funp;
					array_t *upvalues = funp->hdr.upvalues;
					int index = i&PUSH_MASK;
					DEBUG_CHECK(index >= upvalues->size, "upvalue out of bound\n");
					push_svalue(&upvalues->item[index]);
					//printf("push upvalue %d\n", (i & PUSH_MASK));
				}break;
				case PUSH_GLOBAL:
					lval = find_value( (int) ( (i &PUSH_MASK) + variable_index_offset) );
					if ( (lval->type == T_OBJECT) && (lval->u.ob->flags &O_DESTRUCTED) ) {
						*++sp = const0;
						assign_svalue(lval, &const0);
					} else {
						push_svalue(lval);
					}
					break;
				case PUSH_NUMBER:
					push_number(i &PUSH_MASK);
					break;
				}
			}
			break;
			case F_INC:
				DEBUG_CHECK(sp->type != T_LVALUE, "non-lvalue argument to ++\n");
				lval = (sp--)->u.lvalue;
				switch (lval->type)
				{
				case T_NUMBER:
					lval->u.number++;
					break;
				case T_REAL:
					lval->u.real++;
					break;
				case T_LVALUE_BYTE:
					if (global_lvalue_byte.subtype == 0 && *global_lvalue_byte.u.lvalue_byte == (unsigned char)255)
					{
						error("QTZ_SE:Strings cannot contain 0 bytes.\n");
					}
					++ *global_lvalue_byte.u.lvalue_byte;
					break;
				default:
					error("QTZ_SE:++ of non-numeric argument\n");
				}
				break;
			case F_WHILE_DEC:
				{
					svalue_t *s;

					s = fp + EXTRACT_UCHAR(pc++);
					if (s->type == T_NUMBER)
					{
						i = s->u.number--;
					}
					else if (s->type == T_REAL)
					{
						i = s->u.real--;
					}
					else
					{
						error("QTZ_SE:-- of non-numeric argument\n");
					}
					if (i)
					{
						COPY_SHORT(&offset, pc);
						pc -= offset;
					}
					else
					{
						pc += 2;
					}
				}
				break;
		case F_LOCAL_LVALUE:
			(++sp)->type = T_LVALUE;
			sp->u.lvalue = fp + EXTRACT_UCHAR(pc++);
			break;
		case F_UPVALUE_LVALUE: {
			(++sp)->type = T_LVALUE;
			funptr_t *funp = csp->fr.funp;
			array_t *upvalues = funp->hdr.upvalues;
			int index = EXTRACT_UCHAR(pc++);
			DEBUG_CHECK(index >= upvalues->size, "upvalue out of bound\n");
			//printf("assign upvalue %d\n", (i & PUSH_MASK));
			sp->u.lvalue = &(upvalues->item[index]);
			break;
		}
			case F_NUMBER:
				LOAD_INT(i, pc);
				push_number(i);
				break;
			case F_REAL:
				LOAD_FLOAT(real, pc);
				push_real(real);
				break;
			case F_BYTE:
				push_number(EXTRACT_UCHAR(pc++) );
				break;
			case F_NBYTE:
				push_number( - ( (int)EXTRACT_UCHAR(pc++) ) );
				break;
				#ifdef F_JUMP_WHEN_NON_ZERO
				case F_JUMP_WHEN_NON_ZERO:
					if ( (i = (sp->type == T_NUMBER) ) && (sp->u.number == 0) )
					{
						pc += 2;
					}
					else
					{
						COPY_SHORT(&offset, pc);
						pc = current_prog->program + offset;
					}
					if (i)
					{
						sp--; /* when sp is an integer svalue, its cheaper
						 * to do this */
					}
					else
					{
						pop_stack();
					}
					break;
				#endif 
			case F_BRANCH:
				 /* relative offset */
				COPY_SHORT(&offset, pc);
				pc += offset;
				break;
			case F_BBRANCH:
				 /* relative offset */
				COPY_SHORT(&offset, pc);
				pc -= offset;
				break;
			case F_BRANCH_NE:
				f_ne();
				if ( (sp--)->u.number)
				{
					COPY_SHORT(&offset, pc);
					pc += offset;
				}
				else
				{
					pc += 2;
				}
				break;
			case F_BRANCH_GE:
				f_ge();
				if ( (sp--)->u.number)
				{
					COPY_SHORT(&offset, pc);
					pc += offset;
				}
				else
				{
					pc += 2;
				}
				break;
			case F_BRANCH_LE:
				f_le();
				if ( (sp--)->u.number)
				{
					COPY_SHORT(&offset, pc);
					pc += offset;
				}
				else
				{
					pc += 2;
				}
				break;
			case F_BRANCH_EQ:
				f_eq();
				if ( (sp--)->u.number)
				{
					COPY_SHORT(&offset, pc);
					pc += offset;
				}
				else
				{
					pc += 2;
				}
				break;
			case F_BBRANCH_LT:
				f_lt();
				if ( (sp--)->u.number)
				{
					COPY_SHORT(&offset, pc);
					pc -= offset;
				}
				else
				{
					pc += 2;
				}
				break;
			case F_BRANCH_WHEN_ZERO:
				 /* relative offset */
				if (sp->type == T_NUMBER)
				{
					if (!( (sp--)->u.number) )
					{
						COPY_SHORT(&offset, pc);
						pc += offset;
						break;
					}
				}
				else
				{
					pop_stack();
				}
				pc += 2; /* skip over the offset */
				break;
			case F_BRANCH_WHEN_NON_ZERO:
				 /* relative offset */
				if (sp->type == T_NUMBER)
				{
					if (!( (sp--)->u.number) )
					{
						pc += 2;
						break;
					}
				}
				else
				{
					pop_stack();
				}
				COPY_SHORT(&offset, pc);
				pc += offset;
				break;
			case F_BBRANCH_WHEN_ZERO:
				 /* relative backwards offset */
				if (sp->type == T_NUMBER)
				{
					if (!( (sp--)->u.number) )
					{
						COPY_SHORT(&offset, pc);
						pc -= offset;
						break;
					}
				}
				else
				{
					pop_stack();
				}
				pc += 2;
				break;
			case F_BBRANCH_WHEN_NON_ZERO:
				 /* relative backwards offset */
				if (sp->type == T_NUMBER)
				{
					if (!( (sp--)->u.number) )
					{
						pc += 2;
						break;
					}
				}
				else
				{
					pop_stack();
				}
				COPY_SHORT(&offset, pc);
				pc -= offset;
				break;
			case F_LOR:
				/* replaces F_DUP; F_BRANCH_WHEN_NON_ZERO; F_POP */
				if (sp->type == T_NUMBER)
				{
					if (!sp->u.number)
					{
						pc += 2;
						sp--;
						break;
					}
				}
				COPY_SHORT(&offset, pc);
				pc += offset;
				break;
			case F_LAND:
				/* replaces F_DUP; F_BRANCH_WHEN_ZERO; F_POP */
				if (sp->type == T_NUMBER)
				{
					if (!sp->u.number)
					{
						COPY_SHORT(&offset, pc);
						pc += offset;
						break;
					}
					sp--;
				}
				else
				{
					pop_stack();
				}
				pc += 2;
				break;
			case F_LOOP_INCR:
				 /* this case must be just prior to
				 * F_LOOP_COND */
				{
					svalue_t *s;

					s = fp + EXTRACT_UCHAR(pc++);
					if (s->type == T_NUMBER)
					{
						s->u.number++;
					}
					else if (s->type == T_REAL)
					{
						s->u.real++;
					}
					else
					{
						error("++ of non-numeric argument\n");
					}
				}
				if (*pc == F_LOOP_COND_LOCAL)
				{
					pc++;
					do_loop_cond_local();
				}
				else if (*pc == F_LOOP_COND_NUMBER)
				{
					pc++;
					do_loop_cond_number();
				}
				break;
			case F_LOOP_COND_LOCAL:
				do_loop_cond_local();
				break;
			case F_LOOP_COND_NUMBER:
				do_loop_cond_number();
				break;
			case F_TRANSFER_LOCAL:
				{
					svalue_t *s;

					s = fp + EXTRACT_UCHAR(pc++);
					DEBUG_CHECK( (fp - s) >= csp->num_local_variables, "Tried to push non-existent local\n");
					if ( (s->type == T_OBJECT) && (s->u.ob->flags &O_DESTRUCTED) )
					{
						*++sp = const0;
						free_object(s->u.ob, "Transfer dested object");
						*s = const0;
						break;
					}
					*++sp =  *s;

					/* The optimizer has asserted this won't be used again.  Make
					 * it look like a number to avoid double frees. */
					s->type = T_NUMBER;
					break;
				}
		case F_LOCAL: {
			svalue_t *s;

			s = fp + EXTRACT_UCHAR(pc++);
			DEBUG_CHECK( (fp - s) >= csp->num_local_variables, "Tried to push non-existent local\n");

			/*
			 * If variable points to a destructed object, replace it
			 * with 0, otherwise, fetch value of variable.
			 */
			if ( (s->type == T_OBJECT) && (s->u.ob->flags &O_DESTRUCTED) ) {
				*++sp = const0;
				assign_svalue(s, &const0);
			} else {
				assign_svalue_no_free(++sp, s);
			}

			break;
		}
		case F_UPVALUE:{
			funptr_t *funp = csp->fr.funp;
			array_t *upvalues = funp->hdr.upvalues;
			int index = EXTRACT_UCHAR(pc++);
			DEBUG_CHECK(index >= upvalues->size, "upvalue out of bound\n");
			push_svalue(&upvalues->item[index]);
			//printf("push upvalue %d\n", (i & PUSH_MASK));
		}break;

			case F_LT:
				f_lt();
				break;
			case F_ADD:
				{
					switch (sp->type)
					{
					case T_BUFFER:
						{
							if (!( (sp - 1)->type == T_BUFFER) )
							{
								error("QTZ_SE:Bad type argument to +. Had %s and %s.\n", type_name( (sp - 1)->type), type_name(sp->type) );
							}
							else
							{
								buffer_t *b;

								b = allocate_buffer(sp->u.buf->size + (sp - 1)->u.buf->size);
								memcpy(b->item, (sp - 1)->u.buf->item, (sp - 1)->u.buf->size);
								memcpy(b->item + (sp - 1)->u.buf->size, sp->u.buf->item, sp->u.buf->size);
								free_buffer( (sp--)->u.buf);
								free_buffer(sp->u.buf);
								sp->u.buf = b;
							}
							break;
						}
						 /* end of x + T_BUFFER */
					case T_NUMBER:
						{
							switch ( (--sp)->type)
							{
							case T_NUMBER:
								sp->u.number += (sp + 1)->u.number;
								sp->subtype = 0;
								break;
							case T_REAL:
								sp->u.real += (sp + 1)->u.number;
								break;
							case T_STRING:
								{
									char buff[20];

									sprintf(buff, "%d", (sp + 1)->u.number);
									EXTEND_SVALUE_STRING(sp, buff, "f_add: 2");
									break;
								}
							default:
								error("QTZ_SE:Bad type argument to +.  Had %s and %s.\n", type_name(sp->type), type_name( (sp + 1)->type) );
							}
							break;
						}
						 /* end of x + NUMBER */
					case T_REAL:
						{
							switch ( (--sp)->type)
							{
							case T_NUMBER:
								sp->type = T_REAL;
								sp->u.real = sp->u.number + (sp + 1)->u.real;
								break;
							case T_REAL:
								sp->u.real += (sp + 1)->u.real;
								break;
							case T_STRING:
								{
									char buff[40];

									sprintf(buff, "%f", (sp + 1)->u.real);
									EXTEND_SVALUE_STRING(sp, buff, "f_add: 2");
									break;
								}
							default:
								error("QTZ_SE:Bad type argument to +. Had %s and %s\n", type_name(sp->type), type_name( (sp + 1)->type) );
							}
							break;
						}
						 /* end of x + T_REAL */
					case T_ARRAY:
						{
							if (!( (sp - 1)->type == T_ARRAY) )
							{
								error("QTZ_SE:Bad type argument to +. Had %s and %s\n", type_name( (sp - 1)->type), type_name(sp->type) );
							}
							else
							{
								/* add_array now free's the arrays */
								(sp - 1)->u.arr = add_array( (sp - 1)->u.arr, sp->u.arr);
								sp--;
								break;
							}
						}
						 /* end of x + T_ARRAY */
					case T_MAPPING:
						{
							if ( (sp - 1)->type == T_MAPPING)
							{
								mapping_t *map;

								map = add_mapping( (sp - 1)->u.map, sp->u.map);
								free_mapping( (sp--)->u.map);
								free_mapping(sp->u.map);
								sp->u.map = map;
								break;
							}
							else
							{
								error("QTZ_SE:Bad type argument to +. Had %s and %s\n", type_name( (sp - 1)->type), type_name(sp->type) );
							}
						}
						 /* end of x + T_MAPPING */
					case T_STRING:
						{
							switch ( (sp - 1)->type)
							{
							case T_NUMBER:
								{
									char buff[20];

									sprintf(buff, "%d", (sp - 1)->u.number);
									SVALUE_STRING_ADD_LEFT(buff, "f_add: 3");
									break;
								}
								 /* end of T_NUMBER + T_STRING */
							case T_REAL:
								{
									char buff[40];

									sprintf(buff, "%f", (sp - 1)->u.real);
									SVALUE_STRING_ADD_LEFT(buff, "f_add: 3");
									break;
								}
								 /* end of T_REAL + T_STRING */
							case T_STRING:
								{
									SVALUE_STRING_JOIN(sp - 1, sp, "f_add: 1");
									sp--;
									break;
								}
								 /* end of T_STRING + T_STRING */
							default:
								error("QTZ_SE:Bad type argument to +. Had %s and %s\n", type_name( (sp - 1)->type), type_name(sp->type) );
							}
							break;
						}
						 /* end of x + T_STRING */

					default:
						error("QTZ_SE:Bad type argument to +.  Had %s and %s.\n", type_name( (sp - 1)->type), type_name(sp->type) );
					}
					break;
				}
			case F_VOID_ADD_EQ:
			case F_ADD_EQ:
				DEBUG_CHECK(sp->type != T_LVALUE, "non-lvalue argument to +=\n");
				lval = sp->u.lvalue;
				sp--; /* points to the RHS */
				switch (lval->type)
				{
				case T_STRING:
					if (sp->type == T_STRING)
					{
						SVALUE_STRING_JOIN(lval, sp, "f_add_eq: 1");
					}
					else if (sp->type == T_NUMBER)
					{
						char buff[20];

						sprintf(buff, "%d", sp->u.number);
						EXTEND_SVALUE_STRING(lval, buff, "f_add_eq: 2");
					}
					else if (sp->type == T_REAL)
					{
						char buff[40];

						sprintf(buff, "%f", sp->u.real);
						EXTEND_SVALUE_STRING(lval, buff, "f_add_eq: 2");
					}
					else
					{
						bad_argument(sp, T_STRING | T_NUMBER | T_REAL, 2, instruction);
					}
					break;
				case T_NUMBER:
					if (sp->type == T_NUMBER)
					{
						lval->u.number += sp->u.number;
						/* both sides are numbers, no freeing required */
					}
					else if (sp->type == T_REAL)
					{
						lval->u.number += sp->u.real;
						/* both sides are numbers, no freeing required */
					}
					else
					{
						error("QTZ_SE:Left hand side of += is a number (or zero); right side is not a number.\n");
					}
					break;
				case T_REAL:
					if (sp->type == T_NUMBER)
					{
						lval->u.real += sp->u.number;
						/* both sides are numerics, no freeing required */
					}
					else if (sp->type == T_REAL)
					{
						lval->u.real += sp->u.real;
						/* both sides are numerics, no freeing required */
					}
					else
					{
						error("QTZ_SE:Left hand side of += is a real (or zero); right side is not a number.\n");
					}
					break;
				case T_BUFFER:
					if (sp->type != T_BUFFER)
					{
						bad_argument(sp, T_BUFFER, 2, instruction);
					}
					else
					{
						buffer_t *b;

						b = allocate_buffer(lval->u.buf->size + sp->u.buf->size);
						memcpy(b->item, lval->u.buf->item, lval->u.buf->size);
						memcpy(b->item + lval->u.buf->size, sp->u.buf->item, sp->u.buf->size);
						free_buffer(sp->u.buf);
						free_buffer(lval->u.buf);
						lval->u.buf = b;
					}
					break;
				case T_ARRAY:
					if (sp->type != T_ARRAY)
					{
						bad_argument(sp, T_ARRAY, 2, instruction);
					}
					else
					{
						/* add_array now frees the arrays */
						lval->u.arr = add_array(lval->u.arr, sp->u.arr);
					}
					break;
				case T_MAPPING:
					if (sp->type != T_MAPPING)
					{
						bad_argument(sp, T_MAPPING, 2, instruction);
					}
					else
					{
						absorb_mapping(lval->u.map, sp->u.map);
						free_mapping(sp->u.map); /* free RHS */
						/* LHS not freed because its being reused */
					}
					break;
				case T_LVALUE_BYTE:
					{
						char c;

						if (sp->type != T_NUMBER)
						{
							error("QTZ_SE:Bad right type to += of char lvalue.\n");
						}

						c =  *global_lvalue_byte.u.lvalue_byte + sp->u.number;

						if (global_lvalue_byte.subtype == 0 && c == '\0')
						{
							error("QTZ_SE:Strings cannot contain 0 bytes.\n");
						}
						*global_lvalue_byte.u.lvalue_byte = c;
					}
					break;
				default:
					bad_arg(1, instruction);
				}

				if (instruction == F_ADD_EQ)
				{
					 /* not void add_eq */
					assign_svalue_no_free(sp, lval);
				}
				else
				{
					/*
					 * but if (void)add_eq then no need to produce an
					 * rvalue
					 */
					sp--;
				}
				break;
			case F_AND:
				f_and();
				break;
			case F_AND_EQ:
				f_and_eq();
				break;
			case F_FUNCTION_CONSTRUCTOR:
				f_function_constructor();
				break;

			case F_FOREACH:
				{
					int flags = EXTRACT_UCHAR(pc++);

					IF_DEBUG(stack_in_use_as_temporary++);
					if (flags &4)
					{
						CHECK_TYPES(sp, T_MAPPING, 2, F_FOREACH);

						push_refed_array(mapping_indices(sp->u.map) );

						(++sp)->type = T_NUMBER;
						sp->u.lvalue = (sp - 1)->u.arr->item;
						sp->subtype = (sp - 1)->u.arr->size;

						(++sp)->type = T_LVALUE;
						if (flags &2)
						{
							sp->u.lvalue = find_value( (int) (EXTRACT_UCHAR(pc++) + variable_index_offset) );
						}
						else
						{
							sp->u.lvalue = fp + EXTRACT_UCHAR(pc++);
						}
					}
					else
					if (sp->type == T_STRING)
					{
						(++sp)->type = T_NUMBER;
						sp->u.lvalue_byte = (unsigned char*) ( (sp - 1)->u.string);
						sp->subtype = SVALUE_STRLEN(sp - 1);
					}
					else
					{
						CHECK_TYPES(sp, T_ARRAY, 2, F_FOREACH);

						(++sp)->type = T_NUMBER;
						sp->u.lvalue = (sp - 1)->u.arr->item;
						sp->subtype = (sp - 1)->u.arr->size;
					}

					(++sp)->type = T_LVALUE;
					if (flags &1)
					{
						sp->u.lvalue = find_value( (int) (EXTRACT_UCHAR(pc++) + variable_index_offset) );
					}
					else
					{
						sp->u.lvalue = fp + EXTRACT_UCHAR(pc++);
					}
					break;
				}
			case F_NEXT_FOREACH:
				if ( (sp - 1)->type == T_LVALUE)
				{
					/* mapping */
					if ( (sp - 2)->subtype--)
					{
						svalue_t *key = (sp - 2)->u.lvalue++;
						svalue_t *value = find_in_mapping( (sp - 4)->u.map, key);

						assign_svalue( (sp - 1)->u.lvalue, key);
						assign_svalue(sp->u.lvalue, value);
						COPY_SHORT(&offset, pc);
						pc -= offset;
						break;
					}
				}
				else
				{
					/* array or string */
					if ( (sp - 1)->subtype--)
					{
						if ( (sp - 2)->type == T_STRING)
						{
							free_svalue(sp->u.lvalue, "foreach-string");
							sp->u.lvalue->type = T_NUMBER;
							sp->u.lvalue->subtype = 0;
							sp->u.lvalue->u.number = *( (sp - 1)->u.lvalue_byte)++;
						}
						else
						{
							assign_svalue(sp->u.lvalue, (sp - 1)->u.lvalue++);
						}
						COPY_SHORT(&offset, pc);
						pc -= offset;
						break;
					}
				}
				pc += 2;
				/* fallthrough */
			case F_EXIT_FOREACH:
				IF_DEBUG(stack_in_use_as_temporary--);
				if ( (sp - 1)->type == T_LVALUE)
				{
					/* mapping */
					sp -= 3;
					free_array( (sp--)->u.arr);
					free_mapping( (sp--)->u.map);
				}
				else
				{
					/* array or string */
					sp -= 2;
					if (sp->type == T_STRING)
					{
						free_string_svalue(sp--);
					}
					else
					{
						free_array( (sp--)->u.arr);
					}
				}
				break;

			case F_EXPAND_VARARGS:
				{
					svalue_t *s,  *t;
					array_t *arr;

					i = EXTRACT_UCHAR(pc++);
					s = sp - i;

					if (s->type != T_ARRAY)
					{
						error("QTZ_SE:Item being expanded with ... is not an array\n");
					}

					arr = s->u.arr;
					n = arr->size;
					num_varargs += n - 1;
					if (!n)
					{
						t = s;
						while (t < sp)
						{
							*t = *(t + 1);
							t++;
						}
						sp--;
					}
					else if (n == 1)
					{
						assign_svalue_no_free(s, &arr->item[0]);
					}
					else
					{
						t = sp;
						sp += n - 1;
						while (t > s)
						{
							*(t + n - 1) =  *t;
							t--;
						}
						t = s + n - 1;
						if (arr->ref == 1)
						{
							memcpy(s, arr->item, n *sizeof(svalue_t) );
							free_empty_array(arr);
							break;
						}
						else
						{
							while (n--)
							{
								assign_svalue_no_free(t--, &arr->item[n]);
							}
						}
					}
					free_array(arr);
					break;
				}

			case F_NEW_CLASS:
				{
					array_t *cl;
					unsigned char idx = EXTRACT_UCHAR(pc++);

					cl = allocate_class(&current_prog->classes[idx], 1);
					push_refed_class(cl, idx);
				}
				break;
			case F_NEW_EMPTY_CLASS:
				{
					array_t *cl;
					unsigned char idx = EXTRACT_UCHAR(pc++);

					cl = allocate_class(&current_prog->classes[idx], 0);
					push_refed_class(cl, idx);
				}
				break;
			case F_AGGREGATE:
				{
					array_t *v;

					LOAD_SHORT(offset, pc);
					offset += num_varargs;
					num_varargs = 0;
					v = allocate_empty_array( (int)offset);
					/*
					 * transfer svalues in reverse...popping stack as we go
					 */
					while (offset--) {
						v->item[offset] =  *sp--;
					}
					(++sp)->type = T_ARRAY;
					sp->u.arr = v;
				}
				break;
			case F_AGGREGATE_ASSOC:
				{
					mapping_t *m;

					LOAD_SHORT(offset, pc);

					offset += num_varargs;
					num_varargs = 0;
					m = load_mapping_from_aggregate(sp -= offset, offset);
					(++sp)->type = T_MAPPING;
					sp->u.map = m;
					break;
				}
			case F_ASSIGN:
				#ifdef DEBUG
					if (sp->type != T_LVALUE)
					{
						fatal("QTZ_SE:Bad argument to F_ASSIGN\n");
					}
				#endif 
				switch (sp->u.lvalue->type)
				{
				case T_LVALUE_BYTE:
					{
						char c;

						if ( (sp - 1)->type != T_NUMBER)
						{
							error("QTZ_SE:Illegal rhs to char lvalue\n");
						}
						else
						{
							c = ( (sp - 1)->u.number &0xff);
							if (global_lvalue_byte.subtype == 0 && c == '\0')
							{
								error("QTZ_SE:Strings cannot contain 0 bytes.\n");
							}
							*global_lvalue_byte.u.lvalue_byte = c;
						}
						break;
					}
				default:
					assign_svalue(sp->u.lvalue, sp - 1);
					break;
				case T_LVALUE_RANGE:
					assign_lvalue_range(sp - 1);
					break;
				}
				sp--; /* ignore lvalue */
				/* rvalue is already in the correct place */
				break;
			case F_VOID_ASSIGN_LOCAL:
				if (sp->type != T_INVALID)
				{
					lval = fp + EXTRACT_UCHAR(pc++);
					free_svalue(lval, "F_VOID_ASSIGN_LOCAL");
					*lval =  *sp--;
				}
				else
				{
					sp--;
					pc++;
				}
				break;
			case F_VOID_ASSIGN:
				#ifdef DEBUG
					if (sp->type != T_LVALUE)
					{
						fatal("QTZ_SE:Bad argument to F_VOID_ASSIGN\n");
					}
				#endif 
				lval = (sp--)->u.lvalue;
				if (sp->type != T_INVALID)
				{
					switch (lval->type)
					{
					case T_LVALUE_BYTE:
						{
							if (sp->type != T_NUMBER)
							{
								error("QTZ_SE:Illegal rhs to char lvalue\n");
							}
							else
							{
								char c = (sp--)->u.number &0xff;
								if (global_lvalue_byte.subtype == 0 && c == '\0')
								{
									error("QTZ_SE:Strings cannot contain 0 bytes.\n");
								}
								*global_lvalue_byte.u.lvalue_byte = c;
							}
							break;
						}

					case T_LVALUE_RANGE:
						{
							copy_lvalue_range(sp--);
							break;
						}

					default:
						{
							free_svalue(lval, "F_VOID_ASSIGN : 3");
							*lval =  *sp--;
						}
					}
				}
				else
				{
					sp--;
				}
				break;
				#ifdef DEBUG
				case F_BREAK_POINT:
					break_point();
					break;
				#endif 
			case F_CALL_FUNCTION_BY_ADDRESS:
				{
					compiler_function_t *funp;

					LOAD_SHORT(offset, pc);
					offset += function_index_offset;
					/*
					 * Find the fun in the fun table. As the
					 * fun may have been redefined by inheritance, we
					 * must look in the last table, which is pointed to by
					 * current_object.
					 */
					DEBUG_CHECK(offset >= current_object->prog->num_functions_total, "Illegal fun index\n");

					if (current_object->prog->function_flags[offset] &NAME_UNDEFINED) {
						error("QTZ_SE:Undefined fun: %s\n", function_name(current_object->prog, offset) );
					}
					/* Save all important global stack machine registers */
					push_control_stack(FRAME_FUNCTION);
					current_prog = current_object->prog;

					caller_type = ORIGIN_LOCAL;
					/*
					 * If it is an inherited fun, search for the real
					 * definition.
					 */
					csp->num_local_variables = EXTRACT_UCHAR(pc++) + num_varargs;
					num_varargs = 0;
					funp = setup_new_frame(offset);
					csp->pc = pc; /* The corrected return address */
					pc = current_prog->program + funp->address;
				}
				break;
			case F_CALL_INHERITED:
				{
					inherit_t *ip = current_prog->inherit + EXTRACT_UCHAR(pc++);
					program_t *temp_prog = ip->prog;
					compiler_function_t *funp;

					LOAD_SHORT(offset, pc);

					push_control_stack(FRAME_FUNCTION);
					current_prog = temp_prog;

					caller_type = ORIGIN_LOCAL;

					csp->num_local_variables = EXTRACT_UCHAR(pc++) + num_varargs;
					num_varargs = 0;

					function_index_offset += ip->function_index_offset;
					variable_index_offset += ip->variable_index_offset;

					funp = setup_inherited_frame(offset);
					csp->pc = pc;
					pc = current_prog->program + funp->address;
				}
				break;
			case F_COMPL:
				if (sp->type != T_NUMBER)
				{
					error("QTZ_SE:Bad argument to ~\n");
				}
				sp->u.number = ~sp->u.number;
				sp->subtype = 0;
				break;
			case F_CONST0:
				push_number(0);
				break;
			case F_CONST1:
				push_number(1);
				break;
			case F_PRE_DEC:
				DEBUG_CHECK(sp->type != T_LVALUE, "non-lvalue argument to --\n");
				lval = sp->u.lvalue;
				switch (lval->type)
				{
				case T_NUMBER:
					sp->type = T_NUMBER;
					sp->subtype = 0;
					sp->u.number = --(lval->u.number);
					break;
				case T_REAL:
					sp->type = T_REAL;
					sp->u.real = --(lval->u.real);
					break;
				case T_LVALUE_BYTE:
					if (global_lvalue_byte.subtype == 0 && *global_lvalue_byte.u.lvalue_byte == '\x1')
					{
						error("QTZ_SE:Strings cannot contain 0 bytes.\n");
					}
					sp->type = T_NUMBER;
					sp->subtype = 0;
					sp->u.number = --(*global_lvalue_byte.u.lvalue_byte);
					break;
				default:
					error("QTZ_SE:-- of non-numeric argument\n");
				}
				break;
			case F_DEC:
				DEBUG_CHECK(sp->type != T_LVALUE, "non-lvalue argument to --\n");
				lval = (sp--)->u.lvalue;
				switch (lval->type)
				{
				case T_NUMBER:
					lval->u.number--;
					break;
				case T_REAL:
					lval->u.real--;
					break;
				case T_LVALUE_BYTE:
					if (global_lvalue_byte.subtype == 0 && *global_lvalue_byte.u.lvalue_byte == '\x1')
					{
						error("QTZ_SE:Strings cannot contain 0 bytes.\n");
					}
					--(*global_lvalue_byte.u.lvalue_byte);
					break;
				default:
					error("QTZ_SE:-- of non-numeric argument\n");
				}
				break;
			case F_DIVIDE:
				{
					switch ( (sp - 1)->type | sp->type)
					{

					case T_NUMBER:
						{
							if (!(sp--)->u.number)
							{
								error("QTZ_SE:Division by zero\n");
							}
							sp->u.number /= (sp + 1)->u.number;
							break;
						}

					case T_REAL:
						{
							if ( (sp--)->u.real == 0.0)
							{
								error("QTZ_SE:Division by zero\n");
							}
							sp->u.real /= (sp + 1)->u.real;
							break;
						}

						case T_NUMBER | T_REAL: 
						{
							if ( (sp--)->type == T_NUMBER)
							{
								if (!( (sp + 1)->u.number) )
								{
									error("QTZ_SE:Division by zero\n");
								}
								sp->u.real /= (sp + 1)->u.number;
							}
							else
							{
								if ( (sp + 1)->u.real == 0.0)
								{
									error("QTZ_SE:Division by 0.0\n");
								}
								sp->type = T_REAL;
								sp->u.real = sp->u.number / (sp + 1)->u.real;
							}
							break;
						}

					default:
						{
							if (!( (sp - 1)->type &(T_NUMBER | T_REAL) ) )
							{
								bad_argument(sp - 1, T_NUMBER | T_REAL, 1, instruction);
							}
							if (!(sp->type &(T_NUMBER | T_REAL) ) )
							{
								bad_argument(sp, T_NUMBER | T_REAL, 2, instruction);
							}
						}
					}
				}
				break;
			case F_DIV_EQ:
				f_div_eq();
				break;
			case F_EQ:
				f_eq();
				break;
			case F_GE:
				f_ge();
				break;
			case F_GT:
				f_gt();
				break;
			case F_GLOBAL:
				{
					svalue_t *s;

					s = find_value( (int) (EXTRACT_UCHAR(pc++) + variable_index_offset) );

					/*
					 * If variable points to a destructed object, replace it
					 * with 0, otherwise, fetch value of variable.
					 */
					if ( (s->type == T_OBJECT) && (s->u.ob->flags &O_DESTRUCTED) )
					{
						*++sp = const0;
						assign_svalue(s, &const0);
					}
					else
					{
						assign_svalue_no_free(++sp, s);
					}
					break;
				}
			case F_PRE_INC:
				DEBUG_CHECK(sp->type != T_LVALUE, "non-lvalue argument to ++\n");
				lval = sp->u.lvalue;
				switch (lval->type)
				{
				case T_NUMBER:
					sp->type = T_NUMBER;
					sp->subtype = 0;
					sp->u.number = ++lval->u.number;
					break;
				case T_REAL:
					sp->type = T_REAL;
					sp->u.real = ++lval->u.number;
					break;
				case T_LVALUE_BYTE:
					if (global_lvalue_byte.subtype == 0 && *global_lvalue_byte.u.lvalue_byte == (unsigned char)255)
					{
						error("QTZ_SE:Strings cannot contain 0 bytes.\n");
					}
					sp->type = T_NUMBER;
					sp->subtype = 0;
					sp->u.number = ++ * global_lvalue_byte.u.lvalue_byte;
					break;
				default:
					error("QTZ_SE:++ of non-numeric argument\n");
				}
				break;
			case F_MEMBER:
				{
					array_t *arr;

					if (sp->type != T_CLASS)
					{
						error("QTZ_SE:Tried to take a member of something that isn't a class.\n");
					}
					i = EXTRACT_UCHAR(pc++);
					arr = sp->u.arr;
					if (i >= arr->size)
					{
						error("QTZ_SE:Class has no corresponding member.\n");
					}
					assign_svalue_no_free(sp, &arr->item[i]);
					free_class(arr);

					/*
					 * Fetch value of a variable. It is possible that it is a
					 * variable that points to a destructed object. In that case,
					 * it has to be replaced by 0.
					 */
					if (sp->type == T_OBJECT && (sp->u.ob->flags &O_DESTRUCTED) )
					{
						free_object(sp->u.ob, "F_MEMBER");
						sp->type = T_NUMBER;
						sp->u.number = 0;
					}
					break;
				}
			case F_MEMBER_LVALUE:
				{
					array_t *arr;

					if (sp->type != T_CLASS)
					{
						error("QTZ_SE:Tried to take a member of something that isn't a class.\n");
					}
					i = EXTRACT_UCHAR(pc++);
					arr = sp->u.arr;
					if (i >= arr->size)
					{
						error("QTZ_SE:Class has no corresponding member.\n");
					}
					sp->type = T_LVALUE;
					sp->u.lvalue = arr->item + i;
					free_class(arr);
					break;
				}
			case F_INDEX:
				switch (sp->type)
				{
				case T_MAPPING:
					{
						svalue_t *v;
						mapping_t *m;

						v = find_in_mapping(m = sp->u.map, sp - 1);
						assign_svalue(--sp, v); /* v will always have a
						 * value */
						free_mapping(m);
						break;
					}
				case T_BUFFER:
					{
						if ( (sp - 1)->type != T_NUMBER)
						{
							error("QTZ_SE:Buffer indexes must be integers.\n");
						}

						i = (sp - 1)->u.number;
						if ( (i > (int)sp->u.buf->size) || (i < 0) )
						{
							error("QTZ_SE:Buffer index out of bounds.\n");
						}
						i = sp->u.buf->item[i];
						free_buffer(sp->u.buf);
						(--sp)->u.number = i;
						sp->subtype = 0;
						break;
					}
				case T_STRING:
					{
						if ( (sp - 1)->type != T_NUMBER)
						{
							error("QTZ_SE:String indexes must be integers.\n");
						}
						i = (sp - 1)->u.number;
						if ( (i > (int)SVALUE_STRLEN(sp) ) || (i < 0) )
						{
							error("QTZ_SE:String index out of bounds.\n");
						}
						i = (unsigned char)sp->u.string[i];
						free_string_svalue(sp);
						(--sp)->u.number = i;
						break;
					}
				case T_ARRAY:
					{
						array_t *arr;

						if ( (sp - 1)->type != T_NUMBER)
						{
							error("QTZ_SE:Array indexes must be integers.\n");
						}
						i = (sp - 1)->u.number;
						if (i < 0)
						{
							error("QTZ_SE:Array index must be positive or zero.\n");
						}
						arr = sp->u.arr;
						if (i >= arr->size)
						{
							error("QTZ_SE:Array index out of bounds.\n");
						}
						assign_svalue_no_free(--sp, &arr->item[i]);
						free_array(arr);
						break;
					}
				case T_CLASS:
					{
						array_t *arr;

						if ( (sp - 1)->type != T_NUMBER)
						{
							error("QTZ_SE:Class indexes must be integers.\n");
						}
						i = (sp - 1)->u.number;
						if (i < 0)
						{
							error("QTZ_SE:Class index must be positive or zero.\n");
						}
						arr = sp->u.arr;
						if (i >= arr->size)
						{
							error("QTZ_SE:Class index out of bounds.\n");
						}
						assign_svalue_no_free(--sp, &arr->item[i]);
					    free_class(arr);
						break;
					}
				default:
					if (sp->type == T_NUMBER && !sp->u.number)
					{
						error("QTZ_SE:Value being indexed is zero.\n");
					}
					error("QTZ_SE:Cannot index value of type '%s'.\n", type_name(sp->type) );
				}

				/*
				 * Fetch value of a variable. It is possible that it is a
				 * variable that points to a destructed object. In that case,
				 * it has to be replaced by 0.
				 */
				if (sp->type == T_OBJECT && (sp->u.ob->flags &O_DESTRUCTED) )
				{
					free_object(sp->u.ob, "F_INDEX");
					sp->type = T_NUMBER;
					sp->u.number = 0;
				}
				break;
			case F_RINDEX:
				switch (sp->type)
				{
				case T_BUFFER:
					{
						if ( (sp - 1)->type != T_NUMBER)
						{
							error("QTZ_SE:Indexing a buffer with an illegal type.\n");
						}

						i = sp->u.buf->size - (sp - 1)->u.number;
						if ( (i > (int)sp->u.buf->size) || (i < 0) )
						{
							error("QTZ_SE:Buffer index out of bounds.\n");
						}

						i = sp->u.buf->item[i];
						free_buffer(sp->u.buf);
						(--sp)->u.number = i;
						sp->subtype = 0;
						break;
					}
				case T_STRING:
					{
						int len = SVALUE_STRLEN(sp);
						if ( (sp - 1)->type != T_NUMBER)
						{
							error("QTZ_SE:Indexing a string with an illegal type.\n");
						}
						i = len - (sp - 1)->u.number;
						if ( (i > len) || (i < 0) )
						{
							error("QTZ_SE:String index out of bounds.\n");
						}
						i = (unsigned char)sp->u.string[i];
						free_string_svalue(sp);
						(--sp)->u.number = i;
						break;
					}
				case T_ARRAY:
					{
						array_t *arr = sp->u.arr;

						if ( (sp - 1)->type != T_NUMBER)
						{
							error("QTZ_SE:Indexing an array with an illegal type\n");
						}
						i = arr->size - (sp - 1)->u.number;
						if (i < 0 || i >= arr->size)
						{
							error("QTZ_SE:Array index out of bounds.\n");
						}
						assign_svalue_no_free(--sp, &arr->item[i]);
						free_array(arr);
						break;
					}
				default:
					if (sp->type == T_NUMBER && !sp->u.number)
					{
						error("QTZ_SE:Value being indexed is zero.\n");
					}
					error("QTZ_SE:Cannot index value of type '%s'.\n", type_name(sp->type) );
				}

				/*
				 * Fetch value of a variable. It is possible that it is a
				 * variable that points to a destructed object. In that case,
				 * it has to be replaced by 0.
				 */
				if (sp->type == T_OBJECT && (sp->u.ob->flags &O_DESTRUCTED) )
				{
					free_object(sp->u.ob, "F_RINDEX");
					sp->type = T_NUMBER;
					sp->u.number = 0;
				}
				break;
				#ifdef F_JUMP_WHEN_ZERO
				case F_JUMP_WHEN_ZERO:
					if ( (i = (sp->type == T_NUMBER) ) && sp->u.number == 0)
					{
						COPY_SHORT(&offset, pc);
						pc = current_prog->program + offset;
					}
					else
					{
						pc += 2;
					}
					if (i)
					{
						sp--; /* cheaper to do this when sp is an integer
						 * svalue */
					}
					else
					{
						pop_stack();
					}
					break;
				#endif 
				#ifdef F_JUMP
				case F_JUMP:
					COPY_SHORT(&offset, pc);
					pc = current_prog->program + offset;
					break;
				#endif 
			case F_LE:
				f_le();
				break;
			case F_LSH:
				f_lsh();
				break;
			case F_LSH_EQ:
				f_lsh_eq();
				break;
			case F_MOD:
				{
					CHECK_TYPES(sp - 1, T_NUMBER, 1, instruction);
					CHECK_TYPES(sp, T_NUMBER, 2, instruction);
					if ( (sp--)->u.number == 0)
					{
						error("QTZ_SE:Modulus by zero.\n");
					}
					sp->u.number %= (sp + 1)->u.number;
				}
				break;
			case F_MOD_EQ:
				f_mod_eq();
				break;
			case F_MULTIPLY:
				{
					switch ( (sp - 1)->type | sp->type)
					{
					case T_NUMBER:
						{
							sp--;
							sp->u.number *= (sp + 1)->u.number;
							break;
						}

					case T_REAL:
						{
							sp--;
							sp->u.real *= (sp + 1)->u.real;
							break;
						}

						case T_NUMBER | T_REAL: 
						{
							if ( (--sp)->type == T_NUMBER)
							{
								sp->type = T_REAL;
								sp->u.real = sp->u.number *(sp + 1)->u.real;
							}
							else
							{
								sp->u.real *= (sp + 1)->u.number;
							}
							break;
						}

					case T_MAPPING:
						{
							mapping_t *m;
							m = compose_mapping( (sp - 1)->u.map, sp->u.map, 1);
							pop_2_elems();
							(++sp)->type = T_MAPPING;
							sp->u.map = m;
							break;
						}

					default:
						{
							if (!( (sp - 1)->type &(T_NUMBER | T_REAL | T_MAPPING) ) )
							{
								bad_argument(sp - 1, T_NUMBER | T_REAL | T_MAPPING, 1, instruction);
							}
							if (!(sp->type &(T_NUMBER | T_REAL | T_MAPPING) ) )
							{
								bad_argument(sp, T_NUMBER | T_REAL | T_MAPPING, 2, instruction);
							}
							error("QTZ_SE:Args to * are not compatible.\n");
						}
					}
				}
				break;
			case F_MULT_EQ:
				f_mult_eq();
				break;
			case F_NE:
				f_ne();
				break;
			case F_NEGATE:
				if (sp->type == T_NUMBER)
				{
					sp->subtype = 0;
					sp->u.number =  - sp->u.number;
				}
				else if (sp->type == T_REAL)
				{
					sp->u.real =  - sp->u.real;
				}
				else
				{
					error("QTZ_SE:Bad argument to unary minus\n");
				}
				break;
			case F_NOT:
				if (sp->type == T_NUMBER)
				{
					sp->subtype = 0;
					sp->u.number = !sp->u.number;
				}
				else
				{
					assign_svalue(sp, &const0);
				}
				break;
			case F_OR:
				f_or();
				break;
			case F_OR_EQ:
				f_or_eq();
				break;
			case F_POP_VALUE:
				pop_stack();
				break;
			case F_POST_DEC:
				DEBUG_CHECK(sp->type != T_LVALUE, "non-lvalue argument to --\n");
				lval = sp->u.lvalue;
				switch (lval->type)
				{
				case T_NUMBER:
					sp->type = T_NUMBER;
					sp->subtype = 0;
					sp->u.number = lval->u.number--;
					break;
				case T_REAL:
					sp->type = T_REAL;
					sp->u.real = lval->u.real--;
					break;
				case T_LVALUE_BYTE:
					sp->type = T_NUMBER;
					if (global_lvalue_byte.subtype == 0 && *global_lvalue_byte.u.lvalue_byte == '\x1')
					{
						error("QTZ_SE:Strings cannot contain 0 bytes.\n");
					}
					sp->u.number = (*global_lvalue_byte.u.lvalue_byte)--;
					break;
				default:
					error("QTZ_SE:-- of non-numeric argument\n");
				}
				break;
			case F_POST_INC:
				DEBUG_CHECK(sp->type != T_LVALUE, "non-lvalue argument to ++\n");
				lval = sp->u.lvalue;
				switch (lval->type)
				{
				case T_NUMBER:
					sp->type = T_NUMBER;
					sp->subtype = 0;
					sp->u.number = lval->u.number++;
					break;
				case T_REAL:
					sp->type = T_REAL;
					sp->u.real = lval->u.real++;
					break;
				case T_LVALUE_BYTE:
					if (global_lvalue_byte.subtype == 0 && *global_lvalue_byte.u.lvalue_byte == (unsigned char)255)
					{
						error("QTZ_SE:Strings cannot contain 0 bytes.\n");
					}
					sp->type = T_NUMBER;
					sp->u.number = (*global_lvalue_byte.u.lvalue_byte)++;
					break;
				default:
					error("QTZ_SE:++ of non-numeric argument\n");
				}
				break;
			case F_GLOBAL_LVALUE:
				(++sp)->type = T_LVALUE;
				sp->u.lvalue = find_value( (int) (EXTRACT_UCHAR(pc++) + variable_index_offset) );
				break;
			case F_INDEX_LVALUE:
				push_indexed_lvalue(0);
				break;
			case F_RINDEX_LVALUE:
				push_indexed_lvalue(1);
				break;
			case F_NN_RANGE_LVALUE:
				push_lvalue_range(0x00);
				break;
			case F_RN_RANGE_LVALUE:
				push_lvalue_range(0x10);
				break;
			case F_RR_RANGE_LVALUE:
				push_lvalue_range(0x11);
				break;
			case F_NR_RANGE_LVALUE:
				push_lvalue_range(0x01);
				break;
			case F_NN_RANGE:
				f_range(0x00);
				break;
			case F_RN_RANGE:
				f_range(0x10);
				break;
			case F_NR_RANGE:
				f_range(0x01);
				break;
			case F_RR_RANGE:
				f_range(0x11);
				break;
			case F_NE_RANGE:
				f_extract_range(0);
				break;
			case F_RE_RANGE:
				f_extract_range(1);
				break;
			case F_RETURN_ZERO:
				{
					/*
					 * Deallocate frame and return.
					 */
					pop_n_elems(csp->num_local_variables);
					sp++;
					DEBUG_CHECK(sp != fp, "Bad stack at F_RETURN\n");
					*sp = const0;
					pop_control_stack();
					/* The control stack was popped just before */
					if (csp[1].framekind &FRAME_EXTERNAL)
					{
						return ;
					}
					break;
				}
				break;
			case F_RETURN:
				{
					svalue_t sv;

					if (csp->num_local_variables)
					{
						sv =  *sp--;
						/*
						 * Deallocate frame and return.
						 */
						pop_n_elems(csp->num_local_variables);
						sp++;
						DEBUG_CHECK(sp != fp, "Bad stack at F_RETURN\n");
						*sp = sv; /* This way, the same ref counts are
						 * maintained */
					}
					pop_control_stack();
					/* The control stack was popped just before */
					if (csp[1].framekind &FRAME_EXTERNAL)
					{
						return ;
					}
					break;
				}
			case F_RSH:
				f_rsh();
				break;
			case F_RSH_EQ:
				f_rsh_eq();
				break;
			case F_SSCANF:
				f_sscanf();
				break;
			case F_STRING:
				LOAD_SHORT(offset, pc);
				DEBUG_CHECK1(offset >= current_prog->num_strings, "string %d out of range in F_STRING!\n", offset);
				push_shared_string(current_prog->strings[offset]);
				break;
			case F_SHORT_STRING:
				DEBUG_CHECK1(EXTRACT_UCHAR(pc) >= current_prog->num_strings, "string %d out of range in F_STRING!\n", EXTRACT_UCHAR(pc) );
				push_shared_string(current_prog->strings[EXTRACT_UCHAR(pc++)]);
				break;
			case F_SUBTRACT:
				{
					i = (sp--)->type;
					switch (i | sp->type)
					{
					case T_NUMBER:
						sp->u.number -= (sp + 1)->u.number;
						break;

					case T_REAL:
						sp->u.real -= (sp + 1)->u.real;
						break;

						case T_NUMBER | T_REAL: if (sp->type == T_REAL)
						{
							sp->u.real -= (sp + 1)->u.number;
						}
						else
						{
							sp->type = T_REAL;
							sp->u.real = sp->u.number - (sp + 1)->u.real;
						}
						break;

					case T_ARRAY:
						{
							/*
							 * subtract_array already takes care of
							 * destructed objects
							 */
							sp->u.arr = subtract_array(sp->u.arr, (sp + 1)->u.arr);
							break;
						}

					default:
						if (!( (sp++)->type &(T_NUMBER | T_REAL | T_ARRAY) ) )
						{
							error("QTZ_SE:Bad left type to -.\n");
						}
						else if (!(sp->type &(T_NUMBER | T_REAL | T_ARRAY) ) )
						{
							error("QTZ_SE:Bad right type to -.\n");
						}
						else
						{
							error("QTZ_SE:Arguments to - do not have compatible types.\n");
						}
					}
					break;
				}
			case F_SUB_EQ:
				f_sub_eq();
				break;
			case F_SIMUL_EFUN:
				{
					unsigned short index;
					int num_args;

					LOAD_SHORT(index, pc);
					num_args = EXTRACT_UCHAR(pc++) + num_varargs;
					num_varargs = 0;
					call_simul_efun(index, num_args);
				}
				break;
			case F_SWITCH:
				f_switch();
				break;
			case F_XOR:
				f_xor();
				break;
			case F_XOR_EQ:
				f_xor_eq();
				break;
			case F_CATCH:
				{
					/*
					 * Compute address of next instruction after the CATCH
					 * statement.
					 */
					( (char*) &offset)[0] = pc[0];
					( (char*) &offset)[1] = pc[1];
					offset = pc + offset - current_prog->program;
					pc += 2;

					do_catch(pc);

					pc = current_prog->program + offset;

					break;
				}
			case F_END_CATCH:
				{
					free_svalue(&catch_value, "F_END_CATCH");
					catch_value = const0;
					/* We come here when no longjmp() was executed */
					pop_control_stack();
					push_number(0);
					return ; /* return to do_catch */
				}
			case F_TIME_EXPRESSION:
				{
					long sec, usec;

					IF_DEBUG(stack_in_use_as_temporary++);
					get_usec_clock(&sec, &usec);
					push_number(sec);
					push_number(usec);
					break;
				}
			case F_END_TIME_EXPRESSION:
				{
					long sec, usec;

					get_usec_clock(&sec, &usec);
					usec = (sec - (sp - 1)->u.number) *1000000+(usec - sp->u.number);
					sp -= 2;
					IF_DEBUG(stack_in_use_as_temporary--);
					push_number(usec);
					break;
				}
				#define Instruction (instruction + ONEARG_MAX)
				#ifdef DEBUG
					#define CALL_THE_EFUN goto call_the_efun
				#else 
					#define CALL_THE_EFUN \
					{ \
					svalue_t * expect_sp; \
					if (instrs2[instruction].ret_type == TYPE_NOVALUE) \
					expect_sp = sp - st_num_arg; \
					else \
					expect_sp = sp - st_num_arg + 1; \
					\
					(*oefun_table[instruction])(); \
					if (expect_sp != sp) \
					{ \
					debug_message("Bad stack after efun %s\n", instrs2[instruction].name); \
					} \
					} \
					continue
				#endif 
			case F_EFUN0:
				st_num_arg = 0;
				instruction = EXTRACT_UCHAR(pc++);
				CALL_THE_EFUN;
			case F_EFUN1:
				st_num_arg = 1;
				instruction = EXTRACT_UCHAR(pc++);
				CHECK_TYPES(sp, instrs2[instruction].type[0], 1, Instruction);
				CALL_THE_EFUN;
			case F_EFUN2:
				st_num_arg = 2;
				instruction = EXTRACT_UCHAR(pc++);
				CHECK_TYPES(sp - 1, instrs2[instruction].type[0], 1, Instruction);
				CHECK_TYPES(sp, instrs2[instruction].type[1], 2, Instruction);
				CALL_THE_EFUN;
			case F_EFUN3:
				st_num_arg = 3;
				instruction = EXTRACT_UCHAR(pc++);
				CHECK_TYPES(sp - 2, instrs2[instruction].type[0], 1, Instruction);
				CHECK_TYPES(sp - 1, instrs2[instruction].type[1], 2, Instruction);
				CHECK_TYPES(sp, instrs2[instruction].type[2], 3, Instruction);
				CALL_THE_EFUN;
			case F_EFUNV:
				{
					int i, num;
					st_num_arg = EXTRACT_UCHAR(pc++) + num_varargs;
					num_varargs = 0;
					instruction = EXTRACT_UCHAR(pc++);
					num = instrs2[instruction].min_arg;
					for (i = 1; i <= num; i++)
					{
						CHECK_TYPES(sp - st_num_arg + i, instrs2[instruction].type[i - 1], i, Instruction);
					}
					CALL_THE_EFUN;
				}
			default:
				/* optimized 1 arg efun */
				st_num_arg = 1;
				CHECK_TYPES(sp, instrs[instruction].type[0], 1, instruction);
				#ifndef DEBUG
					{
						svalue_t *expect_sp;
						if (instrs[instruction].ret_type == TYPE_NOVALUE)
						{
							expect_sp = sp - st_num_arg;
						}
						else
						{
							expect_sp = sp - st_num_arg + 1;
						}

						(*ooefun_table[instruction]) ();
						if (expect_sp != sp)
						{
							debug_message("Bad stack after efun %s\n", instrs[instruction].name);
						}
					}
					continue;
				#else 
					instruction -= ONEARG_MAX;
					call_the_efun: 
					/* We have an efun.  Execute it
					 */
					if (Instruction > NUM_OPCODES) {
						fatal("QTZ_SE:Undefined instruction %s (%d)\n", get_f_name(Instruction), Instruction);
					}
					if (Instruction < BASE) {
						fatal("QTZ_SE:No case for eoperator %s (%d)\n", get_f_name(Instruction), Instruction);
					}
					if (instrs2[instruction].ret_type == TYPE_NOVALUE) {
						expected_stack = sp - st_num_arg;
					} else {
						expected_stack = sp - st_num_arg + 1;
					}
					num_arg = st_num_arg;

					(*oefun_table[instruction]) ();
					if (expected_stack != sp) {
						fatal("QTZ_SE:Bad stack after efun. Instruction %d, num arg %d\n", instruction, num_arg);
					}
				#endif 
		} /* switch (instruction) */
		DEBUG_CHECK1(sp < fp + csp->num_local_variables - 1, "QTZ_SE:Bad stack after evaluation. Instruction %d\n", instruction);
	} /* while (1) */
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

static void do_catch(char *pc)
{
	error_context_t econ;

	/*
	 * Save some global variables that must be restored separately after a
	 * longjmp. The stack will have to be manually popped all the way.
	 */
	if (!save_context(&econ) )
	{
		error("QTZ_SE:Can't catch too deep recursion error.\n");
	}
	push_control_stack(FRAME_CATCH);
	#if defined(DEBUG) || defined(TRACE_CODE)
		csp->num_local_variables = (csp - 1)->num_local_variables; /* marion */
	#endif 

	if (SETJMP(econ.context) )
	{
		/*
		 * They did a throw() or error. That means that the control stack
		 * must be restored manually here.
		 */
		restore_context(&econ);
		sp++;
		*sp = catch_value;
		catch_value = const1;

		/* if it's too deep or max eval, we can't let them catch it */
		if (max_eval_error)
		{
			pop_context(&econ);
			error("QTZ_SE:Can't catch eval cost too big error.\n");
		}
		if (too_deep_error)
		{
			pop_context(&econ);
			error("QTZ_SE:Can't catch too deep recursion error.\n");
		}
	}
	else
	{
		assign_svalue(&catch_value, &const1);
		/* note, this will work, since csp->extern_call won't be used */
		eval_instruction(pc);
	}
	pop_context(&econ);
}

/*
 * Apply a fun 'fun' to the program in object 'ob', with
 * 'num_arg' arguments (already pushed on the stack).
 * If the fun is not found, search in the object pointed to by the
 * inherit pointer.
 * If the fun name starts with '::', search in the object pointed out
 * through the inherit pointer by the current object. The 'current_object'
 * stores the base object, not the object that has the current fun being
 * evaluated. Thus, the variable current_prog will normally be the same as
 * current_object->prog, but not when executing inherited code. Then,
 * it will point to the code of the inherited object. As more than one
 * object can be inherited, the call of fun by index number has to
 * be adjusted. The fun number 0 in a superclass object must not remain
 * number 0 when it is inherited from a subclass object. The same problem
 * exists for variables. The global variables function_index_offset and
 * variable_index_offset keep track of how much to adjust the index when
 * executing code in the superclass objects.
 *
 * There is a special case when called from the heart beat, as
 * current_prog will be 0. When it is 0, set current_prog
 * to the 'ob->prog' sent as argument.
 *
 * Arguments are always removed from the stack.
 * If the fun is not found, return 0 and nothing on the stack.
 * Otherwise, return 1, and a pushed return value on the stack.
 *
 * Note that the object 'ob' can be destructed. This must be handled by
 * the caller of apply().
 *
 * If the fun failed to be called, then arguments must be deallocated
 * manually !  (Look towards end of this fun.)
 */

#ifdef DEBUG
	static char debug_apply_fun[30]; /* For debugging */
#endif 

#ifdef CACHE_STATS
	unsigned int apply_low_call_others = 0;
	unsigned int apply_low_cache_hits = 0;
	unsigned int apply_low_slots_used = 0;
	unsigned int apply_low_collisions = 0;
#endif 

typedef struct cache_entry_s
{
	int id;
	program_t *oprogp;
	program_t *progp;
	int index; /* index into progp's function_table */
	char *name;
	unsigned short num_arg, num_local;
	int function_index_offset;
	int variable_index_offset;
} cache_entry_t;

static cache_entry_t cache[APPLY_CACHE_SIZE];

#ifdef DEBUGMALLOC_EXTENSIONS
	void mark_apply_low_cache()
	{
		int i;
		for (i = 0; i < APPLY_CACHE_SIZE; i++)
		{
			if (cache[i].id && !cache[i].progp)
			{
				EXTRA_REF(BLOCK(cache[i].name) )++;
			}
		}
	}
#endif 

static program_t *ffbn_recurse(program_t *, char *, int *, int*);

INLINE_STATIC program_t *find_function_by_name(object_t *ob, char *name, int *index, int *runtime_index)
{
	char *funname = findstring(name);

	if (!funname)
	{
		return 0;
	}
	return ffbn_recurse(ob->prog, funname, index, runtime_index);
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

program_t *find_function_by_name2(object_t *ob, char **name, int *index, int *fio, int *vio)
{
	*name = findstring(*name);

	if (! *name)
	{
		return 0;
	}
	return ffbn_recurse2(ob->prog,  *name, index, fio, vio);
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

int apply_low(const char *fun, object_t *ob, int num_arg)
{
	/*
	 * static memory is initialized to zero by the system or so Jacques says
	 * :)
	 */
	char *sfun;
	cache_entry_t *entry;
	program_t *progp,  *prog;
	int ix, fio, vio;
	static int cache_mask = APPLY_CACHE_SIZE - 1;
	int local_call_origin = call_origin;
	IF_DEBUG(control_stack_t *save_csp);

	if (!local_call_origin)
	{
		local_call_origin = ORIGIN_DRIVER;
	}
	call_origin = 0;
	ob->time_of_ref = current_time; /* Used by the swapper */
	/*
	 * This object will now be used, and is thus a target for reset later on
	 * (when time due).
	 */
	ob->flags &= ~O_RESET_STATE;
	#ifdef DEBUG
		strncpy(debug_apply_fun, fun, sizeof(debug_apply_fun) );
		debug_apply_fun[sizeof debug_apply_fun - 1] = '\0';
	#endif 
	#ifdef _USE_SWAP_H_
	if (ob->flags &O_SWAPPED)
	{
		load_ob_from_swap(ob);
	}
	#endif

	progp = ob->prog;
	DEBUG_CHECK(ob->flags &O_DESTRUCTED, "apply() on destructed object\n");
	#ifdef CACHE_STATS
		apply_low_call_others++;
	#endif 
	ix = (progp->id_number ^ (POINTER_INT)fun ^ ( (POINTER_INT)fun >> APPLY_CACHE_BITS) ) &cache_mask;
	entry = &cache[ix];
	if ( (entry->id == progp->id_number) && (entry->oprogp == progp) && (strcmp(entry->name, fun) == 0) )
	{
		#ifdef CACHE_STATS
			apply_low_cache_hits++;
		#endif 
		if (entry->progp)
		{
			compiler_function_t *funp = entry->progp->function_table + entry->index;
			int funflags = entry->oprogp->function_flags[funp->runtime_index + entry->function_index_offset];

			/* if progp is zero, the cache is telling us the fun isn't here*/
			if (!(funflags &(NAME_STATIC | NAME_PRIVATE) ) || current_object == ob || (local_call_origin &(ORIGIN_DRIVER | ORIGIN_CALL_OUT) ) )
			{
				/*
				 * the cache will tell us in which program the fun is,
				 * and where
				 */
				push_control_stack(FRAME_FUNCTION | FRAME_OB_CHANGE);
				current_prog = entry->progp;
				caller_type = local_call_origin;
				csp->num_local_variables = num_arg;
				function_index_offset = entry->function_index_offset;
				variable_index_offset = entry->variable_index_offset;

				csp->fr.table_index = entry->index;
				#ifdef PROFILE_FUNCTIONS
					get_cpu_times(&(csp->entry_secs), &(csp->entry_usecs) );
					current_prog->function_table[entry->index].calls++;
				#endif 

				if (funflags &NAME_TRUE_VARARGS)
				{
					setup_varargs_variables(csp->num_local_variables, entry->num_local, entry->num_arg);
				}
				else
				{
					setup_variables(csp->num_local_variables, entry->num_local, entry->num_arg);
				}

				previous_ob = current_object;
				current_object = ob;
				IF_DEBUG(save_csp = csp);
				call_program(current_prog, funp->address);

				DEBUG_CHECK(save_csp - 1 != csp, "QTZ_SE:Bad csp after execution in apply_low.\n");
				return 1;
			}
		} /* when we come here, the cache has told us
		 * that the fun isn't defined in the
		 * object */
	}
	else
	{
		int index;
		/* we have to search the fun */

		/* The old entry was for a nonexistent fun and had to be allocated */
		if (!entry->progp && entry->id)
		{
			free_string(entry->name);
		}
		#ifdef CACHE_STATS
			if (!entry->id)
			{
				apply_low_slots_used++;
			}
			else
			{
				apply_low_collisions++;
			}
		#endif 
			sfun = (char *)fun;
		prog = find_function_by_name2(ob, &sfun, &index, &fio, &vio);
		if (prog)
		{
			compiler_function_t *funp = &prog->function_table[index];
			runtime_defined_t *fundefp = &(FIND_FUNC_ENTRY(prog, funp->runtime_index)->def);
			int funflags = ob->prog->function_flags[funp->runtime_index + fio];

			if (!(funflags &(NAME_STATIC | NAME_PRIVATE) ) || current_object == ob || (local_call_origin &(ORIGIN_DRIVER | ORIGIN_CALL_OUT) ) )
			{
				push_control_stack(FRAME_FUNCTION | FRAME_OB_CHANGE);
				current_prog = prog;
				caller_type = local_call_origin;
				/* The searched fun is found */
				entry->oprogp = ob->prog;
				entry->id = progp->id_number;
				entry->name = sfun;
				entry->index = index;
				csp->fr.table_index = index;
				csp->num_local_variables = num_arg;
				entry->variable_index_offset = variable_index_offset = vio;
				entry->function_index_offset = function_index_offset = fio;
				if (funflags &NAME_TRUE_VARARGS)
				{
					setup_varargs_variables(csp->num_local_variables, fundefp->num_local, fundefp->num_arg);
				}
				else
				{
					setup_variables(csp->num_local_variables, fundefp->num_local, fundefp->num_arg);
				}
				entry->num_arg = fundefp->num_arg;
				entry->num_local = fundefp->num_local;
				entry->progp = current_prog;
				previous_ob = current_object;
				current_object = ob;
				IF_DEBUG(save_csp = csp);
				call_program(current_prog, funp->address);

				DEBUG_CHECK(save_csp - 1 != csp, "Bad csp after execution in apply_low\n");
				/*
				 * Arguments and local variables are now removed. One
				 * resulting value is always returned on the stack.
				 */
				return 1;
			}
		}
		/* We have to mark a fun not to be in the object */
		entry->id = progp->id_number;
		entry->oprogp = progp;
		if (sfun)
		{
			ref_string(sfun);
			entry->name = sfun;
		}
		else
		{
			entry->name = make_shared_string(fun);
		}
		entry->progp = (program_t*)0;
	}
	/* Failure. Deallocate stack. */
	pop_n_elems(num_arg);
	return 0;
}

/*
 * Arguments are supposed to be
 * pushed (using push_string() etc) before the call. A pointer to a
 * 'svalue_t' will be returned. It will be a null pointer if the called
 * fun was not found. Otherwise, it will be a pointer to a static
 * area in apply(), which will be overwritten by the next call to apply.
 * Reference counts will be updated for this value, to ensure that no pointers
 * are deallocated.
 */

svalue_t *apply(const char *fun, object_t *ob, int num_arg, int where)
{
	IF_DEBUG(svalue_t *expected_sp);

	tracedepth = 0;
	call_origin = where;


	IF_DEBUG(expected_sp = sp - num_arg);
	if (apply_low(fun, ob, num_arg) == 0)
	{
		return 0;
	}
	free_svalue(&apply_ret_value, "sapply");
	apply_ret_value =  *sp--;
	DEBUG_CHECK(expected_sp != sp, "Corrupt stack pointer.\n");
	return  &apply_ret_value;
}

/* Reason for the following 1. save cache space 2. speed :) */
/* The following is to be called only from reset_object for */
/* otherwise extra checks are needed - Sym				  */

void call___INIT(object_t *ob)
{
	program_t *progp;
	compiler_function_t *cfp;
	int num_functions;
	IF_DEBUG(svalue_t *expected_sp);
	IF_DEBUG(control_stack_t *save_csp);

	tracedepth = 0;

	IF_DEBUG(expected_sp = sp);

	/* No try_reset here for obvious reasons :) */

	ob->flags &= ~O_RESET_STATE;

	progp = ob->prog;
	num_functions = progp->num_functions_defined;
	if (!num_functions) {
		return ;
	}

	/* ___INIT turns out to be always the last fun */
	cfp = &progp->function_table[num_functions - 1];
	if (cfp->name[0] != APPLY___INIT_SPECIAL_CHAR) {
		return ;
	}
	push_control_stack(FRAME_FUNCTION | FRAME_OB_CHANGE);
	current_prog = progp;
	csp->fr.table_index = num_functions - 1;
	caller_type = ORIGIN_DRIVER;
	csp->num_local_variables = 0;

	setup_new_frame(cfp->runtime_index);
	previous_ob = current_object;

	current_object = ob;
	IF_DEBUG(save_csp = csp);
	call_program(current_prog, cfp->address);

	DEBUG_CHECK(save_csp - 1 != csp, "QTZ_SE:Bad csp after execution in apply_low\n");
	sp--;
	DEBUG_CHECK(expected_sp != sp, "QTZ_SE:Corrupt stack pointer.\n");
}

/*
 * this is a "safe" version of apply
 * this allows you to have dangerous driver QTZ_SElib dependencies
 * and not have to worry about causing serious bugs when errors occur in the
 * applied fun and the driver depends on being able to do something
 * after the apply. (such as the ed exit fun, and the net_dead fun).
 * note: this fun uses setjmp() and thus is fairly expensive when
 * compared to a normal apply().  Use sparingly.
 */

svalue_t *safe_apply(const char *fun, object_t *ob, int num_arg, int where)
{
	svalue_t *ret;
	error_context_t econ;

	if (!save_context(&econ) )
	{
		return 0;
	}
	if (!SETJMP(econ.context) )
	{
		if (!(ob->flags &O_DESTRUCTED) )
		{
			ret = apply(fun, ob, num_arg, where);
		}
		else
		{
			ret = 0;
		}
	}
	else
	{
		restore_context(&econ);
		pop_n_elems(num_arg);
		ret = 0;
	}
	pop_context(&econ);
	return ret;
}

/*
 * Call a fun in all objects in a array.
 */
array_t *call_all_other(array_t *v, char *func, int numargs)
{
	int size;
	svalue_t *tmp,  *vptr,  *rptr;
	array_t *ret;
	object_t *ob;
	int i;

	tmp = sp;
	(++sp)->type = T_ARRAY;
	sp->u.arr = ret = allocate_array(size = v->size);
	if (size && (sp + numargs >= end_of_stack) )
	{
		too_deep_error = 1;
		error("QTZ_SE:stack overflow\n");
	}
	for (vptr = v->item, rptr = ret->item; size--; vptr++, rptr++)
	{
		if (vptr->type == T_OBJECT)
		{
			ob = vptr->u.ob;
		}
		else if (vptr->type == T_STRING)
		{
			ob = find_object(vptr->u.string);
			if (!ob || !object_visible(ob) )
			{
				continue;
			}
		}
		else
		{
			continue;
		}
		if (ob->flags &O_DESTRUCTED)
		{
			continue;
		}
		i = numargs;
		while (i--)
		{
			push_svalue(tmp - i);
		}
		call_origin = ORIGIN_CALL_OTHER;
		if (apply_low(func, ob, numargs) )
		{
			 *rptr =  *sp--;
		}
	}
	sp--;
	pop_n_elems(numargs);
	return ret;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

static program_t *ffbn_recurse(program_t *prog, char *name, int *index, int *runtime_index)
{
	int high = prog->num_functions_defined - 1;
	int low = 0;
	int i;

	/* Search our fun table */
	while (high >= low)
	{
		int mid = (high + low) / 2;
		char *p = prog->function_table[mid].name;

		if (name < p)
		{
			high = mid - 1;
		}
		else if (name > p)
		{
			low = mid + 1;
		}
		else
		{
			int ridx = prog->function_table[mid].runtime_index;
			int flags = prog->function_flags[ridx];
			if (flags &(NAME_UNDEFINED | NAME_PROTOTYPE) )
			{
				if (flags &NAME_INHERITED)
				{
					break;
				}
				return 0;
			}
			*index = mid;
			*runtime_index = prog->function_table[mid].runtime_index;
			return prog;
		}
	}

	/* Search inherited fun tables */
	i = prog->num_inherited;
	while (i--)
	{
		program_t *ret = ffbn_recurse(prog->inherit[i].prog, name, index, runtime_index);
		if (ret)
		{
			*runtime_index += prog->inherit[i].function_index_offset;
			return ret;
		}
	}
	return 0;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

static program_t *ffbn_recurse2(program_t *prog, char *name, int *index, int *fio, int *vio)
{
	int high = prog->num_functions_defined - 1;
	int low = 0;
	int i;

	/* Search our fun table */
	while (high >= low)
	{
		int mid = (high + low) / 2;
		char *p = prog->function_table[mid].name;

		if (name < p)
		{
			high = mid - 1;
		}
		else if (name > p)
		{
			low = mid + 1;
		}
		else
		{
			/* TODO: as an optimization, we could use this entry to
			 * find the real one, but that requires backtracking all
			 * the way up to the top level and back down again.
			 *
			 * Instead, for now, we just continue searching.  No need to
			 * check the things we inherit, though.
			 *
			 * NAME_INHERITED is possible in the case of prototype slots that
			 * are later replaced by inherited functions.  We could optimize
			 * this one fairly easily, but it probably isn't worth checking
			 * for separately as it is very rare in normal LPC code (since
			 * very little if anything usually precedes inherits).
			 */
			int ridx = prog->function_table[mid].runtime_index;
			int flags = prog->function_flags[ridx];
			if (flags &(NAME_UNDEFINED | NAME_PROTOTYPE | NAME_INHERITED) )
			{
				if (flags &NAME_INHERITED)
				{
					break;
				}
				return 0;
			}
			*index = mid;
			*fio = 0;
			*vio = 0;
			return prog;
		}
	}

	/* Search inherited fun tables */
	i = prog->num_inherited;
	while (i--)
	{
		program_t *ret = ffbn_recurse2(prog->inherit[i].prog, name, index, fio, vio);
		if (ret)
		{
			*fio += prog->inherit[i].function_index_offset;
			*vio += prog->inherit[i].variable_index_offset;
			return ret;
		}
	}
	return 0;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

char *function_name(program_t *prog, int index)
{
	runtime_function_u *func_entry = FIND_FUNC_ENTRY(prog, index);

	while (prog->function_flags[index] &NAME_INHERITED)
	{
		prog = prog->inherit[func_entry->inh.offset].prog;
		index = func_entry->inh.function_index_offset;
		func_entry = FIND_FUNC_ENTRY(prog, index);
	}

	return prog->function_table[func_entry->def.f_index].name;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

void get_trace_details(program_t *prog, int index, char **fname, int *na, int *nl)
{
	compiler_function_t *cfp = &prog->function_table[index];
	runtime_function_u *func_entry = FIND_FUNC_ENTRY(prog, cfp->runtime_index);

	*fname = cfp->name;
	*na = func_entry->def.num_arg;
	*nl = func_entry->def.num_local;
}

/*
 * This fun is similar to apply(), except that it will not
 * call the fun, only return object name if the fun exists,
 * or 0 otherwise.  If flag is nonzero, then we admit static and private
 * functions exist.  Note that if you actually intend to call the fun,
 * it's faster to just try to call it and check if apply() returns zero.
 */
char *function_exists(char *fun, object_t *ob, int flag)
{
	int index, runtime_index;
	program_t *prog;
	compiler_function_t *cfp;

	DEBUG_CHECK(ob->flags &O_DESTRUCTED, "function_exists() on destructed object\n");

	#ifdef _USE_SWAP_H_
	if (ob->flags &O_SWAPPED)
	{
		load_ob_from_swap(ob);
	}
	#endif

	if (fun[0] == APPLY___INIT_SPECIAL_CHAR)
	{
		return 0;
	}

	prog = find_function_by_name(ob, fun, &index, &runtime_index);
	if (!prog)
	{
		return 0;
	}

	cfp = prog->function_table + index;

	if ( (ob->prog->function_flags[runtime_index] &NAME_UNDEFINED) || ( (ob->prog->function_flags[runtime_index] &(NAME_STATIC | NAME_PRIVATE) ) && current_object != ob && !flag) )
	{
		return 0;
	}

	return prog->name;
}


/*
 * Call a specific fun address in an object. This is done with no
 * frame set up. It is expected that there are no arguments. Returned
 * values are removed.
 */
/* used by heart_beat only now; should be looked at and generalized;
possible sefuns? */
void call_function(program_t *progp, int offset)
{
	compiler_function_t *funp;

	if (progp->function_flags[offset] &NAME_UNDEFINED)
	{
		return ;
	}
	push_control_stack(FRAME_FUNCTION | FRAME_OB_CHANGE);
	caller_type = ORIGIN_DRIVER;
	DEBUG_CHECK(csp != control_stack, "call_function with bad csp\n");
	csp->num_local_variables = 0;
	current_prog = progp;
	funp = setup_new_frame(offset);
	previous_ob = current_object;
	current_object = current_heart_beat;
	tracedepth = 0;
	call_program(current_prog, funp->address);
	pop_stack();
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

void translate_absolute_line(int abs_line, unsigned short *file_info, int *ret_file, int *ret_line)
{
	unsigned short *p1,  *p2;
	int file;
	int line_tmp = abs_line;

	/* two passes: first, find out what file we're interested in */
	p1 = file_info;
	while (line_tmp >  *p1)
	{
		line_tmp -=  *p1;
		p1 += 2;
	}
	file = p1[1];

	/* now correct the line number for that file */
	p2 = file_info;
	while (p2 < p1)
	{
		if (p2[1] == file)
		{
			line_tmp +=  *p2;
		}
		p2 += 2;
	}
	*ret_line = line_tmp;
	*ret_file = file;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

int find_line(char *p, program_t *progp, char **ret_file, int *ret_line)
{
	int offset;
	unsigned char *lns;
	unsigned short abs_line;
	int file_idx;

	*ret_file = "";
	*ret_line = 0;

	if (!progp)
	{
		return 1;
	}
	if (progp ==  &fake_prog)
	{
		return 2;
	}

	/*
	 * Load line numbers from swap if necessary.  Leave them in memory until
	 * look_for_objects_to_swap() swaps them back out, since more errors are
	 * likely.
	 */
	if (!progp->line_info)
	{
		load_line_numbers(progp);
		if (!progp->line_info)
		{
			return 4;
		}
	}
	offset = p - progp->program;
	DEBUG_CHECK2(offset > (int)progp->program_size, "Illegal offset %d in object /%s\n", offset, progp->name);

	lns = progp->line_info;
	while (offset >  *lns)
	{
		offset -=  *lns;
		lns += 3;
	}

	COPY_SHORT(&abs_line, lns + 1);

	translate_absolute_line(abs_line, &progp->file_info[2],  &file_idx, ret_line);

	*ret_file = progp->strings[file_idx - 1];
	return 0;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

void get_explicit_line_number_info(char *p, program_t *prog, char **ret_file, int *ret_line)
{
	find_line(p, prog, ret_file, ret_line);
	if (!(*ret_file) )
	{
		*ret_file = prog->name;
	}
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

void get_line_number_info(char **ret_file, int *ret_line)
{
	find_line(pc, current_prog, ret_file, ret_line);
	if (!(*ret_file) )
	{
		*ret_file = current_prog->name;
	}
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

char *get_line_number(char *p, program_t *progp)
{
	static char buf[256];
	int i;
	char *file;
	int line;

	i = find_line(p, progp, &file, &line);

	switch (i)
	{
		case 1:
			strcpy(buf, "(no program)");
			return buf;
		case 2:
			*buf = 0;
			return buf;
		case 3:
			strcpy(buf, "(compiled program)");
			return buf;
		case 4:
			strcpy(buf, "(no line numbers)");
			return buf;
		case 5:
			strcpy(buf, "(includes too deep)");
			return buf;
	}
	if (!file)
	{
		file = progp->name;
	}
	sprintf(buf, "/%s:%d", file, line);
	return buf;
}

/*
 * Write out a trace. If there is a heart_beat(), then return the
 * object that had that heart beat.
 */
char *dump_trace(int how)
{
	control_stack_t *p;
	char *ret = 0;
	char *fname;
	int num_arg =  - 1, num_local =  - 1;

	#if defined(ARGUMENTS_IN_TRACEBACK) || defined(LOCALS_IN_TRACEBACK)
		svalue_t *ptr;
		int i;
	#endif 

	if (current_prog == 0)
	{
		return 0;
	}
	if (csp <  &control_stack[0])
	{
		return 0;
	}
	#ifdef TRACE_CODE
		if (how)
		{
			(void)last_instructions();
		}
	#else 
		(void)how;
	#endif 
	for (p = &control_stack[0]; p < csp; p++)
	{
		switch (p[0].framekind &FRAME_MASK)
		{
			case FRAME_FUNCTION:
				get_trace_details(p[1].prog, p[0].fr.table_index,  &fname, &num_arg, &num_local);
				debug_message("'%15s()' in '%30s' at %s\n",
					fname, p[1].ob->name, get_line_number(p[1].pc, p[1].prog) );
				if (strcmp(fname, "heart_beat") == 0)
				{
					ret = p->ob ? p->ob->name: 0;
				}
				break;
			case FRAME_FUNP:
				debug_message("'<fun>' in '%30s' at %s\n",
						p[1].ob->name, get_line_number(p[1].pc, p[1].prog) );
				num_arg = p[0].fr.funp->f.functional.num_arg;
				num_local = p[0].fr.funp->f.functional.num_local;
				break;
			case FRAME_FAKE:
				/*
				debug_message("'<fun>' in '%30s' at %20s') %s\n",
						p[1].ob->name, get_line_number(p[1].pc, p[1].prog) );
				*/
				debug_message("'<fun>' in '%30s' at %s\n",
						p[1].ob->name, get_line_number(p[1].pc, p[1].prog) );
				num_arg =  - 1;
				break;
			case FRAME_CATCH:
				debug_message("'CATCH' in '%20s' ('%20s') %s\n", 
						p[1].prog->name, p[1].ob->name, get_line_number(p[1].pc, p[1].prog) );
				num_arg =  - 1;
				break;
				#ifdef DEBUG
				default:
					fatal("unknown type of frame\n");
				#endif 
		}
		// by canoe, ??????????????????arguments???locals??????????????????????????????
		/*
		#ifdef ARGUMENTS_IN_TRACEBACK
			if (num_arg !=  - 1) // canoe num_arg >= 1 ?
			{
				ptr = p[1].fp;
				debug_message("arguments were %d(", num_arg );
				for (i = 0; i < num_arg; i++)
				{
					outbuffer_t outbuf;

					if (i)
					{
						debug_message(",");
					}
					outbuf_zero(&outbuf);
					svalue_to_string(&ptr[i], &outbuf, 0, 0, 0);
					debug_message("%s", outbuf.buffer);
					FREE_MSTR(outbuf.buffer);
				}
				debug_message(")\n");
			}
		#endif 
		#ifdef LOCALS_IN_TRACEBACK
			if (num_local > 0 && num_arg !=  - 1)
			{
				ptr = p[1].fp + num_arg;
				debug_message("locals[%d] maybe were: ", num_local); // ???????????????clone?????????object?????????????????????big int. -- canoe
				for (i = 0; i < num_local; i++)
				{
					outbuffer_t outbuf;

					if (i)
					{
						debug_message(",");
					}
					outbuf_zero(&outbuf);
					svalue_to_string(&ptr[i], &outbuf, 0, 0, 0);
					debug_message("%s", outbuf.buffer);
					FREE_MSTR(outbuf.buffer);
				}
				debug_message("\n");
			}
		#endif 
		*/
	}
	switch (p[0].framekind &FRAME_MASK)
	{
		case FRAME_FUNCTION:
			get_trace_details(current_prog, p[0].fr.table_index,  &fname, &num_arg, &num_local);
			debug_message("'%15s()' in '%30s' at %s\n",
					fname, current_object->name, get_line_number(pc, current_prog) );
			break;
		case FRAME_FUNP:
			debug_message("'<fun>' in '%30s' at %s\n",
				current_object->name, get_line_number(pc, current_prog) );
			num_arg = p[0].fr.funp->f.functional.num_arg;
			num_local = p[0].fr.funp->f.functional.num_local;
			break;
		case FRAME_FAKE:
			debug_message("'<fun>' in '%30s' at %s\n",
				current_object->name, get_line_number(pc, current_prog) );
			num_arg =  - 1;
			break;
		case FRAME_CATCH:
			debug_message("'CATCH' in '%30s' at %s\n",
				current_object->name, get_line_number(pc, current_prog) );
			num_arg =  - 1;
			break;
	}
	#ifdef ARGUMENTS_IN_TRACEBACK
		// if (num_arg !=  - 1) -- canoe
		if (num_arg >= 1 )
		{
			debug_message("arguments were (");
			for (i = 0; i < num_arg; i++)
			{
				outbuffer_t outbuf;

				if (i)
				{
					debug_message(",");
				}
				outbuf_zero(&outbuf);
				svalue_to_string(&fp[i], &outbuf, 0, 0, 0);
				/* no need to fix length */
				debug_message("%s", outbuf.buffer);
				FREE_MSTR(outbuf.buffer);
			}
			debug_message(")\n");
		}
	#endif 
	#ifdef LOCALS_IN_TRACEBACK
		if (num_local > 0 && num_arg !=  - 1)
		{
			ptr = fp + num_arg;
			debug_message("locals[%d] maybe were: ", num_local); // ???????????????clone?????????object?????????????????????big int. -- canoe
			for (i = 0; i < num_local; i++)
			{
				outbuffer_t outbuf;

				if (i)
				{
					debug_message(",");
				}
				outbuf_zero(&outbuf);
				svalue_to_string(&ptr[i], &outbuf, 0, 0, 0);
				/* no need to fix length */
				debug_message("%s", outbuf.buffer);
				FREE_MSTR(outbuf.buffer);
			}
			debug_message("\n");
		}
	#endif 
	return ret;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

array_t *get_svalue_trace()
{
	control_stack_t *p;
	array_t *v;
	mapping_t *m;
	char *file;
	int line;
	char *fname;
	int num_arg, num_local;

	#if defined(ARGUMENTS_IN_TRACEBACK) || defined(LOCALS_IN_TRACEBACK)
		svalue_t *ptr;
		int i, n;
		#ifdef LOCALS_IN_TRACEBACK
			int n2;
		#endif 
	#endif 

	if (current_prog == 0)
	{
		return  &the_null_array;
	}
	if (csp <  &control_stack[0])
	{
		return  &the_null_array;
	}
	v = allocate_empty_array( (csp - &control_stack[0]) + 1);
	for (p = &control_stack[0]; p < csp; p++)
	{
		m = allocate_mapping(6);
		switch (p[0].framekind &FRAME_MASK)
		{
			case FRAME_FUNCTION:
				get_trace_details(p[1].prog, p[0].fr.table_index,  &fname, &num_arg, &num_local);
				add_mapping_string(m, "fun", fname);
				break;
			case FRAME_CATCH:
				add_mapping_string(m, "fun", "CATCH");
				num_arg =  - 1;
				break;
			case FRAME_FAKE:
				add_mapping_string(m, "fun", "<fun>");
				num_arg =  - 1;
				break;
			case FRAME_FUNP:
				add_mapping_string(m, "fun", "<fun>");
				num_arg = p[0].fr.funp->f.functional.num_arg;
				num_local = p[0].fr.funp->f.functional.num_local;
				break;
				#ifdef DEBUG
				default:
					fatal("QTZ_SE:unknown type of frame\n");
				#endif 
		}
		add_mapping_string(m, "program", p[1].prog->name);
		add_mapping_object(m, "object", p[1].ob);
		get_explicit_line_number_info(p[1].pc, p[1].prog, &file, &line);
		add_mapping_string(m, "file", file);
		add_mapping_pair(m, "line", line);
		#ifdef ARGUMENTS_IN_TRACEBACK
			if (num_arg !=  - 1)
			{
				array_t *v2;

				n = num_arg;
				ptr = p[1].fp;
				v2 = allocate_empty_array(n);
				for (i = 0; i < n; i++)
				{
					assign_svalue_no_free(&v2->item[i], &ptr[i]);
				}
				add_mapping_array(m, "arguments", v2);
				v2->ref--;
			}
		#endif 
		#ifdef LOCALS_IN_TRACEBACK
			if (num_local > 0 && num_arg !=  - 1)
			{
				array_t *v2;

				n = num_arg;
				n2 = num_local;
				ptr = p[1].fp;
				v2 = allocate_empty_array(n2);
				for (i = 0; i < n2; i++)
				{
					assign_svalue_no_free(&v2->item[i], &ptr[i + n]);
				}
				add_mapping_array(m, "locals", v2);
				v2->ref--;
			}
		#endif 
		v->item[(p - &control_stack[0])].type = T_MAPPING;
		v->item[(p - &control_stack[0])].u.map = m;
	}
	m = allocate_mapping(6);
	switch (p[0].framekind &FRAME_MASK)
	{
		case FRAME_FUNCTION:
			get_trace_details(current_prog, p[0].fr.table_index,  &fname, &num_arg, &num_local);
			add_mapping_string(m, "fun", fname);
			break;
		case FRAME_CATCH:
			add_mapping_string(m, "fun", "CATCH");
			num_arg =  - 1;
			break;
		case FRAME_FAKE:
			add_mapping_string(m, "fun", "<fun>");
			num_arg =  - 1;
			break;
		case FRAME_FUNP:
			add_mapping_string(m, "fun", "<fun>");
			num_arg = p[0].fr.funp->f.functional.num_arg;
			num_local = p[0].fr.funp->f.functional.num_local;
			break;
	}
	add_mapping_string(m, "program", current_prog->name);
	add_mapping_object(m, "object", current_object);
	get_line_number_info(&file, &line);
	add_mapping_string(m, "file", file);
	add_mapping_pair(m, "line", line);
	#ifdef ARGUMENTS_IN_TRACEBACK
		if (num_arg !=  - 1)
		{
			array_t *v2;

			n = num_arg;
			v2 = allocate_empty_array(n);
			for (i = 0; i < n; i++)
			{
				assign_svalue_no_free(&v2->item[i], &fp[i]);
			}
			add_mapping_array(m, "arguments", v2);
			v2->ref--;
		}
	#endif 
	#ifdef LOCALS_IN_TRACEBACK
		if (num_local > 0 && num_arg !=  - 1)
		{
			array_t *v2;

			n = num_arg;
			n2 = num_local;
			v2 = allocate_empty_array(n2);
			for (i = 0; i < n2; i++)
			{
				assign_svalue_no_free(&v2->item[i], &fp[i + n]);
			}
			add_mapping_array(m, "locals", v2);
			v2->ref--;
		}
	#endif 
	v->item[(csp - &control_stack[0])].type = T_MAPPING;
	v->item[(csp - &control_stack[0])].u.map = m;
	/* return a reference zero array */
	v->ref--;
	return v;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

char *get_line_number_if_any()
{
	if (current_prog)
	{
		return get_line_number(pc, current_prog);
	}
	return 0;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

#define SSCANF_ASSIGN_SVALUE_STRING(S) \
arg->type = T_STRING; \
arg->u.string = S; \
arg->subtype = STRING_MALLOC; \
arg--; \
num_arg--

#define SSCANF_ASSIGN_SVALUE_NUMBER(N) \
arg->type = T_NUMBER; \
arg->subtype = 0; \
arg->u.number = N; \
arg--; \
num_arg--

#define SSCANF_ASSIGN_SVALUE(T,U,V) \
arg->type = T; \
arg->U = V; \
arg--; \
num_arg--

/* arg points to the same place it used to */
int inter_sscanf(svalue_t *arg, svalue_t *s0, svalue_t *s1, int num_arg)
{
	char *fmt; /* Format description */
	char *in_string; /* The string to be parsed. */
	int number_of_matches;
	int skipme; /* Encountered a '*' ? */
	int base = 10;
	int num;
	char *match, old_char;
	register char *tmp;

	/*
	 * First get the string to be parsed.
	 */
	CHECK_TYPES(s0, T_STRING, 1, F_SSCANF);
	in_string = s0->u.string;

	/*
	 * Now get the format description.
	 */
	CHECK_TYPES(s1, T_STRING, 2, F_SSCANF);
	fmt = s1->u.string;

	/*
	 * Loop for every % or substring in the format.
	 */
	for (number_of_matches = 0; num_arg >= 0; number_of_matches++)
	{
		while (*fmt)
		{
			if (*fmt == '%')
			{
				if (*++fmt == '%')
				{
					if (*in_string++ != '%')
					{
						return number_of_matches;
					}
					fmt++;
					continue;
				}
				if (! *fmt)
				{
					error("QTZ_SE:Format string cannot end in '%%' in sscanf()\n");
				}
				break;
			}
			if (*fmt++ !=  *in_string++)
			{
				return number_of_matches;
			}
		}

		if (! *fmt)
		{
			/*
			 * We have reached the end of the format string.  If there are
			 * any chars left in the in_string, then we put them in the
			 * last variable (if any).
			 */
			if (*in_string && num_arg)
			{
				number_of_matches++;
				SSCANF_ASSIGN_SVALUE_STRING(string_copy(in_string, "sscanf") );
			}
			break;
		}
		DEBUG_CHECK(fmt[ - 1] != '%', "In sscanf, should be a %% now!\n");

		if ( (skipme = (*fmt == '*') ) )
		{
			fmt++;
		}
		else if (num_arg < 1 &&  *fmt != '%')
		{
			/*
			 * Hmm ... maybe we should return number_of_matches here instead
			 * of an error
			 */
			error("QTZ_SE:Too few arguments to sscanf()\n");
		}

		switch (*fmt++)
		{
			case 'x':
				base = 16;
				/* fallthrough */
			case 'd':
				{
					tmp = in_string;
					num = (int)strtol(in_string, &in_string, base);
					if (tmp == in_string)
					{
						return number_of_matches;
					}
					if (!skipme)
					{
						SSCANF_ASSIGN_SVALUE_NUMBER(num);
					}
					base = 10;
					continue;
				}
			case 'f':
				{
					float tmp_num;

					tmp = in_string;
					tmp_num = _strtof(in_string, &in_string);
					if (tmp == in_string)
					{
						return number_of_matches;
					}
					if (!skipme)
					{
						SSCANF_ASSIGN_SVALUE(T_REAL, u.real, tmp_num);
					}
					continue;
				}
			case '(':
				{
					struct regexp *reg;

					tmp = fmt; /* 1 after the ( */
					num = 1;
					while (1)
					{
						switch (*tmp)
						{
						case '\\':
							if (*++tmp)
							{
								tmp++;
								continue;
							}
						case '\0':
							error("QTZ_SE:Bad regexp format: '%%%s' in sscanf format string\n", fmt);
						case '(':
							num++;
							/* FALLTHROUGH */
						default:
							tmp++;
							continue;
						case ')':
							if (!--num)
							{
								break;
							}
							tmp++;
							continue;
						}
						{
							int n = tmp - fmt;
							char *buf = (char*)DXALLOC(n + 1, TAG_TEMPORARY, "sscanf regexp");
							memcpy(buf, fmt, n);
							buf[n] = 0;
							reg = _regcomp( (unsigned char*)buf, 0);
							FREE(buf);
							if (!reg)
							{
								error(regexp_error);
							}
							if (!_regexec(reg, in_string) || (in_string != reg->startp[0]) )
							{
								return number_of_matches;
							}
							if (!skipme)
							{
								n =  *reg->endp - in_string;
								buf = new_string(n, "sscanf regexp return");
								memcpy(buf, in_string, n);
								buf[n] = 0;
								SSCANF_ASSIGN_SVALUE_STRING(buf);
							}
							in_string =  *reg->endp;
							FREE( (char*)reg);
							fmt = ++tmp;
							break;
						}
					}
					continue;
				}
			case 's':
				break;
			default:
				error("QTZ_SE:Bad type : '%%%c' in sscanf() format string\n", fmt[ - 1]);
		}

		/*
		 * Now we have the string case.
		 */

		/*
		 * First case: There were no extra characters to match. Then this is
		 * the last match.
		 */
		if (! *fmt)
		{
			number_of_matches++;
			if (!skipme)
			{
				SSCANF_ASSIGN_SVALUE_STRING(string_copy(in_string, "sscanf") );
			}
			break;
		}
		/*
		 * If the next char in the format string is a '%' then we have to do
		 * some special checks. Only %d, %f, %x, %(regexp) and %% are allowed
		 * after a %s
		 */
		if (*fmt++ == '%')
		{
			int skipme2;

			tmp = in_string;
			if ( (skipme2 = (*fmt == '*') ) )
			{
				fmt++;
			}
			if (num_arg < (!skipme + !skipme2) &&  *fmt != '%')
			{
				error("QTZ_SE:Too few arguments to sscanf().\n");
			}

			number_of_matches++;

			switch (*fmt++)
			{
				case 's':
					error("QTZ_SE:Illegal to have 2 adjacent %%s's in format string in sscanf()\n");
				case 'x':
					do
					{
						while (*tmp && (*tmp != '0') )tmp++;
						if (*tmp == '0')
						{
							if ( (tmp[1] == 'x' || tmp[1] == 'X') && isxdigit(tmp[2]) )
							{
								break;
							}
							tmp += 2;
						}
					}
					while (*tmp)
						;
					break;
				case 'd':
					while (*tmp && !isdigit(*tmp) )
					{
						tmp++;
					}
					break;
				case 'f':
					while (*tmp && !isdigit(*tmp) && (*tmp != '.' || !isdigit(tmp[1]) ) )
					{
						tmp++;
					}
					break;
				case '%':
					while (*tmp && (*tmp != '%') )
					{
						tmp++;
					}
					break;
				case '(':
					{
						struct regexp *reg;

						tmp = fmt;
						num = 1;
						while (1)
						{
							switch (*tmp)
							{
							case '\\':
								if (*++tmp)
								{
									tmp++;
									continue;
								}
							case '\0':
								error("QTZ_SE:Bad regexp format : '%%%s' in sscanf format string\n", fmt);
							case '(':
								num++;
								/* FALLTHROUGH */
							default:
								tmp++;
								continue;

							case ')':
								if (!--num)
								{
									break;
								}
								tmp++;
								continue;
							}
							{
								int n = tmp - fmt;
								char *buf = (char*)DXALLOC(n + 1, TAG_TEMPORARY, "sscanf regexp");
								memcpy(buf, fmt, n);
								buf[n] = 0;
								reg = _regcomp( (unsigned char*)buf, 0);
								FREE(buf);
								if (!reg)
								{
									error(regexp_error);
								}
								if (!_regexec(reg, in_string) )
								{
									if (!skipme)
									{
										SSCANF_ASSIGN_SVALUE_STRING(string_copy(in_string, "sscanf") );
									}
									FREE( (char*)reg);
									return number_of_matches;
								}
								else
								{
									if (!skipme)
									{
										match = new_string(num = (*reg->startp - in_string), "inter_sscanf");
										memcpy(match, in_string, num);
										match[num] = 0;
										SSCANF_ASSIGN_SVALUE_STRING(match);
									}
									in_string =  *reg->endp;
									if (!skipme2)
									{
										match = new_string(num = (*reg->endp -  *reg->startp), "inter_sscanf");
										memcpy(match,  *reg->startp, num);
										match[num] = 0;
										SSCANF_ASSIGN_SVALUE_STRING(match);
									}
									FREE( (char*)reg);
								}
								fmt = ++tmp;
								break;
							}
						}
						continue;
					}

				case 0:
					error("QTZ_SE:Format string can't end in '%%'.\n");
				default:
					error("QTZ_SE:Bad type : '%%%c' in sscanf() format string\n", fmt[ - 1]);
			}

			if (!skipme)
			{
				match = new_string(num = (tmp - in_string), "inter_sscanf");
				memcpy(match, in_string, num);
				match[num] = 0;
				SSCANF_ASSIGN_SVALUE_STRING(match);
			}
			if (!*(in_string = tmp) )
			{
				return number_of_matches;
			}
			switch (fmt[ - 1])
			{
				case 'x':
					base = 16;
				case 'd':
					{
						num = (int)strtol(in_string, &in_string, base);
						/* We already knew it would be matched - Sym */
						if (!skipme2)
						{
							SSCANF_ASSIGN_SVALUE_NUMBER(num);
						}
						base = 10;
						continue;
					}
				case 'f':
					{
						float tmp_num = _strtof(in_string, &in_string);
						if (!skipme2)
						{
							SSCANF_ASSIGN_SVALUE(T_REAL, u.real, tmp_num);
						}
						continue;
					}
				case '%':
					in_string++;
					continue; /* on the big for loop */
			}
		}
		if ( (tmp = strchr(fmt, '%') ) != NULL)
		{
			num = tmp - fmt + 1;
		}
		else
		{
			tmp = fmt + (num = strlen(fmt) );
			num++;
		}

		old_char =  *--fmt;
		match = in_string;

		/* This loop would be even faster if it used replace_string's skiptable
		algorithm.  Maybe that algorithm should be lifted so it can be
		used in strsrch as well has here, etc? */
		while (*in_string)
		{
			if ( (*in_string == old_char) && !strncmp(in_string, fmt, num) )
			{
				/*
				 * Found a match !
				 */
				if (!skipme)
				{
					char *newmatch;

					newmatch = new_string(skipme = (in_string - match), "inter_sscanf");
					memcpy(newmatch, match, skipme);
					newmatch[skipme] = 0;
					SSCANF_ASSIGN_SVALUE_STRING(newmatch);
				}
				in_string += num;
				fmt = tmp; /* advance fmt to next % */
				break;
			}
			in_string++;
		}
		if (fmt == tmp)
		 /* If match, then do continue. */
		{
			continue;
		}

		/*
		 * No match was found. Then we stop here, and return the result so
		 * far !
		 */
		break;
	}
	return number_of_matches;
}

/* dump # of times each efun has been used */
#ifdef OPCPROF
	void opcdump(char *tfn)
	{
		int i, len, limit;
		char tbuf[SMALL_STRING_SIZE],  *fn;
		FILE *fp;

		if ( (len = strlen(tfn) ) >= (SMALL_STRING_SIZE - 7) )
		{
			error("QTZ_SE:Path '%s' too long.\n", tfn);
			return ;
		}
		strcpy(tbuf, tfn);
		strcpy(tbuf + len, ".efun");
		fn = check_valid_path(tbuf, current_object, "opcprof", 1);
		if (!fn)
		{
			error("QTZ_SE:Invalid path '%s' for writing.\n", tbuf);
			return ;
		}
		fp = fopen(fn, "w");
		if (!fp)
		{
			error("QTZ_SE:Unable to open %s.\n", fn);
			return ;
		}
		limit = sizeof(opc_efun) / sizeof(opc_t);
		for (i = 0; i < limit; i++)
		{
			fprintf(fp, "%-30s: %10d\n", opc_efun[i].name, opc_efun[i].count);
		}
		fclose(fp);

		strcpy(tbuf, tfn);
		strcpy(tbuf + len, ".eoper");
		fn = check_valid_path(tbuf, current_object, "opcprof", 1);
		if (!fn)
		{
			error("QTZ_SE:Invalid path '%s' for writing.\n", tbuf);
			return ;
		}
		fp = fopen(fn, "w");
		if (!fp)
		{
			error("QTZ_SE:Unable to open %s for writing.\n", fn);
			return ;
		}
		for (i = 0; i < BASE; i++)
		{
			fprintf(fp, "%-30s: %10d\n", query_instr_name(i), opc_eoper[i]);
		}
		fclose(fp);
	}
#endif 

/* dump # of times each efun has been used */
#ifdef OPCPROF_2D
	typedef struct
	{
		int op1, op2;
		int num_calls;
	} sort_elem_t;

	int sort_elem_cmp(sort_elem_t *se1, sort_elem_t *se2)
	{
		return se2->num_calls - se1->num_calls;
	}

	void opcdump(char *tfn)
	{
		int ind, i, j, len;
		char tbuf[SMALL_STRING_SIZE],  *fn;
		FILE *fp;
		sort_elem_t ops[(BASE + 1)*(BASE + 1)];

		if ( (len = strlen(tfn) ) >= (SMALL_STRING_SIZE - 10) )
		{
			error("QTZ_SE:Path '%s' too long.\n", tfn);
			return ;
		}
		strcpy(tbuf, tfn);
		strcpy(tbuf + len, ".eop-2d");
		fn = check_valid_path(tbuf, current_object, "opcprof", 1);
		if (!fn)
		{
			error("QTZ_SE:Invalid path '%s' for writing.\n", tbuf);
			return ;
		}
		fp = fopen(fn, "w");
		if (!fp)
		{
			error("QTZ_SE:Unable to open %s for writing.\n", fn);
			return ;
		}
		for (i = 0; i <= BASE; i++)
		{
			for (j = 0; j <= BASE; j++)
			{
				ind = i *(BASE + 1) + j;
				ops[ind].num_calls = opc_eoper_2d[i][j];
				ops[ind].op1 = i;
				ops[ind].op2 = j;
			}
		}
		quickSort( (char*)ops, (BASE + 1)*(BASE + 1), sizeof(sort_elem_t), sort_elem_cmp);
		for (i = 0; i < (BASE + 1)*(BASE + 1); i++)
		{
			if (ops[i].num_calls)
			{
				fprintf(fp, "%-30s %-30s: %10d\n", query_instr_name(ops[i].op1), query_instr_name(ops[i].op2), ops[i].num_calls);
			}
		}
		fclose(fp);
	}
#endif 

/*
 * Reset the virtual stack machine.
 */
void reset_machine(int first)
{
	csp = control_stack - 1;
	if (first)
	{
		sp = &start_of_stack[-1];
	}
	else
	{
		pop_n_elems(sp - start_of_stack + 1);
		IF_DEBUG(stack_in_use_as_temporary = 0);
	}
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

#ifdef TRACE_CODE
	static char *get_arg(int a, int b)
	{
		static char buff[10];
		char *from,  *to;

		from = previous_pc[a];
		to = previous_pc[b];
		if (to - from < 2)
		{
			return "";
		}
		if (to - from == 2)
		{
			sprintf(buff, "%d", from[1]);
			return buff;
		}
		if (to - from == 3)
		{
			short arg;

			COPY_SHORT(&arg, from + 1);
			sprintf(buff, "%d", (int)arg);
			return buff;
		}
		if (to - from == 5)
		{
			int arg;

			COPY_INT(&arg, from + 1);
			sprintf(buff, "%d", arg);
			return buff;
		}
		return "";
	}

	int last_instructions()
	{
		int i;

		i = last;
		do
		{
			if (previous_instruction[i] != 0)
			{
				debug_message("%6x: %3d %8s %-25s (%d)\n", previous_pc[i], previous_instruction[i], get_arg(i, (i + 1) % (sizeof previous_instruction / sizeof(int) ) ), get_f_name(previous_instruction[i]),
  				stack_size[i] + 1);
			}
			i = (i + 1) % (sizeof previous_instruction / sizeof(int) );
		}

		while (i != last);
		return last;
	}

#endif /* TRACE_CODE */


/* If the master object can't be loaded, we return zero. (svalue_t *)-1
 * means that we haven't gotten to loading the master object yet in main.c.
 * In that case, the check should succeed.
 */
svalue_t *apply_master_ob(const char *fun, int num_arg)
{
	IF_DEBUG(svalue_t *expected_sp);

	if (!master_ob)
	{
		pop_n_elems(num_arg);
		return (svalue_t*) - 1;
	}
	call_origin = ORIGIN_DRIVER;

	IF_DEBUG(expected_sp = sp - num_arg);
	if (apply_low(fun, master_ob, num_arg) == 0)
	{
		return 0;
	}
	free_svalue(&apply_ret_value, "sapply");
	apply_ret_value =  *sp--;
	DEBUG_CHECK(expected_sp != sp, "Corrupt stack pointer.\n");
	return  &apply_ret_value;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

svalue_t *safe_apply_master_ob(char *fun, int num_arg)
{
	if (!master_ob)
	{
		pop_n_elems(num_arg);
		return (svalue_t*) - 1;
	}
	return safe_apply(fun, master_ob, num_arg, ORIGIN_DRIVER);
}

/*
 * When an object is destructed, all references to it must be removed
 * from the stack.
 */
void remove_object_from_stack(object_t *ob)
{
	svalue_t *svp;

	for (svp = start_of_stack; svp <= sp; svp++)
	{
		if (svp->type != T_OBJECT)
		{
			continue;
		}
		if (svp->u.ob != ob)
		{
			continue;
		}
		free_object(svp->u.ob, "remove_object_from_stack");
		svp->type = T_NUMBER;
		svp->u.number = 0;
	}
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

int strpref(char *p, char *s)
{
	while (*p)
		if (*p++ !=  *s++)
	    {
			return 0;
	    }
	return 1;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

static float _strtof(char *nptr, char **endptr)
{
	register char *s = nptr;
	register float acc;
	register int neg, c, any, div;

	div = 1;
	neg = 0;
	/*
	 * Skip white space and pick up leading +/- sign if any.
	 */
	do
	{
		c =  *s++;
	}

	while (isspace(c) );
	if (c == '-')
	{
		neg = 1;
		c =  *s++;
	}
	else if (c == '+')
	{
		c =  *s++;
	}

	for (acc = 0, any = 0;; c =  *s++)
	{
		if (isdigit(c) )
		{
			c -= '0';
		}
		else if ( (div == 1) && (c == '.') )
		{
			div = 10;
			continue;
		}
		else
		{
			break;
		}
		if (div == 1)
		{
			acc *= (float)10;
			acc += (float)c;
		}
		else
		{
			acc += (float)c / (float)div;
			div *= 10;
		}
		any = 1;
	}

	if (neg)
	{
		acc =  - acc;
	}

	if (endptr != 0)
	{
		*endptr = any ? s - 1: (char*)nptr;
	}

	return acc;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

#ifdef DEBUGMALLOC_EXTENSIONS
	void mark_stack()
	{
		svalue_t *sv;

		for (sv = start_of_stack; sv <= sp; sv++)
		{
			mark_svalue(sv);
		}
	}
#endif 

/* Be careful.  This assumes there will be a frame pushed right after this,
as we use econ->save_csp + 1 to restore */
int save_context(error_context_t *econ)
{
	if (csp ==  &control_stack[CFG_MAX_CALL_DEPTH - 1])
	{
		/* Attempting to push the frame will give Too deep recursion.
		fail now. */
		return 0;
	}
	econ->save_command_giver = command_giver;
	econ->save_sp = sp;
	econ->save_csp = csp;
	econ->save_context = current_error_context;

	current_error_context = econ;
	return 1;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

void pop_context(error_context_t *econ)
{
	current_error_context = econ->save_context;
}

/* can the error handler do this ? */
void restore_context(error_context_t *econ)
{
	command_giver = econ->save_command_giver;
	DEBUG_CHECK(csp < econ->save_csp, "csp is below econ->csp before unwinding.\n");
	if (csp > econ->save_csp)
	{
		/* Unwind the control stack to the saved position */
		#ifdef PROFILE_FUNCTIONS
			/* PROFILE_FUNCTIONS needs current_prog to be correct in
			pop_control_stack() */
			if (csp > econ->save_csp + 1)
			{
				csp = econ->save_csp + 1;
				current_prog = (csp + 1)->prog;
			}
			else
		#endif 
		{
			csp = econ->save_csp + 1;
		}
		pop_control_stack();
	}
	pop_n_elems(sp - econ->save_sp);
}
