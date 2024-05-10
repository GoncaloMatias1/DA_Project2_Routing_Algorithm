//
// Created by admin1 on 10-05-2024.
//

#include "GraphController.h"


GraphController::GraphController(std::vector<std::vector<double>> graph_) {
    this->graph = graph_;
}

GraphController::GraphController(std::vector<std::vector<double>> graph_,
                                 std::unordered_map<int, std::pair<double, double>> coords) {
    this->graph = graph_;
    this->nodes = coords;
}


std::vector<double> GraphController::getAdj(uint16_t idx) const {
    return this->graph[idx];
}

bool GraphController::setWeight(uint16_t source, uint16_t dest, double weight) {
    if(source >= this->graph.size() || dest >= this->graph.size() || source < 0 || dest < 0) return false;
    this->graph[source][dest] = weight;
    return true;
}

double GraphController::minHamiltonianCicle()  {
    this->recursiveBacktracking(0, 0,0, {});
    return this->min_distance;
}

void GraphController::recursiveBacktracking(uint16_t curr_idx, uint16_t target_idx, double distance, const std::set<uint16_t>& visited){
    std::set<uint16_t> curr_path = visited;
    curr_path.insert(curr_idx);

    for(uint32_t adj_idx = 0; adj_idx < this->graph.size(); adj_idx++){
        // no edge or visited
        if(this->graph[curr_idx][adj_idx] == std::numeric_limits<double>::infinity()) continue;

        // we found the endpoint
        if(adj_idx == target_idx){
            if(this->allVerticesVisited(curr_path)){
                this->min_distance = (this->min_distance <= distance ? min_distance : distance);
            }
            continue;
        }

        // this vertex is not the endpoint
        double updatedDistance = distance + this->graph[curr_idx][adj_idx];
        if(!this->Bound(adj_idx, updatedDistance, visited)) continue;

        recursiveBacktracking(adj_idx, target_idx, updatedDistance, curr_path);
    }
}

bool GraphController::Bound(uint16_t curr_idx, double pathSum, const std::set<uint16_t>& visited) const {
    // this function is never called with curr_idx == endpoint
    bool isMinDistance = pathSum <= this->min_distance;
    bool notVisited = visited.count(curr_idx) == 0;
    return isMinDistance && notVisited;
}

bool GraphController::allVerticesVisited(const std::set<uint16_t> &visited) const{
    return visited.size() == this->graph.size();
}






