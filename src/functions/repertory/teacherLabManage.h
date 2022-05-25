#include"repertoryManageStruct.h"
#include"reagentApplyStruct.h"
#include"repertoryStruct.h"
#include"user.h"


//初始化实验室库存记录。
Status initManageLabList();

//实时更新实验室库存记录。
Status updateManageLabList();


Status addApplyResultToManageLabList();

//更改试剂数量时（消耗）添加消耗记录。
Status createConsumMnanageItem(int,int);

//枚举转字符串用于显示。
String getUpdateWayName(int);