//
// Created by admin1 on 10-05-2024.
//

#include <iostream>
#include <queue>
#include "GraphController.h"


GraphController::GraphController(std::vector<std::vector<double>> graph_) {
    this->graph = graph_;
}

GraphController::GraphController(std::pair<std::vector<std::vector<double>>, std::unordered_map<int, Coordinate>> data) {
    this->graph = data.first;
    this->nodes = data.second;
}


std::vector<double> GraphController::getAdj(uint16_t idx) const {
    return this->graph[idx];
}

bool GraphController::setWeight(uint16_t source, uint16_t dest, double weight) {
    if(source >= this->graph.size() || dest >= this->graph.size() || source < 0 || dest < 0) return false;
    this->graph[source][dest] = weight;
    return true;
}

std::pair<double, std::vector<uint16_t>> GraphController::minHamiltonianCicle()  {
    this->recursiveBacktracking(0, 0);
    return std::make_pair(this->min_distance, this->minPath);
}

void GraphController::recursiveBacktracking(uint16_t curr_idx, uint16_t target_idx, double distance, const std::set<uint16_t>& visited, std::vector<uint16_t> path){

    std::set<uint16_t> curr_visited = visited;
    curr_visited.insert(curr_idx);
    path.push_back(curr_idx);

    for(uint32_t adj_idx = 0; adj_idx < this->graph.size(); adj_idx++){
        // no edge or visited
        if(this->graph[curr_idx][adj_idx] == std::numeric_limits<double>::infinity()) continue;
        double updatedDistance = distance + this->graph[curr_idx][adj_idx];

        // we found the endpoint
        if(adj_idx == target_idx){
            if(this->allVerticesVisited(curr_visited)){
                if(this->min_distance > updatedDistance){
                    this->min_distance = updatedDistance;
                    this->minPath = path;
                }
            }
            continue;
        }
        // this vertex is not the endpoint
        if(!this->Bound(adj_idx, updatedDistance, visited)) continue;

        recursiveBacktracking(adj_idx, target_idx, updatedDistance, curr_visited, path);
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

double GraphController::convertToRadians(double coord) {
    return coord * M_PI / 180;
}

double GraphController::haversine(Coordinate coo1, Coordinate coo2) {
    Coordinate coo1_rad = {convertToRadians(coo1.latitude), convertToRadians(coo1.longitude)};
    Coordinate coo2_rad = {convertToRadians(coo2.latitude), convertToRadians(coo2.longitude)};

    Coordinate delta_rad = {coo2_rad.latitude - coo1_rad.latitude, coo2_rad.longitude - coo1_rad.longitude};

    double aux = pow(sin(delta_rad.latitude / 2) , 2) + cos(coo1_rad.latitude) * cos(coo2_rad.latitude) * pow(sin(delta_rad.longitude / 2), 2);
    double c = 2.0 * atan2(sqrt(aux), sqrt(1.0 - aux));
    double earthRadius = 6371000;
    return earthRadius * c;
}

std::pair<double, std::vector<uint16_t>> GraphController::triangleInequalityApp() {
    std::vector<std::vector<double>> mst = this->getMSTPrim(0);
    std::vector<uint16_t> preorder = this->preOrderWalk(mst);

    double cost = 0;

    for(uint16_t i = 1; i < preorder.size(); i++){
        uint16_t lastIndex = preorder[i-1];
        uint16_t currentIndex = preorder[i];
        // Exists edge
        if(mst[lastIndex][currentIndex] != std::numeric_limits<double>::infinity()){
            cost += this->graph[lastIndex][currentIndex];
            continue;
        }
        // doesnt exist edge
        else{
            double distance = this->haversine(this->nodes[lastIndex], this->nodes[currentIndex]);
            cost += distance;
        }
    }

    if(this->graph[preorder[0]][preorder.back()] != std::numeric_limits<double>::infinity()){
        cost += this->graph[preorder[0]][preorder.back()];
    }else{
        cost += this->haversine(this->nodes[preorder[0]], this->nodes[preorder.back()]);
    }

    return std::make_pair(cost, preorder);
}
std::vector<std::vector<double>> GraphController::getMSTPrim(int root) {
    // Create an edge struct that will help to configure the priority queue
    struct Edge {
        double weight;
        int vertexA;
        int vertexB;

        bool operator>(const Edge& other) const {
            return weight > other.weight;
        }
    };

    std::vector<std::vector<double>> result(this->graph.size(), std::vector<double>(this->graph.size(), std::numeric_limits<double>::infinity()));

    std::vector<bool> visited(this->graph.size(), false);

    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;

    pq.push({0, root, root});

    int max_edges = this->graph.size() - 1;
    int edge_count = 0;

    while (!pq.empty() && edge_count <= max_edges) {
        Edge current = pq.top();
        pq.pop();


        result[current.vertexA][current.vertexB] = this->graph[current.vertexA][current.vertexB];
        result[current.vertexB][current.vertexA] = this->graph[current.vertexA][current.vertexB];

        // get current vertex
        int u = current.vertexB;
        if (visited[u]) continue;
        visited[u] = true;

        // for all adjacent, add it to the priority queue
        for (int v = 0; v < this->graph.size(); v++) {
            if (!visited[v] && this->graph[u][v] != std::numeric_limits<double>::infinity()) {
                pq.push({this->graph[u][v], u ,v});
            }
        }

        edge_count++;
    }

    return result;
}

std::vector<uint16_t> GraphController::preOrderWalk(std::vector<std::vector<double>> mst) {
    std::vector<bool> visited(this->graph.size(), false);
    std::vector<uint16_t> result;
    preorderDFS(0, mst, visited, result);
    return result;
}

void GraphController::preorderDFS(uint16_t node, const std::vector<std::vector<double>>& mst, std::vector<bool>& visited, std::vector<uint16_t>& result) {
    visited[node] = true;
    result.push_back(node);

    for(uint16_t i = 0; i < this->graph.size(); i++){
        if(!visited[i] && mst[node][i] != std::numeric_limits<double>::infinity()){
            preorderDFS(i, mst, visited, result);
        }
    }
}


std::pair<double, std::vector<uint16_t>> GraphController::solveRealWorldTSP(uint16_t startNode) {
    std::vector<uint16_t> path;
    std::set<uint16_t> visited;
    double totalDistance = 0;

    if (graph.empty() || startNode >= graph.size()) {
        std::cout << "Invalid start node or empty graph.\n";
        return std::make_pair(-1, std::vector<uint16_t>());
    }

    std::priority_queue<std::pair<double, std::vector<uint16_t>>,
            std::vector<std::pair<double, std::vector<uint16_t>>>,
            std::greater<std::pair<double, std::vector<uint16_t>>>> pq;

    pq.push({0, {startNode}});
    while (!pq.empty()) {
        auto [currentCost, currentPath] = pq.top();
        pq.pop();
        uint16_t currentNode = currentPath.back();

        if (currentPath.size() == graph.size()) {
            if (graph[currentNode][startNode] != std::numeric_limits<double>::infinity()) {
                currentPath.push_back(startNode);
                currentCost += graph[currentNode][startNode];
                return {currentCost, currentPath};
            }
        }

        for (uint16_t nextNode = 0; nextNode < graph.size(); ++nextNode) {
            if (std::find(currentPath.begin(), currentPath.end(), nextNode) == currentPath.end()) {
                double edgeWeight = graph[currentNode][nextNode];
                if (edgeWeight != std::numeric_limits<double>::infinity()) {
                    std::vector<uint16_t> newPath = currentPath;
                    newPath.push_back(nextNode);
                    pq.push({currentCost + edgeWeight, newPath});
                }
            }
        }
    }

    std::cout << "No valid TSP path exists from the given starting node.\n";
    return std::make_pair(-1, std::vector<uint16_t>());
}



