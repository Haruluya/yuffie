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
    @model_function:"实验室试剂申领管理相关函数".
    @include:[reagentCheck.h]
    @work:reagentCheck.c
    @log:reagentCheck.log

*/
#include"reagentCheckStruct.h"

/*
 @function:"获取所有apply文件名"
 */
Status initReagentApplyFiles();

/*
 @function:"初始化申请项列表"
 */
Status initReagentApplyList();

/*
 @function:"添加请求项"
 */
Status addReagentCheckItem(ReagentCheckItem);

/*
 @function:"删除请求项"
 */
Status deleteReagentCheckItemById(int);

/*
 @function:"提交请求表"
 */
Status commitReagentCheck();