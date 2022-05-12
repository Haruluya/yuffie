#include<Windows.h>
#include"id.h"
#include"resource.h"
#define YUFFIE_WINDOW_X 400
#define YUFFIE_WINDOW_Y 100
#define YUFFIE_WINDOW_NWIDTH 800
#define YUFFIE_WINDOW_NHEIGHT 600
#define YUFFIE_MAIN_TITLE TEXT("Yuffie:实验室信息化综合管理系统")


#define YUFFIE_BEGIN_BUTTON_X 300
#define YUFFIE_BEGIN_BUTTON_Y 350
#define YUFFIE_BEGIN_BUTTON_WIDTH 200
#define YUFFIE_BEGIN_BUTTON_HEIGHT 50

#define YUFFIE_CX_CLIENT 750
#define YUFFIE_CY_CLIENT 350

#define INIT_MENU_POS    0
#define HELLO_MENU_POS   2
#define RECT_MENU_POS    1

#define IDM_FIRSTCHILD   50000




HMENU     hMenuInit, hMenuHello, hMenuRect;
HMENU     hMenuInitWindow, hMenuHelloWindow, hMenuRectWindow;

HINSTANCE hInst;
HWND     hwndFrame, hwndClient;
LRESULT CALLBACK FrameWndProc(HWND, UINT, WPARAM, LPARAM);