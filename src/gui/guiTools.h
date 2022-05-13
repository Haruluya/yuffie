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
    @model_function:"gui工具类，包含gui操作的封装。".
    @include:[globalConst.h,tchar.h,stdio.h,math.h]    
    @work:guiTools.c       
    @log:guiTools.log     

*/


#include"globalConst.h"
#include<tchar.h>
#include<stdio.h>
#include <math.h>
#define EZ_ATTR_BOLD          1
#define EZ_ATTR_ITALIC        2
#define EZ_ATTR_UNDERLINE     4
#define EZ_ATTR_STRIKEOUT     8

/*
    @function:"创建默认按钮封装。"
*/
HWND createDefaultButton(LPCTSTR, LPCTSTR, int, int, int, int, HWND, HMENU, HANDLE);

/*
    @function:"绘制特殊字体封装。"
*/
void PaintRoutine(HWND, HDC, int, int);


/*
    @function:"创建特殊字体封装。"
*/
HFONT EzCreateFont(HDC hdc, TCHAR* szFaceName, int iDeciPtHeight,
    int iDeciPtWidth, int iAttributes, BOOL fLogRes);


/*
    @function:"重构messagebox，支持格式化文字。"
*/
int CDECL messageBoxPrintf(TCHAR*, TCHAR*, ...);


/*
    @function:"级联关闭窗口封装。"
*/
BOOL    CALLBACK CloseEnumProc(HWND, LPARAM);
