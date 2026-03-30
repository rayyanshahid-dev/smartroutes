#ifndef IO_H
#define IO_H

// file I/O header, deals with parsing and handling OSM data from CSV
// features:
// 	- buffered reading
// 	- custom interface over native APIs for ease-of-use
// 	- multiple access patterns (sequential reading for streaming, random access for seeking, memory mapping for large files)
// 	

// platform checks

#if defined(__linux__) || defined(__unix__)
	#define PLATFORM_LINUX 1
#elif defined(__WIN32__) || defined(__WIN64__)
	#define PLATFORM_WINDOWS 1
#else
	#error "Unsupported platform."
#endif

#if PLATFORM_LINUX
  #include <stdio.h>
	#include <sys/uio.h>
	#include <sys/stat.h>
  #include <stdint.h>
#elif PLATFORM_WINDOWS
	#include <Windows.h>
#endif

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

typedef struct vehicle {
	uint32_t id;
	int capacity;
	int distance_limit;
} vehicle; 

#endif
