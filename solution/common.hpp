#pragma once
#include <Windows.h>
#include <winternl.h>

#ifdef NDEBUG
void DPRINT(LPCWSTR str, auto... args)
{
}
#else
void DPRINT(LPCWSTR str, auto... args)
{
    {
        wchar_t buf[512]{0};
        int     len = wsprintfW(buf, str, args...);
        if (len >= 0)
        {
            OutputDebugStringW(buf);
        }
    }
}
#endif