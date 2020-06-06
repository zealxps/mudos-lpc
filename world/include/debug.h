#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <color.h>

#define assert(x)                                   \
    if (!(x)) {                                     \
        error(sprintf("%s:%d: assert error:##x",    \
                      __FILE__, __LINE__) );        \
    }

#define xassert(x, y)                           \
    if (!(x)) {                                 \
        error(sprintf("%s:%d: assert error:%s", \
                      __FILE__, __LINE__, y));  \
    }

#define INTERNAL_XASSERT(x, y)                  \
    if (IsInternalHost()) {                     \
        xassert(x, y);                          \
    }

string _traceback(string *files, string *objs, string *funcs)
{
	for (int i = 0; i < sizeof(files); i++) {
		debug_message("traceback in file: %O obj: %O function: %O",
                      files[i], objs[i], funcs[i]);
	}
}

#define traceback()                                         \
    _traceback(call_stack(0), call_stack(1), call_stack(2))

#ifdef ENABLE_ANALYSE

#define ANALYSE_START(tag)                      \
    int __analyse_time_##tag = time(1)

#define ANALYSE_DEBUG(tag, lasttime)                                \
    "module/debug/analyse"->LogCost("analyse:##tag. Time use %d",   \
                                    time(1) - lasttime)

#define ANALYSE_END(tag)                                            \
    "module/debug/analyse"->LogCost("analyse:##tag. Time use %d",   \
                                    time(1) - __analyse_time_##tag)

#define ANALYSE_START_V2(tag)                   \
    int __analyse_time_##tag = time(1)

#define ANALYSE_END_V2(tag, obj)                                        \
    "module/debug/analyse"->LogCost("analyse:##tag. Obj = %O. Time use %d", \
                                    obj, time(1) - __analyse_time_##tag)

#define ANALYSE_COST_START(tag, id)                 \
    "module/debug/analyse"->LogCostStart(tag, id)

#define ANALYSE_COST_END(tag, id)               \
    "module/debug/analyse"->LogCostEnd(tag, id)

#define ANALYSE_LOG_TIME(tag, id)               \
    "module/debug/analyse"->LogTime(tag, id)

#else

#define ANALYSE_START(tag)
#define ANALYSE_END(tag)
#define ANALYSE_START_V2(tag)
#define ANALYSE_END_V2(tag, obj)
#define ANALYSE_DEBUG(tag, lasttime)
#define ANALYSE_COST_START(tag, id)
#define ANALYSE_COST_END(tag, id)
#define ANALYSE_LOG_TIME(tag, id)

#endif

#endif
