#ifndef GRAPHCONTROLLER_H
#define GRAPHCONTROLLER_H

#include "Vertex.h"
#include "Edge.h"
#include "MutablePriorityQueue.h"

#include <vector>
#include <cinttypes>
#include <unordered_map>
#include <set>
#include <limits>
#include <cmath>
#include <utility>
#include <thread>
#include <queue>

/**
 * @struct Cluster
 * @brief Represents a cluster of nodes in the graph.
 */
struct Cluster {
    std::vector<uint16_t> nodes; /**< Nodes in the cluster. */
    uint16_t clusterId; /**< Identifier for the cluster. */
    Coordinate center; /**< Center coordinate of the cluster. */
    std::vector<uint16_t> tour; /**< Tour of the cluster nodes. */
    double tourCost = 0; /**< Cost of the tour. */

    bool rootCluster = false; /**< Indicates if this is the root cluster. */
    bool processed = false; /**< Indicates if the cluster has been processed. */
};

/**
 * @class GraphController
 * @brief Manages graph operations and algorithms.
 */
class GraphController {
private:
    std::unordered_map<uint16_t, Vertex*> graph; /**< The graph represented as an adjacency list. */
    std::vector<std::vector<double>> graphAdj; /**< Adjacency matrix for the graph. */

    double min_distance = std::numeric_limits<double>::infinity(); /**< Minimum distance found for Hamiltonian cycle. */
    std::vector<uint16_t> minPath; /**< Path representing the minimum Hamiltonian cycle. */

    // AUX functions for backtrack

    /**
     * @brief Recursive backtracking function to find the minimum Hamiltonian cycle.
     * @param curr_vertex The current vertex in the backtracking.
     * @param distance The current distance traveled.
     * @param visited Set of visited nodes.
     * @param path Current path being explored.
     */
    void recursiveBacktracking(Vertex* curr_vertex, double distance = 0, const std::set<uint16_t>& visited = {}, std::vector<uint16_t> path = {});

    /**
     * @brief Checks if the current path can be pruned.
     * @param curr_idx Current vertex index.
     * @param pathSum The current path sum.
     * @param visited Set of visited nodes.
     * @return True if the path can be pruned, false otherwise.
     */
    bool Bound(uint16_t curr_idx, double pathSum, const std::set<uint16_t>& visited) const;

    /**
     * @brief Checks if all vertices have been visited.
     * @param visited Set of visited nodes.
     * @return True if all vertices are visited, false otherwise.
     */
    bool allVerticesVisited(const std::set<uint16_t>& visited) const;

    // AUX functions for 2-approximation

    /**
     * @brief Computes the Minimum Spanning Tree (MST) using Prim's algorithm.
     * @param root The root vertex for the MST.
     * @param graph_ The graph to compute the MST on.
     */
    void getMSTPrim(int root, std::unordered_map<uint16_t, Vertex*>& graph_);

    /**
     * @brief Performs a pre-order depth-first search (DFS) on the graph.
     * @param node The starting node for the DFS.
     * @param result Vector to store the DFS result.
     * @param graph_ The graph to perform the DFS on.
     */
    void preorderDFS(Vertex* node, std::vector<Vertex*>& result, const std::unordered_map<uint16_t, Vertex*>& graph_);

    /**
     * @brief Gets the pre-order walk of the graph.
     * @param graph_ The graph to get the pre-order walk from.
     * @return Vector of vertices in pre-order.
     */
    std::vector<Vertex*> preOrderWalk(std::unordered_map<uint16_t, Vertex*>& graph_);

    /**
     * @brief Gets the cost of a given walk.
     * @param walk The walk to compute the cost for.
     * @param graph The graph to compute the cost on.
     * @return The cost of the walk.
     */
    double getCostFromWalk(std::vector<Vertex*> walk, std::unordered_map<uint16_t, Vertex*>& graph);

    // AUX functions for nearest neighbor

    /**
     * @brief Performs k-means clustering on the graph.
     * @return Vector of clusters.
     */
    std::vector<Cluster> kmeansClustering();

    /**
     * @brief Computes the full nearest neighbor tour.
     * @return Pair of tour cost and tour path.
     */
    std::pair<double, std::vector<uint16_t>> fullNN();

    /**
     * @brief Computes the nearest neighbor tour for a given cluster.
     * @param cluster The cluster to compute the tour for.
     */
    void tourNNFromCluster(Cluster& cluster);

    /**
     * @brief Computes the nearest neighbor tour between clusters.
     * @param root The root cluster.
     * @param clusters Vector of clusters.
     * @return Pair of inter-cluster tour cost and tour path.
     */
    std::pair<double, std::vector<uint16_t>> tourNNInterClusters(Cluster& root, std::vector<Cluster>& clusters);

    // Calculations

    /**
     * @brief Converts a coordinate to radians.
     * @param coord The coordinate to convert.
     * @return The coordinate in radians.
     */
    double convertToRadians(double coord);

    /**
     * @brief Computes the Haversine distance between two coordinates.
     * @param coo1 The first coordinate.
     * @param coo2 The second coordinate.
     * @return The Haversine distance between the coordinates.
     */
    double haversine(Coordinate coo1, Coordinate coo2);

    /**
     * @brief Calculates the data range for clustering.
     * @return The calculated data range.
     */
    double calculateDataRange();

    /**
     * @brief Checks if the graph is connected.
     * @return True if the graph is connected, false otherwise.
     */
    bool isConnectedGraph();

    /**
     * @brief Finds the TSP solution for a disconnected graph starting from a given vertex.
     * @param startVertex The starting vertex.
     * @return Pair of tour cost and tour path.
     */
    std::pair<double, std::vector<uint16_t>> findTSPForDisconnectedGraph(Vertex* startVertex);

public:
    /**
     * @brief Constructs a GraphController with a given graph and adjacency matrix.
     * @param graph The graph represented as an adjacency list.
     * @param graphAdj The adjacency matrix for the graph.
     */
    GraphController(std::unordered_map<uint16_t, Vertex*> graph, std::vector<std::vector<double>> graphAdj_);

    /**
     * @brief Finds the minimum Hamiltonian cycle in the graph.
     * @return Pair of cycle cost and cycle path.
     */
    std::pair<double, std::vector<uint16_t>> minHamiltonianCicle();

    /**
     * @brief Solves the TSP using the triangle inequality approximation.
     * @return Pair of tour cost and tour path.
     */
    std::pair<double, std::vector<uint16_t>> triangleInequalityApp();

    /**
     * @brief Solves the TSP using a cluster heuristic.
     * @return Pair of tour cost and tour path.
     */
    std::pair<double, std::vector<uint16_t>> clusterHeuristic();

    /**
     * @brief Solves the TSP for a disconnected graph starting from a given node.
     * @param startNode The starting node.
     * @return Pair of tour cost and tour path.
     */
    std::pair<double, std::vector<uint16_t>> solveTSPForDisconnectedGraph(uint16_t startNode);
};

#endif // GRAPHCONTROLLER_H
