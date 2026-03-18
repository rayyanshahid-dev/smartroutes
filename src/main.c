// smartroutes - copyright Rayyan Shahid 2026 

#include <X11/Xlib.h>
#include <stdio.h>

#include "../includes/graph.h"
#include "../includes/render.h"


#define RENDER_IMPLEMENTATION

int main(void){
	display();
	algo_sweep();
	return 0;
}
