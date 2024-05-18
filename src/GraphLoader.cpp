#include "GraphLoader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>

double GraphLoader::parseDouble(const std::string& str) {
    return std::stod(str);
}


std::pair<std::unordered_map<uint16_t, Vertex*>, std::vector<std::vector<double>>> GraphLoader::loadToyGraph(const std::string &fileName) {
    std::unordered_map<uint16_t, Vertex*> graph;
    std::vector<std::vector<double>> graphAdj;

    std::string path = "../data/Toy-Graphs/" + fileName + ".csv";
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file at " << path << std::endl;
        return {};
    }

    std::string line, cell;
    int maxSize = 0;
    getline(file, line);
    while (getline(file, line)) {
        std::istringstream lineStream(line);
        int src, dest;

        try{
            getline(lineStream, cell, ',');
            src = stoi(cell);
            getline(lineStream, cell, ',');
            dest = stoi(cell);
            int maxIndex = std::max(src, dest);
            if (maxIndex > maxSize) {
                maxSize = maxIndex;
            }

        }catch (const std::invalid_argument& e){
            std::cout << "Error parsing csv file data [" << cell << "] : " << e.what() << std::endl;
        }

    }

    graphAdj.resize(maxSize + 1, std::vector<double>(maxSize + 1, std::numeric_limits<double>::infinity()));

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
        graphAdj[src][dest] = weight;
        graphAdj[dest][src] = weight;
    }

    file.close();
    return {graph, graphAdj};
}

std::pair<std::unordered_map<uint16_t, Vertex*>, std::vector<std::vector<double>>> GraphLoader::loadRealGraph(const std::string &fileName) {
    std::unordered_map<uint16_t, Vertex*> graph;


    uint16_t vertexCount = 0;

    std::string path = "../data/Real_world_Graphs/" + fileName + "/";
    std::string edges = path + "edges.csv";
    std::string nodes = path + "nodes.csv";

    std::ifstream file(nodes);
    std::ifstream file_(edges);

    if (!file.is_open()) {
        std::cerr << "Failed to open file at " << nodes << std::endl;
        return {graph, {}};
    }
    if (!file_.is_open()) {
        std::cerr << "Failed to open file at " << edges << std::endl;
        return {graph, {}};
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
            vertexCount++;

        }catch (const std::invalid_argument& e){
            std::cout << "Error parsing csv file data [" << cell << "] : " << e.what() << std::endl;
        }
    }

    std::vector<std::vector<double>> graphAdj(vertexCount, std::vector<double>(vertexCount, std::numeric_limits<double>::infinity()));

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
            graphAdj[src][dest] = weight;
            graphAdj[dest][src] = weight;

        }catch (const std::invalid_argument& e){
            std::cout << "Error parsing csv file data [" << cell << "] : " << e.what() << std::endl;
        }
    }

    return {graph, graphAdj};
}

std::pair<std::unordered_map<uint16_t, Vertex*>, std::vector<std::vector<double>>> GraphLoader::loadExtraFullGraph(const std::string &fileName) {

    std::unordered_map<uint16_t, Vertex*> graph;

    std::string substr = fileName.substr(fileName.find('_') + 1, fileName.find('.') - fileName.find('_') - 1);
    int nodeNumber = std::stoi(substr);
    std::vector<std::vector<double>> graphAdj(nodeNumber, std::vector<double>(nodeNumber, std::numeric_limits<double>::infinity()));

    std::string path = "../data/Extra_Fully_Connected_Graphs/" + fileName + ".csv";
    std::string geo = "../data/Extra_Fully_Connected_Graphs/nodes.csv";

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file at " << path << std::endl;
        return {};
    }

    std::string line, cell;

    std::ifstream nodes(geo);
    getline(nodes, line);
    int nodeCount = 0;
    while(getline(nodes, line) && nodeCount != nodeNumber ){
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

            nodeCount++;

        }catch (const std::invalid_argument& e){
            std::cout << "Error parsing csv file data [" << cell << "] : " << e.what() << std::endl;
        }
    }


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

        graphAdj[src][dest] = weight;
        graphAdj[dest][src] = weight;
    }

    file.close();
    return {graph, graphAdj};
}

