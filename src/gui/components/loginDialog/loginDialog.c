#include"loginDialog.h"
#define IDC_RECT                        1008
#define IDC_BLACK                       1000

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
    static HWND beginButton;
	static RECT beginButtonRect;
	static int  beginButtonCxChar, beginButtonCyChar ;
    static int      cxClient, cyClient ;
	static HINSTANCE hInstance ;
    switch (message)
    {
    case WM_INITDIALOG:
    {
        static HWND hCtrlBlock ;
        static int  iColor, iFigure ;
        // hInstance = ((LPCREATESTRUCT) lParam)->hInstance;

		// beginButtonCxChar = 100 ;
		// beginButtonCyChar = 100;
		// beginButton = CreateWindow( 
		// 		TEXT("button"), 
        //         TEXT("Enter System"),
		// 		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,  
		// 		10,         
		// 		20,        
		// 		50,        
		// 		50,        
		// 		hwnd,    
		// 		(HMENU)IDI_BEGIN_BUTTON,      
		// 		hInstance,
		// 		NULL);
        //   iColor  = iCurrentColor ;
        //   iFigure = iCurrentFigure ;
          
        //   CheckRadioButton (hDlg, IDC_BLACK, IDC_WHITE,   iColor) ;
        //   CheckRadioButton (hDlg, IDC_RECT,  IDC_ELLIPSE, iFigure) ;
          
        //   hCtrlBlock = GetDlgItem (hDlg, IDC_PAINT) ;
          
        //   SetFocus (GetDlgItem (hDlg, iColor)) ;
          return TRUE ;
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
