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
    @model_function:"采购申请表数据结构定义".
    @include:[global.h]
    @work:purchaseTable.c
    @log:NONE
*/

#include "global.h"

/*
    @function:"药品种类的抽象."
    @value:{

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
        inventoryId:"药剂id",
        inventoryClass:"药剂类别"，
    }
*/
typedef struct purchaseApplyItem
{
    String inventoryName;
    inventoryClass inventoryClass;
    int inventoryId;
} purchaseApplyItem;

/*
    @value:采购申请表每列最大长度。
*/
#define INFO_MAXSIZE 50
/*
    @value:"采购申请表最大元组数。"
*/
#define PURCHASE_APPLY_LIST_MAX_SIZE 199
/*
    @function:"采购申请表."
    @range:[0,PURCHASE_LIST_MAX_SIZE]
*/
purchaseApplyItem purchaseApplyList[PURCHASE_APPLY_LIST_MAX_SIZE];

/*
    @function:"订购表长度"
    @range:[0,PURCHASE_LIST_MAX_SIZE]
*/
int purchaseApplyListLen;