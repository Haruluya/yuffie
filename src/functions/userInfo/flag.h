#include"global.h"
#include"user.h"
typedef enum PLANSTATUS
{
    ANNOUNCEMENT,
    REVIEWAPPLY,
    REVIEWOFFER,
}PLANSTATUS;

typedef enum TASK_STATUS
{
    UNDERWAY,
    OVER,
}TASK_STATUS;


PLANSTATUS purchasePlanStatus;

TASK_STATUS reagentAudioStatus;



Status initStatus();
Status setPurchasePlanStatus(PLANSTATUS);
Status setReagentAuditStatus(TASK_STATUS);
Status updateFlag();