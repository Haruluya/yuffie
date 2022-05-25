#include"yuffie.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' "\
						"name='Microsoft.Windows.Common-Controls' "\
						"version='6.0.0.0' processorArchitecture='*' "\
						"publicKeyToken='6595b64144ccf1df' language='*'\"")

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

	/*
		@value:"快捷键映射。"
	*/
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

	//MDI-supplier窗口样式设计。
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = SupplierWndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = sizeof(HANDLE);
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szSupplierClass;

	/*
		@Check:"窗口类注册失败处理。"
	*/
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This supplierTemplate register failed!"),
			szAppName, MB_ICONERROR);
		return 0;
	}


	//MDI-frame窗口样式设计。
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = HallWndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = sizeof(HANDLE);
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szHallClass;

	/*
	@Check:"窗口类注册失败处理。"
	*/
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This hallWindow register failed!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	//MDI-admin窗口样式设计。
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = AdminWndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = sizeof(HANDLE);
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAdminClass;

	/*
	@Check:"窗口类注册失败处理。"
	*/
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This hallWindow register failed!"),
			szAppName, MB_ICONERROR);
		return 0;
	}


	//MDI-teacher窗口样式设计。
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = TeacherWndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = sizeof(HANDLE);
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szTeacherClass;

	/*
	@Check:"窗口类注册失败处理。"
	*/
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This hallWindow register failed!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	//获取菜单句柄。
	hMenuInit = LoadMenu(hInstance, TEXT("MdiMenuInit"));
	hMenuSupplier = LoadMenu(hInstance, TEXT("MdiMenuSupplier"));
	hMenuRect = LoadMenu(hInstance, TEXT("MdiMenuRect"));

	hMenuInitWindow = GetSubMenu(hMenuInit, INIT_MENU_POS);
	hMenuSupplierWindow = GetSubMenu(hMenuSupplier, HELLO_MENU_POS);
	hMenuRectWindow = GetSubMenu(hMenuRect, RECT_MENU_POS);

	//快捷键映射。
	hAccel = LoadAccelerators(hInstance, szAppName);

	// 窗口创建。
	hwndFrame = CreateWindow(szFrameClass,
		TEXT("Yuffie"),
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME^ WS_MAXIMIZEBOX | WS_CLIPCHILDREN,
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
		/*
			@check:消息队列处理。
		*/
		if (!TranslateMDISysAccel(hwndClient, &msg) &&
			!TranslateAccelerator(hwndFrame, hAccel, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	//清除资源。
	DestroyMenu(hMenuSupplier);
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
	@execute:[yuffie.WinMain]
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
		@value:"MDI窗口句柄。"
	*/
	static HWND        hwndClient;

	/*
		@value:"MDI窗口配置。"
	*/
	CLIENTCREATESTRUCT clientcreate;

	/*
		@value:"当前子窗口句柄。"
	*/
	HWND               hwndChild;

	/*
		@value:"MDI窗口样式。"
	*/
	MDICREATESTRUCT    mdicreate;


	/*
		@check:"消息处理。"
	*/
	switch (message)
	{

	case WM_CREATE:
	{
		BUFF[0] = '\0';
		/*
			@check:"导入user表是否成功。"
		*/
		if (!initUserList()) {
			MessageBox(hwnd, TEXT("导入user表失败！"), TEXT("ERROR"), MB_ICONINFORMATION);
		}

		initStatus();

		clientcreate.hWindowMenu = hMenuInitWindow;
		clientcreate.idFirstChild = IDM_FIRSTCHILD;

		//创建MDI窗口。
		hwndClient = CreateWindow(TEXT("MDICLIENT"), NULL,
			WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE | WM_MDITILE,
			0, 0, 0, 0, hwnd, (HMENU)1, hInst,
			(PSTR)&clientcreate);


		SendMessage(hwnd, WM_COMMAND, CM_YUFFIE_CREATE_HALL, 0);
		SendMessage(hwndClient, WM_MDITILE, 0, 0);


		return 0;
	}

	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
	}
		return 0;

	case WM_COMMAND:
	{
		
		/*
			@check:"command消息队列事件处理。"
		*/
		switch (LOWORD(wParam))
		{
		
		case CM_YUFFIE_CREATE_HALL:
		{
			//显示MID-hall窗口。
			mdicreate.szClass = szHallClass;
			mdicreate.szTitle = TEXT("Hall");
			mdicreate.hOwner = hInst;
			mdicreate.x = CW_USEDEFAULT;
			mdicreate.y = CW_USEDEFAULT;
			mdicreate.cx = CW_USEDEFAULT;
			mdicreate.cy = CW_USEDEFAULT;
			mdicreate.style = 0;
			mdicreate.lParam = 0;

			hwndHall = (HWND)SendMessage(hwndClient,
				WM_MDICREATE, 0,
				(LPARAM)(LPMDICREATESTRUCT)&mdicreate);
			SendMessage(hwndClient, WM_MDITILE, 0, 0);
			PostMessage(hwndHall, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
			return 0;
		}
		case IDM_FILE_NEWHELLO:
		case CM_YUFFIE_CREATE_TEACHER:
		{
			//显示MID-hall窗口。
			mdicreate.szClass = szTeacherClass;
			mdicreate.szTitle = TEXT("Teacher");
			mdicreate.hOwner = hInst;
			mdicreate.x = CW_USEDEFAULT;
			mdicreate.y = CW_USEDEFAULT;
			mdicreate.cx = CW_USEDEFAULT;
			mdicreate.cy = CW_USEDEFAULT;
			mdicreate.style = 0;
			mdicreate.lParam = 0;

			hwndHall = (HWND)SendMessage(hwndClient,
				WM_MDICREATE, 0,
				(LPARAM)(LPMDICREATESTRUCT)&mdicreate);
			SendMessage(hwndClient, WM_MDITILE, 0, 0);
			PostMessage(hwndHall, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
			return 0;
		}
		case CM_YUFFIE_CREATE_ADMIN:
		{
			//显示MID-hall窗口。
			mdicreate.szClass = szAdminClass;
			mdicreate.szTitle = TEXT("Admin");
			mdicreate.hOwner = hInst;
			mdicreate.x = CW_USEDEFAULT;
			mdicreate.y = CW_USEDEFAULT;
			mdicreate.cx = CW_USEDEFAULT;
			mdicreate.cy = CW_USEDEFAULT;
			mdicreate.style = 0;
			mdicreate.lParam = 0;

			hwndAdmin = (HWND)SendMessage(hwndClient,
				WM_MDICREATE, 0,
				(LPARAM)(LPMDICREATESTRUCT)&mdicreate);
			SendMessage(hwndClient, WM_MDITILE, 0, 0);
			PostMessage(hwndAdmin, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
			return 0;
		}


		case CM_YUFFIE_CREATE_SUPPLIER:
			PostMessage(hwndHall, WM_CLOSE,CM_YUFFI_QUIT, 0);
			//显示MID-supplier窗口。
			mdicreate.szClass = szSupplierClass;
			mdicreate.szTitle = TEXT("Supplier");
			mdicreate.hOwner = hInst;
			mdicreate.x = CW_USEDEFAULT;
			mdicreate.y = CW_USEDEFAULT;
			mdicreate.cx = CW_USEDEFAULT;
			mdicreate.cy = CW_USEDEFAULT;
			mdicreate.style = 0;
			mdicreate.lParam = 0;

			hwndSupplier = (HWND)SendMessage(hwndClient,
				WM_MDICREATE, 0,
				(LPARAM)(LPMDICREATESTRUCT)&mdicreate);
			SendMessage(hwndClient, WM_MDITILE, 0, 0);
			PostMessage(hwndSupplier, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
			return 0;
		case IDM_FILE_CLOSE:          

			//窗口关闭。
			hwndChild = (HWND)SendMessage(hwndClient,
				WM_MDIGETACTIVE, 0, 0);

			if (SendMessage(hwndChild, WM_QUERYENDSESSION, 0, 0))
				SendMessage(hwndClient, WM_MDIDESTROY,
					(WPARAM)hwndChild, 0);
			return 0;

		case IDM_APP_EXIT:            

			//程序关闭。
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			return 0;

		case IDM_WINDOW_TILE:

			//窗口排列。
			SendMessage(hwndClient, WM_MDITILE, 0, 0);
			return 0;

		case IDM_WINDOW_CASCADE:

			//窗口级联。
			SendMessage(hwndClient, WM_MDICASCADE, 0, 0);
			return 0;

		case IDM_WINDOW_ARRANGE:

			//窗口最小化。
			SendMessage(hwndClient, WM_MDIICONARRANGE, 0, 0);
			return 0;

		case IDM_WINDOW_CLOSEALL:     

			//子窗口全部关闭。
			EnumChildWindows(hwndClient, CloseEnumProc, 0);
			return 0;

		default:             

			//获取活跃子窗口。
			hwndChild = (HWND)SendMessage(hwndClient,
				WM_MDIGETACTIVE, 0, 0);

			if (IsWindow(hwndChild))
				SendMessage(hwndChild, WM_COMMAND, wParam, lParam);

			break;       
		}
		return 0;
	}

	//窗口销毁。
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefFrameProc(hwnd, hwndClient, message, wParam, lParam);
}


