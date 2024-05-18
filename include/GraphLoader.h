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
#include "GraphController.h"
#include "Edge.h"


class GraphLoader {
public:

    std::pair<std::unordered_map<uint16_t, Vertex*>, std::vector<std::vector<double>>> loadToyGraph(const std::string& fileName);

    std::pair<std::unordered_map<uint16_t, Vertex*>, std::vector<std::vector<double>>> loadRealGraph(const std::string& fileName);
    std::pair<std::unordered_map<uint16_t, Vertex*>, std::vector<std::vector<double>>> loadExtraFullGraph(const std::string& fileName);

private:
    double parseDouble(const std::string& str);
};
#endif