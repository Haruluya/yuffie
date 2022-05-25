#include "global.h"
#include "user.h"


typedef struct ReagentCheckItem
{
    String reagentName;
    int reagentId;
    int reagentNum;
    int teacherId;
} ReagentCheckItem;


#define INFO_MAXSIZE 50

#define REAGENT_CHECK_LIST_MAX_SIZE 199

ReagentCheckItem reagentCheckList[REAGENT_CHECK_LIST_MAX_SIZE];

int reagentCheckListLen;

String reagentApplyFileName[INFO_MAXSIZE];

int reagentApplyFileLen;
