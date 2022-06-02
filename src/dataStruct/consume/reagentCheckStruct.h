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
    @model_function:"试剂申请审核处理".
    @include:[global.h,user.h]
    @work:reagentCheck.c
    @log:reagentCheckStruct.log

*/
#include "global.h"
#include "user.h"

/*
    @function:"试剂审核结构抽象"
    @value:{
        reagentName:"试剂名称",
        reagentId:"试剂ID",
        reagentNum:"试剂数量",
        teacherId:"申请老师id"
    }
*/
typedef struct ReagentCheckItem
{
    String reagentName;
    int reagentId;
    int reagentNum;
    int teacherId;
} ReagentCheckItem;

/*
    @value:"属性最大长度"
*/
#define INFO_MAXSIZE 50

/*
    @value:"表最大元组数。"
*/
#define REAGENT_CHECK_LIST_MAX_SIZE 199

/*
    @function:"全局缓存变量."
    @range:[0,REAGENT_CHECK_LIST_MAX_SIZE]
*/
ReagentCheckItem reagentCheckList[REAGENT_CHECK_LIST_MAX_SIZE];

/*
    @function:"试剂审核表长度."
*/
int reagentCheckListLen;

/*
    @function:"试剂申请文件名."
    @range:[0,INFO_MAXSIZE]
*/
String reagentApplyFileName[INFO_MAXSIZE];

/*
    @function:"试剂申请文件数量"
*/
int reagentApplyFileLen;
