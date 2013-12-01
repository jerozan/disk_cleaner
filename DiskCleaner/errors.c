#include <Windows.h>
#include <stdio.h>
#include <strsafe.h>
#include "my_string.h"

INT display_error_msg(LPCTSTR text, DWORD dw)
{
	LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;

	 FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)text) + 40) * sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        text, dw, lpMsgBuf); 
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, "AutoClean", MB_ICONERROR);
	return (EXIT_FAILURE);
}

LPCTSTR get_error_msg(DWORD dw)
{
	LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;

	 FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf) + 40) * sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s"), lpMsgBuf); 
    return (LPCTSTR)trim(((LPTSTR)lpDisplayBuf));
}

INT display_usage_error()
{
	MessageBox(NULL, "Usage : AutoClean -[i|d] [-p path] [-L filename]", "AutoClean", MB_ICONINFORMATION);
	return (EXIT_FAILURE);
}

INT display_regedit_error()
{
	MessageBox(NULL, "Can't find path in regedit !", "AutoClean", MB_ICONERROR);
	return (EXIT_FAILURE);
}