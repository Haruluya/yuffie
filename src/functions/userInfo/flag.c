#include"flag.h"


Status initStatus() {
    FILE* fp;
    /*
        @check:"文件打开错误处理."
    */
    if (!(fp = fopen("flag.txt", "r"))) {
        return ERROR;
    }
    while (!feof(fp)) {
        fgets(BUFF, sizeof(BUFF), fp);
        if (!strcmp(BUFF, "\0")) {
            continue;
        }

        //获取以空格切分的属性数组.
        String*  statusInfo = yuffieSplit(BUFF);

        //采购计划状态。
        if (!strcmp(statusInfo[0], "PurchasePlanStatus")) {
            purchasePlanStatus = atoi(statusInfo[1]);
        }
        if (!strcmp(statusInfo[0], "ReagentAuditStatus")) {
            reagentAudioStatus = atoi(statusInfo[1]);
        }
        BUFF[0] = '\0';
    }

    fclose(fp);
    return OK;
}

Status setPurchasePlanStatus(PLANSTATUS planStatus) {
    if (planStatus < ANNOUNCEMENT || planStatus > REVIEWOFFER) {
        return INFASIBLE;
    }
    purchasePlanStatus = planStatus;
    updateFlag();
    return OK;
}

Status setReagentAuditStatus(TASK_STATUS status) {
    if (status < UNDERWAY || status > OVER) {
        return INFASIBLE;
    }
    reagentAudioStatus = status;
    updateFlag();
    return OK;
}


Status updateFlag() {
    FILE* fp;
    /*
        @check:"文件打开错误处理."
    */
    if (!(fp = fopen("flag.txt", "w"))) {
        return ERROR;
    }
    fprintf(fp,
        "PurchasePlanStatus %d\n",
        purchasePlanStatus
    );
    fprintf(fp,
        "ReagentAuditStatus %d",
        reagentAudioStatus
    );
    fclose(fp);
    return OK;
}