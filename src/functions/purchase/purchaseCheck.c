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
    @date:2022/5/15
    @author:Estrella
    @model_function:"This is a file for test".
    @include:[purchaseCheck.h]    //包含的头文件。
    @work:purchaseCheckTest.c       //包含此头文件的源程序。
    @log:purchaseCheck.log     //更新日志。

*/

#include "purchaseCheck.h"

/*
    @author:Estrella
    @date:2022/5/15
    @function:"初始化采购申请单链表"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"函数执行状态"
*/
Status initList()
{
    apply = (LinkList)malloc(sizeof(Node));				//开辟空间
    if (!apply)
    {
        printf("分配内存失败！\n");
        return ERROR;
    }
    apply->next = NULL; //使头节点next为NULL，即表示空链表
    return OK;
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"获取所有的采购申请文件"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"函数执行状态"
*/
Status initApply()
{
    // 读取采购申请目录下的所有申请文件，并保存至fileName.txt
    system("dir purchaseApply  /B > fileName.txt");

    FILE* fp;
    fileLen = 0;

    /*
        @check:"文件打开错误处理."
    */
    if (!(fp = fopen("fileName.txt", "r")))
    {
        return ERROR;
    }
    while (!feof(fp))
    {

        fgets(BUFF, sizeof(BUFF), fp);
        fileName[fileLen] = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        strcpy(fileName[fileLen++], BUFF);
        BUFF[0] = '\0';
    }
    fclose(fp);
    return OK;
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"遍历所有采购申请文件，读取并保存所有老师提交的采购申请"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"函数执行状态"
*/
Status createPurchaseApply()
{
    int i;
    // r为指向尾部的节点的指针, p是新生成的节点
    LinkList p, r;
    r = apply;

    FILE* fp;
    for (i = 0; i < fileLen - 1; i++) {
        fileName[i][12] = '\0';
        strcat(strcpy(BUFF, "./purchaseApply/"), fileName[i]);

        if (!strcmp(BUFF, "\0")) {
            continue;
        }
        /*
            @check:"文件打开错误处理."
        */
        if (!(fp = fopen(BUFF, "r")))
        {
            return ERROR;
        }


        while (!feof(fp))
        {
            fgets(BUFF, sizeof(BUFF), fp);
            if (!strcmp(BUFF, "\0")) {
                break;
            }
            //获取以空格切分的属性数组.
            String* purchaseTableInfo = yuffieSplit(BUFF);
 
            p = (LinkList)malloc(sizeof(Node)); //生成新节点
            p->data.inventoryName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
            strcpy(p->data.inventoryName, purchaseTableInfo[0]);
            p->data.inventoryClass = atoi(purchaseTableInfo[1]);
            p->data.inventoryId = atoi(purchaseTableInfo[2]);
            p->data.inventoryNum = atoi(purchaseTableInfo[3]);
            r->next = p; //将表尾终端节点的指针指向新节点
            r = p;       //将当前的新节点定义为表尾终端节点
            BUFF[0] = '\0';
        }
    }
    r->next = NULL;									//表示单链表结束

}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"计算采购申请单链表的长度"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"采购申请单链表的长度"
*/
int lengthList()
{
    int length = 0;
    LinkList p;
    p = apply->next;

    while (p)
    {
        length++;
        p = p->next;
    }
    return length;
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"将申请元素的链表按照申请药品的编号进行冒泡排序，为后续删除重复元素做准备"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"函数执行状态"
*/
Status sortList()
{
    LinkList cur, tail;
    cur = apply->next;
    tail = NULL;

    if (cur == NULL || cur->next == NULL) {
        return OK;
    }

    while (cur != tail) {
        while (cur->next != tail) {
            if (cur->data.inventoryId > cur->next->data.inventoryId) {
                purchaseApplyItem tmp = cur->data;
                cur->data = cur->next->data;
                cur->next->data = tmp;
            }
            cur = cur->next;
        }
        tail = cur; // 减少最后的已排好的循环
        cur = apply->next;
    }

    return OK;
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:""删除申请链表中重复申请的药剂元素"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"函数执行状态"
*/
Status deleteSameList()
{
    LinkList p, q;
    p = apply->next;

    while (p->next)
    {
        q = p->next;
        if (p->data.inventoryId == q->data.inventoryId) {
            // 删除
            p->next = q->next;
            free(q);
        }
        else {
            p = p->next;
        }
    }

    return OK;
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"保存最终的采购申请至通用试剂采购表、专用实际采购表、采购报价表"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"函数执行状态"
*/
Status initPurchaseTable()
{
    LinkList p, q;
    p = apply->next;

    while (p)
    {
        if (p->data.inventoryClass == 0)
        {
            // 将申请元素添加到通用试剂采购表
            gPurchaseList[gPurchaseListLen++] = p->data;
        }
        else
        {
            // 将申请元素添加到专用试剂采购表
            sPurchaseList[sPurchaseListLen++] = p->data;

            // 将专用试剂采购元素添加到采购报价表
            PurchaseItem purchaseItem;

            //订购项初始化.
            purchaseItem.inventoryName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
            purchaseItem.inventoryName = strcpy(purchaseItem.inventoryName, p->data.inventoryName);
            purchaseItem.inventoryId = p->data.inventoryId;
            purchaseItem.inventoryNum = p->data.inventoryNum;
            purchaseItem.inventoryPrice = 0;

            purchaseTable[purchaseTableLen++] = purchaseItem;
        }
        p = p->next;
    }

    return OK;
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"保存最终的采购申请至通用试剂采购文件"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"函数执行状态"
*/
Status createGPurchaseTable()
{
    FILE* fp;

    /*
        @check:"文件打开错误处理."
    */
    if (!(fp = fopen("generalReagentInventory.txt", "w")))
    {
        return ERROR;
    }

    for (int i = 0; i < gPurchaseListLen; i++)
    {

        fprintf(fp,
            "%s %d %d\n",
            gPurchaseList[i].inventoryName,
            gPurchaseList[i].inventoryId,
            gPurchaseList[i].inventoryNum);
    }
    fclose(fp);
    return OK;
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"保存最终的采购申请至专用实际采购文件"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"函数执行状态"
*/
Status createSPurchaseTable()
{
    FILE* fp;

    /*
        @check:"文件打开错误处理."
    */
    if (!(fp = fopen("specialReagentInventory.txt", "w")))
    {
        return ERROR;
    }

    for (int i = 0; i < sPurchaseListLen; i++)
    {

        fprintf(fp,
            "%s %d %d\n",
            sPurchaseList[i].inventoryName,
            sPurchaseList[i].inventoryId,
            sPurchaseList[i].inventoryNum);
    }
    fclose(fp);
    return OK;
}


/*
    @author:Estrella
    @date:2022/5/15
    @function:"保存最终的采购申请至采购报价文件"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"函数执行状态"
*/
Status createPurchaseTable()
{
    FILE* fp;

    /*
        @check:"文件打开错误处理."
    */
    if (!(fp = fopen("purchaseTable.txt", "w")))
    {
        return ERROR;
    }

    for (int i = 0; i < sPurchaseListLen; i++)
    {

        //输出出价项到.txt.
        fprintf(fp,
            "%s %d %d %d\n",
            sPurchaseList[i].inventoryName,
            sPurchaseList[i].inventoryId,
            sPurchaseList[i].inventoryNum,
            0);
    }
    fclose(fp);
    return OK;
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"删除指定id的通用试剂"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"函数执行状态"
*/
Status deleteGPurchaseTable(int id)
{
    for (int i = 0; i < gPurchaseListLen; i++)
    {
        if (gPurchaseList[i].inventoryId == id)
        {
            for (int j = gPurchaseListLen - 1; j > i; j--)
            {
                gPurchaseList[j - 1].inventoryName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
                strcpy(gPurchaseList[j - 1].inventoryName, gPurchaseList[j].inventoryName);
                gPurchaseList[j - 1].inventoryId = gPurchaseList[j].inventoryId;
                gPurchaseList[j - 1].inventoryClass = gPurchaseList[j].inventoryClass;
            }
            gPurchaseListLen--;
            gPurchaseList[gPurchaseListLen - 1];
        }
    }
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"删除指定id的专用试剂"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"函数执行状态"
*/
Status deleteSPurchaseTable(int id)
{
    for (int i = 0; i < sPurchaseListLen; i++)
    {
        if (sPurchaseList[i].inventoryId == id)
        {
            for (int j = sPurchaseListLen - 1; j > i; j--)
            {
                sPurchaseList[j - 1].inventoryName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
                strcpy(sPurchaseList[j - 1].inventoryName, sPurchaseList[j].inventoryName);
                sPurchaseList[j - 1].inventoryId = sPurchaseList[j].inventoryId;
                sPurchaseList[j - 1].inventoryClass = sPurchaseList[j].inventoryClass;
            }
            sPurchaseListLen--;
            sPurchaseList[sPurchaseListLen - 1];
        }
    }
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"删除指定id的采购试剂"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"函数执行状态"
*/
Status deletePurchaseTable(int id)
{
    for (int i = 0; i < purchaseTableLen; i++)
    {
        if (purchaseTable[i].inventoryId == id)
        {
            for (int j = purchaseTableLen - 1; j > i; j--)
            {
                purchaseTable[j - 1].inventoryName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
                strcpy(purchaseTable[j - 1].inventoryName, purchaseTable[j].inventoryName);
                purchaseTable[j - 1].inventoryId = purchaseTable[j].inventoryId;
                purchaseTable[j - 1].inventoryNum= purchaseTable[j].inventoryNum;
                purchaseTable[j - 1].inventoryPrice = purchaseTable[j].inventoryPrice;
            }
            purchaseTableLen--;
            purchaseTable[purchaseTableLen - 1];
        }
    }
}
