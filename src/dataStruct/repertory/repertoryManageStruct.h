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



#ifndef HEADER_REPERTOR_MANAGE_STRUCT

#include "global.h"
#define  HEADER_REPERTOR_MANAGE_STRUCT 114515
/*
    @function:"药品种类的抽象."
    @value:{

    }
*/
typedef enum mange
{
    ADD,
    SUB,
} mange;

/*
    @function:"总库存中药品的抽象."
    @value:{
        reagentName:"药剂名称",
        reagentId:"药剂id",
        reagentNum:"药剂数量",
    }
*/
typedef struct manageItem
{
    String reagentName;
    String time;
    int reagentId;
    int reagentChangeNum;
    mange mange;
} manageItem;

/*
    @value:总库存表最大元组数。
*/
#define INVENTORY_LIST_MAX_SIZE 199


/*
    @function:"总库存试剂表."
    @range:[0,INVENTORY_LIST_MAX_SIZE]
*/
manageItem manageInventoryList[INVENTORY_LIST_MAX_SIZE];

/*
    @value:"总库存表长度"
    @range:[0,INVENTORY_LIST_MAX_SIZE]
*/
int manageInventoryLen;



//当前teacher的实验室库存记录。
manageItem manageLabList[INVENTORY_LIST_MAX_SIZE];


int manageLabListLen;


manageItem manageRecyleList[INVENTORY_LIST_MAX_SIZE];

int manageRecyleListLen;

#endif // !HEADER_DEFINE