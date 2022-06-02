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
    @date:2022/5/14
    @author:deng
    @model_function:"实验室库存数据结构定义".
    @include:[global.h]
    @work:laborInventory.c
    @log:NONE
*/



#ifndef HEADER_DEFINE


#define HEADER_DEFINE 114514
#include"global.h"
#include"user.h"
/*
    @function:"实验室及总库存中药品的抽象."
    @value:{
        reagentName:"药剂名称",
        reagentId:"药剂id",
        reagentNum:"药剂数量",
    }
*/
typedef struct ReagentItem {
    String reagentName;
    int reagentId;
    int reagentNum;
}ReagentItem;



#define INFO_MAXSIZE 50


/*
    @value:总库存表最大元组数。
*/
#define INVENTORY_LIST_MAX_SIZE 199

/*
    @value:每一实验室库存表最大元组数。
*/
#define LABOR_LIST_MAX_SIZE 49

/*
    @value:实验室最大数。
*/
#define LABOR_MAX 9

/*
    @function:"总库存试剂表."
    @range:[0,INVENTORY_LIST_MAX_SIZE]
*/
ReagentItem inventoryList[INVENTORY_LIST_MAX_SIZE];

/*
    @function:"实验室试剂表."
    @range:[0,REAGENT_LIST_MAX_SIZE]
*/
ReagentItem laborReaList[LABOR_LIST_MAX_SIZE];

/*
    @function:"实验室表."
    @range:[0,INVENTORY_LIST_MAX_SIZE]
*/
ReagentItem* laborList[LABOR_MAX];

/*
    @value:"总库存表长度"
    @range:[0,INVENTORY_LIST_MAX_SIZE]
*/
int inventoryListLen;

/*
    @value:"实验室表长度"
    @range:[0,INVENTORY_LIST_MAX_SIZE]
*/
int laborListLen;


int laborReaListLen;

#endif // !HEADER_DEFINE




