
/*
    @license:
    MIT License

    Copyright (c) 2022 Haruluya

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.   

    @version:0.0.1
    @date:2022/5/9
    @author:haruluya
    @model_function:"登录界面实现".
    @include:loginDialog.h  
    @log:loginDialog.log    
    @functions:{
        loginDlgProc:"窗口过程",
        validateUserName:"账号格式验证"，
        validatePassword:"密码格式验证",

    }

*/

#include"loginDialog.h"

/*
    @author:haruluya
    @date:2022/5/13
    @function:"登录界面窗口过程。"
    @input:{
        hDlg:"窗口句柄。",
        message:"事件信息。",
        wParam:"事件伴随参数。",
        lParam:"事件伴随参数。"
    }
    @output:{
    }
    @execute:[yuffie.WinMain]
    @return:"运行状态。"
*/
BOOL CALLBACK loginDlgProc(HWND hDlg, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    HWND hLabUsername;
    HWND hLabPassword;
    static HWND hEditUsername;
    static HWND hEditPassword;

    
    String userName = (String)malloc(sizeof(char)*100), password = (String)malloc(sizeof(char) * 100);
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
            GetWindowText(hEditUsername, userName, 80);
            GetWindowText(hEditPassword, password, 80);
            if (!validateUserName(userName) || !validatePassword(password)) {
                MessageBox(hDlg, TEXT("输入格式错误，请重新输入！"), TEXT("ERROR"), MB_ICONINFORMATION);
                return TRUE;
            }
            LoginMessage message = validateUser(userName, password);
            if (message.status <= 0) {
                messageBoxPrintf(TEXT("ERROR"), TEXT("ERROR: %s"), message.message);
                return TRUE;
            }
            messageBoxPrintf(TEXT("SUCCESS"), TEXT("SUCCESS: 登录成功 %s 欢迎回来!"), userName);
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

/*
    @author:haruluya
    @date:2022/5/13
    @function:"登录验证函数。"
    @input:{
        userName:"用户账号",
        password:"用户密码"
    }
    @output:{
    }
    @execute:[loginDialog.loginDlgProc]
    @return:"登录状态。"
*/
LoginMessage validateUser(String userName, String password) {
    return loginValidate(userName, password);
}