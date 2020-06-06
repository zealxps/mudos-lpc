#include "compiler.h"
#include <stdio.h>
#include "lpc.h"
#include "config.h"
#include "object.h"
#include "interpret.h"
#include "port.h"
#include "stralloc.h"
#include "otable.h"
#include "lex.h"
#include "simul_efun.h"
#include "lpc_incl.h"

#define LIB_PATH_SIZE   1024

void debug_message(const char *, ...);

int boot_time;
char game_lib_path[LIB_PATH_SIZE];       /*游戏目录的绝对路径*/
char game_lib_bin_path[LIB_PATH_SIZE];   /*游戏目录的绝对路径*/

int max_array_size;
int max_buffer_size;
int max_cost;

svalue_t const0, const1, const0u;


double consts[NUM_CONSTS];

/* -1 indicates that we have never had a master object.  This is so the
 * simul_efun object can load before the master. */
object_t *master_ob = 0;

extern int current_time;
extern int eval_cost;
extern int max_string_length;
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

int vm_init()
{
	printf("Please wait while initializing internal tables....\n");

#ifdef WRAPPEDMALLOC
	wrappedmalloc_init();
#endif /* WRAPPEDMALLOC */
#ifdef DEBUGMALLOC
	MDinit();
#endif 

	boot_time = get_current_time();
	// 初始化Efun用的當前時間
	current_time = boot_time;

	const0.type = T_NUMBER;
	const0.u.number = 0;
	const1.type = T_NUMBER;
	const1.u.number = 1;

	/* const0u used by undefinedp() */
	const0u.type = T_NUMBER;
	const0u.subtype = T_UNDEFINED;
	const0u.u.number = 0;

	fake_prog.program_size = 0;

	// 初始化字符串
	init_strings();
	// 初始化lpc object table
	init_otable();
	// 初始化保留字
	init_identifiers();
	// 初始化編譯器
	init_locals();

	max_cost = RUN_COST;
	eval_cost = max_cost;

	max_array_size = MAX_ARRAY_SIZE;
	max_buffer_size = MAX_BUFFER_SIZE;
	max_string_length = MAX_STRING_LENGTH;

	return 0;
}

void vm_startup(const char *libpath)
{
	error_context_t econ;

	// 初始化目錄
	if (chdir(libpath) ==  - 1) {
		/*   Bad mudlib directory: %s\n            */
		fprintf(stderr, "Error:Bad lib directory: %s\n", libpath);
		exit( - 1);
	}

	memset(game_lib_path, '\0', sizeof(game_lib_path));
	if (getcwd(game_lib_path, LIB_PATH_SIZE) == NULL) {
		fprintf(stderr, "Error:Bad lib directory: %s\n", libpath);
		exit(-1);
	}

	snprintf(game_lib_bin_path, sizeof(game_lib_bin_path), "%s/bin", game_lib_path);

	set_inc_list(INCLUDE_DIRS);

	init_num_args();
	reset_machine(1);

	add_predefines(game_lib_path);

	save_context(&econ);
	if (SETJMP(econ.context) ) {
		/* The simul_efun (%s) and master (%s) objects must be loadable.\n"*/
		debug_message("The simul_efun (%s) objects must be loadable.\n", SIMUL_EFUN);
		exit( - 1);
	} else {
		init_simul_efun(SIMUL_EFUN);
	}
	pop_context(&econ);
}
