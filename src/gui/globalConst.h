
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
    SOFTWARE.   //MIT证书声明，为固定部分。

    @version:0.0.1
    @date:2022/5/13
    @author:haruluya
    @model_function:"GUI界面全局使用的静态值类。"
    @include:[Windows.h,user.h,purchaseTable.h,resource.h]    
    @work:interface.c       
    @log:interfaces.log    

*/
#pragma once
#include<Windows.h>
#include"user.h"
#include"purchaseTable.h"
#include"purchaseNotice.h"
#include"purchaseCheck.h"
#include"finalPurchase.h"
#include"addRepertory.h"
#include"purchaseApplyTable.h"
#include"reagentApply.h"
#include"reagentCheck.h"
#include"teacherLabRepertory.h"
#include"teacherLabManage.h"
#include"recycleManage.h"
#include"flag.h"
#include"loginDialog.h"
#include"aboutDialog.h"
#include"announcementDialog.h"
#include"reviewApplyDialog.h"
#include"reviewOfferDialog.h"
#include"mainLabDialog.h"
#include"userManageDialog.h"
#include"addUserDialog.h"
#include"teacherApplyDialog.h"
#include"addPurchaseApplyDialog.h"
#include"reagentApplyDialog.h"
#include"addReagentApplyDialog.h"
#include"reviewReagentApplyDialog.h"
#include"reagentResultDialog.h"
#include"labRepertoryDialog.h"
#include"recycleManageDialog.h"
#include"addRecycleItemDialog.h"
#include"resource.h"
#include"adminTemplate.h"
#include"supplierTemplate.h"
#include"teacherTemplate.h"
#include"hallWindow.h"


/*
    @value:窗口坐标、宽高。
*/
#define YUFFIE_WINDOW_X 400
#define YUFFIE_WINDOW_Y 100
#define YUFFIE_WINDOW_NWIDTH 800
#define YUFFIE_WINDOW_NHEIGHT 600
#define YUFFIE_MAIN_TITLE TEXT("Yuffie:实验室信息化综合管理系统")






/*
    @value:菜单布局位置。
*/
#define INIT_MENU_POS    0
#define HELLO_MENU_POS   2
#define RECT_MENU_POS    1
#define IDM_FIRSTCHILD   50000

#define CM_YUFFIE_CREATE_HALL 700
#define CM_YUFFIE_CREATE_SUPPLIER 701
#define CM_YUFFIE_CREATE_ADMIN 702
#define CM_YUFFIE_CREATE_TEACHER 703
#define CM_YUFFI_QUIT 704

HMENU     hMenuInit, hMenuSupplier, hMenuRect;
HMENU     hMenuInitWindow, hMenuSupplierWindow, hMenuRectWindow;

HINSTANCE hInst;
HWND     hwndFrame, hwndClient, hwndHall, hwndSupplier,hwndAdmin;
LRESULT CALLBACK FrameWndProc(HWND, UINT, WPARAM, LPARAM);