#include "unittest.h"

mixed *Calc(mixed *val)
{
    mixed *r = allocate(sizeof(val));
    for (int i = 0; i < sizeof(val); i++) {
        // 说明: func_in_example_lib 是在example_lib的一个测试函数，功能实现为参数的平方
        r[i] = func_in_example_lib(val[i]);
    }
    return r;
}

UTEST("test calc")
{
    UT_EQ([1,4,9,16], Calc([1, 2, 3, 4]));
}

