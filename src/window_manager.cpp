#include "../include/window_manager.hpp"
#include <glog/logging.h>

using ::std::unique_ptr;

unique_ptr<WindowManager> WindowManager::Create(){
	//open Xdisplay
	Display * display = XOpenDisplay(nullptr);
	if(display == nullptr){
		LOG(ERROR) << "Failed to open X display"<<XDisplayName(nullptr);
		return nullptr;
	}

	//construct windowmanager instance
	return unique_ptr<WindowManager>(new WindowManager(display));
}

WindowManager::WindowManager(Display* disp) 
	: display_(CHECK_NOTNULL(display)), root_(DefaultRootWindow(display_)) {
}

WindowManager:: ~WindowManager(){
	XCloseDisplay(display_);
}

void WindowManager::Run(){
	//Initialization
	wm_detected_ = false;
	XSetErrorHandler(&WindowManager::OnWMDetected);
	XSelectInput(
			display_,
			root_,
			SubstructureRedirectMask | SubstructureNotifyMask
			);
	XSync(display_,false);

	if(wm_detected_){
		LOG(ERROR) << "Detected another window manager running on display" << XDisplayString(display_);
		return ;
	}

	XSetErrorHandler(&WindowManager::OnXError);

	//Event Loop
	for(;;){

		XEvent e;
		XNextEvent(display_, &e);
		LOG(INFO) << "Received Event:" <<ToString(e);

		switch(e.type){
			case CreateNotify:
				OnCreateNotify(e.xcreatewindow);
				break;

			case DestroyNotify:
				OnDestroyNotify(e.xdestroywindow);
				break;

			case ReparentNotify:
				OnReparentNotify(e.xreparent);
				break;

			case ConfigureRequest:
				OnConfigureRequest(e.xcreatewindow);
				break;


			default:
				LOG(WARNING) << "Ignored Event";
		}
	}
}


int WindowManager::OnWMDetected(Display* disp, XErrorEvent* e){
	//Since this handler is only expected to check for existing window managers
	//we have only checked for bad access
	CHECK_EQ(static_cast<int>(e->error_code), BadAccess); 
	wm_detected_ = true;
	return 0;
}

int WindowManager::OnXError(Display* disp, XErrorEvent* e){
}

void WindowManager::OnCreateNotify(const XCreateWindowEvent& e){
}