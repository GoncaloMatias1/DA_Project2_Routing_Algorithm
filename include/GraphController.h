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

struct Cluster{
    std::unordered_map<uint16_t, Vertex*> nodes;
    Coordinate center;

    uint16_t clusterId;
    double clusterCost = 0;
    std::vector<uint16_t> tour;
    uint16_t endpointA;
    uint16_t endpointB;
    bool aConnected = false;
    bool bConnected = false;

    bool processed = false;
    ~Cluster(){}
};

class GraphController{
private:
    std::unordered_map<uint16_t, Vertex*> graph;

    //std::vector<std::vector<double>> graph;
    //std::unordered_map<int, Coordinate> nodes; // Real-World graph nodes that hold the coordinates

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

   // AUX functions for clustering
   std::vector<Cluster> getClusters();
   Cluster findNearestCluster(std::vector<Cluster>& clusters, Cluster parent);
   Cluster mergeCluster(const Cluster& clusterA, const Cluster& clusterB);


   double getMSTPrimFromCluster(std::vector<Cluster>& clusters);

    // Calculations
    double convertToRadians(double coord);
    double haversine(Coordinate coo1, Coordinate coo2);

public:
    GraphController(std::unordered_map<uint16_t, Vertex*> graph);


    // Node related logic (uint16 because the largest graph is 10k nodes long, with uint16 we get 65k range of numbers that covers the 10k)

    std::pair<double, std::vector<uint16_t>> minHamiltonianCicle();

    std::pair<double, std::vector<Vertex*>> triangleInequalityApp();

    std::pair<double, std::vector<uint16_t>> clusterHeuristic();

};


#endif
