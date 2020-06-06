#include <localtime.h>

#define SEFUN_DAY_SECONDS (86400) // 一天的秒数
#define SEFUN_WEEK_SECONDS (604800) // 一周的秒数

// 外部自然传进来的参数，mon取值范围 1- 12
int mktime(int year, int mon, int day, int hour, int min, int sec)
{
    if(0 >= (mon -= 2)) {	/* 1..12 -> 11,12,1..10 */
        mon += 12;				/* Puts Feb last since it has leap day */
        year -= 1;
    }

    return ((( (year/4 - year/100 + year/400 + 367*mon/12 + day) + year*365 - 719499)*24 + hour )*60 + min)*60 + sec- 28800;
}

// 如果mon是用localtime函数取出来TimeNow[LT_MON]，必须要调本函数
int lpc_mktime(int year, int mon, int day, int hour, int min, int sec)
{
    mon += 1; // lpc 月份取值 0-11

    return mktime(year, mon, day, hour, min, sec);
}



int Min2Sec(int mins)
{
    return mins*60;
}

int Sec2Min(int secs)
{
    return secs/60;
}

int Sec2Day(int secs)
{
    return secs/3600/24;
}

// 函数：将字串转换成时间
// 将“YYYY-MM-DD HH:MMS”格式的时间字符串 -> time stamp
int String2Time(string time )
{
    int year, month, day, hour, min, sec;

    if (sscanf(time, "%d-%d-%d %d:%d:%d", year, month, day, hour, min, sec)  != 6 )
    {
        return 0;
    }

    return mktime(year, month, day, hour, min, sec);
}

// time stamp => chinese string
// 将时间转换成“YYYY-MM-DD HH:MMS”格式的时间字符串，
string Time2String(int time)
{
    mixed *mixTime = localtime( time );

    return sprintf("%04d年%02d月%02d日%02d时%02d分%02d秒", mixTime[LT_YEAR], mixTime[LT_MON] + 1, mixTime[LT_MDAY], mixTime[LT_HOUR], mixTime[LT_MIN], mixTime[LT_SEC]);
}

varargs string Time2StringNoYear(int time, string format)
{
    mixed *mixTime = localtime( time );

    if (!stringp(format) || format == "") format = "%02d月%02d日%02d时%02d分%02d秒"

    return sprintf(format, mixTime[LT_MON] + 1, mixTime[LT_MDAY], mixTime[LT_HOUR], mixTime[LT_MIN], mixTime[LT_SEC]);
}

// 函数：将秒数转换为“日时分”字符串，主要用来计时
// x天x时x分x秒
string Sec2String(int iTime)
{
    int iSec, iMin, iHour, iDay;
    string cRet = "";

    iSec  = iTime % 60;	iTime /= 60;
    iMin  = iTime % 60;	iTime /= 60;
    iHour = iTime % 24;	iTime /= 24;
    iDay  = iTime;

    if (iDay)  cRet += iDay  + "天";
    if (iHour) cRet += iHour + "时";
    if (iMin)  cRet += iMin  + "分";
    return cRet + iSec + "秒";
}

string Sec2HourStr(int iTime)
{
    int iSec, iMin, iHour, iDay;
    string cRet = "";

    iTime += 3600; // 精确到小时，+1
    iSec  = iTime % 60;	iTime /= 60;
    iMin  = iTime % 60;	iTime /= 60;
    iHour = iTime % 24;	iTime /= 24;
    iDay  = iTime;

    if (iDay)  cRet += iDay  + "天";
    if (iHour) cRet += iHour + "小时";
    // if (iMin)  cRet += iMin	+ "分";
    return cRet;
}


string Sec2MinStr(int iTime)
{
    int iSec, iMin, iHour, iDay;
    string cRet="";

    iTime += 60 - 1; //避免0秒的时候被当成1分钟
    iSec	= iTime % 60; iTime /= 60;
    iMin	= iTime % 60; iTime /= 60;
    iHour = iTime % 24; iTime /= 24;
    iDay	= iTime;

    if (iDay) cRet += iDay + "天";
    if (iHour) cRet += iHour + "小时";
    if (iMin) cRet += iMin + "分钟";

    return cRet;
}



string Sec2SecStr(int iTime)
{
    int iSec, iMin, iHour, iDay;
    string cRet = "";

    iSec  = iTime % 60; iTime /= 60;
    iMin  = iTime % 60; iTime /= 60;
    iHour = iTime % 24; iTime /= 24;
    iDay  = iTime;

    if (iDay)  cRet += iDay  + "天";
    if (iHour) cRet += iHour + "小时";
    if (iMin)  cRet += iMin  + "分钟";
    return cRet + iSec + "秒";
}

// 2017年05月29日 星期一 00时00分00秒 CST
#define TIME_BASE   (1495987200)

int get_timebase()
{
    return TIME_BASE;
}

int is_same_year(mixed mixTime0, mixed mixTime1)
{
    return mixTime0[LT_YEAR] == mixTime1[LT_YEAR];
}

int is_same_month(mixed mixTime0, mixed mixTime1)
{
    return ((mixTime0[LT_YEAR] == mixTime1[LT_YEAR]) &&
            (mixTime0[LT_MON] == mixTime1[LT_MON]));
}

