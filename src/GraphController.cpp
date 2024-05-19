//
// Created by admin1 on 10-05-2024.
//

#include <iostream>
#include <queue>
#include <unordered_set>
#include <chrono>
#include <random>
#include <utility>
#include <algorithm>
#include "GraphController.h"


GraphController::GraphController(std::unordered_map<uint16_t, Vertex *> graph_, std::vector<std::vector<double>> graphAdj_) {
    this->graph = std::move(graph_);
    this->graphAdj = std::move(graphAdj_);
}

std::pair<double, std::vector<uint16_t>> GraphController::minHamiltonianCicle()  {
    auto t1 = std::chrono::high_resolution_clock::now();
    this->recursiveBacktracking(this->graph[0]);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Time to run backtracking: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 -t1).count() << "milliseconds" << std::endl;

    return std::make_pair(this->min_distance, this->minPath);
}

void GraphController::recursiveBacktracking(Vertex* curr_vertex, double distance, const std::set<uint16_t>& visited, std::vector<uint16_t> path){
    std::set<uint16_t> curr_visited = visited;
    curr_visited.insert(curr_vertex->getId());

    path.push_back(curr_vertex->getId());

    for(Edge* adj: curr_vertex->getAdj()){
        double updatedDistance = distance + adj->getWeight();
        if(adj->getDestination()->getId() == 0 ){
            if(this->allVerticesVisited(curr_visited) && this->min_distance > updatedDistance){
                this->min_distance = updatedDistance;
                this->minPath = path;
            }
            continue;
        }
        // this vertex is not endpoint
        if(!this->Bound(adj->getDestination()->getId(), updatedDistance, visited)) continue;
        recursiveBacktracking(adj->getDestination(), updatedDistance, curr_visited, path);
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
    if(coo1.latitude == std::numeric_limits<double>::infinity() || coo2.latitude == std::numeric_limits<double>::infinity()) return std::numeric_limits<double>::infinity();
    Coordinate coo1_rad = {convertToRadians(coo1.latitude), convertToRadians(coo1.longitude)};
    Coordinate coo2_rad = {convertToRadians(coo2.latitude), convertToRadians(coo2.longitude)};

    Coordinate delta_rad = {coo2_rad.latitude - coo1_rad.latitude, coo2_rad.longitude - coo1_rad.longitude};

    double aux = pow(sin(delta_rad.latitude / 2) , 2) + cos(coo1_rad.latitude) * cos(coo2_rad.latitude) * pow(sin(delta_rad.longitude / 2), 2);
    double c = 2.0 * atan2(sqrt(aux), sqrt(1.0 - aux));
    double earthRadius = 6371000;
    return earthRadius * c;
}

std::pair<double, std::vector<Vertex*>> GraphController::triangleInequalityApp() {
    auto t1 = std::chrono::high_resolution_clock::now();

    this->getMSTPrim(0, this->graph);
    std::vector<Vertex*> preorder = this->preOrderWalk(this->graph);

    double cost = this->getCostFromWalk(preorder, this->graph);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Time to run triangular: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 -t1).count() << "milliseconds" << std::endl;

    return {cost , preorder};

}

void GraphController::getMSTPrim(int root, std::unordered_map<uint16_t, Vertex*>& graph_) {
    if(graph_.empty()) return ;
    std::vector<Edge*> result;

    for(auto& vertex: graph_){
        Vertex* curr_vertex = vertex.second;
        curr_vertex->setVisited(false);
        curr_vertex->setPath(nullptr);
        curr_vertex->setDistance(std::numeric_limits<double>::infinity());
    }

    Vertex* startVertex = this->graph[root];
    startVertex->setDistance(0);

    MutablePriorityQueue<Vertex> pq;
    pq.insert(startVertex);

    while(!pq.empty()){
        auto v = pq.extractMin();
        v->setVisited(true);

        double weight = 0;

        for(auto &e : v->getAdj()) {
            if(graph_.find(e->getDestination()->getId()) == graph_.end()) continue;
            if(graph_.find(e->getDestination()->getId()) == graph_.end()) continue;
            Vertex* w = e->getDestination();
            if (!w->isVisited()) {
                auto oldDist = w->getDistance();
                if(e->getWeight() < oldDist) {
                    w->setDistance(e->getWeight());
                    w->setPath(v);
                    if (oldDist == std::numeric_limits<double>::infinity()) {
                        pq.insert(w);
                    }
                    else {
                        pq.decreaseKey(w);
                    }
                }
            }
        }
    }
    return;
}

