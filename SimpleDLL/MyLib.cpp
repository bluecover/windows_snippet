
#define MYLIBAPI extern "C" __declspec(dllexport)

int g_result;

extern "C" int __stdcall AddImpl(int a, int b);

typedef int (__stdcall* FunPtr)(int, int);

MYLIBAPI int __stdcall Add(int a, int b)
{
    FunPtr pfun = AddImpl;

    g_result = pfun(a, b);
    return g_result;
}
