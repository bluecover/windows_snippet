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
    pfile=fopen("outfile.txt","w"); //ÿ��д�붼��ɾ��"outfile.txt"��������ݡ���Ҫ���µ�������ӵ���β��������\
    pfile=fopen("outfile.txt","a"); ("a"��ʾ"add");
    for(ch=&str[0];*ch!='\0';ch++)
    {
        fputc(*ch,pfile);
    }
    printf("д���ļ��ɹ���");
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

