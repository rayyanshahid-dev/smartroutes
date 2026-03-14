// smartroutes - copyright Rayyan Shahid 2026 

#include <X11/Xlib.h>
#include <stdio.h>

int w = 800;
int h = 600;

void display() {
	Display *dpy = XOpenDisplay(NULL);
    int scr = DefaultScreen(dpy);
    Window wnd = XCreateSimpleWindow(dpy, RootWindow(dpy, scr), 0, 0, w, h, 0, BlackPixel(dpy, scr), WhitePixel(dpy, scr));
    XStoreName(dpy, wnd, "SmartRoutes");
    XSelectInput(dpy, wnd, ExposureMask | KeyPressMask);
    XMapWindow(dpy, wnd);
    	for (;;) {
      	XEvent e;
       	XNextEvent(dpy, &e);
    }
    return XCloseDisplay(dpy);
  }

int main(void){
	display();
	return 0;
}
