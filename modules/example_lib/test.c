#include "lpc_args_op.h"

void f_func_in_example_lib()
{
    SET_ALL_ARGS;
    int v = ARGS(0)->u.number;
    POP_ALL_ARGS;
    push_number(v*v);
}
