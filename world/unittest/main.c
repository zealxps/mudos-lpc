#include <color.h>
#include <debug.h>

static string utModuleCfg = "unittest/ut.cfg";

void ModuleUnitTest(string module)
{
    if (!sizeof(module)) return;
	debug_message("\r                              ")
	debug_message("\r================================= "KGRN"Tests %s"KWHT" ==============================", module)
	mapping funcs = module->_GetTestFuncArray();	
	if (sizeof(funcs)) {
		string str;
		mixed *sortedFuncs = map(sort(keys(funcs), sub), fun(int line) ->funcs[line])
		foreach (mixed info in sortedFuncs) {
			fun func = info[0]
			string desc = info[1]
			int t = time(true)
			func(desc, 0)
			t = time(true) - t 
			eval_cost(0)
			str = sprintf("Run test: %s", desc)
			str += repeat_string(" ", 60 - sizeof(str))

			int *success = module->_GetUTInfo(desc)["Success"]
			int *failed = module->_GetUTInfo(desc)["Failed"]
			string num = sprintf("%d/%d", sizeof(success),sizeof(failed) + sizeof(success));
			num = repeat_string(" ", 7 - sizeof(num)) + "["KMAG + num + KWHT"]"
			string errinfo = sizeof(failed) > 0? " at line(" + implode(map(failed, fun(int a) -> "" + a), ",") + ")" : "";
			errinfo = sprintf("%s%s%s%s", KCYN, errinfo, KWHT, repeat_string(" ", 25 - sizeof(errinfo)))
			string timeinfo = sprintf("%dms", t);
			timeinfo = sprintf("%s%s%s%s", repeat_string(" ", 9 - sizeof(timeinfo)), KGRN,timeinfo, KWHT)
			debug_message("\r%s%s%s%s[%s]%s%s", 
						  sizeof(failed) > 0? KRED :KWHT,
						  str,
						  KWHT,
						  num,
						  sizeof(failed) > 0? KRED+"FAIL"+KWHT : KGRN"SUCC"KWHT,
						  errinfo, timeinfo)
		}
	}
}

void Init()
{
}


string *UnitTestFileList(string cfg)
{
	cfg = sizeof(cfg) ? cfg : utModuleCfg;
	int fd = OpenFile(cfg);
	string file = "";
	string *fileList = [];

	while ((file = ReadFile(fd))) {
		if (is_start_with(file, "#")) continue; // #作为配置的注释符号
		file = replace_string(file, "\n", "" );
		fileList += [file];
		//ModuleUnitTestDebug(file);
	}
	CloseFile(fd);

	return fileList;
}

void UnitTest(string cfg)
{
	string *fileList = UnitTestFileList(cfg);
	if (sizeof(fileList)) {
		foreach (string file in fileList) {
			ModuleUnitTest(file);
		}
	}
}

int main(string args)
{
	if (!stringp(args)) {
		args = utModuleCfg;
	}
	Init();
	UnitTest(args);
	return 1;
}

