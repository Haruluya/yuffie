#include"reviewApplyDialog.h"

BOOL CALLBACK ReviewApplyDlgProc(HWND hDlg, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    HDC             hdc;
    HDC             mdc;
    PAINTSTRUCT     ps;
    RECT            rect;
    static HWND hLabTitle;
    static HFONT hFont;
    static HDC hdcStatic;


    static HWND allRRadioButton;
    static HWND speRRadioButton;
    static HWND gelRRadioButton;

    static HWND hwndList;
    static HWND deleteButton;
    static HWND finishButton;
    static int selectIndex;
    switch (message)
    {

    case WM_INITDIALOG:
    {
        hLabTitle = CreateWindow(TEXT("static"), TEXT("★审核采购申请★"),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            30, 10, 220, 50,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_REVIEW_APPLY_TITLE_LAB,
            hInst, NULL);
        hFont = CreateFont(-24, -12, 0, 0, 100, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "楷体");



        hwndList = CreateWindow(TEXT("listbox"), NULL,
            WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_SORT | WS_BORDER,
            10, 60,
            400,
            300,
            hDlg, (HMENU)ID_YUFFIE_ADMIN_REVIEW_APPLY_LIST,
            hInst,
            NULL
        );
        allRRadioButton = CreateWindow(
            TEXT("Button"),
            TEXT("所有申请"),
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
            450, 60, 150, 30,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_ALL_RADIO_BUTTON,
            hInst,
            NULL
        );
        gelRRadioButton = CreateWindow(
            TEXT("Button"),
            TEXT("普通试剂"),
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            450, 90, 150, 30,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_GEL_RADIO_BUTTON,
            hInst,
            NULL
        );
        speRRadioButton = CreateWindow(
            TEXT("Button"),
            TEXT("特殊试剂"),
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            450, 120, 150, 30,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_SPE_RADIO_BUTTON,
            hInst,
            NULL
        );
        deleteButton = createDefaultButton(
            TEXT("button"),
            TEXT("删除选中项"),
            450, 160, 150, 50,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_REVIEW_APPLY_DELETE_BUTTON,
            hInst
        );

        finishButton = createDefaultButton(
            TEXT("button"),
            TEXT("提交审核"),
            450, 220, 150, 50,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_REVIEW_APPLY_FINISH_BUTTON,
            hInst
        );

  
        SendMessage(hDlg, WM_COMMAND, ID_YUFFIE_ADMIN_ALL_RADIO_BUTTON, 0);


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
        case ID_YUFFIE_ADMIN_ALL_RADIO_BUTTON:
        {
            SendMessage(hwndList, LB_RESETCONTENT, 0, 0);
            SendMessage(hwndList, LB_INSERTSTRING, -1, "试剂名称    试剂类别    试剂id");
            LinkList p;
            p = apply->next;
            while(p) {
                String purchaseListInfo = (String)malloc(sizeof(char) * 100);
                purchaseListInfo = strcpy(purchaseListInfo, p->data.inventoryName);
                String str = (String)malloc(sizeof(char) * 100);
                sprintf(str, "%d", p->data.inventoryClass);
                purchaseListInfo = strcat(purchaseListInfo, "    ");
                purchaseListInfo = strcat(purchaseListInfo, str);
                sprintf(str, "%d", p->data.inventoryId);
                purchaseListInfo = strcat(purchaseListInfo, "    ");
                purchaseListInfo = strcat(purchaseListInfo, str);
                SendMessage(hwndList, LB_INSERTSTRING, -1, purchaseListInfo);
                p = p->next;
            }
            break;
        }
        case ID_YUFFIE_ADMIN_GEL_RADIO_BUTTON:
        {
            SendMessage(hwndList, LB_RESETCONTENT, 0, 0);
            SendMessage(hwndList, LB_INSERTSTRING, -1, "试剂名称    试剂类别    试剂id");
            for (int i = 0; i < gPurchaseListLen; i++) {
                String gPurchaseListInfo = (String)malloc(sizeof(char) * 100);
                gPurchaseListInfo = strcpy(gPurchaseListInfo, gPurchaseList[i].inventoryName);
                String str = (String)malloc(sizeof(char) * 100);
                sprintf(str, "%d", gPurchaseList[i].inventoryClass);
                gPurchaseListInfo = strcat(gPurchaseListInfo, "    ");
                gPurchaseListInfo = strcat(gPurchaseListInfo, str);
                sprintf(str, "%d", gPurchaseList[i].inventoryId);
                gPurchaseListInfo = strcat(gPurchaseListInfo, "    ");
                gPurchaseListInfo = strcat(gPurchaseListInfo, str);
                SendMessage(hwndList, LB_INSERTSTRING, -1, gPurchaseListInfo);
            }
            break;
        }
        case ID_YUFFIE_ADMIN_SPE_RADIO_BUTTON:
        {
            SendMessage(hwndList, LB_RESETCONTENT, 0, 0);
            SendMessage(hwndList, LB_INSERTSTRING, -1, "试剂名称    试剂类别    试剂id");
            for (int i = 0; i < sPurchaseListLen; i++) {
                String sPurchaseListInfo = (String)malloc(sizeof(char) * 100);
                sPurchaseListInfo = strcpy(sPurchaseListInfo, sPurchaseList[i].inventoryName);
                String str = (String)malloc(sizeof(char) * 100);
                sprintf(str, "%d", sPurchaseList[i].inventoryClass);
                sPurchaseListInfo = strcat(sPurchaseListInfo, "    ");
                sPurchaseListInfo = strcat(sPurchaseListInfo, str);
                sprintf(str, "%d", sPurchaseList[i].inventoryId);
                sPurchaseListInfo = strcat(sPurchaseListInfo, "    ");
                sPurchaseListInfo = strcat(sPurchaseListInfo, str);
                SendMessage(hwndList, LB_INSERTSTRING, -1, sPurchaseListInfo);
            }
            break;
        }
        case ID_YUFFIE_ADMIN_REVIEW_APPLY_DELETE_BUTTON:
        {
            if (IDOK != MessageBox(hDlg, TEXT("你确定要删除此项？"),
                TEXT("Querry"),
                MB_ICONQUESTION | MB_OKCANCEL))
                break;
            if ((selectIndex = SendMessage(hwndList, LB_GETCURSEL, 0, 0)) != LB_ERR) {
                SendMessage(hwndList, LB_DELETESTRING, selectIndex, 0);
                if (SendMessage(allRRadioButton, BM_GETCHECK, 0, 0) == BST_CHECKED) {
                    deletePurchaseTable(purchaseTable[selectIndex-1].inventoryId);
                }
                else if (SendMessage(gelRRadioButton, BM_GETCHECK, 0, 0) == BST_CHECKED) {
                    deleteGPurchaseTable(gPurchaseList[selectIndex - 1].inventoryId);
                }
                else if (SendMessage(gelRRadioButton, BM_GETCHECK, 0, 0) == BST_CHECKED) {
                    deleteSPurchaseTable(sPurchaseList[selectIndex - 1].inventoryId);
                }
            }
            else {
                MessageBox(hDlg, TEXT("请选择一个元素！"), TEXT("ERROR"), MB_ICONINFORMATION);
            }
            break;
        }
        case ID_YUFFIE_ADMIN_REVIEW_APPLY_FINISH_BUTTON:
        {
            if (IDOK != MessageBox(hDlg, TEXT("你确定要提交审核？"),
                TEXT("Querry"),
                MB_ICONQUESTION | MB_OKCANCEL))
                break;
            createPurchaseTable();
            MessageBox(hDlg, TEXT("提交审核成功！"), TEXT("SUCCESS"), MB_ICONINFORMATION);
            setPurchasePlanStatus(REVIEWOFFER);
            EndDialog(hDlg,0);
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