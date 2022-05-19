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
Status initPurchaseList()
{

    scanf("%s", BUFF);

    while (strcmp(BUFF, "-1") != 0)
    {
        // 输入申请采购项
        scanf(" %d %d",
            &purchaseApplyList[purchaseApplyListLen].inventoryClass,
            &purchaseApplyList[purchaseApplyListLen].inventoryId
            );

        purchaseApplyList[purchaseApplyListLen].inventoryName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        strcpy(purchaseApplyList[purchaseApplyListLen].inventoryName, BUFF);

        purchaseApplyListLen++;

        scanf("%s", BUFF);
        }
    
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
Status createApply()
{
    FILE *fp;

    // 文件路径拼接
    // String file = strcat("../../../assert/data/admin/purchaseApply/", presentUser.userName);
    // file = strcat(file, ".txt");

    /*
        @check:"文件打开错误处理."
    */
    if (!(fp = fopen("teacher1.txt", "w")))
    {
        return ERROR;
    }

    for (int i = 0; i < purchaseApplyListLen; i++)
    {

        //输出采购申请项到admin处
        fprintf(fp,
                "%s %d %d\n",
                purchaseApplyList[i].inventoryName,
                purchaseApplyList[i].inventoryClass,
                purchaseApplyList[i].inventoryId);
    }
    fclose(fp);
    return OK;
}
