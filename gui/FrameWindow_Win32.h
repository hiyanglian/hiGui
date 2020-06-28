#ifndef __FRAME_WINDOW_WIN32_H__
#define __FRAME_WINDOW_WIN32_H__
#include "FrameWindow.h"
#include <Windows.h>
namespace higui{
class FrameWindow_Win32: public FrameWindow{
public:
	LRESULT wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	HDC m_hDC;
	HCD m_hMemDC;
	HGLRC m_hRC;
protected:
	FrameWindow_Win32();
	virtual void createGLWindow(int left, int top, int width, int height, const std::string& title, const Options& opt);
	virtual void freeGLWindow();
};
};
#endif//__FRAME_WINDOW_WIN32_H__