#include"guiTools.h"


HWND createDefaultButton(LPCTSTR lpClassName, LPCTSTR lpWindowName, 
		int x, int y, int nWindth, int nHeight, HWND hWndParent, HMENU hMenu, HANDLE hInstance) {
	return CreateWindow(
		lpClassName,
		lpWindowName,
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
		x,
		y,
		nWindth,
		nHeight,
		hWndParent,
		hMenu,
		hInstance,
		NULL
	);
}



HFONT EzCreateFont(HDC hdc, TCHAR* szFaceName, int iDeciPtHeight,
    int iDeciPtWidth, int iAttributes, BOOL fLogRes)
{
    FLOAT      cxDpi, cyDpi;
    HFONT      hFont;
    LOGFONT    lf;
    POINT      pt;
    TEXTMETRIC tm;

    SaveDC(hdc);

    SetGraphicsMode(hdc, GM_ADVANCED);
    ModifyWorldTransform(hdc, NULL, MWT_IDENTITY);
    SetViewportOrgEx(hdc, 0, 0, NULL);
    SetWindowOrgEx(hdc, 0, 0, NULL);

    if (fLogRes)
    {
        cxDpi = (FLOAT)GetDeviceCaps(hdc, LOGPIXELSX);
        cyDpi = (FLOAT)GetDeviceCaps(hdc, LOGPIXELSY);
    }
    else
    {
        cxDpi = (FLOAT)(25.4 * GetDeviceCaps(hdc, HORZRES) /
            GetDeviceCaps(hdc, HORZSIZE));

        cyDpi = (FLOAT)(25.4 * GetDeviceCaps(hdc, VERTRES) /
            GetDeviceCaps(hdc, VERTSIZE));
    }

    pt.x = (int)(iDeciPtWidth * cxDpi / 72);
    pt.y = (int)(iDeciPtHeight * cyDpi / 72);

    DPtoLP(hdc, &pt, 1);

    lf.lfHeight = -(int)(fabs(pt.y) / 10.0 + 0.5);
    lf.lfWidth = 0;
    lf.lfEscapement = 0;
    lf.lfOrientation = 0;
    lf.lfWeight = iAttributes & EZ_ATTR_BOLD ? 400 : 0;
    lf.lfItalic = iAttributes & EZ_ATTR_ITALIC ? 1 : 0;
    lf.lfUnderline = iAttributes & EZ_ATTR_UNDERLINE ? 1 : 0;
    lf.lfStrikeOut = iAttributes & EZ_ATTR_STRIKEOUT ? 1 : 0;
    lf.lfCharSet = DEFAULT_CHARSET;
    lf.lfOutPrecision = 0;
    lf.lfClipPrecision = 0;
    lf.lfQuality = 0;
    lf.lfPitchAndFamily = 0;

    lstrcpy(lf.lfFaceName, szFaceName);

    hFont = CreateFontIndirect(&lf);

    if (iDeciPtWidth != 0)
    {
        hFont = (HFONT)SelectObject(hdc, hFont);

        GetTextMetrics(hdc, &tm);

        DeleteObject(SelectObject(hdc, hFont));

        lf.lfWidth = (int)(tm.tmAveCharWidth *
            fabs(pt.x) / fabs(pt.y) + 0.5);

        hFont = CreateFontIndirect(&lf);
    }

    RestoreDC(hdc, -1);
    return hFont;
}




void PaintRoutine(HWND hwnd, HDC hdc, int cxArea, int cyArea)
{
    static TCHAR szString[] = YUFFIE_MAIN_TITLE;
    HFONT        hFont;
    SIZE         size;

    hFont = EzCreateFont(hdc, TEXT("Times New Roman"), 300, 0, 0, TRUE);

    SelectObject(hdc, hFont);
    SetBkMode(hdc, TRANSPARENT);

    GetTextExtentPoint32(hdc, szString, lstrlen(szString), &size);

    BeginPath(hdc);
    TextOut(hdc, (cxArea - size.cx) / 2, (cyArea - size.cy) / 2,
        szString, lstrlen(szString));
    EndPath(hdc);

    SelectObject(hdc, CreateHatchBrush(HS_DIAGCROSS, RGB(255, 0, 0)));
    SetBkColor(hdc, RGB(0, 0, 255));
    SetBkMode(hdc, OPAQUE);

    StrokeAndFillPath(hdc);

    DeleteObject(SelectObject(hdc, GetStockObject(WHITE_BRUSH)));
    SelectObject(hdc, GetStockObject(SYSTEM_FONT));
    DeleteObject(hFont);
}





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
int CDECL messageBoxPrintf(TCHAR* szCaption, TCHAR* szFormat, ...)
{
    TCHAR szBuffer[1024];
    va_list pArgList;
    va_start(pArgList, szFormat);
    _vsntprintf_s(szBuffer, sizeof(szBuffer) / sizeof(TCHAR),1024, szFormat, pArgList);
    va_end(pArgList);
    return MessageBox(NULL, szBuffer, szCaption, 0);
}



BOOL CALLBACK CloseEnumProc(HWND hwnd, LPARAM lParam)
{
    if (GetWindow(hwnd, GW_OWNER))         // Check for icon title
        return TRUE;

    SendMessage(GetParent(hwnd), WM_MDIRESTORE, (WPARAM)hwnd, 0);

    if (!SendMessage(hwnd, WM_QUERYENDSESSION, 0, 0))
        return TRUE;

    SendMessage(GetParent(hwnd), WM_MDIDESTROY, (WPARAM)hwnd, 0);
    return TRUE;
}
