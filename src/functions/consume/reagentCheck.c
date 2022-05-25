#include"reagentCheck.h"






//获取所有apply文件名。
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

//初始化申请项列表。
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



//添加请求项。
Status addReagentCheckItem(ReagentCheckItem item) {
    if (!item.reagentName) {
        return INFASIBLE;
    }
    reagentCheckList[reagentCheckListLen++] = item;
    return OK;
}

//删除请求项。
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

//提交请求表。
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