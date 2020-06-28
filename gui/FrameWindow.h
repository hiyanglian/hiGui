#ifndef __FRAME_WINDOW_H__
#define __FRAME_WINDOW_H__
namespace higui{
class FrameWindow: public Window{
public:
	struct Options{
		bool bOwnDraw;
		bool bFullScreen;
		int nColorBits;
		int nDepthBits;
		int nStencilBits;
		std::string windowStyleName;
	};
	virtual void create(int left, int top, int width, int height, const std::string &title, const Options *opt = 0,
		const std::string &style_name = "std_framewnd");
	static FrameWindow* FrameWindow::createInstance();
	static FrameWindow* instance(){ return m_pInst; }

	virtual void free();
	Options getOptions()const{return m_options;}
	virtual bool onMouseDown(int x, int y, int button);
	virtual bool onMouseMove(int x, int y, int prevx, int prevy);
	virtual bool onMouseUp(int x, int y, int button);
	virtual void onKeyDown(int key);
	virtual void onKeyUp(int key);
protected:
	FrameWindow();
	virtual void createGLWindow(int left, int top, int width, int height, const std::string& title, const Options& opt) = 0;
	virtual void freeGLWindow() = 0;
	Options m_options;
	static FrameWindow* m_pInst;
};
};
#endif //__FRAME_WINDOW_H__
