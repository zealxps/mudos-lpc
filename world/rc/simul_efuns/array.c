mixed uniq_array(mixed arr)
{
    mapping mpTmp = {};

    foreach (mixed tmp in arr) {
        mpTmp[tmp] = 1;
    }

    return keys(mpTmp);
}

mixed shuffle(mixed arr)
{
    int i, j, sz;
    mixed tmp;

    if (!pointerp(arr)) return [];

    sz = 1;
    if ((sz = sizeof(arr)) < 2) {
        return arr;
    }

    for (i = 0; i < sz; i++) {
        if (i == (j = random(i + 1))) continue;
        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    return arr;
}

int *find_members(mixed target, mixed arr)
{
    int i, *ret;
    ret = [];

    while((i = member_array(target, arr, i)) != -1) {
        ret += [i++];
    }

    return ret;
}

mixed array_del(mixed arr, int start, int len)
{
    return arr[0..start-1] + arr[start+len..];
}

mixed array_insert(mixed arr, mixed el, int pos)
{
    if (stringp(arr)) return arr[0..pos-1] + el + arr[pos..];
    return arr[0..pos-1] + [el] + arr[pos..];
}

string serial_mapping(mapping dict);
string serial_array(mixed arr, string split)
{

    int i = 0;
    string str = "";
    if (!arrayp(arr) && !classp(arr)) return "";
    if (!sizeof(split)) split = ",";
    while (i < sizeof(arr)) {
        string _tmp = "";
        if (mapp(arr[i])) {
            _tmp = serial_mapping(arr[i]);
        } else if (arrayp(arr[i]) || classp(arr[i])) {
            _tmp = serial_array(arr[i], ",");
        } else if (intp(arr[i])) {
            _tmp = sprintf("%d",arr[i]);
        } else if (stringp(arr[i])) {
            if (strsrch(arr[i],split) != -1) {       //  增加字符串中是否含有 分隔字符的判断，如果有，进行替换
                //debug_message("[ERROR]: serial array %s has split :%s", arr[i], split);
                string to_split = "";
                if (split == "|") to_split =",";    //  做分隔符替换，默认 | → ,
                if (split == ",") to_split ="|";    //  或者 , → |
                _tmp = replace_string(arr[i],split,to_split);
            } else {
                _tmp = arr[i];
            }
        } else if (floatp(arr[i])) {
            _tmp = sprintf("%f", arr[i]);
        } else {
            debug_message("[ERROR]: serial array error:%O", arr[i]);
        }
        str += (i > 0 ? split:"") + _tmp;
        i++;
    }
    str = replace_string(str,"","");
    str = replace_string(str,"\n","");
    return str;
}

string serial_mapping(mapping dict)
{
    string str = "";
    if (!mapp(dict) || !sizeof(dict)) return "";
    foreach (string _key, mixed _val in dict) {
        if (sizeof(str)) str += ",";
        if (stringp(_val)) {
            str += sprintf("%s:%s", ""+_key, _val);
        } else if (intp(_val)) {
            str += sprintf("%s:%d", ""+_key, _val);
        } else if (arrayp(_val)  || classp(_val)) {
            str += sprintf("%s:[%s]", ""+_key, serial_array(_val, ","));
        } else if (mapp(_val)) {
            str += sprintf("%s:{%s}", ""+_key, serial_mapping(_val));
        } else if (floatp(_val)) {
            str += sprintf("%s:%f", ""+_key, _val);
        } else {
            str += sprintf("%s:%O", ""+_key, _val);
        }
    }
    return str;
}

mapping make_map(mixed *key_arr, mixed *value_arr)
{
    int size = sizeof(key_arr) > sizeof(value_arr) ? sizeof(value_arr) : sizeof(key_arr);
    mapping result_map = {};
    for (int i=0; i<size; i++) {
        result_map[key_arr[i]] = value_arr[i];
    }
    return result_map;
}

mixed reverse_array(mixed arr)
{
    int size = sizeof(arr);
    int half = size/2;
    for (int i=0; i<half; i++) {
        int tmp = arr[i];
        arr[i] = arr[size-i-1];
        arr[size-i-1] = tmp;
    }
    return arr;
}

mixed intersect_array(mixed *arr1, mixed *arr2)
{
    mixed arrIntersection = [];
    mapping mpTmp = {};
    foreach (mixed el in arr1) {
        mpTmp[el] = 1;
    }

    foreach (mixed el in arr2) {
        if (undefinedp(mpTmp[el])) continue;
        arrIntersection += [el];
    }

    return arrIntersection;
}
