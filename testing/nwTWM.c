#include <X11/Xlib.h>
#include <stdlib.h> 
#include <stdio.h>
#include <cstring>
#include "config.c"
#include "helper.c"

int main(void){
    Display * dpy;
    XWindowAttributes attr;
    XEvent ev;

    if(!(dpy = XOpenDisplay(0x0))) return 1;
	
	int size = sizeof(keys)/sizeof(keys[0]);
	for(int i=0;i<size;i+=2){
		XGrabKey(dpy, XKeysymToKeycode(dpy, XStringToKeysym(keys[i])), Mod1Mask,
            DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);
	}
	for(;;){
    	XNextEvent(dpy, &ev);
		if(ev.type == KeyPress){
			for(int i=0;i<size;i+=2){
				if(ev.xkey.keycode == XKeysymToKeycode(dpy, XStringToKeysym(keys[i]))){
					char * c[] = split(keys[i+1]);
					if(strcmp(c[0],spawn)){

					}
				}

			}

		}
		
	}

}
