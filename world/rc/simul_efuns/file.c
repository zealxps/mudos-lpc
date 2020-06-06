static mapping cacheAssureFiles = {};

int last_modifed( string cFile )
{
	mixed st = stat(cFile);

	 if (! arrayp(st) || sizeof(st) < 2)
	 	return -1 ;

	return st[1];
}

int file_exist( string sFile ) { return file_size(sFile) > 0; }

int dir_exist( string sPath ) { return file_size(sPath) == -2; }

void assure_file( string sFile ) 
{ 
    string *sDir, sPath = "/";
    int i, iSize;

    if(!undefinedp(cacheAssureFiles[sFile])) return;
    cacheAssureFiles[sFile] = true;

    if(file_exist(sFile)) return;

    sDir = explode( sFile, "/" );
    sDir = sDir[ 0..<2 ];
    for( i = 0, iSize = sizeof(sDir); i < iSize; i ++ ) 
    {
        mkdir(sPath += sDir[i], 0);
        sPath += "/";
    }
}

void assure_dir( string Path )
{
	string *sDir, sPath = "/";
	int i, iSize;

	if (dir_exist(Path))	return ;

    sDir = explode(Path, "/");
    for (i = 0, iSize = sizeof(sDir); i < iSize; i ++ ) 
    {
		sPath += sDir[i];
		if (!dir_exist(sPath)) {
			mkdir(sPath, 0);
		}
		sPath += "/";
    }
}

int log_stat_file( string sDir, string sFile, string sMsg )
{
	sFile = sDir + sFile + ".log";
	assure_file(sFile);
	return write_file(sFile, sMsg ) ? 1 : 0;
}

string *remove_file_comments( string sFile )
{
	string *sList, *aRes = [];
	int i, iSize;

	if( !file_exist(sFile) ) return 0;
	if( !(sFile = read_file(sFile)) )  return 0;

	sList = explode( sFile, "\n" );

	for( i = 0, iSize = sizeof(sList); i < iSize; i++ ) 
		if ( sList[i][0] != '#') 
		{	
			aRes += [ sList[i] ];
		}

	return aRes;
}

string basename(string sFile)
{
    int len = sizeof(sFile);
    if (len == 0) return "";    // 异常
    string tmp = sFile;
    int tmplen = len;
    if (tmp[len - 1] == '/') {
        tmp = sFile[0..len - 2];
        tmplen = tmplen--;
    }
    int index = strsrch(tmp, '/', -1);
    if (index == -1) return sFile[0..len-1];
    return tmp[index + 1..tmplen - 1];
}

string dirname(string sFile)
{
    int len = sizeof(sFile);
    if (len == 0) return "";      // 异常
    string tmp = sFile;
    int tmplen = len;
    if (tmp[len - 1] == '/') {
        tmp = sFile[0..len - 2];
        tmplen --;
    }
    int index = strsrch(tmp, '/', -1);
    if (index == -1) return ".";
    return tmp[0..index - 1];
}

// 获取目录中以 ext 结尾的所有文件路径
// 返回值: { filepath: filesize, ... }
mapping get_files(string dirName, string ext)
{
    dirName = strip(dirName, "/");
    if (!stringp(ext)) ext = "";
    mapping allFiles = {};
    if (!dir_exist(dirName)) return allFiles;
    string *dirFiles = get_dir(dirName + "/");
    foreach (string file in dirFiles) {
        string filepath = dirName + "/" + file;
        // 如果是子目录
        if (dir_exist(filepath)) {
            allFiles += get_files(filepath, ext);
        } else if (is_end_with(filepath, ext)) {
            allFiles[filepath] = file_size(filepath);
        }
    }
    return allFiles;
}
