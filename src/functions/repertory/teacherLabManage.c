#include"teacherLabManage.h"



//初始化实验室库存记录。
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

//添加申请结果的入库记录。
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



//实时更新实验室库存记录。
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