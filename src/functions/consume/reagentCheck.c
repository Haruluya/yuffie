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
    @date:2022/5/18
    @author:deng
    @model_function:"实验室试剂申领管理相关函数".
    @include:[reagentApplyStruct.h]
    @work:reagentApply.c
    @log:mainReagent.log

*/
#include"reagentCheck.h"

/*
    @author:deng
    @date:2022/5/31
    @function:"获取所有apply文件名"
    @input:{
    }
    @output:{
    }
    @execute:[deng.WinMain]
    @return:"执行状态"
*/
Status initReagentApplyFiles() {
    // 读取采购申请目录下的所有申请文件，并保存至fileName.txt
    system("dir reagentApply  /B > reagentApplyFileName.txt");

    FILE* fp;
    reagentApplyFileLen = 0;

    /*
        @check:"文件打开错误处理."
    */
    if (!(fp = fopen("reagentApplyFileName.txt", "r")))
    {
        return ERROR;
    }
    while (!feof(fp))
    {

        fgets(BUFF, sizeof(BUFF), fp);
        reagentApplyFileName[reagentApplyFileLen] = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        strcpy(reagentApplyFileName[reagentApplyFileLen++], BUFF);
        BUFF[0] = '\0';
    }
    fclose(fp);
    return OK;
}

/*
    @author:deng
    @date:2022/5/31
    @function:"初始化申请项列表"
    @input:{
    }
    @output:{
    }
    @execute:[deng.WinMain]
    @return:"执行状态"
*/
Status initReagentApplyList() {
    int i;
    FILE* fp;
    for (i = 0; i < reagentApplyFileLen; i++)
    {
        reagentApplyFileName[i][13] = '\0';
        String str = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        strcat(strcpy(str, "./reagentApply/"), reagentApplyFileName[i]);

        /*
            @check:"文件打开错误处理."
        */
        if (!(fp = fopen(str, "r")))
        {
            return ERROR;
        }
        int teacherId = reagentApplyFileName[i][0] - '0';
     

        while (!feof(fp))
        {
            fgets(BUFF, sizeof(BUFF), fp);
            if (!strcmp(BUFF, "\0")) {
                break;
            }
            //获取以空格切分的属性数组.
            String* reagentApplyInfo = yuffieSplit(BUFF);
            if (!strcmp(BUFF, "\r\n")) {
                continue;
            }
            String* applyName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
            strcpy(applyName, reagentApplyInfo[0]);
            ReagentCheckItem item = {
                applyName,
                atoi(reagentApplyInfo[1]),
                atoi(reagentApplyInfo[2]),
                teacherId
            };
            addReagentCheckItem(item);
            BUFF[0] = '\0';
        }
    }
    return OK;
}


/*
    @author:deng
    @date:2022/5/31
    @function:"添加请求项"
    @input:{
    }
    @output:{
    }
    @execute:[deng.WinMain]
    @return:"执行状态"
*/
Status addReagentCheckItem(ReagentCheckItem item) {
    if (!item.reagentName) {
        return INFASIBLE;
    }
    reagentCheckList[reagentCheckListLen++] = item;
    return OK;
}

/*
    @author:deng
    @date:2022/5/31
    @function:"删除请求项"
    @input:{
    }
    @output:{
    }
    @execute:[deng.WinMain]
    @return:"执行状态"
*/
Status deleteReagentCheckItemById(int id) {
    if (id <= 0) {
        return INFASIBLE;
    }
    for (int i = 0; i < reagentCheckListLen; i++) {
        if (reagentCheckList[i].reagentId == id) {
            for (int j = i; j < reagentCheckListLen - 1; j++) {
                reagentCheckList[i] = reagentCheckList[i + 1];
            }
            reagentCheckListLen--;
            return OK;
        }
    }
    return NOT_FOUND;
}

/*
    @author:deng
    @date:2022/5/31
    @function:"提交请求表"
    @input:{
    }
    @output:{
    }
    @execute:[deng.WinMain]
    @return:"执行状态"
*/
Status commitReagentCheck() {
    FILE* fp;
    /*
       @check:"文件打开错误处理."
    */
    if (!(fp = fopen("reagentAuditResult.txt", "w")))
    {
        return ERROR;
    }
    for (int i = 0; i < reagentCheckListLen; i++)
    {

        //输出试剂申请项到admin处
        fprintf(fp,
            "%s %d %d %d\n",
            reagentCheckList[i].reagentName,
            reagentCheckList[i].reagentId,
            reagentCheckList[i].reagentNum,
            reagentCheckList[i].teacherId
        );
    }
    fclose(fp);
    return OK;
}