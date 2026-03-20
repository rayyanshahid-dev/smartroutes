/* algorithms core */

// copyright Rayyan Shahid 2026

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "../includes/graph.h"

int algo_sweep(){
  node node_array[16]; 
  int length = sizeof(node_array) / sizeof(node_array[0]);
  int i;
  double theta;
  for(i=0; i<length; i++){
    node *n = &node_array[i];
    theta = atan2(n->pos.lat, n->pos.lon);  
    n->polar_angle = theta;
  }
 return 0;
}

