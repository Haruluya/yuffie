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
    @date:2022/5/16
    @author:Estrella
    @model_function:"purchaseCheck模块测试类".
*/

#include "purchaseCheck.h"

int main()
{
    //初始化采购申请单链表测试
    initList();

    // 获取所有的采购申请文件测试
    initApply();

    // 遍历所有采购申请文件，读取并保存所有老师提交的采购申请测试
    createPurchaseApply();

    // 将申请元素的链表按照申请药品的编号进行冒泡排序，为后续删除重复元素做准备
    sortList();

    // 删除申请链表中重复申请的药剂元素测试
    deleteSameList();

    // 保存最终的采购申请至通用试剂采购表、专用实际采购表、采购报价表
    initPurchaseTable();

    // 保存最终的采购申请至通用试剂采购文件
    createGPurchaseTable();

    // 保存最终的采购申请至专用实际采购文件
    createSPurchaseTable();

    // 保存最终的采购申请至采购报价文件
    createPurchaseTable();

    return 0;
}
