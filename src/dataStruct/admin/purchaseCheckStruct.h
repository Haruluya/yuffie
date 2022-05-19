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
    @model_function:"采购申请审核用到的数据结构定义".
    @include:[global.h]
    @work:purchaseTable.c
    @log:NONE
*/

#include "global.h"
#include "user.h"

/*
    @function:"药品种类的抽象."
    @value:{
        GENERAL:通用试剂;
        SPECIAL:专用试剂;
    }
*/
typedef enum inventoryClass
{
    GENERAL,
    SPECIAL,
} inventoryClass;

/*
    @function:"采购申请项的抽象."
    @value:{
        inventoryName:"药剂名称",
        inventoryClass:"药剂类别"，
        inventoryId:"药剂id",
    }
*/
typedef struct purchaseApplyItem
{
    String inventoryName;
    inventoryClass inventoryClass;
    int inventoryId;
} purchaseApplyItem;

/*
    @function:"采购申请链表."
    @value:{
        data:采购申请项;
        next:下一采购申请项
    }
*/
typedef struct Node
{
    purchaseApplyItem data;
    struct Node* next;
} Node;
typedef struct Node* LinkList;

/*
    @function:"订购项的抽象."
    @value:{
        inventoryName:"药剂名称",
        inventoryId:"药剂id",
        inventoryNum:"药剂数量",
        inventoryPrice:"报价"
    }
*/
//typedef struct PurchaseItem
//{
//    String inventoryName;
//    int inventoryId;
//    int inventoryNum;
//    int inventoryPrice;
//} PurchaseItem;

/*
    @function:"用链表存储所有的采购申请"
*/
LinkList apply;

/*
    @value:采购申请表每列最大长度。
*/
#define INFO_MAXSIZE 50

/*
    @value:"采购申请表最大元组数。"
*/
#define PURCHASE_APPLY_LIST_MAX_SIZE 199

/*
    @function:"采购申请表分类过后的通用试剂和专用试剂采购申请表(采购申请审核过后)."
    @range:[0,PURCHASE_LIST_MAX_SIZE]
*/
purchaseApplyItem gPurchaseList[PURCHASE_APPLY_LIST_MAX_SIZE];
purchaseApplyItem sPurchaseList[PURCHASE_APPLY_LIST_MAX_SIZE];

/*
    @function:"采购公告(采购申请审核过后)."
    @range:[0,PURCHASE_LIST_MAX_SIZE]
*/
PurchaseItem purchaseTable[PURCHASE_APPLY_LIST_MAX_SIZE];

/*
    @function:"通用试剂、专用试剂采购表和采购公告表长度"
    @range:[0,PURCHASE_LIST_MAX_SIZE/2]
*/
int gPurchaseListLen;
int sPurchaseListLen;
int purchaseTableLen;
