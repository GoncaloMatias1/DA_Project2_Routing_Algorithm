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

struct Cluster{
    std::vector<uint16_t> nodes;
    uint16_t clusterId;
    Coordinate center;
    std::vector<uint16_t> tour;
    double tourCost = 0;

    bool rootCluster = false;
    bool processed = false;
};

class GraphController{
private:
    std::unordered_map<uint16_t, Vertex*> graph;
    std::vector<std::vector<double>> graphAdj;

    double min_distance = std::numeric_limits<double>::infinity();
    std::vector<uint16_t> minPath;

    // AUX functions for backtrack
    void recursiveBacktracking(Vertex* curr_vertex, double distance = 0, const std::set<uint16_t> &
    visited = {}, std::vector<uint16_t> path = {});
    bool Bound(uint16_t curr_idx, double pathSum, const std::set<uint16_t>& visited) const;
    bool allVerticesVisited(const std::set<uint16_t>& visited) const;

    // AUX functions for 2-approximation
    void getMSTPrim(int root, std::unordered_map<uint16_t, Vertex*>& graph_);

    void preorderDFS(Vertex* node, std::vector<Vertex*>& result, const std::unordered_map<uint16_t, Vertex*>& graph_);
    std::vector<Vertex*> preOrderWalk(std::unordered_map<uint16_t, Vertex*>& graph);
    double getCostFromWalk(std::vector<Vertex*> walk, std::unordered_map<uint16_t, Vertex*>& graph);

    // AUX FUNCTIONS FOR nearest neighbor
    std::vector<Cluster> kmeansClustering();
    std::pair<double, std::vector<uint16_t>> fullNN();

    void tourNNFromCluster(Cluster& cluster);
    std::pair<double, std::vector<uint16_t>> tourNNInterClusters(Cluster& root, std::vector<Cluster>& clusters);

    // Calculations
    double convertToRadians(double coord);
    double haversine(Coordinate coo1, Coordinate coo2);
    double calculateDataRange();

public:
    GraphController(std::unordered_map<uint16_t, Vertex*> graph, std::vector<std::vector<double>> graphAdj_);

    std::pair<double, std::vector<uint16_t>> minHamiltonianCicle();

    std::pair<double, std::vector<Vertex*>> triangleInequalityApp();

    std::pair<double, std::vector<uint16_t>> clusterHeuristic();

};


#endif
