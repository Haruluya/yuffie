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
    @model_function:"实验室、主存储库试剂数据结构".
    @include:[global.h,user.h]
    @work:reagentApply.h,reagentApply.c
    @log:reagentApplyStruct.log

*/

#include "global.h"
#include "user.h"

#ifndef HEADER_REAGENT_APPLY_STRUCT
#define HEADER_REAGENT_APPLY_STRUCT 114514
/*
    @function:"试剂申领项的抽象."
    @value:{
        inventoryName:"药剂名称",
        inventoryId:"药剂id",
        inventoryClass:"药剂类别"
    }
*/
typedef struct ReagentApplyItem
{
    String reagentName;
    int reagentId;
    int reagentNum;
} ReagentApplyItem;

/*
    @function:"试剂申领项在链表中的抽象."
    @value:{
        ReagentApplyItem:"试剂申领项的抽象",
        RNode:"下一申领项地址",
    }
*/
typedef struct RNode
{
    ReagentApplyItem data;
    struct RNode* next;
} RNode;

/*
    @function:"试剂申领表链表项指针."
*/
typedef struct RNode* ReagentApplyLinkList;

/*
    @value:"试剂申领表每列最大长度。"
*/
#define INFO_MAXSIZE 50

/*
    @value:"试剂申领表最大元组数。"
*/
#define REAGENT_APPLY_LIST_MAX_SIZE 199

/*
    @function:"试剂申领链表头指针."
    @range:[0,REAGENT_APPLY_LIST_MAX_SIZE]
*/
ReagentApplyLinkList reagentApplyList;

/*
    @function:"试剂申领表链表项长度."
*/
int reagentApplyListLen;

/*
    @function:"试剂申领结果表."
    @range:[0,REAGENT_APPLY_LIST_MAX_SIZE]
*/
ReagentApplyItem reagentResultList[REAGENT_APPLY_LIST_MAX_SIZE];

/*
    @function:"试剂结果表长度."
*/
int reagentResultListLen;
#endif // !HEADER_REAGENT_APPLY_STRUCT