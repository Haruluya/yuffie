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
    @date:2022/5/15
    @author:Estrella
    @model_function:"对药剂申请相关操作函数和全局变量。".
    @include:[purchaseApplyTableStruct.h,user.h]
    @work:[purchaseApplyTable.c,yuffie.c]
    @log:purchaseApplyTable.log

*/

#include "purchaseApplyTableStruct.h"
#include "user.h"

/*
    @function:"初始化采购申请List"
*/
Status initPurchaseApplyList();

/*
    @function:"填写采购申请表，并提交给admin。"
*/
Status createTeacherPurchaseApply();


Status addPurchaseApplyItem(purchaseTApplyItem);

String getReClassName(purchaseTApplyItem);

String deletePurchaseApplyItem(int);
