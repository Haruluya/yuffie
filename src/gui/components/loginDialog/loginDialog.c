#include"loginDialog.h"


BOOL CALLBACK loginDlgProc(HWND hDlg, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    HWND hLabUsername;
    HWND hLabPassword;
    static HWND hEditUsername;
    static HWND hEditPassword;

    
    String userName = TEXT(""), password = TEXT("");
    switch (message)
    {
    case WM_INITDIALOG:
        hLabUsername = CreateWindow(TEXT("static"), TEXT("账号："),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE  | SS_RIGHT ,
            40 , 150 , 70 , 26 ,
            hDlg ,
            (HMENU)ID_YUFFIE_USERNAME_LAB ,
            hInst, NULL);
        hEditUsername = CreateWindow(TEXT("edit"), TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER  | ES_AUTOHSCROLL,
            120, 150, 200, 25,
            hDlg, (HMENU)ID_YUFFIE_USERNAME_EDIT, hInst, NULL);
        hLabPassword = CreateWindow(TEXT("static"), TEXT("密码："),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            40, 200, 70, 26,
            hDlg,
            (HMENU)ID_YUFFIE_PASSWORD_LAB,
            hInst, NULL);
        hEditPassword = CreateWindow(TEXT("edit"), TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            120, 200, 200, 25,
            hDlg, (HMENU)ID_YUFFIE_PASSWORD_EDIT, hInst, NULL);
        break;

        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
        {
            GetWindowText(hEditUsername, &userName, 20);
            GetWindowText(hEditPassword, &password, 20);
            if (!validateUserName(userName) || !validatePassword(password)) {
                MessageBox(hDlg, TEXT("输入格式错误，请重新输入！"), TEXT("ERROR"), MB_ICONINFORMATION);
                return TRUE;
            }
            LoginMessage message = validateUser(userName, password);
            if (!message.status) {
                messageBoxPrintf(TEXT("ERROR"), TEXT("ERROR: %s"), message.message);
                return TRUE;
            }
            messageBoxPrintf(TEXT("SUCCESS"), TEXT("SUCCESS: %s"), message.message);
            EndDialog(hDlg, 0);
            SendMessage(GetParent(hDlg), WM_COMMAND,
                IDD_LOGIN_DIALOG, (LPARAM)hDlg);
           
            return TRUE;
        }
        case IDCANCEL:

            EndDialog(hDlg, 0);
            return TRUE;
        }
        break;
    }
    return FALSE;
}


BOOL validateUserName(String userName) {
    return TRUE;
}



BOOL validatePassword(String password) {
    return TRUE;
}

LoginMessage validateUser(String userName, String password) {
    LoginMessage message = { OK ,"登录成功" };
    return message;
}