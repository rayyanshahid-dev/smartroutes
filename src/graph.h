/* Graph algorithms */

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
} edge; 

typedef struct node {
	int id;
	coordinate pos;
	double distance;
	int visited;
	struct edge *edges;
	int edge_count;
} node;

typedef struct graph {
	node *nodes;
	int node_count;
	int node_cap;
} graph; 

#endif
