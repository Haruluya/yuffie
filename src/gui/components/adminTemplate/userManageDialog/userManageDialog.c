#include"userManageDialog.h"

BOOL CALLBACK UserManageDlgProc(HWND hDlg, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    HDC             hdc;
    HDC             mdc;
    PAINTSTRUCT     ps;
    RECT            rect;
    static HWND hLabTitle;
    static HFONT hFont;
    static HDC hdcStatic;

    static HWND manageButton;
    static HWND hwndList;
    static HWND deleteButton;
    static int selectIndex;
    switch (message)
    {

    case WM_INITDIALOG:
    {
        hLabTitle = CreateWindow(
            TEXT("static"), 
            TEXT("★用户管理★"),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            30, 10, 220, 50,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_USER_MANAGE_TITLE_LAB,
            hInst, 
            NULL
        );
        hFont = CreateFont(-24, -12, 0, 0, 100, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "楷体");



        hwndList = CreateWindow(
            TEXT("listbox"), 
            NULL,
            WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_SORT | WS_BORDER,
            10, 60,
            400,
            300,
            hDlg, (HMENU)ID_YUFFIE_ADMIN_USER_MANAGE_LIST,
            hInst,
            NULL
        );

        deleteButton = createDefaultButton(
            TEXT("button"),
            TEXT("删除所选用户"),
            450, 100, 150, 50,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_USER_MANAGE_DELETE_BUTTON,
            hInst
        );

        manageButton = createDefaultButton(
            TEXT("button"),
            TEXT("添加用户"),
            450, 160, 150, 50,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_USER_MANAGE_ADD_BUTTON,
            hInst
        );



        SendMessage(hDlg, WM_COMMAND, CM_SHOW_LIST, 0);

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



            case CM_SHOW_LIST:
            {
                SendMessage(hwndList, LB_RESETCONTENT, 0, 0);
                SendMessage(hwndList, LB_INSERTSTRING, -1, "用户名称   用户id    用户身份");
                for (int i = 0; i < userListLen; i++) {
                    String userInfo = (String)malloc(sizeof(char) * 100);
                    userInfo = strcpy(userInfo, userList[i].userName);
                    String str = (String)malloc(sizeof(char) * 100);
                    sprintf(str, "%d", userList[i].id);
                    userInfo = strcat(userInfo, "    ");
                    userInfo = strcat(userInfo, str);
                    userInfo = strcat(userInfo, "    ");
                    userInfo = strcat(userInfo, getIdentity(userList[i].identity));
                    SendMessage(hwndList, LB_INSERTSTRING, -1, userInfo);
                }
                break;
            }
            case ID_YUFFIE_ADMIN_USER_MANAGE_DELETE_BUTTON:
            {
                if ((selectIndex = SendMessage(hwndList, LB_GETCURSEL, 0, 0)) != LB_ERR) {
                    if (IDOK != MessageBox(hDlg, TEXT("确认删除此用户？"),
                        TEXT("Querry"),
                        MB_ICONQUESTION | MB_OKCANCEL))
                        break;
                    deleteUser(userList[selectIndex - 1].id);
                    SendMessage(hDlg, WM_COMMAND, CM_SHOW_LIST, 0);
                    break;
                }
                else {
                    MessageBox(hDlg, TEXT("请选择一个元素！"), TEXT("ERROR"), MB_ICONINFORMATION);
                }
                break;

            }
            case ID_YUFFIE_ADMIN_USER_MANAGE_ADD_BUTTON:
            {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ADD_USER_DIALOG), hDlg, UserAddDlgProc);
                break;
            }
        }
        break;
    }
    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return TRUE;
    }
    return FALSE;
}