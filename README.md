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

## Status

Active development. 
