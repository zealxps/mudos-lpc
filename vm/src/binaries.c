/*
binaries.c: code to save loaded LPC objects to binary files (in order
to speed loading during subsequent runs of the driver).

This is mostly original code by Darin Johnson.  Ideas came from CD,
including crdir_fopen().  Feel free to use this code but please keep
credits intact.
 */

#define SUPPRESS_COMPILER_INLINES
#include "std.h"
#include "lpc_incl.h"
#include "file_incl.h"
#include "compiler.h"
#include "binaries.h"
#include "lex.h"
#include "backend.h"
#include "swap.h"
#include "qsort.h"
#include "compile_file.h"
#include <lpc_hash.h>

#include <time.h>             
#include <string.h>

/* This should be a configure check.  What the heck is it needed for, anyway?*/
#ifdef WIN32
	#include <direct.h>
#endif 

#ifdef BINARIES

	static char *magic_id = "QTZ_ServerEngine";
	static time_t driver_id;
	static time_t config_id;

	char driver_name[512];

	static void patch_out(program_t *, short *, int);
	static void patch_in(program_t *, short *, int);
	static int str_case_cmp(char *, char*);
	static int check_times(time_t, char*);
	static int do_stat(char *, struct stat *, char*);

	char *tmp_gbl_name;
	void comp_debug_message(char *name)
	{
		debug_message("please check : %s %s", tmp_gbl_name, name);
	} 


	/*
	 * stats fname or CONFIG_FILE_DIR/fname (for finding config files) and/or
	 * BIN_DIR/fname (for finding config files and/or driver), whichever exists.
	 */
	static int do_stat(char *fname, struct stat *st, char *pathname)
	{
		int i;
		char buf[256];

		if ( (i = stat(fname, st) ) !=  - 1)
		{
			if (pathname)
			{
				strcpy(pathname, fname);
			}
			return i;
		} 
		/* look in CONFIG_FILE_DIR */
		if (!pathname)
		{
			#ifdef LATTICE
				if (strchr(CONFIG_FILE_DIR, ':') )
				{
					sprintf(buf, "%s%s", CONFIG_FILE_DIR, fname);
				}
				else
			#endif 
			{
				sprintf(buf, "%s/%s", CONFIG_FILE_DIR, fname);
			}
			if ( (i = stat(buf, st) ) !=  - 1)
			{
				return i;
			}
		}
		/* look in BIN_DIR */
		#ifdef LATTICE
			if (strchr(BIN_DIR, ':') )
			{
				sprintf(buf, "%s%s", BIN_DIR, fname);
			}
			else
		#endif 
		{
			sprintf(buf, "%s/%s", BIN_DIR, fname);
		}

		if ( (i = stat(buf, st) ) !=  - 1)
		{
			if (pathname)
			{
				strcpy(pathname, buf);
			}
			return i;
		}
		return  - 1;
	} /* do_stat() */

	void save_binary(program_t *prog, mem_block_t *includes, mem_block_t *patches)
	{
		char file_name_buf[200];
		char *file_name = file_name_buf;
		FILE *f;
		int i, tmp;
		//    short len;
		int len;
		program_t *p;
		struct stat st;

		/*
		svalue_t *ret;
		char *nm;

		nm = add_slash(prog->name);
		push_malloced_string(nm);
		ret = safe_apply_master_ob(APPLY_VALID_SAVE_BINARY, 1);
		if (!MASTER_APPROVED(ret) )
		{
			return ;
		}
		*/
		//    if (prog->total_size > (int) USHRT_MAX ||
		//	includes->current_size > (int) USHRT_MAX)
		/* assume all other sizes ok */
		//	return;

		strcpy(file_name, SAVE_BINARIES);
		if (file_name[0] == '/')
		{
			file_name++;
		}
		if (stat(file_name, &st) ==  - 1)
		{
			return ;
		}
		strcat(file_name, "/");
		strcat(file_name, prog->name);
		len = strlen(file_name);

		file_name[len - 1] = 'b'; /* change .c ending to .b */

		if (!(f = crdir_fopen(file_name) ) )
		{
			return ;
		}

		if (comp_flag)
		{
			debug_message(" saving binary ... ");
			#ifdef LATTICE
				fflush(stderr);
			#endif 
		} 
		/*
		 * Write out preamble.  Includes magic number, etc, all of which must
		 * match while loading.
		 */
		if (fwrite(magic_id, strlen(magic_id), 1, f) != 1 || fwrite( (char*) &driver_id, sizeof driver_id, 1, f) != 1 || fwrite( (char*) &config_id, sizeof config_id, 1, f) != 1)
		{

			debug_message("write error when save to binary.\n");
			fclose(f);
			unlink(file_name);
			return ;
		}
		/*
		 * Write out list of include files.
		 */
		len = includes->current_size;
		fwrite( (char*) &len, sizeof len, 1, f);
		fwrite(includes->block, includes->current_size, 1, f);

		/*
		 * copy and patch program
		 */
		p = (program_t*)DXALLOC(prog->total_size, TAG_TEMPORARY, "save_binary");
		/* convert to relative pointers, copy, then convert back */
		locate_out(prog);
		memcpy(p, prog, prog->total_size);
		locate_in(prog);
		if (patches->current_size)
		{
			locate_in(p);
			patch_out(p, (short*)patches->block, patches->current_size / sizeof(short) );
			locate_out(p);
		}
		/*
		 * write out prog.  The prog structure is mostly setup, but strings will
		 * have to be stored specially.
		 */
		len = SHARED_STRLEN(p->name);
		fwrite( (char*) &len, sizeof len, 1, f);
		fwrite(p->name, sizeof(char), len, f);

		fwrite( (char*) &p->total_size, sizeof p->total_size, 1, f);
		fwrite( (char*)p, p->total_size, 1, f);
		FREE(p);
		p = prog;

		/* inherit names */
		for (i = 0; i < (int)p->num_inherited; i++)
		{
			len = SHARED_STRLEN(p->inherit[i].prog->name);
			fwrite( (char*) &len, sizeof len, 1, f);
			fwrite(p->inherit[i].prog->name, sizeof(char), len, f);
		}

		/* string table */
		for (i = 0; i < (int)p->num_strings; i++)
		{
			tmp = SHARED_STRLEN(p->strings[i]);
			if (tmp > (int)USHRT_MAX)
			{
				 /* possible? */
				fclose(f);
				unlink(file_name);

				error("Can't save too long string of binary.\n");
				return ;
			}
			len = tmp;
			fwrite( (char*) &len, sizeof len, 1, f);
			fwrite(p->strings[i], sizeof(char), len, f);
		}

		/* var names */
		for (i = 0; i < (int)p->num_variables_defined; i++)
		{
			len = SHARED_STRLEN(p->variable_table[i]);
			fwrite( (char*) &len, sizeof len, 1, f);
			fwrite(p->variable_table[i], sizeof(char), len, f);
		}

		/* fun names */
		for (i = 0; i < (int)p->num_functions_defined; i++)
		{
			len = SHARED_STRLEN(p->function_table[i].name);
			fwrite( (char*) &len, sizeof len, 1, f);
			fwrite(p->function_table[i].name, sizeof(char), len, f);
		}

		/* line_numbers */
		if (p->line_info)
		{
			len = p->file_info[0];
		}
		else
		{
			len = 0;
		}
		fwrite( (char*) &len, sizeof len, 1, f);
		fwrite( (char*)p->file_info, len, 1, f);

		/*
		 * patches
		 */
		len = patches->current_size;
		fwrite( (char*) &len, sizeof len, 1, f);
		fwrite(patches->block, patches->current_size, 1, f);

		fclose(f);

		/*
        {
            struct stat debug_st;
            stat(file_name, &debug_st);
			debug_message( "[%d]\n", debug_st.st_mtime );
        }
		*/
	} /* save_binary() */

	static program_t *comp_prog;

	static int compare_compiler_funcs(int *x, int *y)
	{
		char *n1 = comp_prog->function_table[ *x].name;
		char *n2 = comp_prog->function_table[ *y].name;

		/* make sure #global_init# stays last */
		if (n1[0] == '#')
		{
			if (n2[0] == '#')
			{
				return 0;
			}
			return 1;
		}
		if (n2[0] == '#')
		{
			return  - 1;
		}

		if (n1 < n2)
		{
			return  - 1;
		}
		if (n1 > n2)
		{
			return 1;
		}
		return 0;
	}

	static void sort_function_table(program_t *prog)
	{
		int *temp,  *inverse,  *sorttmp,  *invtmp;
		int i;
		int num = prog->num_functions_defined;

		if (!num)
		{
			return ;
		}

		temp = CALLOCATE(num, int, TAG_TEMPORARY, "copy_and_sort_function_table");
		for (i = 0; i < num; i++)
		{
			temp[i] = i;
		}

		comp_prog = prog;
		quickSort(temp, num, sizeof(int), (int (*)(void *, void *))compare_compiler_funcs);

		inverse = CALLOCATE(num, int, TAG_TEMPORARY, "copy_and_sort_function_table");
		for (i = 0; i < num; i++)
		{
			inverse[temp[i]] = i;
		}

		/* We're not copying, so we have to do the sort in place.  This is a
		 * bit tricky to do based on a permutation table, but can be done.
		 *
		 * Basically, we figure out how to turn the permutation into n swaps.
		 * If anyone has a reference for an algorithm for this, I'd like to
		 * know; I made this one up.  The basic idea is to do a swap, and then
		 * figure out the correct permutation on the remaining n-1 elements.
		 */
		sorttmp = CALLOCATE(num, int, TAG_TEMPORARY, "copy_and_sort_function_table");
		invtmp = CALLOCATE(num, int, TAG_TEMPORARY, "copy_and_sort_function_table");
		for (i = 0; i < num; i++)
		{
			sorttmp[i] = temp[i];
			invtmp[i] = inverse[i];
		}

		for (i = 0; i < num - 1; i++)
		{
			 /* moving n-1 of them puts the last one
			in place too */
			compiler_function_t cft;
			int where = sorttmp[i];

			if (i == where)
			 /* Already in the right spot */
			{
				continue;
			}

			cft = prog->function_table[i];
			prog->function_table[i] = prog->function_table[where];
			DEBUG_CHECK(sorttmp[invtmp[i]] != i, "sorttmp is messed up.");
			sorttmp[invtmp[i]] = where;
			invtmp[where] = invtmp[i];
			prog->function_table[where] = cft;
		}

		#ifdef COMPRESS_FUNCTION_TABLES
			{
				compressed_offset_table_t *cftp = prog->function_compressed;
				int f_ov = cftp->first_overload;
				int f_def = cftp->first_defined;
				int n_ov = f_def - cftp->num_compressed;
				int n_def = prog->num_functions_total - f_def;
				int n_real = f_def - cftp->num_deleted;

				for (i = 0; i < n_ov; i++)
				{
					int j = cftp->index[i];
					int ri = f_ov + i;
					if (j == 255)
					{
						continue;
					}
					if (!(prog->function_flags[ri] &NAME_INHERITED) )
					{
						int oldix = prog->function_offsets[j].def.f_index;

						DEBUG_CHECK(oldix >= num, "Function index is out of bounds");
						prog->function_offsets[j].def.f_index = inverse[oldix];
					}
				}
				for (i = 0; i < n_def; i++)
				{
					int ri = f_def + i;
					if (!(prog->function_flags[ri] &NAME_INHERITED) )
					{
						int oldix = prog->function_offsets[n_real + i].def.f_index;


						DEBUG_CHECK(oldix >= num, "Function index is out of bounds");
						prog->function_offsets[n_real + i].def.f_index = inverse[oldix];
					}
				}
			}
		#else 
			{
				int num_runtime = prog->num_functions_total;
				for (i = 0; i < num_runtime; i++)
				{
					if (!(prog->function_flags[i] &NAME_INHERITED) )
					{
						int oldix = prog->function_offsets[i].def.f_index;


						DEBUG_CHECK(oldix >= num, "Function index is out of bounds");
						prog->function_offsets[i].def.f_index = inverse[oldix];
					}
				}
			}
		#endif 

		if (prog->type_start)
		{
			for (i = 0; i < num; i++)
			{
				prog->type_start[i] = prog->type_start[temp[i]];
			}
		}

		FREE(sorttmp);
		FREE(invtmp);
		FREE(temp);
		FREE(inverse);
	}

	#define ALLOC_BUF(size) \
	if ((size) > buf_size) { FREE(buf); buf = DXALLOC(buf_size = size, TAG_TEMPORARY, "ALLOC_BUF"); }

	/* crude hack to check both .B and .b */
	#define OUT_OF_DATE 0

	program_t *int_load_binary(char *name)
	{
		char file_name_buf[400];
		char *buf,  *iname,  *file_name = file_name_buf,  *file_name_two = &file_name_buf[200];
		FILE *f;
		time_t tmp_i;
		int i, buf_size, ilen;
		time_t mtime;
		//    short len;
		int len;
		program_t *p,  *prog;
		object_t *ob;
		struct stat st;

		/* stuff from prolog() */
		num_parse_error = 0;

		sprintf(file_name, "%s/%s", SAVE_BINARIES, name);
		if (file_name[0] == '/')
		{
			file_name++;
		}
		len = strlen(file_name);

		file_name[len - 1] = 'b';

		if (stat(file_name, &st) !=  - 1)
		{
			mtime = st.st_mtime;
		}
		else
		{
			return OUT_OF_DATE;
		}

		if (!(f = fopen(file_name, FOPEN_READ) ) )
		{
			return OUT_OF_DATE;
		}

		tmp_gbl_name = name;
		/*
		if (comp_flag) {

		debug_message(" Please Wait");
		debug_message(" . ");
		debug_message(" . ");
		debug_message(" . \n");
		debug_message(" loading binary %s ... ", name);
		#ifdef lattice
		fflush(stderr);
		#endif
		}
		 */

		/* see if we're out of date with source */
		if (check_times(mtime, name) == 0)
		{
			//old is <= : user binary
			if (comp_flag)
			{
				comp_debug_message("source file is new.\n");
			}
			fclose(f);
			return OUT_OF_DATE;
		} buf = DXALLOC(buf_size = SMALL_STRING_SIZE, TAG_TEMPORARY, "ALLOC_BUF");

		/*
		 * Read preamble.  This must match, or we assume a different driver or
		 * configuration.
		 */
		if (fread(buf, strlen(magic_id), 1, f) != 1 || strncmp(buf, magic_id, strlen(magic_id) ) != 0)
		{
			if (comp_flag)
			{
				comp_debug_message("magic id is error?\n");
			}
			fclose(f);
			FREE(buf);
			return OUT_OF_DATE;
		}
		//    if(fread((char *) &i, sizeof i, 1, f) && 0)
		if ( (fread( (char*) &tmp_i, sizeof tmp_i, 1, f) != 1 || driver_id != tmp_i) )
		{
			if (comp_flag)
			{
				comp_debug_message("driver has changed!\n");
			}
			fclose(f);
			FREE(buf);
			return OUT_OF_DATE;
		}

		// ??????config_id,config_id?????????????????????????????????????????????????????????sizeof tmp_i
		fread((char *) &tmp_i, sizeof tmp_i, 1, f); 

		/*
		 * read list of includes and check times
		 */
		fread( (char*) &len, sizeof len, 1, f);
		ALLOC_BUF(len);
		fread(buf, sizeof(char), len, f);
		for (iname = buf; iname < buf + len; iname += strlen(iname) + 1)
		{
			if (check_times(mtime, iname) == 0)
			{
				if (comp_flag)
				{
					comp_debug_message("include file change!\n");
				}
				fclose(f);
				FREE(buf);
				return OUT_OF_DATE;
			}
		}

		/* check program name */
		fread( (char*) &len, sizeof len, 1, f);
		ALLOC_BUF(len + 1);
		fread(buf, sizeof(char), len, f);
		buf[len] = '\0';
		if (strcmp(name, buf) != 0)
		{
			if (comp_flag)
			{
				debug_message("The binary name is inconsistent with file: %s vs %s.\n", name, buf);
			}
			fclose(f);
			FREE(buf);
			return OUT_OF_DATE;
		}
		/*
		 * Read program structure.
		 */
		fread( (char*) &ilen, sizeof ilen, 1, f);
		p = (program_t*)DXALLOC(ilen, TAG_PROGRAM, "load_binary");
		fread( (char*)p, ilen, 1, f);
		locate_in(p); /* from swap.c */
		p->name = make_shared_string(name);

		/* Read inherit names and find prog.  Check mod times also. */
		for (i = 0; i < (int)p->num_inherited; i++)
		{
			int check_ret1, check_ret2;

			fread( (char*) &len, sizeof len, 1, f);
			ALLOC_BUF(len + 1);
			fread(buf, sizeof(char), len, f);
			buf[len] = '\0';

			/*
			 * Check times against inherited source.  If saved binary of
			 * inherited prog exists, check against it also.
			 */
			sprintf(file_name_two, "%s/%s", SAVE_BINARIES, buf);
			if (file_name_two[0] == '/')
			{
				file_name_two++;
			}
			len = strlen(file_name_two);
			file_name_two[len - 1] = 'b';

			check_ret1 = check_times(mtime, buf);
			check_ret2 = check_times(mtime, file_name_two);
			if (check_ret1 == 0 ||  //old is <= : use binary
			    check_ret2 == 0)
			{
				/*
				debug_message("check_ret1[%d][%s] check_ret2[%d][%s]\n", check_ret1, buf, check_ret2, file_name_two);
                {
                    struct stat debug_st;
                    stat(file_name_two, &debug_st);
                    debug_message( "Prophet:check[%d]?[%d]\n", mtime, debug_st.st_mtime );
                }
				*/
				/* ok if -1 */
				//if (comp_flag)
				{
					comp_debug_message("Inherited source changed.\n");
				}
				fclose(f);
				free_string(p->name);
				FREE(p);
				FREE(buf);
				return OUT_OF_DATE;
			}
			/* find inherited program (maybe load it here?) */
			ob = find_object2(buf);
			if (!ob)
			{
				if (comp_flag)
				{
					//compile ???????????????????????????find_object,??????????????????inherited prog is missed
					//????????????buff????????????load?????????find_object2?????????NULL
					ob = find_object(buf);
					if (ob == NULL)
					{
						comp_debug_message("The inherited prog is missed.\n");
					}
				}
				fclose(f);
				free_string(p->name);
				FREE(p);
				inherit_file = buf; /* freed elsewhere */
				return 0;
			}
			p->inherit[i].prog = ob->prog;
		}

		/* Read string table */
		for (i = 0; i < (int)p->num_strings; i++)
		{
			fread( (char*) &len, sizeof len, 1, f);
			ALLOC_BUF(len + 1);
			fread(buf, sizeof(char), len, f);
			buf[len] = '\0';
			p->strings[i] = make_shared_string(buf);
		}

		/* var names */
		for (i = 0; i < (int)p->num_variables_defined; i++)
		{
			fread( (char*) &len, sizeof len, 1, f);
			ALLOC_BUF(len + 1);
			fread(buf, sizeof(char), len, f);
			buf[len] = '\0';
			p->variable_table[i] = make_shared_string(buf);
		}

		/* fun names */
		for (i = 0; i < (int)p->num_functions_defined; i++)
		{
			fread( (char*) &len, sizeof len, 1, f);
			ALLOC_BUF(len + 1);
			fread(buf, sizeof(char), len, f);
			buf[len] = '\0';
			p->function_table[i].name = make_shared_string(buf);
		}
		sort_function_table(p);

		/* line numbers */
		fread( (char*) &len, sizeof len, 1, f);
		p->file_info = (unsigned short*)DXALLOC(len, TAG_LINENUMBERS, "load binary");
		fread( (char*)p->file_info, len, 1, f);
		p->line_info = (unsigned char*) &p->file_info[p->file_info[1]];

		/* patches */
		fread( (char*) &len, sizeof len, 1, f);
		ALLOC_BUF(len);
		fread(buf, len, 1, f);
		/* fix up some stuff */
		patch_in(p, (short*)buf, len / sizeof(short) );

		fclose(f);
		FREE(buf);

		/*
		 * Now finish everything up.  (stuff from epilog())
		 */
		prog = p;
		prog->id_number = get_id_number();

		total_prog_block_size += prog->total_size;
		total_num_prog_blocks += 1;

		swap_line_numbers(prog);
		reference_prog(prog, "load_binary");
		for (i = 0; (unsigned)i < prog->num_inherited; i++)
		{
			reference_prog(prog->inherit[i].prog, "inheritance");
		}

		/*
		if (comp_flag)
		comp_debug_message("Finish.\n");
		 */
		return prog;
	} /* load_binary() */

	time_t get_compile_time()
	{
		static time_t tval = 0;

		if (tval)
		{
			return tval;
		}

		{
			struct tm tmval;
			bzero(&tmval, sizeof(tmval) );
			if (strptime(__DATE__ " " __TIME__, "%b %e %Y %T", &tmval) )
			{
				return (tval = mktime(&tmval) );
			}
		}

		return (tval = 0);
	}

	void init_binaries(int argc, char **argv)
	{
		struct stat st;
		int arg_id, i;

		driver_id = get_compile_time();

		arg_id = 0;
		for (i = 1; i < argc; i++)
		{
			if (argv[i][0] != '-')
			{
				if (config_id)
				{
					continue;
				}
				if (do_stat(argv[i], &st, 0) !=  - 1)
				{
					config_id = st.st_mtime;
				}
				else
				{
					config_id = current_time;
				}
			} 
			else if (argv[i][1] == 'D' || argv[i][1] == 'm')
			{
				arg_id = (arg_id << 1) ^ whashstr(argv[i] + 2, 32);
			}
		}

		config_id ^= (arg_id << (sizeof(short) *8) );
	} /* init_binaries() */

	/*
	 * Test against modification times.  -1 if file doesn't exist,
	 * 0 if out of date, and 1 if it's ok.
	 */
	static int check_times(time_t mtime, char *nm)
	{
		struct stat st;

		#ifdef LATTICE
			if (*nm == '/')
			{
				nm++;
			}
		#endif 
		if (stat(nm, &st) ==  - 1)
		{
			return  - 1;
		}
		if (st.st_mtime > mtime)
		{
			return 0;
		} return 1;
	} /* check_times() */

	/*
	 * Routines to do some hacking on the program being saved/loaded.
	 * Basically to fix up string switch tables, since the alternative
	 * would probably need a linear search in f_switch().
	 * I set things up so these routines can be used with other things
	 * that might need patching.
	 */
	static void patch_out(program_t *prog, short *patches, int len)
	{
		int i;
		char *p;

		p = prog->program;
		while (len > 0)
		{
			i = patches[--len];
			if (p[i] == F_SWITCH && p[i + 1] >> 4 != 0xf)
			{
				 /* string switch */
				unsigned short offset, break_addr;
				char *s;

				/* replace strings in table with string table indices */
				COPY_SHORT(&offset, p + i + 2);
				COPY_SHORT(&break_addr, p + i + 4);

				while (offset < break_addr)
				{
					COPY_PTR(&s, p + offset);
					/*
					 * take advantage of fact that s is in strings table to find
					 * it's index.
					 */
					if (s == 0)
					{
						s = (char*) (POINTER_INT) - 1;
					}
					else
					{
						s = (char*) (POINTER_INT)store_prog_string(s);
					}
					COPY_PTR(p + offset, &s);
					offset += SWITCH_CASE_SIZE;
				}
			}
		}
	} /* patch_out() */

	static int str_case_cmp(char *a, char *b)
	{
		char *s1,  *s2;

		COPY_PTR(&s1, a);
		COPY_PTR(&s2, b);

		return s1 - s2;
	} /* str_case_cmp() */

	static void patch_in(program_t *prog, short *patches, int len)
	{
		int i;
		char *p;

		p = prog->program;
		while (len > 0)
		{
			i = patches[--len];
			if (p[i] == F_SWITCH && p[i + 1] >> 4 != 0xf)
			{
				 /* string switch */
				unsigned short offset, start, break_addr;
				char *s;

				/* replace string indices with string pointers */
				COPY_SHORT(&offset, p + i + 2);
				COPY_SHORT(&break_addr, p + i + 4);

				start = offset;
				while (offset < break_addr)
				{
					COPY_PTR(&s, p + offset);
					/*
					 * get real pointer from strings table
					 */
					if (s == (char*) - 1)
					{
						s = 0;
					}
					else
					{
						s = prog->strings[(POINTER_INT)s];
					}
					COPY_PTR(p + offset, &s);
					offset += SWITCH_CASE_SIZE;
				}
				/* sort so binary search still works */
				quickSort(&p[start], (break_addr - start) / SWITCH_CASE_SIZE, SWITCH_CASE_SIZE,
						  (int (*)(void *, void *))str_case_cmp);
			}
		}
	} /* patch_in() */

#endif 

/*
 * open file for writing, creating intermediate directories if needed.
 */
FILE *crdir_fopen(char *file_name)
{
	char *p;
	struct stat st;
	FILE *ret;

	/*
	 * Beek - These directories probably exist most of the time, so let's
	 * optimize by trying the fopen first
	 */
	if ( (ret = fopen(file_name, "wb") ) != NULL)
	{
		return ret;
	} p = file_name;

	while (*p && (p = (char*)strchr(p, '/') ) )
	{
		*p = '\0';
		if (stat(file_name, &st) ==  - 1)
		{
			/* make this dir */
			if (OS_mkdir(file_name, 0770) ==  - 1)
			{
				*p = '/';
				return (FILE*)0;
			}
		}
		*p = '/';
		p++;
	}

	return fopen(file_name, "wb");
} /* crdir_fopen() */
