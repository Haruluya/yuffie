/*
②.h头文件接口规范。
*/
// #include"a.h";
// #include"b.h";
// #include"c.h";

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
    @model_function:"win32主窗口头文件".
    @include:[Windows.h,guiTools.h,id.h,resource.h,loginDialog.h,supplierTemplate.h,user.h]    
    @work:[yuffie.c,all clas with gui]       
    @log:yuffie.log     

*/
#pragma once
#include<Windows.h>
#include"guiTools.h"
#include "resource.h"
#include"id.h"
#include"loginDialog.h"
#include"supplierTemplate.h"
#include"user.h"


#define ID_YUFFIE_BEGIN_BUTTON 200

/*
    @function:"主窗口类名."
    @range:Const
*/
TCHAR     szFrameClass[] = TEXT("MdiFrame");

/*
    @function:"Supplier窗口类名."
    @range:Const
*/
TCHAR     szHelloClass[] = TEXT("MdiHelloChild");


/*
    @functionL"程序主函数。"
*/
int WINAPI WinMain(HINSTANCE, HINSTANCE,PSTR, int);


/*
	@function:"主窗口事件处理函数。"
*/
LRESULT CALLBACK FrameWndProc(HWND, UINT, WPARAM, LPARAM);
