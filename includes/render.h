/* copyright Rayyan Shahid 2026 */

// rendering code backend


#ifndef RENDER_H
#define RENDER_H

// platform checks
#if defined(__linux__) || defined(__unix__)
	#define PLATFORM_LINUX 1
#elif defined(__WIN32__) || defined(__WIN64__)
	#define PLATFORM_WINDOWS 1
#else
	#error "Unsupported platform."
#endif

#if PLATFORM_LINUX
	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <X11/Xatom.h>
	#include <stdio.h>
	#include <stdint.h>
	#include <stdlib.h>
#elif PLATFORM_WINDOWS
	#include <Windows.h>
	#include <d3d9.h>
	#include <d3dx9mesh.h>
	#include <d3dx9xof.h>
	#include <dxfile.h>
	#include <DirectXMath.h>
	#pragma comment(lib, "d3d9.lib")
#endif

// setting up globals and structs, platform-dependent

#if PLATFORM_LINUX
typedef struct Renderer {
	Display *dpy;
	Window win;
	GC gc;

	Atom wm_protocols;
	Atom wm_delete_window;
	Atom wm_state;
	Atom max_horz;
	Atom max_vert;
	
	int width, height;
	int scr;
	int should_close;
	XImage *image;
	uint32_t* fb;
}; 
#elif PLATFORM_WINDOWS
typedef struct Renderer {
	HWND hwnd;
	int width, height;
	int should_close;

	/* d3d9 globals */

	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3dDevice;
	LPDIRECT3DVERTEXBUFFER9 vb;
	LPDIRECT3DINDEXBUFFER9  ib;
	D3DPRESENT_PARAMETERS d3dpp;

	char classname[32];

};
#endif

typedef struct Renderer Renderer; 

// separating X11 display function into own API - will wrap ifdefs later
Renderer* render_create(int width, int height, const char* title){
  Renderer* r = calloc(1, sizeof(Renderer));
	if(!r) return NULL;

	r->width        = width;
	r->height       = height;

	r->dpy = XOpenDisplay(NULL);
	if(!r->dpy){
		free(r);
		return NULL;
	 }

	r->scr = DefaultScreen(r->dpy);

	r->win = XCreateSimpleWindow(

		r->dpy,
		RootWindow(r->dpy, r->scr),
		0, 0,
		width, height,
		0,
		BlackPixel(r->dpy, r->scr),
		BlackPixel(r->dpy, r->scr)
	);

	XStoreName(r->dpy, r->win, title);

	XSelectInput(r->dpy, r->win, ExposureMask | KeyPressMask | StructureNotifyMask);

	r->gc = XCreateGC(r->dpy, r->win, 0, NULL);

	r->fb = malloc(width * height * sizeof(uint32_t));
	if(!r->fb){
		XCloseDisplay(r->dpy);
		free(r);
		return NULL;		
	}

	r->image = XCreateImage(r->dpy, DefaultVisual(r->dpy, r->scr),
																	DefaultDepth(r->dpy,  r->scr),
																	ZPixmap, 0, (char*)r->fb,
																	width, height, 32, 0);

	XMapWindow(r->dpy, r->win);

return r;

}

void render_poll_events(Renderer *r){
	#if PLATFORM_LINUX
	while(XPending(r->dpy)){
		XEvent e;
		XNextEvent(r->dpy, &e);
		switch(e.type){
			case Expose:
				break;
			case KeyPress:
				if(XLookupKeysym(&e.xkey, 0) == XK_Escape){
					r->should_close = 1;
				}
				break;
			case ClientMessage:
			 XClientMessageEvent* cme = (XClientMessageEvent*)&e;
			 Atom wm_protocols = XInternAtom(r->dpy, "WM_PROTOCOLS", False);
			 if(cme->message_type == wm_protocols &&
			   (Atom)cme->data.l[0] == r->wm_delete_window){
			 	 r->should_close = 1;
			   } 	
				break;
		  }
	#endif
	
 }
}

int render_should_close(Renderer *r){
	return r->should_close;
}

void render_present(Renderer *r){
	#if PLATFORM_LINUX
  XPutImage(r->dpy, r->win, r->gc, r->image, 0, 0, 0, 0, r->width, r->height);
  XFlush(r->dpy);
  #endif  	
}

void render_destroy(Renderer *r){
	if (!r) return;

	#if PLATFORM_LINUX
	if(r->image) XDestroyImage(r->image);
	if(r->fb) free(r->fb);
	if(r->gc) XFreeGC(r->dpy, r->gc);
	if(r->win) XDestroyWindow(r->dpy, r->win);
	if(r->dpy) XCloseDisplay(r->dpy);
	#endif

	free(r);
}

void render_clear(Renderer *r, uint32_t color){
	#if PLATFORM_LINUX
	for(int i = 0; i < r->width * r-> height; i++){
		r->fb[i] = color;
	}
	#endif
}

#endif


