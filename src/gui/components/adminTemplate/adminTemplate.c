#include"adminTemplate.h"

LRESULT CALLBACK AdminWndProc(HWND hwnd, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    HDC             hdc;
    HDC             mdc;
    HMENU           hMenu;
    PAINTSTRUCT     ps;
    RECT            rect;
    static HDC hdcStatic;
    static HWND purchasePlanButton;
    static HWND reagentApplyButton;
    static HWND userManageButton;
    static HWND repertoryManageButton;
    static HWND logOutButton;


    static HWND  hLabWecome;
    static HBITMAP avaImg;
    static HBITMAP bgImg;
    static HWND  hLabName;
    static HFONT hFont;
    switch (message)
    {
    case WM_CREATE:
    {
 
        initFinalPurchaseList();
        hLabWecome = CreateWindow(TEXT("static"), TEXT("★欢迎使用YUFFIE★"),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            30, 10, 220, 50,
            hwnd,
            (HMENU)ID_YUFFIE_ADMIN_WECOME_LAB,
            hInst, NULL);
        hFont = CreateFont(-24, -12, 0, 0, 100, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "楷体");//创建字体

        String presentUserInfo = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        presentUserInfo = strcat(strcat(strcat(strcpy(presentUserInfo, presentUser.userName), "("), getIdentity(presentUser.identity)), ")");
        hLabName = CreateWindow(
            TEXT("static"),
            presentUserInfo,
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            500, 190, 250, 30,
            hwnd,
            (HMENU)ID_YUFFIE_ADMIN_NAME_LAB ,
            hInst, 
            NULL);


        purchasePlanButton = createDefaultButton(
            TEXT("button"),
            TEXT("采购计划"),
            80, 100, 150, 50,
            hwnd,
            (HMENU)ID_YUFFIE_ADMIN_PURCHASE_PLAN_BUTTON,
            hInst
            );

        reagentApplyButton = createDefaultButton(
            TEXT("button"),
            TEXT("领用申请"),
            80, 160, 150, 50,
            hwnd,
            (HMENU)ID_YUFFIE_ADMIN_REAGENT_APPLY_BUTTON,
            hInst
        );


        userManageButton = createDefaultButton(
            TEXT("button"),
            TEXT("用户管理"),
            80, 220, 150, 50,
            hwnd,
            (HMENU)ID_YUFFIE_USER_MANAGE_BUTTON,
            hInst
        );

        repertoryManageButton = createDefaultButton(
            TEXT("button"),
            TEXT("库存管理"),
            80, 280, 150, 50,
            hwnd,
            (HMENU)ID_YUFFIE_ADMIN_LAB_BUTTON,
            hInst
        );

        logOutButton = createDefaultButton(
            TEXT("button"),
            TEXT("退出登录"),
            80, 340, 150, 50,
            hwnd,
            (HMENU)ID_YUFFIE_ADMIN_LOGOUT_BUTTON,
            hInst
        );
        break;

    }

    case WM_PAINT:
    {
        avaImg = (HBITMAP)LoadImage(NULL, TEXT("G:\\桌面\\Course\\c语言课设\\bitmaps\\admin1.bmp"), IMAGE_BITMAP, 162, 172, LR_LOADFROMFILE);
        bgImg = (HBITMAP)LoadImage(NULL, TEXT("G:\\桌面\\Course\\c语言课设\\bitmaps\\bg1.bmp"), IMAGE_BITMAP, 400, 500, LR_LOADFROMFILE);

        SendMessage(hLabWecome, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(hLabName, WM_SETFONT, (WPARAM)hFont, TRUE);
        hdc = BeginPaint(hwnd, &ps);
        mdc = CreateCompatibleDC(hdc);
        SelectObject(mdc, bgImg);
        BitBlt(hdc, 120, 20, 400, 500, mdc, 0, 0, SRCAND);
        SelectObject(mdc, avaImg);
        BitBlt(hdc, 550, 5, 162, 172, mdc, 0, 0, SRCAND);
        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_CTLCOLORSTATIC:
        hdcStatic = (HDC)wParam;
        if (lParam == hLabWecome) {
            SetTextColor(hdcStatic, RGB(255, 51, 51));
        }
        else {
            SetTextColor(hdcStatic, RGB(0, 191, 255));
        }

        SetBkMode(hdcStatic, TRANSPARENT);
        return (INT_PTR)GetStockObject(NULL_BRUSH);


    case WM_COMMAND:
    {
        switch (LOWORD(wParam)) 
        {
        case ID_YUFFIE_ADMIN_LOGOUT_BUTTON:
        {
            if (IDOK != MessageBox(hwnd, TEXT("你确定要退出登录吗?"),
                TEXT("Exit"),
                MB_ICONQUESTION | MB_OKCANCEL))
                break;
            PostMessage(hwnd, WM_CLOSE, 111, 1);
            SendMessage(hwndFrame, WM_COMMAND, CM_YUFFIE_CREATE_HALL, 0);
            break;
        }
        case ID_YUFFIE_ADMIN_LAB_BUTTON:
        {
            DialogBox(hInst, MAKEINTRESOURCE(IDD_MAIN_LAB_DIALOG), hwnd, MainLabDlgProc);
            break;
        }
        case ID_YUFFIE_USER_MANAGE_BUTTON:
        {
            DialogBox(hInst, MAKEINTRESOURCE(IDD_USER_MANAGE_DIALOG), hwnd, UserManageDlgProc);
            break;
        }
        case ID_YUFFIE_ADMIN_PURCHASE_PLAN_BUTTON:
        {

            switch (purchasePlanStatus)
            {
            case ANNOUNCEMENT:
            {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_NOTICE_DIALOG), hwnd, AnnoucementDlgProc);
                break;
            }
            case REVIEWAPPLY:
            {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_REVIEW_APPLY_DIALOG), hwnd, ReviewApplyDlgProc);
                break;
            }
            case REVIEWOFFER:
            {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_REVIEW_OFFER_DIALOG), hwnd, ReviewOfferDlgProc);
                break;
            }
            default:
                break;
            }
        }
        break;
        }
    }
    case WM_MDIACTIVATE:


        if (lParam == (LPARAM)hwnd)
            SendMessage(hwndClient, WM_MDISETMENU,
                (WPARAM)hMenuSupplier, (LPARAM)hMenuSupplierWindow);


        if (lParam != (LPARAM)hwnd)
            SendMessage(hwndClient, WM_MDISETMENU, (WPARAM)hMenuInit,
                (LPARAM)hMenuInitWindow);

        DrawMenuBar(hwndFrame);
        return 0;

    case WM_QUERYENDSESSION:
    case WM_CLOSE:
        if (LOWORD(wParam) == 111) {
        }
        else if (IDOK != MessageBox(
            hwnd,
            TEXT("OK to close window?"),
            TEXT("Exit"),
            MB_ICONQUESTION | MB_OKCANCEL))
            return 0;
        break;

    case WM_DESTROY:
        return 0;
    }


    return DefMDIChildProc(hwnd, message, wParam, lParam);
}

