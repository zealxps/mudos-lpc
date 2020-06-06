int is_number(string sNum)
{
    int i ;

    for ( i = 0; i < sizeof(sNum); i++ )
    {
        if ( (sNum[i] < 48 || sNum[i] > 57) )
        {
            return 0 ;
        }
    }
    return 1 ;
}

int is_sign_number(string sNum)
{
    int i ;

    for ( i = 0; i < sizeof(sNum); i++ )
    {
        if ( (sNum[i] < 48 || sNum[i] > 57) && sNum[i] != 45 )
        {
            return 0 ;
        }
    }
    return 1 ;
}

int atoi(string sNumStr)
{
    int iNum;

    if ( !stringp(sNumStr) ) return 0;

    if( !sscanf(sNumStr, "%d", iNum) )
        return 0;

    return iNum;
}

string itoa(int iNum)
{
    return sprintf("%d", iNum);
}

string to_str(mixed data)
{
    if (mapp(data)) return serial_mapping(data);
    if (arrayp(data) || classp(data)) return serial_array(data, ",");
    if (objectp(data)) return sprintf("%O", data);
    return data + "";
}

mixed left_trim( mixed mArray )
{
    int i, iSize;

    if( stringp(mArray) )
    {
        iSize = sizeof(mArray);
        for( i = 0; i < iSize && mArray[i] == ' '; i ++ ) ;
        return mArray[ i..<1 ];
    }
    else if( arrayp(mArray) )
    {
        iSize = sizeof(mArray);
        for( i = 0; i < iSize && mArray[i] == ""; i ++ ) ;
        return mArray[ i..<1 ];
    }

    return mArray;
}

mixed right_trim( mixed mArray )
{
    int iSize;

    if( stringp(mArray) )
    {
        iSize = sizeof(mArray);
        while( iSize -- ) if( mArray[iSize] != ' ' ) break;
        return mArray[ 0..iSize ];
    }
    else if( arrayp(mArray) )
    {
        iSize = sizeof(mArray);
        while( iSize -- ) if( mArray[iSize] != "" ) break;
        return mArray[ 0..iSize ];
    }
    else return mArray;
}


mixed all_trim( mixed mArray )
{
    return left_trim( right_trim( mArray ) );
}


mixed atom(string sArg)
{
    mixed *m, m1, m2;
    object o;
    string s, s1, s2;
    int i, iSize;

    if( ! ( sArg = all_trim(sArg) ) )
        return sArg;

    if( sscanf( sArg, "%d", i ) && is_sign_number(sArg) )
        return i;

    if( sscanf( sArg, "\"%s\"", s ) )
        return s;

    if( o = find_object( sArg ) )
        return o;

    if( sscanf( sArg, "(:%s,%s:)", s1, s2 ) == 2 )
    {
        m1 = atom( s1 );
        m2 = atom( s2 );
    }

    if( sscanf( sArg, "[%s]", s ) )
    {
        m = explode( s, "," );
        iSize = sizeof( m );

        if( iSize && !m[0] )
            return [ ];

        for( i = 0; i < iSize; i ++ )
            m[i] = atom( m[i] );

        return m;
    }

    if( sscanf( sArg, "{%s}", s ) )
    {
        mapping mp = {};
        m = explode( s, "," );
        iSize = sizeof( m );

        if( iSize && !m[0] )
            return { };

        for( i = 0; i < iSize; i ++ )
            if( sscanf( m[i], "%s:%s", s1, s2 ) == 2 )
                mp[ atom(s1) ] = atom(s2);

        return mp;
    }

    return sArg;
}


mixed random_one( mixed *sArray )
{
    return sArray[ random( sizeof(sArray) ) ];
}

/*
string string_join(string * arr, string spe)
{
    string str = "";
    if (!arrayp(arr)) return "";
    if (sizeof(arr) < 1) return "";

    foreach(string s in arr)
    {
        str += sprintf("%s%s", spe, s);
    }
    return str[sizeof(spe)..sizeof(str)];
}
*/

string base_filename(string fullname)
{
    int idx=strsrch(fullname,"/",-1);
    if ( idx == -1 ) {
        return fullname;
    } else {
        return fullname[idx+1 .. sizeof(fullname)-1];
    }
}

