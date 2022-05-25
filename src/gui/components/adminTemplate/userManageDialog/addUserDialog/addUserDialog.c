#include"addUserDialog.h"

BOOL CALLBACK UserAddDlgProc(HWND hDlg, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    HDC             hdc;
    HDC             mdc;
    PAINTSTRUCT     ps;
    RECT            rect;

    int userId;
    IDENTITY identity;

    static HWND hLabTitle;
    static HFONT hFont;
    static HDC hdcStatic;

    static HWND hLabUserName;
    static HWND hLabPassword;
    static HWND hEditUserName;
    static HWND hEditPassword;


    static HWND adminRadioButton;
    static HWND teacherRadioButton;
    static HWND supplierRadioButton;


    static HWND finishButton;

    String userName = (String)malloc(sizeof(char) * 100), password = (String)malloc(sizeof(char) * 100);

    switch (message)
    {

    case WM_INITDIALOG:
    {
        hLabTitle = CreateWindow(
            TEXT("static"), 
            TEXT("★创建用户★"),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            30, 10, 220, 50,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_ADD_USER_LAB,
            hInst, 
            NULL
        );
        hFont = CreateFont(-24, -12, 0, 0, 100, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "楷体");//创建字体


        hLabUserName = CreateWindow(
            TEXT("static"), 
            TEXT("账号："),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            40, 150, 70, 26,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_ADD_USER_USERNAME_LAB,
            hInst, 
            NULL
        );


        hEditUserName = CreateWindow(
            TEXT("edit"), 
            TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            120, 150, 200, 25,
            hDlg, 
            (HMENU)ID_YUFFIE_ADMIN_ADD_USER_USERNAME_EDIT,
            hInst, 
            NULL
        );

        hLabPassword = CreateWindow(
            TEXT("static"), 
            TEXT("密码："),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            40, 200, 70, 26,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_ADD_USER_PASSWORD_LAB,
            hInst, 
            NULL
        );

        hEditPassword = CreateWindow(
            TEXT("edit"), 
            TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            120, 200, 200, 25,
            hDlg, 
            (HMENU)ID_YUFFIE_ADMIN_ADD_USER_PASSWORD_EDIT,
            hInst,
            NULL
        );


        adminRadioButton = CreateWindow(
            TEXT("Button"),
            TEXT("Admin"),
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
            70, 100, 80, 30,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_ADD_USER_ADMIN_RADIO_BUTTON,
            hInst,
            NULL
        );

        teacherRadioButton = CreateWindow(
            TEXT("Button"),
            TEXT("Teacher"),
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            150, 100, 80, 30,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_ADD_USER_TEACHER_RADIO_BUTTON,
            hInst,
            NULL
        );

        supplierRadioButton = CreateWindow(
            TEXT("Button"),
            TEXT("Supplier"),
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            230, 100, 80, 30,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_ADD_USER_SUPPLIER_RADIO_BUTTON,
            hInst,
            NULL
        );

        finishButton = createDefaultButton(
            TEXT("button"),
            TEXT("完成"),
            130, 250, 120, 40,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_ADD_USER_FINISH_BUTTON,
            hInst
        );

        break;
    }
    case WM_CTLCOLORSTATIC:
    {
        hdcStatic = (HDC)wParam;
        if (lParam == hLabTitle) {
            SetTextColor(hdcStatic, RGB(0, 191, 255));
        }
        else {
            SetTextColor(hdcStatic, RGB(0, 191, 255));
        }

        SetBkMode(hdcStatic, TRANSPARENT);
        return (INT_PTR)GetStockObject(NULL_BRUSH);
    }
    case WM_PAINT:
    {
        SendMessage(hLabTitle, WM_SETFONT, (WPARAM)hFont, TRUE);
        hdc = BeginPaint(hDlg, &ps);
        EndPaint(hDlg, &ps);
        return 0;
    }

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
             case ID_YUFFIE_ADMIN_ADD_USER_FINISH_BUTTON:
             {
                 GetWindowText(hEditUserName, userName, 80);
                 GetWindowText(hEditPassword, password, 80);
                 if (!strcmp(userName, "") || !strcmp(password, "")) {
                     MessageBox(hDlg, TEXT("输入不为空，请重新输入！"), TEXT("ERROR"), MB_ICONINFORMATION);
                     break;
                 }
                 if (SendMessage(adminRadioButton, BM_GETCHECK, 0, 0) == BST_CHECKED) {
                     identity = ADMIN;
                 }
                 else if (SendMessage(teacherRadioButton, BM_GETCHECK, 0, 0) == BST_CHECKED) {
                     identity = TEACHER;
                 }
                 else if (SendMessage(teacherRadioButton, BM_GETCHECK, 0, 0) == BST_CHECKED) {
                     identity = SUPPLIER;
                 }
                 else {
                     MessageBox(hDlg, TEXT("请选择用户身份！"), TEXT("ERROR"), MB_ICONINFORMATION);
                     break;
                 }
                 User user = { userName,password,identity,userListLen + 1 };
                 addUser(user);
                 MessageBox(hDlg, TEXT("添加用户成功！"), TEXT("SUCCESS"), MB_ICONINFORMATION);
                 SendMessage(GetParent(hDlg), WM_COMMAND, CM_SHOW_LIST, 0);
                 break;
             }
            break;
        }
        break;
    }
    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return TRUE;
    }
    return FALSE;
}