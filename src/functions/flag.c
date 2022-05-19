#include"flag.h"



Status initPurchasePlanStatus() {
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
        String* purchasePlanStatusInfo = yuffieSplit(BUFF);

        //采购计划状态。
        if (!strcmp(purchasePlanStatusInfo[0], "PurcahsePlanStatus")) {
            purchasePlanStatus = atoi(purchasePlanStatusInfo[1]);
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
    FILE* fp;
    /*
        @check:"文件打开错误处理."
    */
    if (!(fp = fopen("flag.txt", "w"))) {
        return ERROR;
    }
    purchasePlanStatus = planStatus;
    fprintf(fp,
        "PurcahsePlanStatus %d",
        purchasePlanStatus
    );
    return OK;
}