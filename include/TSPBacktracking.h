#pragma once
#include <vector>
#include <limits>

/**
 * @class TSPBacktracking
 * @brief Solves the Traveling Salesman Problem (TSP) using a backtracking approach.
 */
class TSPBacktracking {
public:
    /**
     * @brief Finds the shortest tour in the given graph.
     * @param graph A 2D vector representing the adjacency matrix of the graph.
     * @return The cost of the shortest tour.
     */
    double findShortestTour(const std::vector<std::vector<double>>& graph);

private:
    /**
     * @brief Helper function for backtracking to find the shortest tour.
     * @param path The current path being explored.
     * @param visited A vector indicating which nodes have been visited.
     * @param minCost The minimum cost found so far.
     * @param currentCost The current cost of the path.
     * @param level The current level of the search tree.
     * @param graph The adjacency matrix of the graph.
     */
    void backtrack(std::vector<int>& path, std::vector<bool>& visited, double& minCost, double currentCost, int level, const std::vector<std::vector<double>>& graph);
};
