/* Graph algorithms */

#include <stdint.h>

#ifndef GRAPH_H
#define GRAPH_H

// core structures

typedef struct coordinate {
	double lat;
	double lon;
} coordinate;

typedef struct edge {
	int target_node;
	double weight;
	int from, to;
	uint64_t osm_id;
	int oneway;
	double length_m;
	double speed_km;
} edge; 

typedef struct node {
	int id;
	coordinate pos;
	double distance;
	int visited;
	struct edge *edges;
	int edge_count;
	double polar_angle;
} node;

typedef struct graph {
	node *nodes;
	int node_count;
	int node_cap;
} graph; 

#endif
