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
	//����Ⱦ
	return true;
}
int BaseAppWin::run()
{
	MSG msg;	//windows��Ϣ�ṹ��
	BOOL done = FALSE; //����ָʾ�Ƿ���ɣ���Ҫ�˳���Ϣѭ��
	while(!done)
	{
		WaitMessage();//�ȴ���Ϣ���������û����Ϣ�����̹߳���
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			/*message����Ϣ�ı�ʶ�ţ�Ϊ�˷�����䣬msg.message ��winUser���ж���WM_XXXX,WM_NULLΪ0��
			����һ������Ϣ
			*/
			if(msg.message == 0)
			{
				if(FrameWindow::instance()->isActive())
				{
					//����Ⱦ,todo
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
			//����Ⱦ,todo
		}
		else
		{
			//���û����Ϣ,��������ش���
		}
	}
	FrameWindow::instance()->free();
	return msg.wParam;
}