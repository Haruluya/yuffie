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
    @date:2022/5/14
    @author:haruluya
    @model_function:"This is a file for test".
    @include:[a.h,b.h,c.h]    //包含的头文件。
    @work:interface.c       //包含此头文件的源程序。
    @log:interfaces.log     //更新日志。

*/

#include "purchaseApplyTable.h"

/*
    @author:haruluya
    @date:2022/5/14
    @function:"初始化采购申请List"
    @input:{
    }
    @output:{
    }
    @execute:[yuffie.WinMain]
    @return:"执行状态"
*/
Status initPurchaseApplyList()
{


    return OK;
}

Status addPurchaseApplyItem(purchaseTApplyItem item) {
    if (!item.inventoryName) {
        return INFASIBLE;
    }
    purchaseApplyList[purchaseApplyListLen++] = item;
    return OK;
}

/*
    @author:haruluya
    @date:2022/5/14
    @function:"创建出价表(创建对应出价文件到admin下并删除订购表)"
    @input:{
    }
    @output:{
    }
    @execute:[yuffie.WinMain]
    @return:"执行状态"
*/
Status createTeacherPurchaseApply()
{
    FILE* fp;

    String fileName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    fileName = strcat(strcat(strcpy(fileName, "./purchaseApply/"), presentUser.userName),".txt");
    /*
        @check:"文件打开错误处理."
    */
    if (!(fp = fopen(fileName, "w")))
    {
        return ERROR;
    }

    for (int i = 0; i < purchaseApplyListLen; i++)
    {

        //输出采购申请项到admin处
        fprintf(fp,
            "%s %d %d %d\n",
            purchaseApplyList[i].inventoryName,
            purchaseApplyList[i].inventoryClass,
            purchaseApplyList[i].inventoryId,
            purchaseApplyList[i].inventoryNum
        );
    }
    purchaseApplyListLen = 0;
    fclose(fp);
    return OK;
}


String getReClassName(purchaseTApplyItem item) {
    if (!item.inventoryName) {
        return INFASIBLE;
    }
    String className = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    if (item.inventoryClass == TGENERAL) {
        className = "General";
        return className;
    }
    else if (item.inventoryClass == TSPECIAL) {
        className = "Special";
        return className;
    }
    return "ERROR";
}


String deletePurchaseApplyItem(int id) {
    for (int i = 0; i < purchaseApplyListLen; i++)
    {
        if (purchaseApplyList[i].inventoryId == id)
        {
            for (int j = purchaseApplyListLen - 1; j > i; j--)
            {
                purchaseApplyList[j - 1].inventoryName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
                strcpy(purchaseApplyList[j - 1].inventoryName, purchaseApplyList[i].inventoryName);
                purchaseApplyList[j - 1].inventoryClass = purchaseApplyList[i].inventoryClass;
                purchaseApplyList[j - 1].inventoryId = purchaseApplyList[i].inventoryId;
                purchaseApplyList[j - 1].inventoryNum = purchaseApplyList[i].inventoryNum;
            }
            purchaseApplyListLen--;
        }
    }
}