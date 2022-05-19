#include"hallWindow.h"

LRESULT CALLBACK HallWndProc(HWND hwnd, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    /*
    @value:""
    */
    HDC         hdc;
    /*
    @value:"绘制状态信息。"
    */
    PAINTSTRUCT ps;

    /*
        @value:"title区域。"
    */
    RECT titleRect;

    /*
        @value:"title字体。"
    */
    static HFONT titleFont;

    /*
    @value:"进入系统按钮。"
    */
    static HWND beginButton;

    static HWND aboutYuffieButton;

    static HWND hLabVersion;

    HDC             mdc;
    static HBITMAP bgImg;
    static HDC hdcStatic;

  
    
    switch (message)
    {
    case WM_CREATE:
    {
       
        //创建进入系统按钮。
        beginButton = createDefaultButton(
        	TEXT("button"),
        	TEXT("Enter System"),
        	YUFFIE_BEGIN_BUTTON_X,
        	YUFFIE_BEGIN_BUTTON_Y,
        	YUFFIE_BEGIN_BUTTON_WIDTH,
        	YUFFIE_BEGIN_BUTTON_HEIGHT,
        	hwnd,
        	(HMENU)ID_YUFFIE_BEGIN_BUTTON,
        	hInst
        );


        beginButton = createDefaultButton(
            TEXT("button"),
            TEXT("About Yuffie"),
            YUFFIE_ABOUT_BUTTON_X,
            YUFFIE_ABOUT_BUTTON_Y,
            YUFFIE_ABOUT_BUTTON_WIDTH,
            YUFFIE_ABOUT_BUTTON_HEIGHT,
            hwnd,
            (HMENU)ID_YUFFIE_ABOUT_BUTTON,
            hInst
        );


        hLabVersion = CreateWindow(TEXT("static"), TEXT("Version:1.0.0"),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            200, 550, 220, 50,
            hwnd,
            (HMENU)ID_YUFFIE_VESION_LAB,
            hInst, NULL);

        

        return 0;
    }


    case WM_PAINT:
    {
        bgImg = (HBITMAP)LoadImage(NULL, TEXT("G:\\桌面\\Course\\c语言课设\\bitmaps\\bg5.bmp"), IMAGE_BITMAP, 850, 980, LR_LOADFROMFILE);
        hdc = BeginPaint(hwnd, &ps);
        mdc = CreateCompatibleDC(hdc);
        SelectObject(mdc, bgImg);
        BitBlt(hdc, -50, 0, 850, 980, mdc, 0, 0, SRCAND);
        PaintRoutine(hwnd, hdc, YUFFIE_CX_CLIENT, YUFFIE_CY_CLIENT);

        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_CTLCOLORSTATIC:
        hdcStatic = (HDC)wParam; 
        SetTextColor(hdcStatic, RGB(0, 191, 255));
        SetBkMode(hdcStatic, TRANSPARENT);
        return (INT_PTR)GetStockObject(NULL_BRUSH);


    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {


        case ID_YUFFIE_BEGIN_BUTTON:
        {
            //显示登录dialog。
            DialogBox(hInst, MAKEINTRESOURCE(IDD_LOGIN_DIALOG), hwnd, loginDlgProc);
            break;
        }
        case ID_YUFFIE_ABOUT_BUTTON:
        {
            //显示关于dialog。
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUT_DIALOG), hwnd, aboutDlgProc);
            break;
        }
        }

    }

    case WM_MDIACTIVATE:
    {
        if (lParam == (LPARAM)hwnd)
            SendMessage(hwndClient, WM_MDISETMENU,
                (WPARAM)hMenuSupplier, (LPARAM)hMenuSupplierWindow);


        if (lParam != (LPARAM)hwnd)
            SendMessage(hwndClient, WM_MDISETMENU, (WPARAM)hMenuInit,
                (LPARAM)hMenuInitWindow);

        DrawMenuBar(hwndFrame);
        return 0;
    };


    case WM_QUERYENDSESSION:
    case WM_CLOSE:
    {
        //if (LOWORD(wParam) == YUFFI_QUIT) {
        //    return 1;
        //}
        //if (IDOK != MessageBox(hwnd, TEXT("OK to close window?"),
        //    TEXT("Exit"),
        //    MB_ICONQUESTION | MB_OKCANCEL))
        //    return 0;
    }

        break;

    case WM_DESTROY:
        return 0;
    }

    return DefMDIChildProc(hwnd, message, wParam, lParam);
}