std::vector<Vertex*> GraphController::preOrderWalk(std::unordered_map<uint16_t, Vertex*>& graph_) {
    std::vector<Vertex*> result;
    if(graph_.find(0) != graph_.end()){
        preorderDFS(graph_[0],  result, graph_);
    }else{
        preorderDFS(graph.begin()->second, result, graph_);
    }
    return result;
}

void GraphController::preorderDFS(Vertex* node, std::vector<Vertex*>& result, const std::unordered_map<uint16_t, Vertex*>& graph_) {
    result.push_back(node);

    for(auto vertexPair: graph_){
        if(vertexPair.second->getPath() == node){
            preorderDFS(vertexPair.second, result, graph_);
        }
    }
}

std::pair<double, std::vector<uint16_t>> GraphController::clusterHeuristic() {
    auto t1 = std::chrono::high_resolution_clock::now();
    if(this->graph.begin()->second->getCoordinates().latitude == std::numeric_limits<double>::infinity()){
        auto t2 = std::chrono::high_resolution_clock::now();
        std::cout << "Time to run cluster: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 -t1).count() << "milliseconds" << std::endl;
        return this->fullNN();
    }


    // K-means clustering for geographic based clustering
    std::vector<Cluster> clusters;
    clusters = this->kmeansClustering();


    Cluster rootCluster;

    // for each cluster get a tour and a walk cost
    double totalCost = 0;

    std::vector<std::thread> threads;
    for (Cluster& cluster : clusters) {
        threads.emplace_back(&GraphController::tourNNFromCluster, this, std::ref(cluster));
    }
    // Join threads to ensure all complete before moving on
    for (std::thread& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }
    // generate cost from intra-cluster and find cluster with 0
    for(Cluster& cluster: clusters){
        totalCost += cluster.tourCost;
        if(cluster.rootCluster) rootCluster = cluster;
    }

    std::pair<double, std::vector<uint16_t>> finalTour = this->tourNNInterClusters(rootCluster, clusters);
    finalTour.first += totalCost;


    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Time to run cluster: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 -t1).count() << "milliseconds" << std::endl;
    return finalTour;
}

double GraphController::getCostFromWalk(std::vector<Vertex *> walk, std::unordered_map<uint16_t, Vertex *> &graph) {
    double cost = 0;

    for(uint16_t i = 1; i < walk.size(); i++){
        Vertex* last = walk[i-1];
        Vertex* current = walk[i];

        for(Edge* adj: last->getAdj()){
            if(adj->getDestination() == current){
                cost += adj->getWeight();
            }
        }
    }

    Vertex* endpoint = walk.back();
    Vertex* endpointB = walk.front();
    double dist = 0;
    for(auto adj: endpoint->getAdj()){
        if(adj->getDestination() == endpointB){
            dist = adj->getWeight();
        }
    }
    if(dist == 0){
        dist = this->haversine(endpoint->getCoordinates(), endpointB->getCoordinates());
        if(dist == std::numeric_limits<double>::infinity()) dist = 0;
        std::cout << "Graph is not fully connected!Results can be inaccurate!\n";
    }

    cost += dist;
    return cost;
}

double GraphController::calculateDataRange() {
    Coordinate min = {std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()};
    Coordinate max = {std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest()};

    for(auto v: this->graph){
        Coordinate coo = v.second->getCoordinates();
        if(coo.latitude < min.latitude) {
            min.latitude = coo.latitude;
        }
        if(coo.longitude < min.longitude){
            min.longitude = coo.longitude;
        }
        if(coo.latitude > max.latitude){
            max.latitude = coo.latitude;
        }
        if(coo.longitude > max.longitude){
            max.longitude = coo.longitude;
        }
    }

    return this->haversine(min, max);
}

