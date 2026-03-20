# SmartRoutes

SmartRoutes is a zero-dependency desktop tool for optimizing municipal resources in shrinking Japanese cities. As populations decline and tax bases contract, cities must do more with less efficient
garbage collection routes, optimally placed senior centers, and data-driven infrastructure decisions. 

SmartRoutes is built in C with cross-platform, native windowing code (X11/D3D). This means it can run on older hardware still common in many municipal offices in Japan. 

## Features

- Graph visualization: OSM data is streamed in and loaded to render city road networks
- Facility locations: Find optimal sites for senior centers, health clinics, or schools to maximize population coverage within walking distance
- Vehicle routing: Plan garbage collection or snow plow routes efficiently with regard to vehicle capacity
- interactive: Parameters can be adjusted and changed in real time - such as facility or vehicle numbers

## Algorithms

- Djikstra's shortest path algorithm with binary heap
- Facility location: greedy addition for maximal coverage
- Vehicle routing: Capacitated VRP with 2-opt local search
- All-pairs precomputation for small graphs, on-demand for large ones

## Rational for using C

C is performant, portable, and transparent. This encourages lightweight, cross-platform binaries with easily auditable code, with the goal to be simple, efficient, and fast - ease of use
and sensible implementations of algorithms for low overhead, memory usage, and high performance on lower end machines. 

## TL;DR

SmartRoutes is a simple 2D application rendered in X11/D3D9 that displays a 2D bird's-eye view of a geographic area taken from OSM data. This data is transformed into CSV information that's then piped in and splatted onto the screen using a simple display implementation (software rendering stuff with X11, XCreateSimpleWindow, XPresentPixmap etc, hardware accelerated rendering with D3D9). The map is then populated with nodes taken from real data (the CSV information) that represents various things like facilities, health centers, residential blocks and roads. The backend is structured like a simple graph with nodes and edges corresponding to facilities and roads respectively. The graph is then traversed by a vehicle entity which captures the state of the traversal based on its relationship to the nodes and edges - and is used to visually solve (naively, metaheuristically) the CVRP based on example scenarios - like snow plow availability or garbage truck routes. 

## Status

Active development. 
