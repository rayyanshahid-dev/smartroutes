// smartroutes - copyright Rayyan Shahid 2026 

#include <X11/Xlib.h>
#include <stdio.h>
#include "../includes/io.h"
#include "../includes/render.h"
#include "../includes/io.h"


#define RENDER_IMPLEMENTATION

int main(void){

  Renderer *r = render_create(800, 600, "SmartRoutes");
  if(!r){
    fprintf(stderr, "Failed to create renderer!\n");
    return 1;
  }

  while(!render_should_close(r)){
    render_poll_events(r);
    render_clear(r, 0x000000);
    render_present(r);
  }

  render_destroy(r);
  return 0;
}
