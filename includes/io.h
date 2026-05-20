#ifndef IO_H
#define IO_H

// file I/O header, deals with parsing and handling OSM data from CSV
// features:
// 	- buffered reading
// 	- custom interface over native APIs for ease-of-use
// 	- multiple access patterns (sequential reading for streaming, random access for seeking, memory mapping for large files)

   #include <stdint.h>
   #include <stddef.h>
   #include <ctype.h>
	
// platform checks

#if defined(__linux__) || defined(__unix__)
	#define PLATFORM_LINUX 1
#elif defined(__WIN32__) || defined(__WIN64__)
	#define PLATFORM_WINDOWS 1
	#define WIN32_LEAN_AND_MEAN
#else
	#error "Unsupported platform."
#endif

#if PLATFORM_LINUX
	#include <stdio.h>
	#include <sys/uio.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>
#elif PLATFORM_WINDOWS
	#include <Windows.h>
#endif

#define READER_DEFAULT_BUFFER_SIZE (64 * 1024) // 64kb, should be enough for this test project (~4mb)


// ---------------------
// core graph structures 
// ---------------------

typedef struct coordinate {
	double lat;
	double lon;
} coordinate;

typedef struct edge {
	uint64_t osm_id;
	double speed_km;
	double length_m;
	double weight;
	int target_node;
	int oneway;
	int highway_type;
} edge; 

typedef struct node {
	int id;
	int edge_count;
	double distance;
	double polar_angle;
	double demand;
	edge* edges;
	coordinate pos;
} node;

typedef struct graph {
	int node_count;
	int node_cap;
	node *nodes;
	edge* edges;
} graph; 

typedef struct vehicle {
	uint32_t id;
	int capacity;
	int distance_limit;
} vehicle;

typedef struct node_map node_map_t; 

// --------------------------------------------
// Misc data structures and function prototypes
// --------------------------------------------

typedef enum {
	HIGHWAY_MOTORWAY,
	HIGHWAY_PRIMARY,
	HIGHWAY_SECONDARY,
	HIGHWAY_RESIDENTIAL,
	HIGHWAY_UNCLASSIFIED,
} highway_t;

typedef struct {
	int(*on_node)(uint64_t id, double lat, double lon, void* ctx);
	int(*on_way_start)(uint64_t id, void* ctx);
	int(*on_way_node)(uint64_t node_ref, void* ctx);
	int(*on__way_tag)(const char* tag, const char* val, void* ctx);
	int(*on_way_end)(void* ctx);
} sm_callback_t; 
 	
graph* graph_create(void);
void   graph_free(graph* g);
int    graph_add_node(graph* g, double lat, double lon);
int    graph_add_edge(graph* g, int from, int to, double length_m, double speed_km, int highway_type, int oneway);

node_map_t* node_map_create(void);
void node_map_destroy(node_map_t* map);

#endif
