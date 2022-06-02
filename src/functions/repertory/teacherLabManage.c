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
    @model_function:"实验室试剂管理相关函数".
    @include:[teacherLabManage.h]
    @work:teacherLabManage.c
    @log:teacherLabManage.log

*/
#include"teacherLabManage.h"

/*
    @author:deng
    @date:2022/5/31
    @function:"初始化实验室库存记录"
    @input:{
    }
    @output:{
    }
    @execute:[deng.WinMain]
    @return:"执行状态"
*/
Status initManageLabList() {
    FILE* fp;

    String fileName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    String str = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    sprintf(str, "%d", presentUser.id);
    fileName = strcat(strcat(strcat(strcpy(fileName, "./teacher"), str), "/"), "labManageRepertory.txt");
    /*
        @check:"文件打开错误处理."
    */
    if (!(fp = fopen(fileName, "r")))
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
        String* labManangeItemInfo = yuffieSplit(BUFF);

        manageItem item;
        item.reagentName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        strcpy(item.reagentName, labManangeItemInfo[0]);
        item.time = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        strcpy(item.time, labManangeItemInfo[1]);
        item.reagentId = atoi(labManangeItemInfo[2]);
        item.reagentChangeNum = atoi(labManangeItemInfo[3]);
        item.mange = atoi(labManangeItemInfo[4]);
        manageLabList[manageLabListLen++] = item;

        BUFF[0] = '\0';
    }

    fclose(fp);
}

/*
    @author:deng
    @date:2022/5/31
    @function:"添加申请结果的入库记录"
    @input:{
    }
    @output:{
    }
    @execute:[deng.WinMain]
    @return:"执行状态"
*/
Status addApplyResultToManageLabList() {

    // 获取当前时间
    char nowTime[20] = { 0 };
    time_t timep;
    time(&timep);
    struct tm* p;
    p = gmtime(&timep);
    snprintf(nowTime, 20, "%d-%d-%d_%d:%d:%d", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec);


    for (int i = 0; i < reagentResultListLen; i++)
    {
        manageItem item;
        item.reagentName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        item.reagentName = strcpy(item.reagentName, reagentResultList[i].reagentName);
        item.reagentChangeNum = reagentResultList[i].reagentNum;
        item.reagentId = reagentResultList[i].reagentId;
        item.time = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        item.time = strcpy(item.time,nowTime);
        item.mange = ADD;
        manageLabList[manageLabListLen++] = item;
    }
    updateManageLabList();

    return OK;
}

/*
    @author:deng
    @date:2022/5/31
    @function:"实时更新实验室库存记录"
    @input:{
    }
    @output:{
    }
    @execute:[deng.WinMain]
    @return:"执行状态"
*/
Status updateManageLabList() {
    FILE* fp;
    String fileName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    String str = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    sprintf(str, "%d", presentUser.id);
    fileName = strcat(strcat(strcat(strcpy(fileName, "./teacher"), str), "/"), "labManageRepertory.txt");
    /*
        @check:"文件打开错误处理."
    */
    if (!(fp = fopen(fileName, "w")))
    {
        return ERROR;
    }

    for (int i = 0; i < manageLabListLen; i++)
    {

        fprintf(fp,
            "%s %s %d %d %d\n",
            manageLabList[i].reagentName,
            manageLabList[i].time,
            manageLabList[i].reagentId,
            manageLabList[i].reagentChangeNum,
            manageLabList[i].mange
        );
    }
    fclose(fp);
    return OK;
}

/*
    @author:deng
    @date:2022/5/31
    @function:"更改试剂数量时（消耗）添加消耗记录"
    @input:{
    }
    @output:{
    }
    @execute:[deng.WinMain]
    @return:"执行状态"
*/
Status createConsumMnanageItem(int index, int changeNum) {
    // 获取当前时间
    char nowTime[20] = { 0 };
    time_t timep;
    time(&timep);
    struct tm* p;
    p = gmtime(&timep);
    snprintf(nowTime, 20, "%d-%d-%d_%d:%d:%d", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec);

    manageItem item;
    item.reagentName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    item.reagentName = strcpy(item.reagentName,laborReaList[index].reagentName);
    item.reagentChangeNum = changeNum;
    item.reagentId = laborReaList[index].reagentId;
    item.time = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    item.time = strcpy(item.time, nowTime);
    item.mange = changeNum > 0 ? ADD : SUB;
    manageLabList[manageLabListLen++] = item;

    updateManageLabList();

    return OK;
}

/*
    @author:deng
    @date:2022/5/31
    @function:"枚举转字符串用于显示"
    @input:{
    }
    @output:{
    }
    @execute:[deng.WinMain]
    @return:"执行状态"
*/
String getUpdateWayName(int way) {
    if (way == ADD) {
        return"ADD";
    }
    else if (way == SUB) {
        return"SUB";
    }
    else {
        return"ERROR";
    }
}