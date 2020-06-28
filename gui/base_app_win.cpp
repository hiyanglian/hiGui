#include "base_app_win.h"
using namespace higui;
bool BaseAppWin::initialize(const std::string& title, size_t width, size_t height, Window::Style frame_style /* = Window::MULTIPLE */, FrameWindow::Options* popt /* = 0 */)
{
	FrameWindow::Options opt;
	if(popt)
	{
		opt = * popt;
	}
	else
	{
		opt.bOwnDraw = true;
		opt.bFullScreen = true;
		opt.nColorBits = 16;
		opt.nDepthBits = 16;
		opt.nStencilBits = 0;
	}
	FrameWindow::createInstance();
	sd::string wnd_style = "std_framewnd";
	if(opt.windowStyleName.length() > 0)
		wnd_style = opt.windowStyleName;
	try{
		FrameWindow::instance()->create(0, 0, (int)width, (int)height, title, &opt, wnd_style);
	}
	catch(std::exception& e)
	{
		//to do error process!
		return false;
	}
	//do extra initialization
	//做渲染
	return true;
}
int BaseAppWin::run()
{
	MSG msg;	//windows消息结构体
	BOOL done = FALSE; //用于指示是否完成，需要退出消息循环
	while(!done)
	{
		WaitMessage();//等待消息到来，如果没有消息，则线程挂起
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			/*message是消息的标识号，为了方便记忆，msg.message 在winUser中有定义WM_XXXX,WM_NULL为0，
			它是一个空消息
			*/
			if(msg.message == 0)
			{
				if(FrameWindow::instance()->isActive())
				{
					//做渲染,todo
				}
			}
			if(msg.message == WM_QUIT)
			{
				done = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			//做渲染,todo
		}
		else
		{
			//如果没有消息,做其他相关处理
		}
	}
	FrameWindow::instance()->free();
	return msg.wParam;
}