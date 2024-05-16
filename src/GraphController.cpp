//
// Created by admin1 on 10-05-2024.
//

#include <iostream>
#include <queue>
#include <unordered_set>
#include <chrono>
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
    // remove this line is for testing other function
    std::cout << "Cost: " << this->clusterHeuristic().first << std::endl;

    auto t1 = std::chrono::high_resolution_clock::now();

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
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Time to run triangular: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 -t1).count() << "miliseconds" << std::endl;
    return std::make_pair(cost, preorder);
}



std::vector<std::vector<double>> GraphController::getMSTPrim(int root) {
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

std::vector<Cluster> GraphController::getClusters() {
    // vector with n clusters that will decrease to n^(1/2)
    std::vector<Cluster> clusters(this->graph.size());

    // populate clusters (complexity -> size of the graph)
    for(size_t idx = 0; idx < this->graph.size(); idx++){
        // Creates a cluster for each point in the graph, this cluster has the id of the point
        Cluster curr;
        curr.clusterId = idx;
        curr.nodes = {static_cast<uint16_t>(idx)};
        curr.center = this->nodes[idx];
        curr.processed = false;
        clusters[idx] = curr;
    }

    uint16_t maxClusters = sqrt(this->graph.size());

    while((clusters.size() / 2) > maxClusters){
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

    for (uint16_t node : clusterB.nodes) {
        parent.nodes.insert(node);
    }

    return parent;
}

std::pair<double, std::vector<uint16_t>> GraphController::clusterHeuristic() {
    // Get each cluster up to roughly (n ^ 1/2)
    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<Cluster> clusters = this->getClusters();

    double cost = this->getCostFromClusters(clusters);

    cost += this->getcostFromInterClusterConnections(clusters);

    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Time it took for cluster approach: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << " miliseconds " << std::endl;

    return {cost, {}};
}

std::unordered_map<uint16_t, std::set<uint16_t>> GraphController::getMSTPrimFromCluster(Cluster cluster) {
    std::set<uint16_t> visited;
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;

    pq.push({0, *cluster.nodes.begin(), *cluster.nodes.begin()});

    int max_edges = cluster.nodes.size() - 1;
    int edge_count = 0;


    // Map with (VertexId -> vector of adj)
    std::unordered_map<uint16_t, std::set<uint16_t>> result;
    while (!pq.empty() && edge_count <= max_edges) {
        Edge current = pq.top();
        pq.pop();

        result[current.vertexA].insert(current.vertexB);
        result[current.vertexB].insert(current.vertexA);

        // get current vertex
        int u = current.vertexB;
        if (visited.find(u) != visited.end()) continue;
        visited.insert(u);

        // for all adjacent, add it to the priority queue
        for(uint16_t node: cluster.nodes){
            if(visited.find(node) == visited.end() && this->graph[u][node] != std::numeric_limits<double>::infinity()){
                pq.push({this->graph[u][node], u, node});
            }
        }

        edge_count++;
    }
    return result;
}

std::vector<uint16_t> GraphController::preOrderWalkCluster(std::unordered_map<uint16_t, std::set<uint16_t>> mst) {
    std::set<uint16_t> visited;
    std::vector<uint16_t> result;
    if(mst.find(0) != mst.end()) preorderDFSCluster(0, mst, visited, result);
    else preorderDFSCluster(mst.begin()->first, mst, visited, result);
    return result;
}
void GraphController::preorderDFSCluster(uint16_t node, const std::unordered_map<uint16_t, std::set<uint16_t>> &mst, std::set<uint16_t> &visited, std::vector<uint16_t> &result) {
    visited.insert(node);
    result.push_back(node);

    // for adjacent
    for(uint16_t adj: mst.at(node)){
        // each adjacent of this node
        if(visited.find(adj) == visited.end()){
            preorderDFSCluster(adj, mst, visited, result);
        }
    }
}

double GraphController::getCostFromClusters(std::vector<Cluster> &clusters) {
    std::vector<uint16_t> resultWalk;
    double cost = 0;

    // process each cluster
    for(Cluster& cluster: clusters){
        // for each cluster get its mst
        auto clusterMst = this->getMSTPrimFromCluster(cluster);
        if(clusterMst.size() != cluster.nodes.size()){
            std::cerr << "Cluster was truncated when transforming to mst\n";
        }
        // do a preorder walk
        auto walk = preOrderWalkCluster(clusterMst);
        if(walk.size() != cluster.nodes.size()){
            std::cerr << "Walk of cluster is wrong!\n";
        }

        // for each walk calculate cost
        for(uint16_t i = 1; i < walk.size(); i++){
            uint16_t lastIndex = walk[i-1];
            uint16_t currentIndex = walk[i];

            // Exists edge

            if(clusterMst[lastIndex].find(currentIndex) != clusterMst[lastIndex].end()){
                cost += this->graph[lastIndex][currentIndex];
                continue;
            }
            // doesnt exist edge
            else{

                double distance = this->haversine(this->nodes[lastIndex], this->nodes[currentIndex]);
                cost += distance;
            }
        }
        if(cluster.nodes.size() < 2){
            cluster.endpointA = walk.back();
            cluster.bConnected = true;
            continue;
        }
        cluster.endpointA = walk.back();
        cluster.endpointB = walk.front();
    }
    return cost;
}

double GraphController::getcostFromInterClusterConnections(std::vector<Cluster> &clusters) {
    double cost = 0;
    for(Cluster& rootCluster: clusters){
        // for each iteration it should connect two clusters (from rootCluster - A to connectingCluster - B)
        Cluster* nearestCluster;
        double nearestEndpoint = std::numeric_limits<double>::infinity();
        // for all clusters endpoints find its nearest
        for(Cluster& connectingCluster: clusters){
            if(connectingCluster.bConnected) continue;
            double distance;
            if(this->graph[connectingCluster.endpointB][rootCluster.endpointA] != std::numeric_limits<double>::infinity()){
                distance = this->graph[connectingCluster.endpointB][rootCluster.endpointA];
            }
            else{
                distance = this->haversine(this->nodes[connectingCluster.endpointB], this->nodes[rootCluster.endpointA]);
            }

            if(distance < nearestEndpoint){
                nearestEndpoint = distance;
                nearestCluster = &connectingCluster;
            }
        }

        if(nearestEndpoint == std::numeric_limits<double>::infinity())continue;
        rootCluster.aConnected = true;
        nearestCluster->bConnected = true;
        cost += nearestEndpoint;
    }
    return cost;
}


