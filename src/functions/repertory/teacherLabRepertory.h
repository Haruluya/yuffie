#include "repertoryStruct.h"
#include"reagentApplyStruct.h"



//初始化实验室仓库。
Status initLabRepertoryList();

//手动更新（使用试剂）实验室仓库。
Status updateLabRepertory(int,int);



//privace函数，删除实验室仓库某项。
Status deleteLabRepertoryItemById(int);

//更新实验室仓库文件。
Status updateLabRepertoryFile();


//添加申请结果到实验室仓库。
Status addApplyResultItemToLab();


Status printLabRepertory();
