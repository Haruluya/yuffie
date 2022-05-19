#include"global.h"
#include"user.h"
typedef enum PLANSTATUS
{
    ANNOUNCEMENT,
    REVIEWAPPLY,
    REVIEWOFFER,
}PLANSTATUS;

PLANSTATUS purchasePlanStatus;



Status initPurchasePlanStatus();
Status setPurchasePlanStatus(PLANSTATUS);
