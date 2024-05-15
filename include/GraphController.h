#ifndef GRAPHCONTROLLER_H
#define GRAPHCONTROLLER_H

#include <vector>
#include <cinttypes>
#include <unordered_map>
#include <set>
#include <limits>
#include <cmath>

struct Coordinate {
    double latitude;
    double longitude;
};

struct Cluster{
    uint16_t clusterId;
    std::set<uint16_t> nodes;
    Coordinate center;
    bool processed = false;
};

class GraphController{
private:
    std::vector<std::vector<double>> graph;
    std::unordered_map<int, Coordinate> nodes; // Real-World graph nodes that hold the coordinates
    double min_distance = std::numeric_limits<double>::infinity();
    std::vector<uint16_t> minPath;

    // AUX functions for backtrack
    void recursiveBacktracking(uint16_t curr_idx, uint16_t target_idx, double distance = 0, const std::set<uint16_t> &
    visited = {}, std::vector<uint16_t> path = {});
    bool Bound(uint16_t curr_idx, double pathSum, const std::set<uint16_t>& visited) const;
    bool allVerticesVisited(const std::set<uint16_t>& visited) const;

    // AUX functions for 2-approximation
    std::vector<std::vector<double>> getMSTPrim(int root);
    void preorderDFS(uint16_t node, const std::vector<std::vector<double>>& mst, std::vector<bool>& visited, std::vector<uint16_t>& result);
    std::vector<uint16_t> preOrderWalk(std::vector<std::vector<double>> mst);

    // AUX functions for clustering
    std::vector<Cluster> getClusters();

    Cluster findNearestCluster(std::vector<Cluster>& clusters, Cluster parent);
    Cluster mergeCluster(const Cluster& clusterA, const Cluster& clusterB);

    // Calculations
    double convertToRadians(double coord);
    double haversine(Coordinate coo1, Coordinate coo2);

public:
    GraphController(std::vector<std::vector<double>> graph_);
    GraphController(std::pair<std::vector<std::vector<double>>, std::unordered_map<int, Coordinate>> data);

    // Node related logic (uint16 because the largest graph is 10k nodes long, with uint16 we get 65k range of numbers that covers the 10k)

    std::vector<double> getAdj(uint16_t idx) const;
    bool setWeight(uint16_t source, uint16_t dest, double weight);
    std::pair<double, std::vector<uint16_t>> minHamiltonianCicle();

    std::pair<double, std::vector<uint16_t>> triangleInequalityApp();

};


#endif
