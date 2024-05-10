#ifndef GRAPHCONTROLLER_H
#define GRAPHCONTROLLER_H

#include <vector>
#include <cinttypes>
#include <unordered_map>
#include <set>
#include <limits>
class GraphController{
private:
    std::vector<std::vector<double>> graph;
    std::unordered_map<int, std::pair<double, double>> nodes; // Real-World graph nodes that hold the coordinates
    double min_distance = std::numeric_limits<double>::infinity();
    std::vector<uint16_t> minPath;

    // AUX fucntions for backtrack
    void recursiveBacktracking(uint16_t curr_idx, uint16_t target_idx, double distance = 0,const std::set<uint16_t> &
    visited = {}, std::vector<uint16_t> path = {});
    bool Bound(uint16_t curr_idx, double pathSum, const std::set<uint16_t>& visited) const;
    bool allVerticesVisited(const std::set<uint16_t>& visited) const;

public:
    GraphController(std::vector<std::vector<double>> graph_);
    GraphController(std::vector<std::vector<double>> graph, std::unordered_map<int, std::pair<double, double>> coords);

    // Node related logic (uint16 because the largest graph is 10k nodes long, with uint16 we get 65k range of numbers that covers the 10k)

    std::vector<double> getAdj(uint16_t idx) const;
    bool setWeight(uint16_t source, uint16_t dest, double weight);
    std::pair<double, std::vector<uint16_t>> minHamiltonianCicle();

};


#endif