int is_same_day(mixed mixTime0, mixed mixTime1)
{
    return ((mixTime0[LT_YEAR] == mixTime1[LT_YEAR]) &&
            (mixTime0[LT_MON]  == mixTime1[LT_MON])  &&
            (mixTime0[LT_MDAY] == mixTime1[LT_MDAY]));
}

static mapping mpRecentDay = {
0 : "今天",
    1 : "明天",
    2 : "后天",
    3 : "大后天",
    -1 : "昨天",
    -2 : "前天",
    -3 : "大前天",
};

int GetRelaDayNo( int iTime )
{
    int iStandard = TIME_BASE;
    iTime = iTime ? iTime : time();
    return abs(iTime - iStandard) / 3600 / 24 + 1;
}

string get_recent_day(int iTime)
{
    int iDay = GetRelaDayNo(iTime);
    int iToday = GetRelaDayNo(time());
    string day, week;
    int iWeek, iCurWeek;

    day = mpRecentDay[(iDay - iToday)];
    if (sizeof(day) > 0) {
        return day;
    }
    return "";
}

static mapping mpRecentWeek = {
    0 : "本周",
    1 : "下周",
    -1 : "上周",
};

int GetRelaWeekNo(int iTime)
{
    iTime = (iTime > 0) ? iTime : time();
    return abs(iTime - TIME_BASE) / 3600 / 24 / 7 + 1;
}

string get_recent_week(int iTime)
{
    mixed mixNow = localtime(time());
    mixed mixTime = localtime(iTime);
    int iNowWeek = GetRelaWeekNo(time());
    int iWeek = GetRelaWeekNo(iTime);
    string week;

    mixTime[LT_MON] += 1;

    week = mpRecentWeek[(iWeek - iNowWeek)];
    if (sizeof(week) > 0)
    {
        return week + "周" + mixTime[LT_WDAY];
    }
    return "";
}


string get_chinese_timestr(int iTime)
{
    string cDay = get_recent_day(iTime);
    mixed mixTime = localtime(iTime);
    string cHour;
    mixTime[LT_MON] += 1;
    cHour = "" + mixTime[LT_HOUR] + "点" + mixTime[LT_MIN] + "分";
    if (sizeof(cDay) > 0)
    {
        return cDay + "" + cHour;
    }
    cDay = get_recent_week(iTime);
    if (sizeof(cDay) > 0)
    {
        return cDay + "" + cHour;
    }
    cDay = "" + mixTime[LT_YEAR] + "年" + mixTime[LT_MON] + "月" + mixTime[LT_MDAY] + "号";
    return cDay + "" + cHour;
}

varargs string short_time( int iTime, int iFlag )
{
    mixed *mTime;

    // iTime 缺省的处理
    if( nullp(iTime) ) mTime = localtime( time() );
    else mTime = localtime(iTime);

    // iFlag 缺省的处理
    if( nullp(iFlag) ) iFlag = 0;
    if( !iFlag ) return sprintf("%04d-%02d-%02d %02d:%02d:%02d",
            mTime[LT_YEAR], mTime[LT_MON] + 1, mTime[LT_MDAY],
            mTime[LT_HOUR], mTime[LT_MIN], mTime[LT_SEC]);
    else return sprintf("%02d%02d%02d%02d%02d%02d",
            mTime[LT_YEAR] % 100, mTime[LT_MON] + 1, mTime[LT_MDAY],
            mTime[LT_HOUR], mTime[LT_MIN], mTime[LT_SEC]);
}

varargs int get_month(int iTime)
{
    mixed *mTime = localtime( iTime ? iTime : time() );

    return mTime[LT_MON] + 1;
}

// 当前时间到下个具体时间点的差值
int TimeDelta(int iToHour, int iToMinute, int iToSec, int nowTime)
{
    int iRes, iHour, iMinute, iSec, iTimeNow;
    int * TimeNow;

    iTimeNow = nowTime ? nowTime : time();
    TimeNow = localtime( iTimeNow );

    iRes = lpc_mktime( TimeNow[LT_YEAR], TimeNow[LT_MON], TimeNow[LT_MDAY], iToHour, iToMinute, iToSec ) - iTimeNow;

    if ( iRes <= 0 ) iRes += 86400;

    return iRes;
}

//下个整点时刻(秒)
// bContainCurrent : 如果当前时间是整点，是否把当前时间作为返回值
varargs int GetNextZhengdian( int iCurTime, int bContainCurrent )
{
    int iModSec = iCurTime % 3600;

    if( bContainCurrent )
    {
        return (iModSec == 0) ? iCurTime : (iCurTime - iModSec + 3600);
    }
    else
    {
        return (iModSec == 0) ? (iCurTime + 3600) : (iCurTime - iModSec + 3600);
    }
}

//上一个整点时刻(秒)
varargs int GetLastZhengdian( int iCurTime, int bContainCurrent )
{
    return GetNextZhengdian( iCurTime, !bContainCurrent) - 3600;
}

int GetYearWeekNo(int iTime)
{
    mixed *mTime = localtime(iTime);
    int year_start = lpc_mktime(mTime[LT_YEAR], 1, 1, 0 ,0 ,0);
    mTime = localtime(year_start);
    int wDay = mTime[LT_WDAY];
    int year_week_start = year_start - (wDay + 6) % 7 * SEFUN_DAY_SECONDS;
    return abs(iTime - year_week_start) / 3600 / 24 / 7 + 1;
}
