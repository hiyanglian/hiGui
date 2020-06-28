#include "FrameWindow_Win32.h"
#include <WinGDI.h>
#include <exception>
#include <string.h>
#include <gl/GL.h>
#include <gl/glew.h>
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
using namespace higui;
void FrameWindow_Win32::createGLWindow(int left, int top, int width, int height, const std::string& title, const Options& opt)
{
	WNDCLASS wc;
	DWORD dwExStyle;
	DWORD dwStyle;
	RECT WindowRect;
	WindowRect.left = (long)0;
	WindowRect.right = (long)width;
	WindowRect.top = (long)0;
	WindowRect.bottom = (long)height;

	m_options = opt;

	m_hInstance = GetModuleHandle(NULL);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "higuiFrameWindow";

	if(!RegisterClass(&wc))
	{
		throw std::exception("failed to register window class");
	}
	try{
		if(!(m_hWnd = CreateWindowEx(
			dwExStyle,
			"higuiFrameWindow",
			title.c_str(),
			dwStyle|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
			0, 0,
			WindowRect.right - WindowRect.left,
			WindowRect.bottom - WindowRect.top,
			NULL, NULL, m_hInstance, NULL
			))){
				std::rethrow_exception("create window failed.");
		}
		//create gl window
		PIXELFORMATDESCRIPTOR pdf;
		memset(&pdf, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pdf.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pdf.nVersion = 1;
		pdf.dwFlags = PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
		pdf.iPixelType = PFD_TYPE_RGBA;
		pdf.cColorBits = m_options.nColorBits;
		pdf.cDepthBits = m_options.nDepthBits;
		pdf.cStencilBits = m_options.nStencilBits;
		pdf.iLayerType = PFD_MAIN_PLANE;
		if(!(m_hDC = GetDC(m_hWnd)))
		{
			throw std::exception("can not create DC");
		}
		int pixelFormat;

		if(!(pixelFormat = ChoosePixelFormat(m_hDC, &pdf)))
		{
			throw std::exception("can not find s sutiable pixelformat.");
		}
		if(!SetPixelFormat(m_hDC, pixelFormat, &pdf))
		{
			throw std::exception("can not set the pixel format");
		}
		if(!(m_hRC = wglCreateContext(m_hDC)))
		{
			throw std::exception("can not create a gl rendering context");
		}
		if(!(wglMakeCurrent(m_hDC, m_hRC)))
		{
			throw std::exception("can not active the gl rendering context");
		}
		GLenum err = glewInit();
		if(err != GLEW_OK)
		{
			throw std::exception((char*)glewGetErrorString(err));
		}
		bool bSimpleOk = true;
		std::string err_str = "";
		if(!GL_VERSION_2_0)
			err_str = "WARINING:OPENGL 2.0 not support. Try updating the graphic card drivers.";
		if(!glewIsSupported("GL_EXT_framebuffer_ojbect"))
		{
			err_str = "frame buffer object is not supported.";
		}
		if(err_str.length() > 0)
		{
			//无法支持 gl2.0，进行善后工作
		}
		if(m_options.bOwnDraw)
		{
			SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
			HDC dc = GetDC(NULL);
			m_hMemDC = CreateCompatibleDC(0);
			if(!m_hMemDC)
			{
				//
			}
			std::vector<unsigned char> data(width * height * 4, 0);
			HBITMAP hBMP = CreateBitmap(width, height, 1, 32, &data[0]);
			if(!hBMP)
			{
				//
			}
			HBITMAP bmpold = (HBITMAP)SelectObject(m_hMemDC, hBMP);
			SIZE sz = {width, height};
			POINT ptSrc = {0, 0};
			BLENDFUNCTION blend = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
			if(!UpdateLayeredWindow(m_hWnd, dc, 0, &sz, m_hMemDC, &ptSrc, 0, &blend, ULW_ALPHA))
			{

			}
			SelectObject(m_hMemDC, bmpold);
			DeleteObject(hBMP);
			//创建一个离屏渲染表面,todo
		}
		ShowWindow(m_hWnd, SW_SHOW);
		SetForegroundWindow(m_hWnd);
		SetFocus(m_hWnd);
	}
	catch(std::exception e)
	{
		//todo 善后工作
		freeGLWindow();
	}
}