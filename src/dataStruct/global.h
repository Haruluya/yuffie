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
    @model_function:"数据结构全局静态类。"
    @include:[a.h,b.h,c.h]
    @work:all in dataStruct file
    @log:NONE

*/

#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

/*
    @function:"函数执行状态封装，所有返回void的函数应该返回Status并检查执行情况。"
*/
typedef int Status;
#define TRUE         1
#define OK           1
#define ERROR        0
#define INFASIBLE   -1
#define OVERFLOW    -2
#define NOT_FOUND   -3

/*
    @function:"全局缓存区."
    @range:[0,255]
*/
char BUFF[255];

/*
    @function:"逻辑类String定义。"
*/
typedef char* String;

typedef struct PurchaseItem {
    String inventoryName;
    int inventoryId;
    int inventoryNum;
    int inventoryPrice;
}PurchaseItem;




