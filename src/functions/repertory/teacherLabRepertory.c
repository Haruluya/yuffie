#include"teacherLabRepertory.h"


//初始化实验室仓库。
Status initLabRepertoryList() {

    FILE* fp;
    laborReaListLen = 0;

    /*
        @check:"文件打开错误处理."
    */
    String fileName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    String str = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    sprintf(str, "%d",presentUser.id);
    fileName = strcat(strcat(strcat(strcpy(fileName, "./teacher"), str), "/"),"labRepertory.txt");

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
        String* reagentItemInfo= yuffieSplit(BUFF);

        ReagentItem reagentItem;

 
        reagentItem.reagentName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        reagentItem.reagentName = strcpy(reagentItem.reagentName, reagentItemInfo[0]);
        reagentItem.reagentId = atoi(reagentItemInfo[1]);
        reagentItem.reagentNum = atoi(reagentItemInfo[2]);

        laborReaList[laborReaListLen++] = reagentItem;
        BUFF[0] = '\0';
    }

    fclose(fp);
    return OK;
}

//手动更新（使用试剂）实验室仓库。
Status updateLabRepertory(int id, int num) {
    for (int i = 0; i < laborReaListLen; i++) {
        if (id == laborReaList[i].reagentId) {
            if (num + laborReaList[i].reagentNum ==  0) {
                deleteLabRepertoryItemById(id);
            }
            else {
                laborReaList[i].reagentNum += num;
            }
            updateLabRepertoryFile();
            return OK;
        }
    }
    return NOT_FOUND;
}

//入库申请结果。
Status appendApplyResultRepertory() {

    for (int i = 0; i < reagentResultListLen; i++) {
        ReagentItem item;
        item.reagentName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        item.reagentName = strcpy(item.reagentName, reagentResultList[i].reagentName);
        item.reagentId = reagentResultList[i].reagentId;
        item.reagentNum = reagentResultList[i].reagentNum;
        laborReaList[laborReaListLen++] = item;
    }
    updateLabRepertoryFile();

    return OK;
}


Status deleteLabRepertoryItemById(int id) {
    for (int i = 0; i < laborReaListLen; i++) {
        if (laborReaList[i].reagentId == id) {
            for (int j = i; j < laborReaListLen - 1; j++) {
                String str = (String)malloc(sizeof(char) * INFO_MAXSIZE);
                strcpy(str, laborReaList[j + 1].reagentName);
                laborReaList[j].reagentName = str;
                laborReaList[j].reagentId = laborReaList[j + 1].reagentId;
                laborReaList[j].reagentNum = laborReaList[j + 1].reagentNum;
            }
            laborReaListLen--;
            return OK;
        }
    }
    return NOT_FOUND;
}

Status updateLabRepertoryFile() {
    FILE* fp;

    String fileName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    String str = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    sprintf(str, "%d", presentUser.id);
    fileName = strcat(strcat(strcat(strcpy(fileName, "./teacher"), str), "/"), "labRepertory.txt");

    if (!(fp = fopen(fileName, "w")))
    {
        return ERROR;
    }
    for (int i = 0; i < laborReaListLen; i++)
    {

        fprintf(fp,
            "%s %d %d\n",
            laborReaList[i].reagentName,
            laborReaList[i].reagentId,
            laborReaList[i].reagentNum
        );
    }
    fclose(fp);
    return OK;
}

//打印实验室库存。
Status printLabRepertory() {
    FILE* fp;

    String fileName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    String str = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    sprintf(str, "%d", presentUser.id);
    fileName = strcat(strcat(strcat(strcpy(fileName, "./teacher"), str), "/"), "labRepertoryPrint.txt");

    if (!(fp = fopen(fileName, "w")))
    {
        return ERROR;
    }
    for (int i = 0; i < laborReaListLen; i++)
    {


        fprintf(fp,
            "%s %d %d\n",
            laborReaList[i].reagentName,
            laborReaList[i].reagentId,
            laborReaList[i].reagentNum
        );
    }
    fclose(fp);
    return OK;
}



