#include"reagentApplyDialog.h"

BOOL CALLBACK ReagentApplyDlgProc(HWND hDlg, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    HDC             hdc;
    HDC             mdc;
    PAINTSTRUCT     ps;
    RECT            rect;
    static HWND hLabTitle;
    static HFONT hFont;
    static HDC hdcStatic;

    static HWND hwndList;
    static HWND deleteButton;
    static HWND addButton;
    static HWND finishButton;
    static int selectIndex;
    switch (message)
    {

    case WM_INITDIALOG:
    {
        hLabTitle = CreateWindow(
            TEXT("static"),
            TEXT("★试剂领用申请★"),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            30, 10, 220, 50,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_REAGENT_APPLY_TITLE_LAB,
            hInst, 
            NULL
        );
        hFont = CreateFont(-24, -12, 0, 0, 100, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "楷体");

        hwndList = CreateWindow(TEXT("listbox"), NULL,
            WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_SORT | WS_BORDER,
            10, 60,
            400,
            300,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_REAGENT_APPLY_LIST,
            hInst,
            NULL
        );

        addButton = createDefaultButton(
            TEXT("button"),
            TEXT("添加申请项"),
            450, 100, 150, 50,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_REAGENT_ADD_BUTTON,
            hInst
        );

        deleteButton = createDefaultButton(
            TEXT("button"),
            TEXT("删除选中项"),
            450, 160, 150, 50,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_REAGENT_DELETE_BUTTON,
            hInst
        );

        finishButton = createDefaultButton(
            TEXT("button"),
            TEXT("提交申请"),
            450, 220, 150, 50,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_REAGENT_COMMIT_BUTTON,
            hInst
        );


        //SendMessage(hDlg, WM_COMMAND, ID_YUFFIE_ADMIN_ALL_RADIO_BUTTON, 0);


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
        switch (LOWORD(wParam)) {
        
            case ID_YUFFIE_TEACHER_REAGENT_ADD_BUTTON:
            {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_REAGENT_APPLY_ADD_DIALOG), hDlg, ReagentApplyAddDlgProc);
                break;
            }
            case ID_YUFFIE_TEACHER_REAGENT_DELETE_BUTTON:
            {
                if (IDOK != MessageBox(hDlg, TEXT("你确定要删除此项？"),
                    TEXT("Querry"),
                    MB_ICONQUESTION | MB_OKCANCEL))
                    break;
                if ((selectIndex = SendMessage(hwndList, LB_GETCURSEL, 0, 0)) != LB_ERR) {
                    SendMessage(hwndList, LB_DELETESTRING, selectIndex, 0);
                }
                else {
                    MessageBox(hDlg, TEXT("请选择一个元素！"), TEXT("ERROR"), MB_ICONINFORMATION);
                }
                break;
            }
            case ID_YUFFIE_TEACHER_REAGENT_COMMIT_BUTTON:
            {
                if (IDOK != MessageBox(hDlg, TEXT("你确定要提交申请？"),
                    TEXT("Querry"),
                    MB_ICONQUESTION | MB_OKCANCEL))
                    break;
                MessageBox(hDlg, TEXT("提交申请成功！"), TEXT("SUCCESS"), MB_ICONINFORMATION);
                EndDialog(hDlg, 0);
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