
#define SUPPRESS_COMPILER_INLINES
#include <sys/utsname.h>
#include <sys/resource.h>
#include <unistd.h>

#include "std.h"
#include "file_incl.h"
#include "lpc_incl.h"
#include "lex.h"
#include "file.h"
#include "backend.h"
#include "simul_efun.h"
#include "binaries.h"
#include "otable.h"
#include "comm.h"
#include "compiler.h"
#include "port.h"
#include "md.h"
#include "main.h"
#include "compile_file.h"
#include "object.h"
#include "stack.h"
#include "vm.h"
#include "fs_startup.h"

#define TRAP_CRASHES

int comp_flag = 0; /* Trace compilations */
int run_flag = 0;

module_fun_t module_init;
module_fun_t module_startup;

extern void module_init_runfile(void);
extern void system_startup_runfile(char *runfile, char *script_args);

static int maxdepth = 10;
int compile_all_file(const char *path, int depth)
{
    DIR *dirp;
    struct dirent *dp;
    char realpath[256];
    char pathname[256];

    if (strcmp(path, "/") == 0 || strcmp(path, game_lib_path) == 0) {
        path = "";
        depth = 0;
    }
    depth += 1;
    if (depth >= maxdepth) {
        return 0;
    }
    strlcpy(realpath, game_lib_path, sizeof(realpath) );
    strlcat(realpath, "/", sizeof(realpath) );
    strlcat(realpath, path, sizeof(realpath) );

    dirp = opendir(realpath);
    if (dirp == NULL) {
        printf("error compile path: %s\n", path);
        return 0;
    }
    while ( (dp = readdir(dirp) ) != NULL) {
        if (dp->d_name[0] == '.') {
            continue;
        }
        strlcpy(pathname, path, sizeof(pathname) );
        strlcat(pathname, "/", sizeof(pathname) );
        strlcat(pathname, dp->d_name, sizeof(pathname) );
        if (dp->d_type == DT_DIR || dp->d_type == DT_LNK) {
            compile_all_file(pathname, depth);
        } else {
            int d_namlen = strlen(dp->d_name);
            if (d_namlen >= 2 && (dp->d_name[d_namlen - 1] == 'c' || dp->d_name[d_namlen - 1] == 'C') && dp->d_name[d_namlen - 2] == '.') {
                if (!find_object(pathname)) {
                    (void)closedir(dirp);
                    return 0;
                }
            }
        }
    }
    (void)closedir(dirp);
    return 1;
}

void log_sys_info()
{
    time_t now = time(NULL);
    fprintf(stderr, "*** Start engine (%dbit) on [%.*s] ***\n", (int) sizeof(void*)*8, 24, ctime(&now));

#if defined(BUILD_DATE)
    fprintf(stderr, "compiled with version: %s on %s\n", __VERSION__, BUILD_DATE);
#endif

    struct utsname name;
    uname(&name);
    fprintf(stderr, "os: %s-%s %s\n", name.sysname, name.release, name.version);
    fprintf(stderr, "nodename: %s\n", name.nodename);
    fprintf(stderr, "machine: %s\n", name.machine);

    int cpus = 1;
#if defined(_SC_NPROCESSORS_ONLN)
    cpus = sysconf(_SC_NPROCESSORS_ONLN);
#elif defined(_SC_NPROCESSORS_CONF)
    cpus = sysconf(_SC_NPROCESSORS_CONF);
#endif
    fprintf(stderr, "detected number of CPU cores: %d\n", cpus);

    char cwd[256];
    if (getcwd(cwd, 256) != NULL) {
        fprintf(stderr, "current working directory: %s\n", cwd);
    }

#if defined(__linux__)
    char binary_path[256+1];
    ssize_t len = readlink("/proc/self/exe", binary_path, 256);
    if (len > 0) {
        binary_path[len] = '\0';
        fprintf(stderr, "detected binary path: %s\n", binary_path);
    }
#endif

    struct rlimit rl;
    if (!getrlimit(RLIMIT_NOFILE, &rl)) {
        fprintf(stderr, "detected max file descriptor number: %lu\n", (unsigned long) rl.rlim_cur);
    }

    fprintf(stderr, "***\n");
}

int fs_startup(int argc, char **argv)
{
    int ch;
    char *runfile = NULL;
    char *script_args = NULL;
    const char *libpath = NULL;

    optind = 1;
    while ( (ch = getopt(argc, argv, "f:br:l:O:h:") ) !=  - 1) {
        switch (ch)	{
            case 'l':
                // 初始化配置文件
                libpath = optarg;
                break;
            case 'b':
                comp_flag = 1;
                break;
            case 'r':
                run_flag = 1;
                runfile = optarg;
                module_init = module_init_runfile;
                break;
            case 'O':
                script_args = optarg;
                break;
            default:
                break;
        }
    }

    if (!module_init && !comp_flag) {
        fprintf(stderr, "please declare module args!\n");
        return -1;
    }

    log_sys_info();

    if (!libpath) {
        libpath = QTZ_ServerEngine_LIB;
    }

    unsigned int _stim = get_current_time() + getpid();
    srand(_stim);
    srandom(_stim);
    //srandomdev();

    // 初始化
#ifdef BINARIES               
    init_binaries(argc, argv);
#endif 

    // 初始化虚拟机, 这样配置文件可以存为一个map
    vm_init();
    vm_startup(libpath);

    extern char *log_dir; 
    char *tdir = "./log/";
    int tlen = strlen(tdir); 
    log_dir = calloc(1,tlen+2); 
    memcpy(log_dir,tdir,tlen); 
    if(log_dir[tlen-1] != '/') {
        log_dir[tlen] = '/'; 
    }

    if (module_init) {
        module_init();
    }

    error_context_t econ;
    // 编译
    if (comp_flag) {
        save_context(&econ);
        if (SETJMP(econ.context)) {
            debug_message("compile error!!!\n");
            exit( - 1);
        }
        compile_all_file("/", 0);
        pop_context(&econ);
        debug_message("编译代码完毕\n");
        return 0;
    }

    if (runfile != NULL) {
        system_startup_runfile(runfile, script_args);
        return 0;
    }

    //system_startup();
    if (module_startup) {
        module_startup();
    }
    return 0;
}

