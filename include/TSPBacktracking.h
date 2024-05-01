#pragma once
#include <vector>
#include <limits>

class TSPBacktracking {
public:
    double findShortestTour(const std::vector<std::vector<double>>& graph);
private:
    void backtrack(std::vector<int>& path, std::vector<bool>& visited, double& minCost, double currentCost, int level, const std::vector<std::vector<double>>& graph);
};
