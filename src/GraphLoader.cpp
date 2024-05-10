#include "GraphLoader.h"


std::vector<std::vector<double>> GraphLoader::loadGraphFromCSV(const std::string& filePath) {
    std::vector<std::vector<double>> graph;
    std::ifstream file(filePath);
    std::string line, cell;

    if (!file.is_open()) {
        std::cerr << "Failed to open file at " << filePath << std::endl;
        return graph;
    }

    int maxSize = 0;
    while (getline(file, line)) {
        std::istringstream lineStream(line);
        int src, dest;
        getline(lineStream, cell, ',');
        src = stoi(cell);
        getline(lineStream, cell, ',');
        dest = stoi(cell);

        int maxIndex = std::max(src, dest);
        if (maxIndex > maxSize) {
            maxSize = maxIndex;
        }
    }

    graph.resize(maxSize + 1, std::vector<double>(maxSize + 1, std::numeric_limits<double>::infinity()));
    file.clear();
    file.seekg(0);

    while (getline(file, line)) {
        std::istringstream lineStream(line);
        int src, dest;
        double weight;

        getline(lineStream, cell, ',');
        src = stoi(cell);
        getline(lineStream, cell, ',');
        dest = stoi(cell);
        getline(lineStream, cell);
        weight = parseDouble(cell);

        graph[src][dest] = weight;
        graph[dest][src] = weight;
    }

    file.close();
    return graph;
}

double GraphLoader::parseDouble(const std::string& str) {
    return std::stod(str);
}

std::vector<std::vector<double>> GraphLoader::loadToyGraph(const std::string &fileName) {
    std::vector<std::vector<double>> graph;
    std::string path = "../data/Toy-Graphs/" + fileName + ".csv";
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file at " << path << std::endl;
        return graph;
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

    graph.resize(maxSize + 1, std::vector<double>(maxSize + 1, std::numeric_limits<double>::infinity()));

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


        graph[src][dest] = weight;
        graph[dest][src] = weight;
    }

    file.close();
    return graph;
}

std::pair<std::vector<std::vector<double>>, std::unordered_map<int, std::pair<double, double>>> GraphLoader::loadLargeGraph(const std::string &fileName) {
    std::vector<std::vector<double>> graph;
    std::unordered_map<int, std::pair<double, double>> coords;
    uint16_t graphSize = 0;

    std::string path = "../data/Real_world_Graphs/" + fileName + "/";
    std::string edges = path + "edges.csv";
    std::string nodes = path + "nodes.csv";

    std::ifstream file(nodes);
    std::ifstream file_(edges);

    if (!file.is_open()) {
        std::cerr << "Failed to open file at " << nodes << std::endl;
        return std::make_pair(graph, coords);
    }
    if (!file_.is_open()) {
        std::cerr << "Failed to open file at " << edges << std::endl;
        return std::make_pair(graph, coords);
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
            coords[id] = std::make_pair(longitude, latitude);
            graphSize++;
        }catch (const std::invalid_argument& e){
            std::cout << "Error parsing csv file data [" << cell << "] : " << e.what() << std::endl;
        }
    }

    graph.resize(graphSize + 1, std::vector<double>(graphSize + 1, std::numeric_limits<double>::infinity()));


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

            graph[src][dest] = weight;
            graph[dest][src] = weight;

        }catch (const std::invalid_argument& e){
            std::cout << "Error parsing csv file data [" << cell << "] : " << e.what() << std::endl;
        }
    }

    return std::make_pair(graph, coords);
}
