// ExceptionHandlerOverload.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>

//#define USE_EXCEPTION

#ifdef USE_EXCEPTION
#define MY_TRY try
#define MY_CATCH catch(...)
#else
#define MY_TRY
#define MY_CATCH
#endif

class Foo
{

};

void fun()
{
#ifdef USE_EXCEPTION
    throw Foo();
#endif
}

int _tmain(int argc, _TCHAR* argv[])
{
    DWORD time = timeGetTime();
    for (int i = 0; i < 100000000; ++i)
    {
        MY_TRY
        {
            int j = i + 22;
            int k = j * i;
            int m = k * j;
            int n = k * m;
            if (i > 99999998)
            {
                fun();
            }
        }
        MY_CATCH
        {
            int ddd = i  * i;
        }
    }

    printf("%d\n", timeGetTime() - time);

	return 0;
}

