#ifndef __FS_STARTUP_H_
#define __FS_STARTUP_H_

extern int comp_flag;
extern int run_flag;
extern int auth_flag;
extern char *config_file;
extern struct event_base *ev_base;

// define in vm
extern char game_lib_path[];


typedef void (*module_fun_t)(void);

extern module_fun_t module_init;
extern module_fun_t module_startup;

int compile_all_file(const char *path, int depth);
void log_sys_info();
int fs_startup(int argc, char **argv);

#endif
