//
// Created by admin1 on 10-05-2024.
//

#include <iostream>
#include <queue>
#include <unordered_set>
#include <chrono>
#include "GraphController.h"


GraphController::GraphController(std::unordered_map<uint16_t, Vertex *> graph_) {
    this->graph = graph_;
}

std::pair<double, std::vector<uint16_t>> GraphController::minHamiltonianCicle()  {
    this->recursiveBacktracking(this->graph[0]);
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
    Coordinate coo1_rad = {convertToRadians(coo1.latitude), convertToRadians(coo1.longitude)};
    Coordinate coo2_rad = {convertToRadians(coo2.latitude), convertToRadians(coo2.longitude)};

    Coordinate delta_rad = {coo2_rad.latitude - coo1_rad.latitude, coo2_rad.longitude - coo1_rad.longitude};

    double aux = pow(sin(delta_rad.latitude / 2) , 2) + cos(coo1_rad.latitude) * cos(coo2_rad.latitude) * pow(sin(delta_rad.longitude / 2), 2);
    double c = 2.0 * atan2(sqrt(aux), sqrt(1.0 - aux));
    double earthRadius = 6371000;
    return earthRadius * c;
}

std::pair<double, std::vector<Vertex*>> GraphController::triangleInequalityApp() {
    this->clusterHeuristic();
    auto t1 = std::chrono::high_resolution_clock::now();

   this->getMSTPrim(0, this->graph);
    std::vector<Vertex*> preorder = this->preOrderWalk(this->graph);

    double cost = this->getCostFromWalk(preorder, this->graph);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Time to run triangular: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 -t1).count() << "miliseconds" << std::endl;

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


std::vector<Cluster> GraphController::getClusters() {
    // vector with n clusters that will decrease to n^(1/2)
    std::vector<Cluster> clusters(this->graph.size());

    // populate clusters (complexity -> size of the graph)
    for(auto vPair: this->graph){
        Vertex* vertex = vPair.second;

        Cluster curr;
        curr.clusterId = vPair.first;
        curr.nodes[vPair.first] = vertex;
        curr.center = vertex->getCoordinates();
        curr.processed = false;
        clusters[vPair.first] = curr;
    }

    uint16_t maxClusters = sqrt(this->graph.size());

    while((clusters.size() / 2 + 5) > maxClusters){
        // for each cluster find its nearest and merge
        std::vector<Cluster> clusters_;
        int processedNodes = 0;

        // iterate over clusters
        for(int idx = 0; idx < clusters.size(); idx++){
            Cluster cluster = clusters[idx];
            if(cluster.processed) continue;
            clusters[idx].processed = true;
            Cluster nearestCluster = this->findNearestCluster(clusters, cluster);
            // absorve parent cluster
            Cluster biggerCluster = mergeCluster(nearestCluster, cluster);
            clusters_.push_back(biggerCluster);
            processedNodes++;
        }

        // swap between clusters_ and clusters
        for(uint16_t idx = 0; idx < clusters_.size(); idx++){
            clusters[idx] = clusters_[idx];
        }
        clusters.resize(clusters_.size());
    }

    return clusters;
}

Cluster GraphController::findNearestCluster(std::vector<Cluster>& clusters, Cluster parent) {
    // this function should get the parent id and find its nearest cluster based on coordinates

    double minDistance = std::numeric_limits<double>::infinity();
    Cluster nearestCluster;
    int clusterIdx = -1;

    for(size_t i = 0; i < clusters.size(); i++){
        if(clusters[i].clusterId == parent.clusterId || clusters[i].processed) continue;
        // diff cluster
        double curr_distance = this->haversine(parent.center, clusters[i].center);

        if(curr_distance < minDistance){
            minDistance = curr_distance;
            nearestCluster = clusters[i];
            clusterIdx = i;
        }
    }
    clusters[clusterIdx].processed = true;
    return nearestCluster;
}

Cluster GraphController::mergeCluster(const Cluster &clusterA, const Cluster &clusterB) {
    Cluster parent = clusterA;

    parent.processed = false;
    auto newSize = static_cast<double>(clusterA.nodes.size() + clusterB.nodes.size());

    parent.center.latitude = (parent.center.latitude * parent.nodes.size() + clusterB.center.latitude) / newSize;
    parent.center.longitude = (parent.center.longitude * parent.nodes.size() + clusterB.center.longitude) / newSize;

    for (auto nodePair : clusterB.nodes) {
        parent.nodes[nodePair.first] = nodePair.second;
    }

    return parent;
}

std::pair<double, std::vector<uint16_t>> GraphController::clusterHeuristic() {
    // Get each cluster up to roughly (n ^ 1/2)
    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<Cluster> clusters = this->getClusters();

    double cost = this->getMSTPrimFromCluster(clusters);

    /*
    this->colapseClusters(clusters);
    std::vector<uint16_t> interClusterTour = solveInterCluster(clusters);
    */
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Time it took for cluster approach: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << " miliseconds " << std::endl;

    return {cost, {}};
}

double GraphController::getMSTPrimFromCluster(std::vector<Cluster>& clusters) {
    double cost = 0;
    for(Cluster& cluster: clusters){
        if(cluster.nodes.find(0) != cluster.nodes.end()){
            // there is zero in this cluster
            this->getMSTPrim(0, cluster.nodes);
        }
        else{
            this->getMSTPrim(cluster.nodes.begin()->first, cluster.nodes);
        }
        std::vector<Vertex*> walk = this->preOrderWalk(cluster.nodes);
        cost += this->getCostFromWalk(walk, cluster.nodes);
    }

    return cost;
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
        std::cout << "Graph is not fully connected!\n Results can be inacurate!\n";
    }


    cost += dist;
    return cost;
}
