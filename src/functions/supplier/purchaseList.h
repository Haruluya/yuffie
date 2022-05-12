
#define YUFFIE_PURCHASE_LIST_MAX_SIZE 199
typedef char* String;
typedef struct LoginMessage {
    int status;
    String message;
}LoginMessage;

typedef int Status;

typedef struct PurchaseItem {
    String inventoryName;
    int inventoryId;
    int inventoryNum;
}PurchaseItem;

PurchaseItem purchaseList[YUFFIE_PURCHASE_LIST_MAX_SIZE];

LoginMessage loginValidate(String userName);

String getPurchaseItemByIndex(int index);

Status initPurchaseList();

Status updatePurchaseByIndex();

Status createOfferApply();


