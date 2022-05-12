#include"globalConst.h"
#include<tchar.h>
#include<stdio.h>
#include <math.h>

#define EZ_ATTR_BOLD          1
#define EZ_ATTR_ITALIC        2
#define EZ_ATTR_UNDERLINE     4
#define EZ_ATTR_STRIKEOUT     8

HWND createDefaultButton(LPCTSTR, LPCTSTR, int, int, int, int, HWND, HMENU, HANDLE);

void PaintRoutine(HWND, HDC, int, int);


HFONT EzCreateFont(HDC hdc, TCHAR* szFaceName, int iDeciPtHeight,
    int iDeciPtWidth, int iAttributes, BOOL fLogRes);


/*
    @function:"重构messagebox，支持格式化文字。"
*/
int CDECL messageBoxPrintf(TCHAR*, TCHAR*, ...);



BOOL    CALLBACK CloseEnumProc(HWND, LPARAM);
