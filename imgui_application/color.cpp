#include <iostream>
#include <string>
#include <windows.h>

#include "color.h"
#include "menu.h"
#include "imgui/imgui.h"

extern int color::r = NULL;
extern int color::g = NULL;
extern int color::b = NULL;

void color::copy_color()
{
	const std::string rgb = std::to_string(color::r) + "," + std::to_string(color::g) + "," + std::to_string(color::b);
	menu::saved_rgb.push_back(rgb);

	OpenClipboard(NULL);
	EmptyClipboard();
	HGLOBAL HG = GlobalAlloc(GMEM_MOVEABLE, rgb.size() + 1);
	if (!HG)
	{
		CloseClipboard();
	}
	memcpy(GlobalLock(HG), rgb.c_str(), rgb.size() + 1);
	GlobalUnlock(HG);
	SetClipboardData(CF_TEXT, HG);
	CloseClipboard();
	GlobalFree(HG);
}

void color::thread()
{
	while (1)
	{
		if (GetAsyncKeyState(VK_RBUTTON) & 1)
		{
			color::copy_color();
		}
			
		POINT cursor_pos;
		HDC hDC = GetDC(NULL);

		GetCursorPos(&cursor_pos);
		COLORREF color = GetPixel(hDC, cursor_pos.x, cursor_pos.y);
		ReleaseDC(GetDesktopWindow(), hDC);

		color::r = GetRValue(color);
		color::g = GetGValue(color);
		color::b = GetBValue(color);

		Sleep(1);
	}
}