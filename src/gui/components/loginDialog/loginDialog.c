#include"loginDialog.h"
#define IDC_RECT                        1008
#define IDC_BLACK                       1000
#define IDC_WHITE                       1007
#define IDC_ELLIPSE                     1009
#define IDC_PAINT 1010
int iCurrentColor  = IDC_BLACK,
    iCurrentFigure = IDC_RECT ;
int loginDialog(HWND hwnd,HWND hInst)
{
    WORD  *p, *pdlgtemplate;
    int   nchar;
    DWORD lStyle;

    // 手动申请内存。
    pdlgtemplate = p = (PWORD) LocalAlloc (LPTR, 1000);


    //配置dialog信息。
    lStyle = DS_MODALFRAME | WS_CAPTION | WS_SYSMENU | WS_VISIBLE;
    *p++ = LOWORD (lStyle);
    *p++ = HIWORD (lStyle);
    *p++ = 0;          // LOWORD (lExtendedStyle)
    *p++ = 0;          // HIWORD (lExtendedStyle)
    *p++ = 1;          // NumberOfItems
    *p++ = 100;         // x
    *p++ = 100;         // y
    *p++ = 100;        // cx
    *p++ = 100;        // cy
    *p++ = 0;          // Menu
    *p++ = 0;          // Class


    nchar = nCopyAnsiToWideChar (p, TEXT("LOGIN"));
    p += nchar;

    // 如果DS_SETFONT位开启，在这里添加wPointSize和szFontName。
    p = lpwAlign (p);


    // 设置按钮样式。
    lStyle = BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD;

    *p++ = LOWORD (lStyle);
    *p++ = HIWORD (lStyle);
    *p++ = 0;          // LOWORD (lExtendedStyle)
    *p++ = 0;          // HIWORD (lExtendedStyle)
    *p++ = 10;         // x
    *p++ = 70;         // y
    *p++ = 50;         // cx
    *p++ = 20;         // cy
    *p++ = IDI_LOGIN_IDOK;       // ID

    *p++ = (WORD)0xffff;
    *p++ = (WORD)0x0080;


    nchar = nCopyAnsiToWideChar (p, TEXT("OK"));
    p += nchar;
    *p++ = 0;  
    CreateDialogIndirect (hInst, (LPDLGTEMPLATE) pdlgtemplate, hwnd, (DLGPROC)loginProc);

    LocalFree (LocalHandle (pdlgtemplate));

    return 0;
}

void PaintWindow (HWND hwnd, int iColor, int iFigure)
{
     static COLORREF crColor[8] = { RGB (  0,   0, 0), RGB (  0,   0, 255),
                                    RGB (  0, 255, 0), RGB (  0, 255, 255),
                                    RGB (255,   0, 0), RGB (255,   0, 255),
                                    RGB (255, 255, 0), RGB (255, 255, 255) } ;

     HBRUSH          hBrush ;
     HDC             hdc ;
     RECT            rect ;
     
     hdc = GetDC (hwnd) ;
     GetClientRect (hwnd, &rect) ;
     hBrush = CreateSolidBrush (crColor[iColor - IDC_BLACK]) ;
     hBrush = (HBRUSH) SelectObject (hdc, hBrush) ;
     
     if (iFigure == IDC_RECT)
          Rectangle (hdc, rect.left, rect.top, rect.right, rect.bottom) ;
     else
          Ellipse   (hdc, rect.left, rect.top, rect.right, rect.bottom) ;
     
     DeleteObject (SelectObject (hdc, hBrush)) ;
     ReleaseDC (hwnd, hdc) ;
}

void PaintTheBlock (HWND hCtrl, int iColor, int iFigure)
{
     InvalidateRect (hCtrl, NULL, TRUE) ;
     UpdateWindow (hCtrl) ;
     PaintWindow (hCtrl, iColor, iFigure) ;
}

LRESULT CALLBACK loginProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    // if (message == WM_INITDIALOG)
    //     return TRUE;
    // if ((message == WM_COMMAND) && (LOWORD(wParam) == IDI_LOGIN_IDOK)) {
    //     EndDialog (hwnd, TRUE);
    //     return TRUE;
    // }
    // if ((message == WM_SYSCOMMAND) && (wParam == SC_CLOSE)) {
    //     EndDialog (hwnd, TRUE);
    //     return TRUE;
    // }
    static HWND hCtrlBlock ;
    static int  iColor, iFigure ;

    switch (message)
    {
    case WM_INITDIALOG:
    {
          iColor  = iCurrentColor ;
          iFigure = iCurrentFigure ;
          
          CheckRadioButton (hDlg, IDC_BLACK, IDC_WHITE,   iColor) ;
          CheckRadioButton (hDlg, IDC_RECT,  IDC_ELLIPSE, iFigure) ;
  
        hCtrlBlock = GetDlgItem (hDlg, IDC_PAINT) ;
        SetFocus (GetDlgItem (hDlg, iColor)) ;
          return FALSE ;
    }
    case WM_PAINT:
    {
        PaintTheBlock (hCtrlBlock, iColor, iFigure) ;
        break ;
    }
    default:
        break;
    }    


    return FALSE;
}

LPWORD lpwAlign ( LPWORD lpIn)
{
  ULONG ul;

  ul = (ULONG) lpIn;
  ul +=3;
  ul >>=2;
  ul <<=2;
  return (LPWORD) ul;
}


int nCopyAnsiToWideChar (LPWORD lpWCStr, LPSTR lpAnsiIn)
{
  int cchAnsi = lstrlen(lpAnsiIn);

  return MultiByteToWideChar(GetACP(), MB_PRECOMPOSED, lpAnsiIn, cchAnsi, lpWCStr, cchAnsi) + 1;
}


