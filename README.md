# DA-Project_2

# Routing Algorithm for Ocean Shipping and Urban Deliveries

## Introduction

Developed for the Design of Algorithms course (Spring 2024) at the University of Porto, this project focuses on analyzing and solving the Travelling Salesperson Problem (TSP) in the context of ocean shipping and urban deliveries. It utilizes various heuristic approaches to efficiently handle complex routing problems that are otherwise intractable due to their size and constraints.

**Grade:** 17.7/20

## Team Members

- Rodrigo Ferreira Alves - up202207478
- Gonçalo de Abreu Matias - up202108703
- David Tavares Simões - up202210329

## Features

- Implementation of a basic exhaustive TSP approach for small graphs.
- Development of heuristic algorithms, including a triangular approximation approach for larger datasets.
- Data parsing and processing from provided CSV files.
- User-friendly menu interface for selecting and running different algorithmic approaches.
- Visual and analytical presentation of algorithmic performance and efficiency.

## Algorithmic Approach

The project uses a combination of backtracking for small graphs and heuristic methods for larger problems. A particular focus is on the triangular approximation heuristic, which provides a guaranteed approximation bound for certain classes of graphs.

## Documentation

The project's documentation is generated using Doxygen and is available under the `doxygen` directory. It includes detailed descriptions of all implemented functions and algorithms, along with their time complexity analysis.

## Usage

### User Interface

The application provides a user-friendly interface with the following options:
1. Load Graph
2. Execute TSP Backtracking
3. Execute Triangular Approximation
4. Execute Cluster Approximation
5. Execute TSP for Disconnected Graph
6. Exit

### Loading Graphs

Users can load different types of graphs:
- Toy Graphs
- Real World Graphs
- Extra Fully Connected Graphs

### Running Algorithms

After loading the graphs, users can run the following algorithms:
- **Backtracking TSP**: Finds the optimal solution for small graphs.
- **Triangular Approximation**: Provides a 2-approximation solution for the TSP.
- **Cluster Approximation**: Solves the TSP using clustering heuristics.
- **TSP for Disconnected Graphs**: Handles real-world graphs that are not fully connected.

## File Structure

- `Edge.h` / `Edge.cpp`: Defines the `Edge` class representing graph edges.
- `GraphController.h` / `GraphController.cpp`: Manages graph operations and algorithms.
- `GraphLoader.h` / `GraphLoader.cpp`: Handles loading and parsing of graph data from CSV files.
- `MutablePriorityQueue.h`: Implements a mutable priority queue used in prim's algorithm.
- `UserInterface.h` / `UserInterface.cpp`: Provides the user interface for the application.
- `Vertex.h` / `Vertex.cpp`: Defines the `Vertex` class representing graph vertices.

## Conclusion

This project provides a comprehensive solution to the TSP in the context of ocean shipping and urban deliveries, demonstrating the applicability of both exact and heuristic approaches to solve complex routing problems efficiently.

## Acknowledgements

This project was developed under the guidance of the DA 2024 Instructors Team at the University of Porto.

## References

- Project Description: [Programming Project II Description](file-Abn8dhBzZmZY0kTOZ36OgEvB)
- Haversine Formula: [Wikipedia](https://en.wikipedia.org/wiki/Haversine_formula)
- GitHub C++ Implementation: [haversine](https://github.com/AhiyaHiya/haversine)
- scikit-mobility Python Implementation: [gislib.py](https://github.com/scikit-mobility/scikit-mobility/blob/master/skmob/utils/gislib.py)
