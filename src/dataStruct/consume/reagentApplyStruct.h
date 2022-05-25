#include "global.h"
#include "user.h"


#ifndef HEADER_REAGENT_APPLY_STRUCT

#define HEADER_REAGENT_APPLY_STRUCT 114514



typedef struct ReagentApplyItem
{
    String reagentName;
    int reagentId;
    int reagentNum;
} ReagentApplyItem;


typedef struct RNode
{
    ReagentApplyItem data;
    struct RNode* next;
} RNode;
typedef struct RNode* ReagentApplyLinkList;

#define INFO_MAXSIZE 50

#define REAGENT_APPLY_LIST_MAX_SIZE 199

ReagentApplyLinkList reagentApplyList;

//Á´±í´úÌæ¡£
//ReagentApplyItem reagentApplyList[REAGENT_APPLY_LIST_MAX_SIZE];


int reagentApplyListLen;

ReagentApplyItem reagentResultList[REAGENT_APPLY_LIST_MAX_SIZE];

int reagentResultListLen;

#endif // !HEADER_REAGENT_APPLY_STRUCT