/*
varargs mixed mid( mixed mArray, int iStart, int iNum )
{
    int iSize;

    if( stringp(mArray) || arrayp(mArray) )
    {
        iSize = sizeof(mArray);
        if( iStart < 1 ) iStart = 1;
        if( nullp(iNum) ) return mArray[iStart - 1 .. iSize - 1];
        if( iNum < 1 || iStart > iSize ) return mArray[ iSize..iSize ];
        return mArray[iStart - 1 .. iStart + iNum - 2];
    }
    else return mArray;
}
*/

/*
varargs mixed exclude( mixed mArray, int iStart, int iNum )
{
    mixed mLeft, mRight;
    int iSize;

    if( stringp(mArray) || arrayp(mArray) )
    {
        iSize = sizeof(mArray);
        if( iStart < 1 ) iStart = 1;
        if( nullp(iNum) )
        {
            if( iStart == 1 ) return mArray[iSize .. iSize];
            else return mArray[0 .. iStart - 2];
        }
        if( iNum <= 0 || iStart > iSize ) return mArray;

        if( iStart >= 2 ) mLeft = mArray[0 .. iStart - 2];
        else mLeft = mArray[ iSize..iSize ];

        if( iStart + iNum - 1 < iSize )
            mRight = mArray[iStart + iNum - 1 .. sizeof(mArray) - 1];
        else
            mRight = mArray[ iSize..iSize ];
        return mLeft + mRight;
    }
    else return mArray;
}
*/

string base_name( mixed val ) {
    string name, base;

    if( stringp(val) )
        name = val;
    else
        name = file_name(val);

    if( sscanf( name, "%s#%*d", base ) == 2 )
        return base;
    else
        return name;
} /* base_name() */

string TrueName(string cName)
{
    sscanf( cName, "/%s", cName);
    sscanf( cName, "%s.c", cName);

    return "/"+cName+".c";
}

mixed asort( mixed strlist ) {
    return sort_array(strlist, strcmp);
}

#define ADD_STAGE(s) { \
    curSection = all_trim(s); \
    mpData[curSection] = {}; \
}

#define ADD_STAGE_KEY(k, v) { \
    k = all_trim(k); \
    v = all_trim(v); \
    if (!sizeof(curSection)) { \
        ADD_STAGE("default"); \
    } \
    mpData[curSection][atom(k)] = atom(v); \
}

mapping File2Map(string fileName)
{
    string sKey, sValue, * strLines, curSection;
    mapping mpData = {};

    string fileContent = read_file(fileName);
    if( !stringp(fileContent) || !strlen(fileContent) ) return {};

    fileContent = replace_string(fileContent, "\r", "");
    strLines = explode(fileContent, "\n");

    foreach ( string row in strLines ) {
        row = all_trim(row);
        if ( !strlen(row) ) continue;
        if ( row[0] == '#' || ( row[0] == '/' && row[1] == '/' ) )
            continue;

        if ( row[0] == '[' ) {
            string section;
            if ( sscanf(row, "[%s]", section) == 1 ){
                ADD_STAGE(section);
            }
            continue;
        }

        row = replace_string( row, "\t", "");

        if ( !strlen(row) ) continue;
        if ( row[<1] == ';' ) row = row[0..<2];

        int equalPos = strsrch(row, '=');
        if (equalPos <=0 || equalPos >= strlen(row)) continue;
        sKey = row[0..(equalPos-1)];
        sValue = row[(equalPos+1)..<1];
        ADD_STAGE_KEY(sKey, sValue);
    }
    //debug_message("mpData %O", mpData);
    return mpData;
}

//
// 函数：将字串转换成时间
// 注释：当 iFlag 缺省或者值为零时，
//          将时间转换成“YYYY-MM-DD HH:MM:SS”格式的时间字符串，
//          否则将时间转换成“YYMMDDHHMMSS”格式的时间字符串。
varargs int string2time(string time, int iFlag )
{
    int year, month, day, hour, min, sec;

    if (iFlag)
    {
        if (sscanf(time, "%4d%2d%2d%2d%2d%2d", year, month, day, hour, min, sec)  != 6 )
        {
            return 0;
        }
    }
    else
    {
        if (sscanf(time, "%d-%d-%d %d:%d:%d", year, month, day, hour, min, sec)  != 6 )
        {
            return 0;
        }
    }

    return mktime(year, month, day, hour, min, sec);
}

