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
    @date:2022/5/15
    @author:haruluya
    @model_function:"teacher视图中添加采购申请的dialog配置".
    @include:addPurchaseApplyDialog.h    
    @log:addPurchaseApplyDialog.log     
    @functions:{
        PurchaseApplyAddDlgProc:"窗口过程.",
    }
*/
#include"addPurchaseApplyDialog.h"

BOOL CALLBACK PurchaseApplyAddDlgProc(HWND hDlg, UINT message,
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

    static HWND hLabReName;
    static HWND hLabReId;
    static HWND hLabReNum;
    static HWND hEditReName;
    static HWND hEditReId;
    static HWND hEditReNum;
    static HWND hLabReClass;

    static HWND genRadioButton;
    static HWND speRadioButton;
    static HWND finishButton;

    String reName = (String)malloc(sizeof(char) * INFO_MAXSIZE), reId = (String)malloc(sizeof(char) * INFO_MAXSIZE),
        reNum = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    int reClass;

    switch (message)
    {

    case WM_INITDIALOG:
    {
        hLabTitle = CreateWindow(
            TEXT("static"), 
            TEXT("★添加试剂采购申请项★"),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            30, 10, 280, 50,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_PURCHASE_APPLY_LAB,
            hInst, 
            NULL
        );
        hFont = CreateFont(-24, -12, 0, 0, 100, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "楷体");//创建字体


        hLabReName = CreateWindow(
            TEXT("static"), 
            TEXT("名称："),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            40, 100, 70, 26,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_PURCHASE_APPLY_RENAME_LAB,
            hInst, 
            NULL
        );
        hEditReName = CreateWindow(
            TEXT("edit"), 
            TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            120, 100, 200, 25,
            hDlg, 
            (HMENU)ID_YUFFIE_TEACHER_PURCHASE_APPLY_RENAME_EDIT,
            hInst, 
            NULL
        );

        hLabReId = CreateWindow(
            TEXT("static"), 
            TEXT("Id："),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            40, 150, 70, 26,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_PURCHASE_APPLY_REID_LAB,
            hInst, 
            NULL
        );
        hEditReId = CreateWindow(
            TEXT("edit"), 
            TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            120, 150, 200, 25,
            hDlg, 
            (HMENU)ID_YUFFIE_TEACHER_PURCHASE_APPLY_REID_EDIT,
            hInst, 
            NULL
        );
        hLabReNum = CreateWindow(
            TEXT("static"), 
            TEXT("数量："),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            40, 200, 70, 26,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_PURCHASE_APPLY_RENUM_LAB,
            hInst, 
            NULL
        );
        hEditReNum = CreateWindow(
            TEXT("edit"), 
            TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            120, 200, 200, 25,
            hDlg, 
            (HMENU)ID_YUFFIE_TEACHER_PURCHASE_APPLY_RENUM_EDIT,
            hInst, 
            NULL
        );

        hLabReClass = CreateWindow(
            TEXT("static"), 
            TEXT("种类："),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            40, 60, 70, 26,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_PURCHASE_APPLY_RECLASS_LAB,
            hInst, 
            NULL
        );

        genRadioButton = CreateWindow(
            TEXT("Button"),
            TEXT("General"),
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
            150, 60, 80, 30,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_PURCHASE_APPLY_GEN_RADIO_BUTTON,
            hInst,
            NULL
        );
        speRadioButton = CreateWindow(
            TEXT("Button"),
            TEXT("Special"),
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            230, 60, 80, 30,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_PURCHASE_APPLY_SPE_RADIO_BUTTON,
            hInst,
            NULL
        );

        finishButton = createDefaultButton(
            TEXT("button"),
            TEXT("完成"),
            130, 250, 120, 40,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_PURCHASE_APPLY_FINISH_BUTTON,
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
            case ID_YUFFIE_TEACHER_PURCHASE_APPLY_FINISH_BUTTON:
            {
                GetWindowText(hEditReId, reId, 80);
                GetWindowText(hEditReName, reName, 80);
                GetWindowText(hEditReNum, reNum, 80);
                if (!strcmp(reId, "") || !strcmp(reName, "") || !strcmp(reNum, "")) {
                    MessageBox(hDlg, TEXT("输入不为空，请重新输入！"), TEXT("ERROR"), MB_ICONINFORMATION);
                    break;
                }
                if (SendMessage(genRadioButton, BM_GETCHECK, 0, 0) == BST_CHECKED) {
                    reClass = TGENERAL;
                }
                else if (SendMessage(speRadioButton, BM_GETCHECK, 0, 0) == BST_CHECKED) {
                    reClass = TSPECIAL;
                }
                else {
                    MessageBox(hDlg, TEXT("请选择试剂种类！"), TEXT("ERROR"), MB_ICONINFORMATION);
                    break;
                }

                purchaseTApplyItem item = { reName,reClass,atoi(reId),atoi(reNum) };
                addPurchaseApplyItem(item);
                MessageBox(hDlg, TEXT("添加试剂申请项成功！"), TEXT("SUCCESS"), MB_ICONINFORMATION);
                SendMessage(GetParent(hDlg), WM_COMMAND, CM_SHOW_LIST, 0);
                EndDialog(hDlg,0);
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