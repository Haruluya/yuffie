#include"src/gui/guiTools.h"
#include"src/globalConst.h"
#include"src/gui/components/loginDialog/loginDialog.h"

#define IDM_DIALOG1     101
#define IDM_DIALOG2     102
#define IDM_HELP        201
#define IDM_ABOUT       202

/*
	@function:"主窗口事件处理函数。"
*/
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInst;

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
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
	/*
		@value:"主窗口类名。"
	*/
	static TCHAR szAppName[] = TEXT ("Yuffie") ;

	/*
		@value:"主窗口句柄。"
	*/
	HWND         hwnd ;

	/*
		@value:"消息队列消息。"
	*/
	MSG          msg ;

	/*
		@value:"窗口类。"
	*/
	WNDCLASS     wndclass ;

	hInst = hInstance;

	//窗口类属性设计。
	wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
	wndclass.lpfnWndProc   = WndProc ;
	wndclass.cbClsExtra    = 0 ;
	wndclass.cbWndExtra    = 0 ;
	wndclass.hInstance		= hInstance;
	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
	wndclass.lpszMenuName  = NULL ;
	wndclass.lpszClassName = szAppName ;
    wndclass.hIcon  = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
	
	/*
		@Check:"窗口类注册失败处理。"
	*/
	if (!RegisterClass (&wndclass))
	{
		MessageBox (NULL, TEXT ("This program requires Windows NT!"), 
					szAppName, MB_ICONERROR) ;
		return 0 ;
	}

	// 窗口创建。
	hwnd = CreateWindow (szAppName,                
						TEXT ("Yuffie"), 
						WS_OVERLAPPEDWINDOW^WS_THICKFRAME,        
						YUFFIE_WINDOW_X,             
						YUFFIE_WINDOW_Y,              
						YUFFIE_WINDOW_NWIDTH,             
						YUFFIE_WINDOW_NHEIGHT,             
						NULL,                       
						NULL,                    
						hInstance,                 
						NULL) ;                    

	// 创建总菜单。
	HMENU hMenu = CreateMenu();

	// 创建弹出菜单项。
	HMENU hSubMenu = CreatePopupMenu();
	AppendMenu(hSubMenu, MF_STRING, ID_FILE_EXIT, "E&xit");
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");

	hSubMenu = CreatePopupMenu();
	AppendMenu(hSubMenu, MF_STRING, ID_STUFF_GO, "&Go");
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Stuff");

	SetMenu(hwnd, hMenu);

	// 显示、更新窗口。
	ShowWindow (hwnd, iCmdShow) ;
	UpdateWindow (hwnd) ;
	
	// 消息队列循环。
     while (GetMessage (&msg, NULL, 0, 0))
     {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     return msg.wParam ;
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
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	/*
		@value:""
	*/
	HDC         hdc ;

	/*
		@value:"绘制状态信息。"
	*/
	PAINTSTRUCT ps ;
	
	/*
		@value:"title区域。"
	*/
	RECT titleRect ;
	static HFONT titleFont;

	static HWND beginButton;
	static RECT beginButtonRect;
	static int  beginButtonCxChar, beginButtonCyChar ;
    static int      cxClient, cyClient ;


	static HINSTANCE hInstance ;


	/*
		@check:"消息处理。"
	*/
	switch (message)
	{

	case WM_CREATE:
	{
		hInstance = ((LPCREATESTRUCT) lParam)->hInstance ;
		loadYuffieIcon(hwnd,YUFFIE_ICON_FILENAME);

		beginButtonCxChar = 100 ;
		beginButtonCyChar = 100;
		beginButton = CreateWindow( 
				TEXT("button"), 
                TEXT("Enter System"),
				WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,  
				300,         
				350,        
				200,        
				50,        
				hwnd,    
				(HMENU)IDI_BEGIN_BUTTON,      
				hInst,
				NULL);
		return 0 ;
	}
	case WM_SIZE:
		cxClient = 750 ;
		cyClient = 350 ;
		return 0 ;

	case WM_PAINT:
		hdc = BeginPaint (hwnd, &ps) ;
 		PaintRoutine (hwnd, hdc, cxClient, cyClient) ;
		EndPaint (hwnd, &ps) ;
		return 0 ;


	case WM_COMMAND:
	{
		YUFFIE_COM_ID commandComID;
		commandComID = LOWORD(wParam);
		switch (commandComID){
			case IDI_BEGIN_BUTTON: 
			{
				loginDialog(hwnd,hInst);
				return DefWindowProc (hwnd, message, wParam, lParam) ;
			}
			case ID_FILE_EXIT:
			{
				return DefWindowProc (hwnd, message, wParam, lParam) ;

			}
			default:
				return DefWindowProc (hwnd, message, wParam, lParam) ;
		}
	}
		
	case WM_DESTROY:
		PostQuitMessage (0) ;
		return 0 ;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;

}