std::vector<Cluster> GraphController::kmeansClustering() {
    int k = sqrt(this->graph.size());
    std::vector<Cluster> clusters(k);

    int index = 0;
    for (const auto& node : graph) {
        if (index < k) {
            clusters[index].center = node.second->getCoordinates();
            clusters[index].clusterId = index;
            index++;
        } else {
            break;
        }
    }

    double tolerance = 0.01 * this->calculateDataRange();

    bool changed = true;
    // update clusters until no further change
    while(changed){
        for(auto& cluster: clusters){
            cluster.nodes.clear();
        }

        for (const auto& node : graph) {
            double minDist = std::numeric_limits<double>::infinity();
            int bestCluster = 0;
            for (int i = 0; i < k; ++i) {
                double dist = this->haversine(node.second->getCoordinates(), clusters[i].center);
                if (dist < minDist) {
                    minDist = dist;
                    bestCluster = i;
                }
            }
            clusters[bestCluster].nodes.push_back(node.first);
        }
        changed = false;
        for (int i = 0; i < k; ++i) {
            double sumLat = 0;
            double sumLon = 0;
            for (uint16_t nodeId : clusters[i].nodes) {
                sumLat += graph.at(nodeId)->getCoordinates().latitude;
                sumLon += graph.at(nodeId)->getCoordinates().longitude;
            }
            Coordinate newCenter = {sumLat / clusters[i].nodes.size(), sumLon / clusters[i].nodes.size()};
            double distance = this->haversine(newCenter, clusters[i].center);
            if (distance > tolerance) {
                changed = true;
                clusters[i].center = newCenter;
            }
        }
    }

    return clusters;
}

void GraphController::tourNNFromCluster(Cluster &cluster) {
    std::set<uint16_t> nodes;

    cluster.tour.clear();
    for(uint16_t node: cluster.nodes){
        nodes.insert(node);
        if(node == 0) cluster.rootCluster = true;
    }

    // do nearest neighbor (if is zero i want to start tour in 0)
    uint16_t currNode = 0;
    if(nodes.find(0) == nodes.end()) currNode = *nodes.begin();

    while(!nodes.empty()){
        double minDistance = std::numeric_limits<double>::infinity();
        uint16_t minVertex;

        for(uint16_t adjNode: nodes){
            if(adjNode == currNode) continue;
            double distance = this->graphAdj[currNode][adjNode];
            // no edge between
            if(distance == std::numeric_limits<double>::infinity()){
                distance = this->haversine(this->graph[adjNode]->getCoordinates(), this->graph[currNode]->getCoordinates());
            }
            if(distance < minDistance){
                minVertex = adjNode;
                minDistance = distance;
            }
        }

        nodes.erase(currNode);
        cluster.tour.push_back(currNode);
        currNode = minVertex;
        if(minDistance == std::numeric_limits<double>::infinity()) break;
        cluster.tourCost += minDistance;
    }
}

// connect clusters endpoints
std::pair<double, std::vector<uint16_t>> GraphController::tourNNInterClusters(Cluster &root, std::vector<Cluster> &clusters) {
    std::vector<uint16_t> interClusterTour;
    double totalInterClusterCost = 0;

    uint16_t currCluster;
    for(uint16_t idx = 0; idx < clusters.size(); idx++){
        if(clusters[idx].rootCluster){
            currCluster = idx;
            break;
        }
    }
    int connectedCluster = 0;

    while(connectedCluster != clusters.size()){
        clusters[currCluster].processed = true;
        for(uint16_t node: clusters[currCluster].tour) interClusterTour.push_back(node);

        uint16_t endpointB = clusters[currCluster].tour.front();
        uint16_t nearestCluster;
        double minDistance = std::numeric_limits<double>::infinity();

        for(uint16_t childIdx = 0; childIdx < clusters.size(); childIdx++){
            if(clusters[childIdx].processed || clusters[childIdx].nodes.empty()) continue;
            uint16_t endpointA = clusters[childIdx].tour.back();
            double distance = this->graphAdj[endpointA][endpointB];
            if(distance == std::numeric_limits<double>::infinity()){
                distance = this->haversine(this->graph[endpointA]->getCoordinates(), this->graph[endpointB]->getCoordinates());
            }
            if(distance < minDistance){
                nearestCluster = childIdx;
                minDistance = distance;
            }
        }
        if(minDistance == std::numeric_limits<double>::infinity()) break;
        totalInterClusterCost += minDistance;
        currCluster = nearestCluster;
        connectedCluster++;
    }
    if(interClusterTour.size() != this->graph.size()){
        std::cout << "The tour does not match the graph size, in this way the result is not reliable!\n";
    }

    return {totalInterClusterCost, interClusterTour};
}

