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
    SOFTWARE.

    @version:0.0.1
    @date:2022/5/15
    @author:Estrella
    @model_function:"对供应商报价审核操作函数".
    @include:user.h
    @log:user.log
*/

#include "finalPurchase.h"
#include<Windows.h>
/*
    @author:Estrella
    @date:2022/5/15
    @function:"载入最终订购表数据"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"函数执行状态"
*/
Status initFinalPurchaseList(String path,int userId)
{
    FILE* fp;

    /*
        @check:"文件打开错误处理."
    */
    if (!(fp = fopen(path, "r")))
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

        finalPurchaseItem finalPurchaseItem;
        //订购项初始化.
        finalPurchaseItem.inventoryName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        strcpy(finalPurchaseItem.inventoryName, purchaseTableInfo[0]);
        finalPurchaseItem.inventoryId = atoi(purchaseTableInfo[1]);
        finalPurchaseItem.inventoryNum = atoi(purchaseTableInfo[2]);
        finalPurchaseItem.inventoryPrice = atoi(purchaseTableInfo[3]);
        finalPurchaseItem.userID = userId;
        finalPurchaseTable[finalPurchaseLen++] = finalPurchaseItem;
        BUFF[0] = '\0';
    }
    fclose(fp);
    return OK;
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"获取所有的供应商报价文件"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"函数执行状态"
*/
Status initOfferApply()
{
    // 读取采购申请目录下的所有申请文件，并保存至fileName.txt
    system("dir offerApply  /B > priceFileName.txt");

    FILE* fp;
    priceFileLen = 0;

    /*
        @check:"文件打开错误处理."
    */
    if (!(fp = fopen("priceFileName.txt", "r")))
    {
        return ERROR;
    }

    while (!feof(fp))
    {
        fgets(BUFF, sizeof(BUFF), fp);
        if (!strcmp(BUFF, "\0")) {
            continue;
        }
        priceFileName[priceFileLen] = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        strcpy(priceFileName[priceFileLen++], BUFF);
        BUFF[0] = '\0';
    }
    fclose(fp);
    return OK;
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"载入每个药品对应的所有供应商报价数据"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"函数执行状态"
*/
Status initPrice()
{
    int i;
    FILE* fp;
    for (i = 0; i < priceFileLen; i++)
    {
        priceFileName[i][14] = '\0';
        strcat(strcpy(BUFF, "./offerApply/"), priceFileName[i]);
        int userId = priceFileName[i][0] - '0';
        String path = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        strcpy(path, BUFF);
        initFinalPurchaseList(path,userId);
        /*
            @check:"文件打开错误处理."
        */
        if (!(fp = fopen(path, "r")))
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
            if (!strcmp(BUFF, "\r\n")) {
                continue;
            }
            // 这里假设不超过10个供应商 
            price[atoi(purchaseTableInfo[1])][priceFileName[i][0] - '0'] = atoi(purchaseTableInfo[3]);

            BUFF[0] = '\0';
        }
    }
    return OK;
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"对每个药品对应的所有供应商报价数据选择报价最少的"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"函数执行状态"
*/
Status selectPrice()
{
    for (int i = 1; i < INFO_MAXSIZE; i++) {
        int min = 1000000;
        for (int j = 1; j < INFO_MAXSIZE; j++) {
            if (price[i][j] < min && price[i][j] != 0)
            {
                // 0号单元保存供应商的id
                price[i][0] = j;
                min = price[i][j];
            }
        }
    }
    return OK;
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"载入每个药品最终选择的报价和供应商数据"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"函数执行状态"
*/
Status finalPrice()
{

}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"完成比价并创建最终的购买表"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"函数执行状态"
*/
Status createFinalPrice()
{
    FILE* fp;

    /*
        @check:"文件打开错误处理."
    */
    if (!(fp = fopen("finalPurchaseInventory.txt", "w")))
    {
        return ERROR;
    }

    for (int i = 0; i < finalPurchaseLen - 1; i++)
    {

        //输出出价项到supplier1.txt.
        fprintf(fp,
            "%s %d %d %d %d\n",
            finalPurchaseTable[i].inventoryName,
            finalPurchaseTable[i].inventoryId,
            finalPurchaseTable[i].inventoryNum,
            finalPurchaseTable[i].inventoryPrice,
            finalPurchaseTable[i].userID);
    }
    fclose(fp);
    return OK;
}