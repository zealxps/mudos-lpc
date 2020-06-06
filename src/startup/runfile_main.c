#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <time.h>

#include "object.h"


static void shutdown_server()
{
    exit(0);
}

static void signal_event(int sig, short evtype, void *arg)
{
    fprintf(stderr, "catch signal:%d", sig);
    call_script_func("/rc/signal", "runfile_on_signal", "i", sig);
    if (sig == SIGINT) {
        shutdown_server();
    }
}

void module_init_runfile()
{
}

static int rpc_call_imp(int argc, svalue_t *argv)
{
    return 0;
}

void system_startup_runfile(char *runfile, char *script_args)
{
    printf("Want To run file %s \n ", runfile);
    if(script_args && strlen(script_args) > 0){
        call_script_func(runfile, "main", "s", script_args);
    } else {
        call_script_func(runfile, "main", "");
    }
}

