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

    std::unordered_map<uint16_t, Vertex*> loadToyGraph(const std::string& fileName);

    std::unordered_map<uint16_t, Vertex*> loadRealGraph(const std::string& fileName);
    std::unordered_map<uint16_t, Vertex*> loadExtraFullGraph(const std::string& fileName);

private:
    double parseDouble(const std::string& str);
};
#endif