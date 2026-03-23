/* copyright Rayyan Shahid 2026 */

// rendering code x11 backend

#ifndef RENDER_H
#define RENDER_H

#if defined(__linux__) || defined(__unix__)
	#define RENDER_PLATFORM_LINUX 1
#elif defined(__WIN32__) || defined(__WIN64__)
	#define RENDER_PLATFORM_WINDOWS 1
#else
	#error "Unsupported platform."
#endif

#if RENDER_PLATFORM_LINUX
	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <stdio.h>
	#include <stdint.h>
	#include <stdlib.h>
#elif RENDER_PLATFORM_WINDOWS
	#include <Windows.h>
	#include <d3d9.h>
	#include <d3dx9mesh.h>
	#include <d3dx9xof.h>
	#include <dxfile.h>
	#include <DirectXMath.h>
	#pragma comment(lib, "d3d9.lib")
#endif

int w = 800;
int h = 600;

void display() {
	Display *dpy = XOpenDisplay(NULL);
    int scr = DefaultScreen(dpy);
    Window wnd = XCreateSimpleWindow(

                                     dpy,
                                     RootWindow(dpy, scr),
                                     0,
                                     0,
                                     w,
                                     h,
                                     0,
                                     BlackPixel(dpy, scr),
                                     WhitePixel(dpy, scr));

    XStoreName(dpy, wnd, "SmartRoutes");
    XSelectInput(dpy, wnd, ExposureMask | KeyPressMask);
    XMapWindow(dpy, wnd);
    	for (;;) {
      	XEvent e;
       	XNextEvent(dpy, &e);
    }
    return XCloseDisplay(dpy);
  }

  #endif