std::pair<double, std::vector<uint16_t>> GraphController::fullNN() {
    std::set<uint16_t> nodes;
    std::vector<uint16_t> tour;
    double tourCost = 0;

    for(auto v: this->graph){
        nodes.insert(v.first);
    }
    // do nearest neighbor (if is zero i want to start tour in 0)
    uint16_t currNode = 0;
    while(!nodes.empty()){
        double minDistance = std::numeric_limits<double>::infinity();
        uint16_t minVertex;

        for(uint16_t adjNode: nodes){
            if(adjNode == currNode) continue;

            double distance = this->graphAdj[currNode][adjNode];
            if(distance < minDistance){
                minVertex = adjNode;
                minDistance = distance;
            }
        }

        nodes.erase(currNode);
        tour.push_back(currNode);
        currNode = minVertex;
        if(minDistance == std::numeric_limits<double>::infinity()) break;
        tourCost += minDistance;
    }

    // compute trace back
    if(this->graphAdj[tour.front()][tour.back()] != std::numeric_limits<double>::infinity()){
        tourCost += this->graphAdj[tour.front()][tour.back()];
    }

    return {tourCost, tour};
}

bool GraphController::isConnectedGraph() {
    if (graph.empty()) return false;
    std::unordered_set<uint16_t> visited;
    std::queue<uint16_t> q;
    q.push(graph.begin()->first);
    visited.insert(graph.begin()->first);

    while (!q.empty()) {
        uint16_t current = q.front();
        q.pop();

        for (Edge* edge : graph[current]->getAdj()) {
            uint16_t neighbor = edge->getDestination()->getId();
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }

    return visited.size() == graph.size();
}

std::pair<double, std::vector<uint16_t>> GraphController::solveTSPForDisconnectedGraph(uint16_t startNode) {
    if (!isConnectedGraph()) {
        return {std::numeric_limits<double>::infinity(), {}};
    }
    return findTSPForDisconnectedGraph(graph[startNode]);
}

std::pair<double, std::vector<uint16_t>> GraphController::findTSPForDisconnectedGraph(Vertex* startVertex) {
    std::set<uint16_t> nodes;
    std::vector<uint16_t> tour;
    double tourCost = 0;

    for (const auto& v : graph) {
        nodes.insert(v.first);
    }

    uint16_t currNode = startVertex->getId();
    while (!nodes.empty()) {
        double minDistance = std::numeric_limits<double>::infinity();
        uint16_t minVertex;

        for (uint16_t adjNode : nodes) {
            if (adjNode == currNode) continue;

            double distance = this->graphAdj[currNode][adjNode];
            if (distance < minDistance) {
                minVertex = adjNode;
                minDistance = distance;
            }
        }

        nodes.erase(currNode);
        tour.push_back(currNode);
        currNode = minVertex;
        if (minDistance == std::numeric_limits<double>::infinity()) break;
        tourCost += minDistance;
    }

    if (this->graphAdj[tour.front()][tour.back()] != std::numeric_limits<double>::infinity()) {
        tourCost += this->graphAdj[tour.front()][tour.back()];
    }

    return {tourCost, tour};
}
