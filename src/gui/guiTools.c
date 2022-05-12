/*
  @license:
    MIT License

    Copyright (c) 2022 Haruluya

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

    @version:0.0.1
    @date:2022/5/9
    @author:haruluya
    @function:"基于Win 32 API 的GUI辅助工具类。".   
    @include:[guiTools.h]  
    @log:guiTools.log    
    @functions:{
        message_box_printf:"重构messagebox，支持格式化文字。",
        play_wav_music:"播放wav音乐文件。" ,
        draw_text:"区域内绘制文字。"
    }
*/

#include"guiTools.h"
#include"../globalConst.h"




/*
    @author:haruluya
    @date:2022/5/9
    @function:"重构messagebox，支持格式化文字。"
    @input:{
        szCaption:"消息标题。",
        szFormat:"消息格式化字符。",
        ...:"messageBox配置参数。"
    }
    @output:{  
    }
    @execute:[yuffie.WinMain] 
    @return:"status code."
*/
int CDECL messageBoxPrintf(TCHAR* szCaption, TCHAR* szFormat,...)
{
    TCHAR szBuffer [1024];
    va_list pArgList;
    va_start (pArgList, szFormat);
    _vsntprintf(szBuffer,sizeof(szBuffer)/sizeof(TCHAR),szFormat,pArgList);
    va_end(pArgList);
    return MessageBox(NULL,szBuffer,szCaption,0);
}

/*
    @author:haruluya
    @date:2022/5/9
    @function:"播放wav音乐文件。"
    @input:{
        fileName:"wav文件名。"
    }
    @output:{  
    }
    @execute:[yuffie.WinMain] 
    @return:"status code."
*/
void playWavMusic(char* fileName)
{
    // PlaySound (TEXT("minnan.wav"),NULL,SND_FILENAME | SND_ASYNC);
}


/*
    @author:haruluya
    @date:2022/5/9
    @function:"区域内绘制文字。"
    @input:{
        hdc:"绘制窗口的句柄。",
        rect:"绘制区域。"
    }
    @output:{  
    }
    @execute:[yuffie.WinMain] 
    @return:"status code."
*/
void drawText(HDC hdc,RECT rect)
{
    DrawText(hdc,TEXT("Hello,Window 98!"),-1,&rect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
}

void loadYuffieIcon(HWND hwnd, char* filename)
{
    HICON hIcon;
    hIcon = LoadImage(NULL, "assert/image/logo.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
    if(hIcon)
        SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    else
        MessageBox(hwnd, "找不到图标文件!", "Error", MB_OK | MB_ICONERROR);
}




HFONT EzCreateFont (HDC hdc, TCHAR * szFaceName, int iDeciPtHeight,
                    int iDeciPtWidth, int iAttributes, BOOL fLogRes)
{
     FLOAT      cxDpi, cyDpi ;
     HFONT      hFont ;
     LOGFONT    lf ;
     POINT      pt ;
     TEXTMETRIC tm ;
     
     SaveDC (hdc) ;
     
     SetGraphicsMode (hdc, GM_ADVANCED) ;
     ModifyWorldTransform (hdc, NULL, MWT_IDENTITY) ;
     SetViewportOrgEx (hdc, 0, 0, NULL) ;
     SetWindowOrgEx   (hdc, 0, 0, NULL) ;
     
     if (fLogRes)
     {
          cxDpi = (FLOAT) GetDeviceCaps (hdc, LOGPIXELSX) ;
          cyDpi = (FLOAT) GetDeviceCaps (hdc, LOGPIXELSY) ;
     }
     else
     {
          cxDpi = (FLOAT) (25.4 * GetDeviceCaps (hdc, HORZRES) /
                                        GetDeviceCaps (hdc, HORZSIZE)) ;
          
          cyDpi = (FLOAT) (25.4 * GetDeviceCaps (hdc, VERTRES) /
                                        GetDeviceCaps (hdc, VERTSIZE)) ;
     }
     
     pt.x = (int) (iDeciPtWidth  * cxDpi / 72) ;
     pt.y = (int) (iDeciPtHeight * cyDpi / 72) ;
     
     DPtoLP (hdc, &pt, 1) ;
     
     lf.lfHeight         = - (int) (fabs (pt.y) / 10.0 + 0.5) ;
     lf.lfWidth          = 0 ;
     lf.lfEscapement     = 0 ;
     lf.lfOrientation    = 0 ;
     lf.lfWeight         = iAttributes & EZ_ATTR_BOLD      ? 400 : 0 ;
     lf.lfItalic         = iAttributes & EZ_ATTR_ITALIC    ?   1 : 0 ;
     lf.lfUnderline      = iAttributes & EZ_ATTR_UNDERLINE ?   1 : 0 ;
     lf.lfStrikeOut      = iAttributes & EZ_ATTR_STRIKEOUT ?   1 : 0 ;
     lf.lfCharSet        = DEFAULT_CHARSET ;
     lf.lfOutPrecision   = 0 ;
     lf.lfClipPrecision  = 0 ;
     lf.lfQuality        = 0 ;
     lf.lfPitchAndFamily = 0 ;
     
     lstrcpy (lf.lfFaceName, szFaceName) ;
     
     hFont = CreateFontIndirect (&lf) ;
     
     if (iDeciPtWidth != 0)
     {
          hFont = (HFONT) SelectObject (hdc, hFont) ;
          
          GetTextMetrics (hdc, &tm) ;
          
          DeleteObject (SelectObject (hdc, hFont)) ;
          
          lf.lfWidth = (int) (tm.tmAveCharWidth *
                                        fabs (pt.x) / fabs (pt.y) + 0.5) ;
          
          hFont = CreateFontIndirect (&lf) ;
     }
     
     RestoreDC (hdc, -1) ;
     return hFont ;
}




void PaintRoutine (HWND hwnd, HDC hdc, int cxArea, int cyArea)
{
    static TCHAR szString [] = YUFFIE_MAIN_TITLE ;
	HFONT        hFont ;
	SIZE         size ;

	hFont = EzCreateFont (hdc, TEXT ("Times New Roman"), 300, 0, 0, TRUE) ;

	SelectObject (hdc, hFont) ;
	SetBkMode (hdc, TRANSPARENT) ;

	GetTextExtentPoint32 (hdc, szString, lstrlen (szString), &size) ;

	BeginPath (hdc) ;
	TextOut (hdc, (cxArea - size.cx) / 2, (cyArea - size.cy) / 2,
				szString, lstrlen (szString)) ;
	EndPath (hdc) ;

	SelectObject (hdc, CreateHatchBrush (HS_DIAGCROSS, RGB (255, 0, 0))) ;
	SetBkColor (hdc, RGB (0, 0, 255)) ;
	SetBkMode (hdc, OPAQUE) ;

	StrokeAndFillPath (hdc) ;

	DeleteObject (SelectObject (hdc, GetStockObject (WHITE_BRUSH))) ;
	SelectObject (hdc, GetStockObject (SYSTEM_FONT)) ;
	DeleteObject (hFont) ;
}



