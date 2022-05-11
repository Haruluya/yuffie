#include<windows.h>
#include"../../guiTools.h"
#include"../id.h"

LRESULT APIENTRY About(HWND, UINT, WPARAM, LPARAM );
int loginDialog(HWND,HWND);
LRESULT CALLBACK loginProc(HWND, UINT, WPARAM, LPARAM);
LPWORD lpwAlign ( LPWORD);
int nCopyAnsiToWideChar (LPWORD, LPSTR);