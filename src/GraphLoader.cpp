#include "GraphLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>

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
