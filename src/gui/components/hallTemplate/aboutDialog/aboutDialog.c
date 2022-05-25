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

    @version:0.0.2
    @date:2022/5/15
    @author:haruluya
    @model_function:"[关于Yuffie]Dialog控件配置".
    @include:aboutDialog.h   
    @log:aboutDialog.log     
    @functions:{
        aboutDlgProc:"窗口过程.",
    }
*/
#include"aboutDialog.h"



BOOL CALLBACK aboutDlgProc(HWND hDlg, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    /*
        @value:"dialog句柄"
   */
    HDC         hdc;

    /*
        @value:"绘制状态信息。"
    */
    PAINTSTRUCT ps;

    /*
        @value:"设备句柄。"
    */
    HDC             mdc;

    /*
        @value:"img静态句柄。"
    */
    static HDC hdcStatic;

    /*
        @value:"About Label。"
    */
    static HWND  hLabAbout;

    /*
        @value:"背景位图。"
    */
    static HWND bgImg;

    /*
        @check:"消息队列处理。"
    */
    switch (message)
    {

    case WM_INITDIALOG:
    {
        hLabAbout = CreateWindow(
            TEXT("static"), 
            TEXT("\t本项目基于学期c语言语法和Win32 SDK知识，基本实现了实验室信息化管理系统功能。\n\t\tVersion 1.0.0"),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            20, 40, 200, 100,
            hDlg,
            (HMENU)ID_YUFFIE_ABOUT_ABOUT_LAB,
            hInst, 
            NULL);
        break;
    }

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDOK:
            EndDialog(hDlg, 0);
            return TRUE;
        }
        break;

    case WM_PAINT:
    {
        bgImg = (HBITMAP)LoadImage(NULL, TEXT("G:\\桌面\\Course\\c语言课设\\bitmaps\\bg3.bmp"), IMAGE_BITMAP, 400, 400, LR_LOADFROMFILE);
        hdc = BeginPaint(hDlg, &ps);
        mdc = CreateCompatibleDC(hdc);
        SelectObject(mdc, bgImg);
        BitBlt(hdc, 50, -100, 400, 400, mdc, 0, 0, SRCAND);
        EndPaint(hDlg, &ps);
        return 0;
    }
    case WM_CTLCOLORSTATIC:
    {
        hdcStatic = (HDC)wParam;
        SetTextColor(hdcStatic, RGB(0, 191, 255));
        SetBkMode(hdcStatic, TRANSPARENT);
        return (INT_PTR)GetStockObject(NULL_BRUSH);
    }
    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return TRUE;
    }
    return FALSE;
}