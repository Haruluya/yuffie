
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
#include"resource.h"

/*
    @value:窗口坐标、宽高。
*/
#define YUFFIE_WINDOW_X 400
#define YUFFIE_WINDOW_Y 100
#define YUFFIE_WINDOW_NWIDTH 800
#define YUFFIE_WINDOW_NHEIGHT 600
#define YUFFIE_MAIN_TITLE TEXT("Yuffie:实验室信息化综合管理系统")

/*
    @value:按钮坐标、宽高。
*/
#define YUFFIE_BEGIN_BUTTON_X 300
#define YUFFIE_BEGIN_BUTTON_Y 350
#define YUFFIE_BEGIN_BUTTON_WIDTH 200
#define YUFFIE_BEGIN_BUTTON_HEIGHT 50
#define YUFFIE_CX_CLIENT 750
#define YUFFIE_CY_CLIENT 350

/*
    @value:菜单布局位置。
*/
#define INIT_MENU_POS    0
#define HELLO_MENU_POS   2
#define RECT_MENU_POS    1
#define IDM_FIRSTCHILD   50000




HMENU     hMenuInit, hMenuHello, hMenuRect;
HMENU     hMenuInitWindow, hMenuHelloWindow, hMenuRectWindow;

HINSTANCE hInst;
HWND     hwndFrame, hwndClient;
LRESULT CALLBACK FrameWndProc(HWND, UINT, WPARAM, LPARAM);