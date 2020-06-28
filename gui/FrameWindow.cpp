#include "FrameWindow.h"
#include <iostream>
#include <exception>
using namespace higui;
void FrameWindow::free()
{
	freeGLWindow();
}
void FrameWindow::create(int left, int top, int width, int height, const std::string &title, 
	const Options *opt /* = 0 */, const std::string &style_name /* = "std_framewnd" */)
{
	if(opt){
		m_options = *opt;
	}
	else
	{
		m_options.bOwnDraw = true;
		m_options.bFullScreen = false;
		m_options.nColorBits = 16;
		m_options.nDepthBits = 16;
		m_options.nStencilBits = 0;
	}
	try
	{
		createGLWindow(left, top, width, height, title, m_options);
	}
	catch (std::exception e)
	{
		
	}
	//todo window create
}