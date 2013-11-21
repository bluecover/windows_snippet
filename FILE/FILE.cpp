// FILE.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
    FILE* pfile=NULL;
    char* ch;
    char str[100]="To be or not to be,that is a question.";
    pfile=fopen("outfile.txt","w"); //每次写入都先删除"outfile.txt"里面的内容。若要将新的内容添加到结尾可这样：\
    pfile=fopen("outfile.txt","a"); ("a"表示"add");
    for(ch=&str[0];*ch!='\0';ch++)
    {
        fputc(*ch,pfile);
    }
    printf("写到文件成功。");
    getchar();
 
    fstream fs;
    fs.open("./ReadMe.txt", ios::in | ios::binary|ios::ate);
    if (fs.fail())
    {
        return 0;
    }
    streampos pos = fs.tellg();

    return 0;
}

