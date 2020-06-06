#include <var_prop.h>
MEMORY_VAR(CurFd, 0)
MEMORY_VAR(FileObjs, {})

int OpenFile(string fileName)
{
    object obj = clone_object("rc/common/file_handle");
    if ( !obj->Init(fileName) ) {
         destruct(obj);   
         return -1;
    } 

    if( !objectp(obj) ){
        debug_message( "[warn] can't clone file object ! ");
        return -1;
    } 

    CurFd++;

    if ( CurFd < 0 ) CurFd = 1;
    
    FileObjs[CurFd] = obj;

    return CurFd;
}

string ReadFile(int fd)
{
    if( objectp(FileObjs[fd]) ){
        return FileObjs[fd]->SeekLine(); 
    }
    return 0;
}

void CloseFile(int fd)
{
    if( !objectp(FileObjs[fd]) ) return;
 
    destruct(FileObjs[fd]);
    map_delete(FileObjs, fd);
}

void on_loadin()
{
    
}

void UpdateObjs()
{
    mapping cache = {}; 
    foreach( int fd, object obj in FileObjs ){
        cache[fd] = obj->GetVarsValue();
        destruct(obj);
    }

    foreach( int fd, mapping c in cache ){
        FileObjs[fd] = clone_object("rc/common/file_handle");
        FileObjs[fd]->SetVarsValue(c);
    }
}
