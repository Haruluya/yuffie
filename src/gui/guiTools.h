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
    @date:2022/5/9
    @author:haruluya
    @model_function:"基于Win 32 API 的GUI辅助工具类。".  
    @include:[windows.h,tchar.h,stdio.h]    
    @work:[guiTools.c,yuffie.c]      
    @log:guiTools.log   

*/


#include<windows.h>
#include<tchar.h>
#include<stdio.h>
#include <math.h>
#include"components/id.h"
#define EZ_ATTR_BOLD          1
#define EZ_ATTR_ITALIC        2
#define EZ_ATTR_UNDERLINE     4
#define EZ_ATTR_STRIKEOUT     8



/*
    @function:"重构messagebox，支持格式化文字。"
*/
int CDECL message_box_printf(TCHAR* , TCHAR* ,...);

/*
    @function:"播放wav音乐文件。"
*/
void playWavMusic(char*);

/*
    @function:"区域内绘制文字。"
*/
void drawText(HDC,RECT );


/*
    @function:"加载程序ico图标。"
*/
void loadYuffieIcon(HWND,char*);



void PaintRoutine (HWND, HDC, int, int);


HFONT EzCreateFont (HDC hdc, TCHAR * szFaceName, int iDeciPtHeight,
                    int iDeciPtWidth, int iAttributes, BOOL fLogRes);




