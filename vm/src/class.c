#include "std.h"
#include "lpc_incl.h"


#ifdef CLASS_STATS

int vnum_distinct_classes = 0;
int num_distinct_classes = 0;

#define SUB_CLASS(size) vnum_distinct_classes -= size; num_distinct_classes -= 1;
#define ADD_CLASS(size) vnum_distinct_classes += size; num_distinct_classes += 1;

#else
#define SUB_CLASS(size) 
#define ADD_CLASS(size) 
#endif

void dealloc_class(array_t *p)
{
	int i;

	for (i = p->size; i--;)	{
		free_svalue(&p->item[i], "dealloc_class");
	}
    SUB_CLASS(p->size);
	FREE( (char*)p);
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

void free_class(array_t *p)
{
	if (--(p->ref) > 0)	{
		return ;
	}

	dealloc_class(p);
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

array_t *allocate_class(class_def_t *cld, int has_values)
{
	array_t *p;
	int n = cld->size;

	p = (array_t*)DXALLOC(sizeof(array_t) + sizeof(svalue_t)*(n - 1), TAG_CLASS, "allocate_class");
	p->ref = 1;
	p->size = n;
    ADD_CLASS(n);
	if (has_values)	{
		while (n--)	{
			p->item[n] =  *sp--;
		}
	} else {
		while (n--) {
			p->item[n] = const0u;
		}
	}
	return p;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

array_t *allocate_class_by_size(int size)
{
	array_t *p;

	p = (array_t*)DXALLOC(sizeof(array_t) + sizeof(svalue_t)*(size - 1), TAG_CLASS, "allocate_class");
	p->ref = 1;
	p->size = size;

    ADD_CLASS(size);
	while (size--) {
		p->item[size] = const0u;
	}

	return p;
}

array_t *allocate_empty_class_by_size(int size)
{
	array_t *p;

	p = (array_t *)DXALLOC(sizeof(array_t) + sizeof(svalue_t) * (size - 1), TAG_CLASS, "allocate_class");
	p->ref = 1;
	p->size = size;
    ADD_CLASS(size);

	return p;
}

int add_class_status(outbuffer_t *out, int verbose)
{
#ifdef CLASS_STATS
    int size = num_distinct_classes * (sizeof(array_t) - sizeof(svalue_t)) + vnum_distinct_classes * sizeof(svalue_t);
    outbuf_addv(out, "All Classes:(values num of class :%7d,num of class :%7d)\n", vnum_distinct_classes, num_distinct_classes);
    outbuf_addv(out, "All Classes Size:%7d\n", size);
    return size;
#else
    return 0;
#endif

}
