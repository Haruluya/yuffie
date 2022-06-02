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
    @date:2022/5/9
    @author:haruluya
    @model_function:"对订购相关操作函数和全局变量。".
    @include:[purchaseTableStruct.h,user.h]
    @work:[purchaseTable.c,yuffie.h]
    @log:purchaseTable.log

*/

#include "purchaseNotice.h"

/*
    @author:haruluya
    @date:2022/5/13
    @function:"生成采购通知"
    @input:{
    }
    @output:{
    }
    @execute:[yuffie.WinMain]
    @return:"执行状态"
*/
Status createPurchaseNotice(String notice)
{
    FILE* fp;

    /*
        @check:"文件打开错误处理."
    */
    if (!(fp = fopen("purchaseNotice.txt", "w")))
    {
        return ERROR;
    }

    // 将采购通知写入文件
    fputs(notice, fp);
    fclose(fp);
    return OK;
}


String getNoticeContent() {
    FILE* fp;

    /*
        @check:"文件打开错误处理."
    */
    if (!(fp = fopen("purchaseNotice.txt", "r")))
    {
        return "ERROR";
    }
    String content = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    strcpy(content,"");
    while (!feof(fp))
    {
        fgets(BUFF, sizeof(BUFF), fp);
        if (!strcmp(BUFF, "\0")) {
            break;
        }
        strcat(content, BUFF);
        BUFF[0] = '\0';
    }



    fclose(fp);
    return content;
}