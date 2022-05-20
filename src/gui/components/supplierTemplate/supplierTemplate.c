
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
    @date:2022/5/13
    @author:haruluya
    @model_function:"supplier的事物处理界面".
    @include:supplierTemplate.h    
    @log:supplierTemplate.log     
    @functions:{
        testa:"This is a function for test.",
        testb:"This is a function for test." //源程序函数功能声明。
    }
*/
#include"supplierTemplate.h"

LRESULT CALLBACK SupplierWndProc(HWND hwnd, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    HDC             hdc;
    HDC             mdc;
    HMENU           hMenu;
    PAINTSTRUCT     ps;
    RECT            rect;
    int             selectIndex;
    static HWND  offerButton;
    static HWND  commitButton;
    static HWND  hwndList;
    static HWND  hLabCount;
    static HWND  hLabName;
    static HWND  hEditOfferPrice;
    static HWND  hLabOfferPrice;
    static HWND  hLabWecome;
    static HWND  purchaseOverviewButton;
    static HWND  logOutButton;
    static HWND  backHallButton;
    static HBITMAP avaImg;
    static HBITMAP bgImg;
    static HDC hdcStatic;
    static HFONT hFont;
    switch (message)
    {
    case WM_CREATE:
      
       
        /*
        @check:"导入purchaseTable表是否成功。"
        */
        if (!initPurchaseList()) {
            MessageBox(hwnd, TEXT("导入purchaseTable表失败！"), TEXT("ERROR"), MB_ICONINFORMATION);
        }

        hwndList = CreateWindow(
            TEXT("listbox"), 
            NULL,
            WS_CHILD | WS_VISIBLE | LBS_STANDARD |LBS_SORT |WS_BORDER,
            10, 100,
            400,
            400,
            hwnd, (HMENU)ID_YUFFI_SUPPLIER_LIST,
            hInst,
            NULL
        );

        SendMessage(hwndList, LB_INSERTSTRING, -1, "试剂名称    试剂id    试剂总数    报价");

        for (int i = 0; i < purchaseListLen; i++) {
            String purchaseTableInfo = (String)malloc(sizeof(char) * 100);
            purchaseTableInfo = strcpy(purchaseTableInfo, purchaseList[i].inventoryName);
            String str = (String)malloc(sizeof(char) * 100);
            sprintf(str, "%d", purchaseList[i].inventoryId);
            purchaseTableInfo = strcat(purchaseTableInfo, "    ");
            purchaseTableInfo = strcat(purchaseTableInfo, str);
            sprintf(str, "%d", purchaseList[i].inventoryNum);
            purchaseTableInfo = strcat(purchaseTableInfo, "    ");
            purchaseTableInfo = strcat(purchaseTableInfo, str);
            sprintf(str, "%d", purchaseList[i].inventoryPrice);
            purchaseTableInfo = strcat(purchaseTableInfo, "    ");
            purchaseTableInfo = strcat(purchaseTableInfo, str);
            SendMessage(hwndList, LB_INSERTSTRING, -1, purchaseTableInfo);
        }


        hLabCount = CreateWindow(
            TEXT("static"), 
            TEXT("当前需处理的采购清单:"),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            20, 60, 150, 26,
            hwnd,
            (HMENU)ID_YUFFIE_SUPPLIPER_WECOME_LAB,
            hInst, 
            NULL
        );

        String presentUserInfo = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        presentUserInfo = strcat(strcat(strcat(strcpy(presentUserInfo, presentUser.userName), "("), getIdentity(presentUser.identity)), ")");
        
        hLabName = CreateWindow(
            TEXT("static"), 
            presentUserInfo,
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            500, 190, 250, 30,
            hwnd,
            (HMENU)ID_YUFFIE_SUPPLIPER_NAME_LAB,
            hInst, NULL);

        offerButton = createDefaultButton(
            TEXT("button"),
            TEXT("出价"),
            550,320,150,50,
            hwnd,
            (HMENU)ID_YUFFIE_SUPPLIPER_OFFER_BUTTON,
            hInst
        );

        commitButton = createDefaultButton(
            TEXT("button"),
            TEXT("提交"),
            550, 380, 150, 50,
            hwnd,
            (HMENU)ID_YUFFIE_SUPPLIPER_COMMIT_BUTTON,
            hInst
        );

        backHallButton = createDefaultButton(
            TEXT("button"),
            TEXT("返回"),
            550, 440, 150, 50,
            hwnd,
            (HMENU)ID_YUFFIE_SUPPLIPER_BACK_BUTTON,
            hInst
        );

        hLabOfferPrice = CreateWindow(
            TEXT("static"), 
            TEXT("报价："),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            550, 250, 50, 26,
            hwnd,
            (HMENU)ID_YUFFIE_SUPPLIPER_OFFER_PRICE_LAB,
            hInst, 
            NULL
        );

        hEditOfferPrice = CreateWindow(
            TEXT("edit"), 
            TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            600, 251, 100, 25,
            hwnd, 
            (HMENU)ID_YUFFIE_SUPPLIPER_OFFER_PRICE_EDIT,
            hInst, 
            NULL
        );
      
        SendMessage(hwnd, WM_COMMAND, CM_YUFFIE_SUPPLIPER_SHOW_HALL, 0);


        hLabWecome = CreateWindow(
            TEXT("static"), 
            TEXT("★欢迎使用YUFFIE★"),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            30, 10, 220, 50,
            hwnd,
            (HMENU)ID_YUFFIE_SUPPLIPER_OFFER_PRICE_LAB,
            hInst, 
            NULL
        );
        hFont = CreateFont(-24, -12, 0, 0, 100, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "楷体");//创建字体

        purchaseOverviewButton = createDefaultButton(
            TEXT("button"),
            TEXT("订单管理"),
            80, 150, 150, 50,
            hwnd,
            (HMENU)ID_YUFFIE_SUPPLIPER_PURCHASE_BUTTON,
            hInst
        );

       logOutButton = createDefaultButton(
            TEXT("button"),
            TEXT("退出登录"),
            80, 220, 150, 50,
            hwnd,
            (HMENU)ID_YUFFIE_SUPPLIPER_LOGOUT_BUTTON,
            hInst
        );

        return 0;
    
    case WM_PAINT:
    {
        avaImg = (HBITMAP)LoadImage(NULL, TEXT("G:\\桌面\\Course\\c语言课设\\bitmaps\\supplier1.bmp"), IMAGE_BITMAP, 162, 172, LR_LOADFROMFILE);
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

        switch (LOWORD(wParam))
        {
            case ID_YUFFIE_SUPPLIPER_OFFER_BUTTON:
                if ((selectIndex = SendMessage(hwndList, LB_GETCURSEL, 0, 0)) != LB_ERR) {
                    String price = (String)malloc(sizeof(char)*100);
                    GetWindowText(hEditOfferPrice, price,10);
                    if (!price) {
                        messageBoxPrintf(TEXT("ERROR"), TEXT("请输入报价！"));
                        return 0;
                    }
                    else {
                        messageBoxPrintf(TEXT("SUCCESS"), TEXT("报价成功，你的报价为 %s"), price);
                    }

                    purchaseList[selectIndex-1].inventoryPrice = atoi(price);
                    SendMessage(hwndList, LB_DELETESTRING, selectIndex, 0);
                    selectIndex;
                    String purchaseTableInfo = (String)malloc(sizeof(char) * 100);
                    purchaseTableInfo = strcpy(purchaseTableInfo, purchaseList[selectIndex-1].inventoryName);
                    String str = (String)malloc(sizeof(char) * 100);
                    sprintf(str, "%d", purchaseList[selectIndex - 1].inventoryId);
                    purchaseTableInfo = strcat(purchaseTableInfo, "    ");
                    purchaseTableInfo = strcat(purchaseTableInfo, str);
                    sprintf(str, "%d", purchaseList[selectIndex - 1].inventoryNum);
                    purchaseTableInfo = strcat(purchaseTableInfo, "    ");
                    purchaseTableInfo = strcat(purchaseTableInfo, str);
                    sprintf(str, "%d", purchaseList[selectIndex - 1].inventoryPrice);
                    purchaseTableInfo = strcat(purchaseTableInfo, "    ");
                    purchaseTableInfo = strcat(purchaseTableInfo, str);
                    SendMessage(hwndList, LB_INSERTSTRING, selectIndex, purchaseTableInfo);

                }
                else {
                    MessageBox(hwnd, TEXT("请选择一个元素！"), TEXT("ERROR"), MB_ICONINFORMATION);
                }

                break;

            case ID_YUFFIE_SUPPLIPER_COMMIT_BUTTON:
                createOfferApply();
                messageBoxPrintf(TEXT("SUCCESS"), TEXT("提交报价表成功！"));
                SendMessage(hwndList, LB_RESETCONTENT, 0, 0);
                break;
            case ID_YUFFIE_SUPPLIPER_LOGOUT_BUTTON:
            {
                if (IDOK != MessageBox(hwnd, TEXT("你确定要退出登录吗?"),
                    TEXT("Exit"),
                    MB_ICONQUESTION | MB_OKCANCEL))
                    break;
                PostMessage(hwnd, WM_CLOSE, 111, 1);
                SendMessage(hwndFrame, WM_COMMAND, CM_YUFFIE_CREATE_HALL, 0);
                break;
                break;
            }
            case ID_YUFFIE_SUPPLIPER_PURCHASE_BUTTON:
            {
                if (IDOK != MessageBox(hwnd, TEXT("是否查看需处理采购报价？"),
                    TEXT("Querry"),
                    MB_ICONQUESTION | MB_OKCANCEL))
                    break;
                SendMessage(hwnd, WM_COMMAND, CM_YUFFIE_SHOW_PURCHASE,0);
                break;
            }
            case ID_YUFFIE_SUPPLIPER_BACK_BUTTON:
            {
                if (IDOK != MessageBox(hwnd, TEXT("是否返回主界面？"),
                    TEXT("Querry"),
                    MB_ICONQUESTION | MB_OKCANCEL))
                    break;
                SendMessage(hwnd, WM_COMMAND, CM_YUFFIE_SUPPLIPER_SHOW_HALL,0);
                break;
            }
            case CM_YUFFIE_SHOW_PURCHASE:
            {
                ShowWindow(hwndList, TRUE);
                ShowWindow(hLabCount, TRUE);
                ShowWindow(hLabOfferPrice, TRUE);
                ShowWindow(hEditOfferPrice, TRUE);
                ShowWindow(commitButton, TRUE);
                ShowWindow(offerButton, TRUE);
                ShowWindow(backHallButton, TRUE);

                ShowWindow(purchaseOverviewButton, FALSE);
                ShowWindow(logOutButton, FALSE);
                break;
            }
            case CM_YUFFIE_SUPPLIPER_SHOW_HALL:
            {
                ShowWindow(hwndList, FALSE);
                ShowWindow(hLabCount, FALSE);
                ShowWindow(hLabOfferPrice, FALSE);
                ShowWindow(hEditOfferPrice, FALSE);
                ShowWindow(commitButton, FALSE);
                ShowWindow(offerButton, FALSE);
                ShowWindow(backHallButton, FALSE);

                ShowWindow(purchaseOverviewButton, TRUE);
                ShowWindow(logOutButton, TRUE);
                break;
            }
         }
        return 0;


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
        }else if (IDOK != MessageBox(
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



Status showPurchasePanel() {

}