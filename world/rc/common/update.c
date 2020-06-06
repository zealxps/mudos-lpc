// #include <macros.h>

int DoUpdate(string file);

string* MultiObjsFiles = ["module/ext_data/main"];

int DoUpdate(string sFile)
{
    mapping mpCaches ;
    object ob;
    int ret = 0;

    if (sizeof(sFile) > 2 && sFile[<2] == '.') {
        sFile = sFile[0..<3];
    }
    if (member_array(sFile, MultiObjsFiles) >= 0) {
        debug_message("%s cloned multi objects, cannot hotfix", sFile);
        return 1;
    }
    // release old object
    int last_variables_num = 0;
    if ( ob = find_object(sFile) ) {
        if ( function_exists("GetVarsValue", ob) ) {
            mpCaches = ob->GetVarsValue();
        } else {
            mpCaches = {};
        }
        last_variables_num = sizeof(variables(ob));
        // update删除时调用
        if ( function_exists("do_destruct", ob) ) {
            catch(ob->do_destruct());
        }

        if (base_name(ob) != "/rc/common/update") {
            destruct(ob);
        }
    }

    // load new object
    // 将原来的接口改为reload_object, 主要是默认load_object会调用on_loadin, 而reload_object就不去调用了
    if (catch( ob = reload_object(sFile))) {
        // ob = find_object(sFile);
        return 1;
    }

    // resume object
    if (ob) {
        // update载入时调用，和create有些许不同
        if (sizeof(mpCaches)) {
            ob->SetVarsValue(mpCaches);
        }
        if( function_exists("on_loadin", ob) ) {
            catch( ob->on_loadin() );
        }

        return 0;
    }
    else {
        return 1;
    }
}
