#ifndef GRAPH_LOADER_H
#define GRAPH_LOADER_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include <unordered_map>


class GraphLoader {
public:
    std::vector<std::vector<double>> loadGraphFromCSV(const std::string& filePath);

    std::vector<std::vector<double>> loadToyGraph(const std::string& fileName);
    std::pair<std::vector<std::vector<double>>, std::unordered_map<int, std::pair<double, double>>> loadLargeGraph(const std::string& fileName);
private:
    double parseDouble(const std::string& str);
};
#endif