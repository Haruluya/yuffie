
#include"globalConst.h"

typedef TCHAR* String;
#define ID_YUFFIE_USERNAME_EDIT 500
#define ID_YUFFIE_PASSWORD_EDIT 501
#define ID_YUFFIE_USERNAME_LAB 502
#define ID_YUFFIE_PASSWORD_LAB 503
#define OK 1
#define ERROR 0

typedef struct LoginMessage {
    int status;
    String message;
}LoginMessage;

BOOL CALLBACK loginDlgProc(HWND, UINT,
    WPARAM, LPARAM);
BOOL validateUserName(String);
BOOL validatePassword(String);



LoginMessage validateUser(String, String);
