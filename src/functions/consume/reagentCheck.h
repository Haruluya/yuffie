#include"reagentCheckStruct.h"


//获取所有apply文件名。
Status initReagentApplyFiles();

//初始化申请项列表。
Status initReagentApplyList();

//添加请求项。
Status addReagentCheckItem(ReagentCheckItem);

//删除请求项。
Status deleteReagentCheckItemById(int);

//提交请求表。
Status commitReagentCheck();