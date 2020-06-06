#include <color.h>

static mapping _GUnitTestFuncArray = {};
static mapping _GTestInfo = {};

#define _InsertUTFunction(func,desc) _GUnitTestFuncArray[__LINE__] = [func, desc]

#define UTEST(func_desc) \
	void func####__LINE__(string desc);									\
	mixed var####__LINE__ = (_InsertUTFunction(func####__LINE__, func_desc), _GTestInfo[func_desc] = {"Success":[], "Failed":[]}, 0); \
	void func####__LINE__(string desc)

mapping _GetTestFuncArray()
{
	return _GUnitTestFuncArray;
}

mapping _GetUTInfo(string desc)
{
	return _GTestInfo[desc]
}

bool ut_equal(mixed v, mixed r)
{
	string vt = typeof(v);
	if (vt != typeof(r)) return false;

	int i;
	switch(vt) {
		case "int":
		case "string":
		case "float":
			return (v == r);
		case "array":
			if (sizeof(v) != sizeof(r)) return false;
			i = 0;
			while (i < sizeof(v)) {
				if (v[i] != r[i]) return false;
				i ++;
			}
			return true;
		case "mapping":
			if (sizeof(v) != sizeof(r)) return false;
			foreach (mixed _k, mixed _v in v) {
				if (_v != r[_k]) return false;
			}
			return true;
		case "class":
			// TODO
			return false;
		case "object":
		case "fun":
		case "buffer":
		default:
			return false;
			
	}
}

#define _UT_TRUE(exp, exp_str) \
		if (!(exp)) { \
			debug_message("\r%sFailed:%s%s%s return false  %sat line %d%s", KBLU,KYEL, \
						  replace_string(replace_string(exp_str, "\n", "")," ",""),KBLU,KCYN, __LINE__, KWHT); \
			_GTestInfo[desc]["Failed"] += [__LINE__] \
		} else { \
			_GTestInfo[desc]["Success"] += [__LINE__] \
		}
#define UT_TRUE(exp) \
	_UT_TRUE(exp, "##exp")
#define UT_EQ(v, t) \
	_UT_TRUE(ut_equal(v, t), sprintf("%O==%O", v, t))
#define UT_NE(v,t) \
	_UT_TRUE(not ut_equal(v, t), sprintf("%O!=%O", v, t))

