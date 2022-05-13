
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

LRESULT CALLBACK HelloWndProc(HWND hwnd, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    HDC             hdc;
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
    switch (message)
    {
    case WM_CREATE:


        // Create listbox and static text windows.

        hwndList = CreateWindow(TEXT("listbox"), NULL,
            WS_CHILD | WS_VISIBLE | LBS_STANDARD |LBS_SORT |WS_BORDER,
            10, 50,
            400,
            400,
            hwnd, (HMENU)ID_SUPPLIER_LIST,
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

        hLabCount = CreateWindow(TEXT("static"), TEXT("Purchase List"),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            50, 450, 120, 26,
            hwnd,
            (HMENU)ID_YUFFIE_SUPPLIPER_COUNT_LAB,
            hInst, NULL);


        offerButton = createDefaultButton(
            TEXT("button"),
            TEXT("OFFER"),
            450,270,150,50,
            hwnd,
            (HMENU)ID_YUFFIE_OFFER_BUTTON,
            hInst
        );

        commitButton = createDefaultButton(
            TEXT("button"),
            TEXT("COMMIT"),
            450, 370, 150, 50,
            hwnd,
            (HMENU)ID_YUFFIE_COMMIT_BUTTON,
            hInst
        );

        hLabOfferPrice = CreateWindow(TEXT("static"), TEXT("报价："),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            450, 200, 50, 26,
            hwnd,
            (HMENU)ID_YUFFIE_SUPPLIPER_COUNT_LAB,
            hInst, NULL);

        hEditOfferPrice = CreateWindow(TEXT("edit"), TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            500, 200, 100, 40,
            hwnd, (HMENU)ID_YUFFIE_OFFER_PRICE_EDIT, hInst, NULL);

        return 0;

    case WM_COMMAND:

        switch (LOWORD(wParam))
        {
        case ID_YUFFIE_OFFER_BUTTON:
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

        case ID_YUFFIE_COMMIT_BUTTON:
            createOfferApply();
            messageBoxPrintf(TEXT("SUCCESS"), TEXT("提交报价表成功！"));
        }
        return 0;


    case WM_MDIACTIVATE:


        if (lParam == (LPARAM)hwnd)
            SendMessage(hwndClient, WM_MDISETMENU,
                (WPARAM)hMenuHello, (LPARAM)hMenuHelloWindow);


        if (lParam != (LPARAM)hwnd)
            SendMessage(hwndClient, WM_MDISETMENU, (WPARAM)hMenuInit,
                (LPARAM)hMenuInitWindow);

        DrawMenuBar(hwndFrame);
        return 0;

    case WM_QUERYENDSESSION:
    case WM_CLOSE:
        if (IDOK != MessageBox(hwnd, TEXT("OK to close window?"),
            TEXT("Hello"),
            MB_ICONQUESTION | MB_OKCANCEL))
            return 0;

        break;   

    case WM_DESTROY:
        return 0;
    }


    return DefMDIChildProc(hwnd, message, wParam, lParam);
}