int OpenFile(string fileName)
{
    return "rc/common/file_reader"->OpenFile(fileName);
}

string ReadFile(int fd)
{
    return "rc/common/file_reader"->ReadFile(fd);
}

void CloseFile(int fd)
{
    "rc/common/file_reader"->CloseFile(fd);
}
