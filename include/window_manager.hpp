extern "C" {
	#include <X11/Xlib.h>
}
#include <memory>

class WindowManager{
	public:

	//window manager instance
	static::std::unique_ptr<WindowManager> Create();
	//disconnects from X server
	~WindowManager();
	//enters main event loop
	void Run();
	
	private:
	
	//invoked by create
	WindowManager(Display* display);

	//Handle to Xlib Display struct
	Display* display_;

	//handle to root window
	const Window root_;

	//Xlib Error handler;
	static int OnXError(Display* disp, XErrorEvent* e);

	//checking if another WM running
	static int OnWMDetected(Display* disp, XErrorEvent* e);
	static bool wm_detected_;

	//CreateNotify
	void OnCreateNotify(const XCreateWindowEvent& e);
	
};

