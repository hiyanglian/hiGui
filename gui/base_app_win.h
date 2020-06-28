#ifndef __BASE_APP_WIN_H__
#define __BASE_APP_WIN_H__
#include "frame_window.h"
namespace higui{
class BaseAppWin{
private:
	static BaseAppWin* m_pInstance;
	BaseAppWin(const BaseAppWin&);
public:
	virtual bool initialize(const std::string& title, size_t width, 
		size_t height, Window::Style frame_style = Window::MULTIPLE, 
		FrameWindow::Options* opt = 0);
	virtual int run();
	static BaseAppWin* instance(){
		if(!m_pInstance)
		{
			m_pInstance = new BaseAppWin();
		}
		return m_pInstance;
	}
protected:
	BaseAppWin();
	virtual ~BaseAppWin();
};
};
#endif //__BASE_APP_WIN_H__