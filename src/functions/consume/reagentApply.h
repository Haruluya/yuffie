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
    @model_function:"实验室试剂申领相关函数".
    @include:[reagentApplyStruct.h]
    @work:reagentApply.c
    @log:mainReagent.log

*/

#include"reagentApplyStruct.h"

/*
 @function:"载入所有申请表"
 */
Status initReagentApply();

/*
 @function:"添加请求项"
 */
Status addReagentApplyItem(ReagentApplyItem);

/*
 @function:"删除请求项"
 */
Status deleteReagentApplyItemById(int);

/*
 @function:"提交请求项"
 */
Status commitReagentApply();

/*
 @function:"载入当前用户的申请表结果"
 */
Status initResultList();

