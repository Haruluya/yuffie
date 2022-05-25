/*
    @license:
    MIT License

    Copyright (c) 2022

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
    @date:2022/5/9
    @author:haruluya
    @model_function:"对采购申请审核相关操作函数和全局变量。".
    @include:[purchaseApplyTableStruct.h,user.h]
    @work:[purchaseApplyTable.c,yuffie.c]
    @log:purchaseApplyTable.log

*/
#include "purchaseCheckStruct.h"

/*
    @function:"初始化采购申请单链表"
*/
Status initList();

/*
    @function:"保存所有的采购申请文件名"
*/
String fileName[50];

/*
    @function:"保存所有的采购申请文件个数"
*/
int fileLen;

/*
    @function:"获取所有的采购申请文件"
*/
Status initApply();

/*
    @function:"遍历所有采购申请文件，读取并保存所有老师提交的采购申请"
*/
Status createPurchaseApply();

/*
    @function:"计算采购申请单链表的长度"
*/
int lengthList();

/*
    @function:"删除指定id的通用试剂"
*/
Status deleteGPurchaseTable(int id);

/*
    @function:"删除指定id的专用试剂"
*/
Status deleteSPurchaseTable(int id);

/*
    @function:"删除指定的试剂"
*/
Status deletePurchaseTable(int id);

/*
    @function:"将申请元素的链表按照申请药品的编号进行冒泡排序，为后续删除重复元素做准备"
*/
Status sortList();

/*
    @function:"删除申请链表中重复申请的药剂元素"
*/
Status deleteSameList();

/*
    @function:"保存最终的采购申请至通用试剂采购表、专用实际采购表、采购报价表"
*/
Status initPurchaseTable();

/*
    @function:"保存最终的采购申请至通用试剂采购文件"
*/
Status createGPurchaseTable();

/*
    @function:"保存最终的采购申请至专用实际采购文件"
*/
Status createSPurchaseTable();

/*
    @function:"保存最终的采购申请至采购报价文件"
*/
Status createPurchaseTable();

