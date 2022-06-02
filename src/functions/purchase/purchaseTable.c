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
    @date:2022/5/13
    @author:haruluya
    @model_function:"This is a file for test".
    @include:[a.h,b.h,c.h]    //包含的头文件。
    @work:interface.c       //包含此头文件的源程序。
    @log:interfaces.log     //更新日志。

*/

#include"purchaseTable.h"
#include "globalConst.h"

/*
    @author:haruluya
    @date:2022/5/13
    @function:"通过id获取订购项"
    @input:{
        id:"订购项id"
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc] 
    @return:"对应id的订购项"
*/
PurchaseItem getPurchaseItemById(int id) {

    for (int i = 0; i < purchaseListLen; i++) {

        /*
            @check:"id相同则返回."
        */
        if (purchaseList[i].inventoryId == id) {
            return purchaseList[i];
        }
    }
    //错误处理.
    PurchaseItem notFound = { "NULL", -1, 0, 0 };
    return notFound;
}


/*
    @author:haruluya
    @date:2022/5/13
    @function:"载入订购表数据至全局变量purchaseList.(全局只读取一次文件)"
    @input:{
    }
    @output:{
    }
    @execute:[yuffie.WinMain]
    @return:"执行状态"
*/
Status initPurchaseList() {
    FILE* fp;

    /*
        @check:"文件打开错误处理."
    */
    if (!(fp = fopen("purchaseTable.txt", "r"))) {
        return ERROR;
    }
    purchaseListLen = 0;
    while (!feof(fp)) {
        fgets(BUFF, sizeof(BUFF), fp);

        if (!strcmp(BUFF, "\0")) {
            break;
        }

        //获取以空格切分的属性数组.
        String* purchaseTableInfo = yuffieSplit(BUFF);


        PurchaseItem purchaseItem;
        //订购项初始化.
        purchaseItem.inventoryName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        purchaseItem.inventoryName = strcpy(purchaseItem.inventoryName, purchaseTableInfo[0]);
        purchaseItem.inventoryId = atoi(purchaseTableInfo[1]);
        purchaseItem.inventoryNum = atoi(purchaseTableInfo[2]);


        //出价初始为0.
        purchaseItem.inventoryPrice = 0;

        purchaseList[purchaseListLen++] = purchaseItem;
        BUFF[0] = '\0';
    }
    fclose(fp);
    return OK;
}


/*
    @author:haruluya
    @date:2022/5/13
    @function:"创建出价表(创建对应出价文件到admin下并删除订购表)"
    @input:{
    }
    @output:{
    }
    @execute:[yuffie.WinMain]
    @return:"执行状态"
*/
Status createOfferApply() {
    FILE* fp;



    /*
        @check:"文件打开错误处理."
    */
    String fileName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    String str = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    sprintf(str, "%d", presentUser.id);
    fileName = strcat(strcat(strcat(strcpy(fileName, "./offerApply/"), str),presentUser.userName), ".txt");
    if (!(fp = fopen(fileName, "w"))) {
        return ERROR;
    }
    for (int i = 0; i < purchaseListLen; i++) {

        //输出出价项到supplier1.txt.
        fprintf(fp,
            "%s %d %d %d\n",
            purchaseList[i].inventoryName,
            purchaseList[i].inventoryId,
            purchaseList[i].inventoryNum,
            purchaseList[i].inventoryPrice
        );
    }
    fclose(fp);
    if (!(fp = fopen("purchaseTable.txt", "w"))) {
        return ERROR;
    }
    for (int i = 0; i < purchaseListLen; i++) {


        fprintf(fp,
            "%s %d %d %d\n",
            purchaseList[i].inventoryName,
            purchaseList[i].inventoryId,
            purchaseList[i].inventoryNum,
            0
        );
    }
    fclose(fp);


    //if (!(fp = fopen("./purchaseApply/supplier2.txt", "w"))) {
    //    return ERROR;
    //}
    //for (int i = 0; i < purchaseListLen; i++) {

    //    //输出出价项到supplier1.txt.
    //    fprintf(fp,
    //        "%s %d %d %d\n",
    //        purchaseList[i].inventoryName,
    //        purchaseList[i].inventoryId,
    //        purchaseList[i].inventoryNum,
    //        purchaseList[i].inventoryPrice
    //    );
    //}
    //fclose(fp);
    return OK;
}

