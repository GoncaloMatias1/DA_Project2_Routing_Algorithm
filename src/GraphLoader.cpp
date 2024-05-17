#include "GraphLoader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>

double GraphLoader::parseDouble(const std::string& str) {
    return std::stod(str);
}


std::unordered_map<uint16_t, Vertex*> GraphLoader::loadToyGraph(const std::string &fileName) {
    std::unordered_map<uint16_t, Vertex*> graph;

    std::string path = "../data/Toy-Graphs/" + fileName + ".csv";
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file at " << path << std::endl;
        return graph;
    }

    std::string line, cell;

    file.clear();
    file.seekg(0);
    getline(file, line);
    while (getline(file, line)) {
        std::istringstream lineStream(line);
        int src, dest;
        double weight;

        try{
            getline(lineStream, cell, ',');
            src = std::stoi(cell);
            getline(lineStream, cell, ',');
            dest = std::stoi(cell);
            getline(lineStream, cell);
            weight = std::stod(cell);
        }catch (const std::invalid_argument& e){
            std::cout << "Error parsing csv file data [" << cell << "] : " << e.what() << std::endl;
        }

        if(graph.find(src) == graph.end()){
               graph[src] = new Vertex(src);
        }
        if(graph.find(dest) == graph.end()){
            graph[dest] = new Vertex(dest);
        }

        graph[src]->addEdge(new Edge(weight, graph[src],graph[dest]));
        graph[dest]->addEdge(new Edge(weight, graph[dest], graph[src]));
    }

    file.close();
    return graph;
}

std::unordered_map<uint16_t, Vertex*> GraphLoader::loadRealGraph(const std::string &fileName) {
    std::unordered_map<uint16_t, Vertex*> graph;

    std::string path = "../data/Real_world_Graphs/" + fileName + "/";
    std::string edges = path + "edges.csv";
    std::string nodes = path + "nodes.csv";

    std::ifstream file(nodes);
    std::ifstream file_(edges);

    if (!file.is_open()) {
        std::cerr << "Failed to open file at " << nodes << std::endl;
        return graph;
    }
    if (!file_.is_open()) {
        std::cerr << "Failed to open file at " << edges << std::endl;
        return graph;
    }

    std::string line, cell;
    getline(file, line);
    while (getline(file, line)) {
        std::istringstream lineStream(line);
        int id;
        double longitude, latitude;

        try{
            getline(lineStream, cell, ',');
            id = stoi(cell);
            getline(lineStream, cell, ',');
            longitude = stod(cell);
            getline(lineStream, cell, ',');
            latitude = stod(cell);
            graph[id] = new Vertex(id, {}, {latitude, longitude});

        }catch (const std::invalid_argument& e){
            std::cout << "Error parsing csv file data [" << cell << "] : " << e.what() << std::endl;
        }
    }


    getline(file_, line);
    while (getline(file_, line)) {
        std::istringstream lineStream(line);
        int src, dest;
        double weight;

        try{
            getline(lineStream, cell, ',');
            src = stoi(cell);
            getline(lineStream, cell, ',');
            dest = stoi(cell);
            getline(lineStream, cell, ',');
            weight = stod(cell);

            if(graph.find(src) == graph.end()){
                graph[src] = new Vertex(src);
            }
            if(graph.find(dest) == graph.end()){
                graph[dest] = new Vertex(dest);
            }

            graph[src]->addEdge(new Edge(weight, graph[src],graph[dest]));
            graph[dest]->addEdge(new Edge(weight, graph[dest], graph[src]));

        }catch (const std::invalid_argument& e){
            std::cout << "Error parsing csv file data [" << cell << "] : " << e.what() << std::endl;
        }
    }

    return graph;
}

std::unordered_map<uint16_t, Vertex*> GraphLoader::loadExtraFullGraph(const std::string &fileName) {
    std::unordered_map<uint16_t, Vertex*> graph;

    std::string path = "../data/Extra_Fully_Connected_Graphs/" + fileName + ".csv";
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file at " << path << std::endl;
        return graph;
    }

    std::string line, cell;
    while (getline(file, line)) {
        std::istringstream lineStream(line);
        int src, dest;
        double weight;

        try{
            getline(lineStream, cell, ',');
            src = std::stoi(cell);
            getline(lineStream, cell, ',');
            dest = std::stoi(cell);
            getline(lineStream, cell);
            weight = std::stod(cell);
        }catch (const std::invalid_argument& e){
            std::cout << "Error parsing csv file data [" << cell << "] : " << e.what() << std::endl;
        }

        if(graph.find(src) == graph.end()){
            graph[src] = new Vertex(src);
        }
        if(graph.find(dest) == graph.end()){
            graph[dest] = new Vertex(dest);
        }
        graph[src]->addEdge(new Edge(weight, graph[src],graph[dest]));
        graph[dest]->addEdge(new Edge(weight, graph[dest], graph[src]));
    }

    file.close();
    return graph;
    return {};
}

