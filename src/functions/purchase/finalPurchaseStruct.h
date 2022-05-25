/*
    @license:
    MIT License

    Copyright (c) 2022 Estrella

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
    @model_function:"对供应商报价审核用到的数据结构定义".
    @include:[global.h，user.h]
    @work:purchaseTable.c
    @log:NONE
*/

#include "global.h"

/*
    @function:"订购项的抽象."
    @value:{
        inventoryName:"药剂名称",
        inventoryId:"药剂id",
        inventoryNum:"药剂数量",
        inventoryPrice:"报价",
        userID:"供应商",
    }
*/
typedef struct finalPurchaseItem
{
    String inventoryName;
    int inventoryId;
    int inventoryNum;
    int inventoryPrice;
    int userID;
} finalPurchaseItem;

/*
    @function:"保存所有的报价文件名"
*/
String priceFileName[50];

/*
    @function:"保存所有的报价文件个数"
*/
int priceFileLen;

/*
    @value:采购申请表每列最大长度。
*/
#define INFO_MAXSIZE 50

/*
    @value:"采购申请表最大元组数。"
*/
#define PURCHASE_APPLY_LIST_MAX_SIZE 199

/*
    @function:"采购公告(采购申请审核过后)."
    @range:[0,PURCHASE_LIST_MAX_SIZE]
*/
finalPurchaseItem finalPurchaseTable[PURCHASE_APPLY_LIST_MAX_SIZE];

/*
    @function:"采购表长度"
    @range:[0,PURCHASE_LIST_MAX_SIZE/2]
*/
int finalPurchaseLen;

/*
    @value:"每个药品对应的所有供应商报价的二维数组结构。"
*/
int price[INFO_MAXSIZE][INFO_MAXSIZE];