int is_start_with(string str, string strHead)
{
    if ( !stringp(str) || !stringp(strHead) )
        return 0;

    if ( !sizeof(strHead) )
        return 1;

    return strHead == str[0..(sizeof(strHead)-1)];
}

int is_end_with(string str, string end)
{
    if (!stringp(str) || !stringp(end)) return 0;
    int strLength = sizeof(str);
    int endLength = sizeof(end);
    if (!endLength) return 1;
    if (endLength > strLength) return 0;
    return end == str[(strLength - endLength) .. (strLength - 1)];
}

/* string unicode_decode(string unicode) */
/* { */
/*     if (!stringp(unicode)) return ""; */
/*     string utf_asc = fs_iconv(unicode,"c99","utf-8"); */
/*     return utf_asc; */
/* } */

string map2json(mapping mpInfo)
{
    string ret_str = "";
    if(sizeof(mpInfo)) {
        foreach(mixed _key , mixed _data in mpInfo) {
            if (sizeof(ret_str)) ret_str += ",";
            if(intp(_key)) {
                ret_str += sprintf("\"%d\":",_key);
            } else {
                ret_str += sprintf("%O:",_key);
            }

            if(mapp(_data)) {
                ret_str += sprintf("%s",map2json(_data));
            } else {
                if(arrayp(_data)) {
                    ret_str += "[";
                    foreach (mixed _list in _data) {
                        ret_str += sprintf("\"%O\",",_list);
                    }
                    ret_str += "]";
                    //ret_str += sprintf("%O:%d,",_key,_data);
                } else if (intp(_data)) {
                    ret_str += sprintf("\"%O\"",_data);
                } else {
                    ret_str += sprintf("%O",_data);
                }
            }
        }
    }
//	debug_message("map2json : %s", ret_str);
    return "{" + ret_str + "}";
}

// LPC 不支持char定义单个字符, 所以可以使用int来定义字符
int in_string(int char, string str)
{
    for (int i = 0; i < strlen(str); i++) {
        if (char == str[i]) {
            return 1;
        }
    }
    return 0;
}

// 当rm为空字符串时, 删除字符串str左边的所有空白符
// 当rm不为空字符串时, 删除字符串str左边所有出现在rm中的字符
varargs string lstrip(string str, string rm)
{
    if (undefinedp(str)) {
        debug_message("[error] the function lstrip must pass at least 1 argument!");
        return str;
    } else if (undefinedp(rm)) {
        // 如果不删除, 默认删除左边的所有空白符, ' ', '\t', '\r', '\n'
        return lstrip(str, " \t\r\n");
    } else {
        // 如果传入了rm, 则删除左边在rm中出现过的所有字符
        for (int i = 0; i < strlen(str); i++) {
            if (!in_string(str[i], rm)) {
                return str[i..<1];
            }
        }
        return "";
    }
}

// 同上, 方向为从右边删除
varargs string rstrip(string str, string rm)
{
    if (undefinedp(str)) {
        debug_message("[error] the function rstrip must pass at least 1 argument!");
        return str;
    } else if (undefinedp(rm)) {
        // 如果不删除, 默认删除左边的所有空白符, ' ', '\t', '\r', '\n'
        return rstrip(str, " \t\r\n");
    } else {
        // 如果传入了rm, 则删除左边在rm中出现过的所有字符
        for (int i = strlen(str) - 1; i >= 0; i--) {
            if (!in_string(str[i], rm)) {
                return str[0..i];
            }
        }
        return "";
    }
}

// 同上, 双向删除
// 以上三个函数是模仿python的strip的功能
varargs string strip(string str, string rm)
{
    if (undefinedp(str)) {
        debug_message("[error] the function strip must pass at least 1 argument!");
        return str;
    } else {
        return rstrip(lstrip(str, rm), rm);
    }
}
