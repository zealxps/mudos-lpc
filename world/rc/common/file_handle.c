#include <var_prop.h>

MEMORY_VAR(FileSize, -1)
MEMORY_VAR(Start, 0)
MEMORY_VAR(FileEnd, 0)
MEMORY_VAR(LinePtr, 0)
MEMORY_VAR(LineCount, 0)
MEMORY_VAR(FileName, "")
MEMORY_VAR(ReadLines, [])

int READ_LINE_BUFF=4096;			//一次读入的字节数

//按回车解析成多行
string * Explode(string strInput)
{
    string * strArray = [];
    if( !sizeof(strInput) ) return strArray;
    
    strArray = explode( strInput, "\n" );
    if (strInput[<1..] == "\n") {
        strArray += [""];
    }
    return strArray;
}


//读入下一段 返回读入的实际行数
int ReadDocLines()
{
	int count = READ_LINE_BUFF;
	string result, lastLine="";

    if ( Start >= FileSize ){
        FileEnd = 1;
        return 0;
    }

    if ( Start + count > FileSize ){
        count = FileSize - Start;
        FileEnd = 1;
    }

    if ( LineCount )
        lastLine = ReadLines[LineCount - 1];

    result = lastLine + read_bytes( FileName, Start, count );
    Start += count;
    ReadLines = Explode( result );
    LineCount = sizeof( ReadLines );
    return LineCount;
}

string SeekLine()
{
	if (FileEnd)
	{
		if (LinePtr < LineCount)
			return ReadLines[LinePtr++];
	}
	else		
	{
	    if ( LinePtr < LineCount-1 )
		    return ReadLines[LinePtr++];

		if ( !ReadDocLines() ) return 0;
		LinePtr = 0;		
		return SeekLine();
	}
	return 0;
}

int Init(string fileName)
{
	FileSize = file_size(fileName);
	if (FileSize < 1) return 0;

	FileName = fileName;
	Start = 0;
	FileEnd = 0;
	LineCount = 0;
	LinePtr = 0;	
	ReadLines = [];

	return 1;
}

void do_destruct()
{
    "module/file_reader"->UpdateObjs();
}
