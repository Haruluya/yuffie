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
    @date:2022/5/18
    @author:deng
    @model_function:"实验室试剂管理相关函数".
    @include:[reagentApplyStruct.h,repertoryManageStruct.h,repertoryStruct.h,user.h]
    @work:teacherLabManage.c
    @log:teacherLabManage.log

*/
#include"repertoryManageStruct.h"
#include"reagentApplyStruct.h"
#include"repertoryStruct.h"
#include"user.h"

/*
 @function:"初始化实验室库存记录"
 */
Status initManageLabList();

/*
 @function:"实时更新实验室库存记录"
 */
Status updateManageLabList();

/*
 @function:"添加申请结果的入库记录"
 */
Status addApplyResultToManageLabList();

/*
 @function:"更改试剂数量时（消耗）添加消耗记录"
 */
Status createConsumMnanageItem(int,int);

/*
 @function:"枚举转字符串用于显示"
 */
String getUpdateWayName(int);