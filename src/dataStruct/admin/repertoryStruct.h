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
    SOFTWARE.   //MIT֤��������Ϊ�̶����֡�

    @version:0.0.1
    @date:2022/5/14
    @author:deng
    @model_function:"ʵ���ҿ�����ݽṹ����".
    @include:[global.h]
    @work:laborInventory.c
    @log:NONE
*/

#include"global.h"

/*
    @function:"�ܿ����ҩƷ�ĳ���."
    @value:{
        reagentName:"ҩ������",
        reagentId:"ҩ��id",
        reagentNum:"ҩ������",
    }
*/
typedef struct ReagentItem {
    String reagentName;
    int reagentId;
    int reagentNum;
}ReagentItem;

/*
    @value:�ܿ������Ԫ������
*/
#define INVENTORY_LIST_MAX_SIZE 199

/*
    @value:ÿһʵ���ҿ������Ԫ������
*/
#define LABOR_LIST_MAX_SIZE 49

/*
    @value:ʵ�����������
*/
#define LABOR_MAX 9

/*
    @function:"�ܿ���Լ���."
    @range:[0,INVENTORY_LIST_MAX_SIZE]
*/
ReagentItem inventoryList[INVENTORY_LIST_MAX_SIZE];

/*
    @function:"ʵ�����Լ���."
    @range:[0,REAGENT_LIST_MAX_SIZE]
*/
ReagentItem laborReaList[LABOR_LIST_MAX_SIZE];

/*
    @function:"ʵ���ұ�."
    @range:[0,INVENTORY_LIST_MAX_SIZE]
*/
ReagentItem* laborList[LABOR_MAX];

/*
    @value:"�ܿ�������"
    @range:[0,INVENTORY_LIST_MAX_SIZE]
*/
int inventoryListLen;

/*
    @value:"ʵ���ұ�����"
    @range:[0,INVENTORY_LIST_MAX_SIZE]
*/
int laborListLen;