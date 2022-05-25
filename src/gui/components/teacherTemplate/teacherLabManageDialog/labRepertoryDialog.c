#include"labRepertoryDialog.h"

BOOL CALLBACK LabRepertoryDlgProc(HWND hDlg, UINT message,
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
    static HWND printButton;
    static HWND deleteButton;
    static HWND updateButton;
    static HWND hEditReNum;
    static HWND recButton;
    static int selectIndex;
    String num = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    switch (message)
    {

    case WM_INITDIALOG:
    {




        hLabTitle = CreateWindow(
            TEXT("static"),
            TEXT("★实验室库存管理★"),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            30, 10, 220, 50,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_REPERTORY_TITLE_LAB,
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
            hDlg, (HMENU)ID_YUFFIE_TEACHER_REPERTORY_LIST,
            hInst,
            NULL
        );

        hEditReNum = CreateWindow(
            TEXT("edit"),
            TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            450, 70, 150, 25,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_REAGENT_NUM_REID_EDIT,
            hInst,
            NULL
        );

        updateButton = createDefaultButton(
            TEXT("button"),
            TEXT("更新选中试剂数量"),
            450, 100, 150, 50,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_LAB_REPERTORY_UPDATE_BUTTON,
            hInst
        );

        manageButton = createDefaultButton(
            TEXT("button"),
            TEXT("查看入库记录"),
            450, 160, 150, 50,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_LAB_REPERTORY_MANAGE_BUTTON,
            hInst
        );

        recButton = createDefaultButton(
            TEXT("button"),
            TEXT("查看废液处理记录"),
            450, 220, 150, 50,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_LAB_REPERTORY_REC_BUTTON,
            hInst
        );

        printButton = createDefaultButton(
            TEXT("button"),
            TEXT("打印仓库"),
            450, 280, 150, 50,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_LAB_PRINT_BUTTON,
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
        switch (LOWORD(wParam)) {



        case CM_SHOW_LIST:
        {
            SendMessage(hwndList, LB_RESETCONTENT, 0, 0);
            SendMessage(hwndList, LB_INSERTSTRING, -1, "试剂名称    试剂ID    试剂数量");
            for (int i = 0; i < laborReaListLen; i++) {
                String labReInfo = (String)malloc(sizeof(char) * 100);
                labReInfo = strcpy(labReInfo, laborReaList[i].reagentName);
                String str = (String)malloc(sizeof(char) * 100);
                sprintf(str, "%d", laborReaList[i].reagentId);
                labReInfo = strcat(labReInfo, "    ");
                labReInfo = strcat(labReInfo, str);
                sprintf(str, "%d", laborReaList[i].reagentNum);
                labReInfo = strcat(labReInfo, "    ");
                labReInfo = strcat(labReInfo, str);
                SendMessage(hwndList, LB_INSERTSTRING, -1, labReInfo);
            }
            break;
        }
        case CM_SHOW_MANAGE_LIST:
        {
            SendMessage(hwndList, LB_RESETCONTENT, 0, 0);
            SendMessage(hwndList, LB_INSERTSTRING, -1, "试剂名称    更新时间    试剂ID    更新数量    更新方式");
            for (int i = 0; i < manageLabListLen; i++) {
                String manageLabInfo = (String)malloc(sizeof(char) * 100);
                manageLabInfo = strcpy(manageLabInfo, manageLabList[i].reagentName);
                manageLabInfo = strcat(manageLabInfo, "    ");
                manageLabInfo = strcat(manageLabInfo, manageLabList[i].time);
                String str = (String)malloc(sizeof(char) * 100);
                sprintf(str, "%d", manageLabList[i].reagentId);
                manageLabInfo = strcat(manageLabInfo, "    ");
                manageLabInfo = strcat(manageLabInfo, str);
                sprintf(str, "%d", manageLabList[i].reagentChangeNum);
                manageLabInfo = strcat(manageLabInfo, "    ");
                manageLabInfo = strcat(manageLabInfo, str);
                manageLabInfo = strcat(manageLabInfo, "    ");
                manageLabInfo = strcat(manageLabInfo, getUpdateWayName(manageLabList[i].mange));
                SendMessage(hwndList, LB_INSERTSTRING, -1, manageLabInfo);
            }
            break;
        }
        case ID_YUFFIE_TEACHER_LAB_REPERTORY_UPDATE_BUTTON:
        {
            GetWindowText(hEditReNum, num, INFO_MAXSIZE);
            if ((selectIndex = SendMessage(hwndList, LB_GETCURSEL, 0, 0)) != LB_ERR) {
                if (atoi(num) == 0) {
                    MessageBox(hDlg, TEXT("试剂数量变化不能为0！"), TEXT("ERROR"), MB_ICONINFORMATION);
                    break;
                }
                updateLabRepertory(laborReaList[selectIndex - 1].reagentId, atoi(num));
                createConsumMnanageItem(selectIndex - 1,atoi(num));
                SendMessage(hDlg, WM_COMMAND, CM_SHOW_LIST, 0);
                break;
            }
            else {
                MessageBox(hDlg, TEXT("请选择一个元素！"), TEXT("ERROR"), MB_ICONINFORMATION);
                break;
            }
        }
        case ID_YUFFIE_TEACHER_LAB_PRINT_BUTTON:
        {
            if (IDOK != MessageBox(hDlg, TEXT("打印实验室仓库库存？"),
                TEXT("Querry"),
                MB_ICONQUESTION | MB_OKCANCEL))
                break;
            printLabRepertory();
            MessageBox(hDlg, TEXT("已打印到labReperotyPrint.txt！"), TEXT("SUCCESS"), MB_ICONINFORMATION);
            break;
        }

        case ID_YUFFIE_TEACHER_LAB_REPERTORY_MANAGE_BUTTON:
        {
            String text = (String)malloc(sizeof(char) * INFO_MAXSIZE);
            GetWindowText(manageButton, text, INFO_MAXSIZE);
            if (!strcmp(text, "查看入库记录")) {
                if (IDOK != MessageBox(hDlg, TEXT("查看入库记录？"),
                    TEXT("Querry"),
                    MB_ICONQUESTION | MB_OKCANCEL))
                    break;
                
                ShowWindow(updateButton,FALSE);
                ShowWindow(hEditReNum, FALSE);
                SendMessage(hDlg, WM_COMMAND, CM_SHOW_MANAGE_LIST, 0);
                SetWindowText(manageButton, "查看库存");
            }
            else if (!strcmp(text, "查看库存")) {
                if (IDOK != MessageBox(hDlg, TEXT("查看库存？"),
                    TEXT("Querry"),
                    MB_ICONQUESTION | MB_OKCANCEL))
                    break;

                ShowWindow(updateButton, TRUE);
                ShowWindow(hEditReNum, TRUE);
                SendMessage(hDlg, WM_COMMAND, CM_SHOW_LIST, 0);
                SetWindowText(manageButton, "查看入库记录");
            }
            break;

        }
        case ID_YUFFIE_TEACHER_LAB_REPERTORY_REC_BUTTON:
        {

            DialogBox(hInst, MAKEINTRESOURCE(IDD_TEACHER_RECYCLE_DIALOG), hDlg, RecycleManageDlgProc);
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