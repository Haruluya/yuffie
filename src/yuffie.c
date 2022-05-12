#include"yuffie.h"

/*
	@function:"主窗口事件处理函数。"
*/

TCHAR     szFrameClass[] = TEXT("MdiFrame");
TCHAR     szHelloClass[] = TEXT("MdiHelloChild");
/*
	@author:haruluya
	@date:2022/5/9
	@model_function:"程序主函数，主窗口构造函数。"
	@input:{
		hInstance:"程序可执行模块的句柄。",
		hPrevInstance:"历史遗留参数，始终为NULL。",
		szCmdLine:"命令行参数。",
		iCmdShow:"窗口显示形式。"
	}
	@output:{
	}
	@execute:[yuffie.WinMain]
	@return:"status code."
*/


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	/*
		@value:"主窗口类名。"
	*/
	static TCHAR szAppName[] = TEXT("Yuffie");

	/*
		@value:"主窗口句柄。"
	*/
	HWND         hwnd;

	/*
		@value:"消息队列消息。"
	*/
	MSG          msg;

	/*
		@value:"窗口类。"
	*/
	WNDCLASS     wndclass;

	HACCEL   hAccel;


	hInst = hInstance;




	//窗口类属性设计。
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = FrameWndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE + 1);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szFrameClass;
	/*
		@Check:"窗口类注册失败处理。"
	*/
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This Window register failed!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = HelloWndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = sizeof(HANDLE);
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szHelloClass;


	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This supplierTemplate register failed!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	hMenuInit = LoadMenu(hInstance, TEXT("MdiMenuInit"));
	hMenuHello = LoadMenu(hInstance, TEXT("MdiMenuHello"));
	hMenuRect = LoadMenu(hInstance, TEXT("MdiMenuRect"));

	hMenuInitWindow = GetSubMenu(hMenuInit, INIT_MENU_POS);
	hMenuHelloWindow = GetSubMenu(hMenuHello, HELLO_MENU_POS);
	hMenuRectWindow = GetSubMenu(hMenuRect, RECT_MENU_POS);


	hAccel = LoadAccelerators(hInstance, szAppName);

	// 窗口创建。
	hwndFrame = CreateWindow(szFrameClass,
		TEXT("Yuffie"),
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME | WS_CLIPCHILDREN,
		YUFFIE_WINDOW_X,
		YUFFIE_WINDOW_Y,
		YUFFIE_WINDOW_NWIDTH,
		YUFFIE_WINDOW_NHEIGHT,
		NULL,
		hMenuInit,
		hInstance,
		NULL);



	hwndClient = GetWindow(hwndFrame, GW_CHILD);

	// 显示、更新窗口。
	ShowWindow(hwndFrame, iCmdShow);
	UpdateWindow(hwndFrame);

	// 消息队列循环。
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateMDISysAccel(hwndClient, &msg) &&
			!TranslateAccelerator(hwndFrame, hAccel, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	// Clean up by deleting unattached menus
	DestroyMenu(hMenuHello);
	DestroyMenu(hMenuRect);

	return msg.wParam;
}


/*
	@author:haruluya
	@date:2022/5/9
	@function:"主窗口事件处理函数。"
	@input:{
		hwnd:"主窗口句柄。",
		message:"事件信息。",
		wParam:"事件伴随参数。",
		lParam:"事件伴随参数。"
	}
	@output:{
	}
	@execute:[haruluya.WinMain]
	@return:"运行状态。"
*/
LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	/*
		@value:""
	*/
	HDC         hdc;

	/*
		@value:"绘制状态信息。"
	*/
	PAINTSTRUCT ps;

	/*
		@value:"title区域。"
	*/
	RECT titleRect;
	static HFONT titleFont;

	/*
	@value:"进入系统按钮。"
	*/
	static HWND beginButton;

	static HWND        hwndClient;
	CLIENTCREATESTRUCT clientcreate;
	HWND               hwndChild;
	MDICREATESTRUCT    mdicreate;
	

	/*
		@check:"消息处理。"
	*/
	switch (message)
	{

	case WM_CREATE:
	{
		//创建进入系统按钮。
		beginButton = createDefaultButton(
			TEXT("button"),
			TEXT("Enter System"),
			YUFFIE_BEGIN_BUTTON_X,
			YUFFIE_BEGIN_BUTTON_Y,
			YUFFIE_BEGIN_BUTTON_WIDTH,
			YUFFIE_BEGIN_BUTTON_HEIGHT,
			hwnd,
			(HMENU)ID_YUFFIE_BEGIN_BUTTON,
			hInst
		);

		clientcreate.hWindowMenu = hMenuInitWindow;
		clientcreate.idFirstChild = IDM_FIRSTCHILD;

		hwndClient = CreateWindow(TEXT("MDICLIENT"), NULL,
			WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE | WM_MDITILE,
			0, 0, 0, 0, hwnd, (HMENU)1, hInst,
			(PSTR)&clientcreate);
		return 0;
	}

	


	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		PaintRoutine(hwnd, hdc, YUFFIE_CX_CLIENT, YUFFIE_CY_CLIENT);
		EndPaint(hwnd, &ps);
		return 0;


	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_YUFFIE_BEGIN_BUTTON:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_LOGIN_DIALOG), hwnd, loginDlgProc);
			break;
		case IDM_FILE_NEWHELLO:
		case IDD_LOGIN_DIALOG:

			mdicreate.szClass = szHelloClass;
			mdicreate.szTitle = TEXT("Hello");
			mdicreate.hOwner = hInst;
			mdicreate.x = CW_USEDEFAULT;
			mdicreate.y = CW_USEDEFAULT;
			mdicreate.cx = CW_USEDEFAULT;
			mdicreate.cy = CW_USEDEFAULT;
			mdicreate.style = 0;
			mdicreate.lParam = 0;

			hwndChild = (HWND)SendMessage(hwndClient,
				WM_MDICREATE, 0,
				(LPARAM)(LPMDICREATESTRUCT)&mdicreate);
			SendMessage(hwndClient, WM_MDITILE, 0, 0);
			return 0;

		case IDM_FILE_CLOSE:          // Close the active window

			hwndChild = (HWND)SendMessage(hwndClient,
				WM_MDIGETACTIVE, 0, 0);

			if (SendMessage(hwndChild, WM_QUERYENDSESSION, 0, 0))
				SendMessage(hwndClient, WM_MDIDESTROY,
					(WPARAM)hwndChild, 0);
			return 0;

		case IDM_APP_EXIT:            // Exit the program

			SendMessage(hwnd, WM_CLOSE, 0, 0);
			return 0;

			// messages for arranging windows

		case IDM_WINDOW_TILE:
			SendMessage(hwndClient, WM_MDITILE, 0, 0);
			return 0;

		case IDM_WINDOW_CASCADE:
			SendMessage(hwndClient, WM_MDICASCADE, 0, 0);
			return 0;

		case IDM_WINDOW_ARRANGE:
			SendMessage(hwndClient, WM_MDIICONARRANGE, 0, 0);
			return 0;

		case IDM_WINDOW_CLOSEALL:     // Attempt to close all children

			EnumChildWindows(hwndClient, CloseEnumProc, 0);
			return 0;

		default:             // Pass to active child...

			hwndChild = (HWND)SendMessage(hwndClient,
				WM_MDIGETACTIVE, 0, 0);

			if (IsWindow(hwndChild))
				SendMessage(hwndChild, WM_COMMAND, wParam, lParam);

			break;        // ...and then to DefFrameProc
		}
		return 0;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefFrameProc(hwnd, hwndClient, message, wParam, lParam);
}


