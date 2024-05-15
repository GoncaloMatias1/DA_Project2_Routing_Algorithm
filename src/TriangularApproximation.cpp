/*
#include "TriangularApproximation.h"

TriangularApproximation::TriangularApproximation(const GraphLoader::Graph& graph, const std::unordered_map<int, Coordinate>& nodes)
        : graph(graph), nodes(nodes) {}

double TriangularApproximation::solve() {
    double totalDistance = 0.0;

    for (auto& node : nodes) {
        for (auto& neighbor : nodes) {
            if (node.first != neighbor.first) {
                totalDistance += calculateDistance(node.first, neighbor.first);
            }
        }
    }

    return totalDistance / 2;
}

double TriangularApproximation::calculateDistance(int from, int to) {
    Coordinate coo1 = nodes.at(from);
    Coordinate coo2 = nodes.at(to);

    double lat1 = coo1.latitude * M_PI / 180.0;
    double lon1 = coo1.longitude * M_PI / 180.0;
    double lat2 = coo2.latitude * M_PI / 180.0;
    double lon2 = coo2.longitude * M_PI / 180.0;

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = std::sin(dlat / 2) * std::sin(dlat / 2) +
               std::cos(lat1) * std::cos(lat2) * std::sin(dlon / 2) * std::sin(dlon / 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    double earthRadius = 6371000;
    return earthRadius * c;
}
*/