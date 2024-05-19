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

/**
 * @class GraphLoader
 * @brief Loads different types of graphs from files.
 */
class GraphLoader {
public:
    /**
     * @brief Loads a toy graph from a CSV file.
     * @param fileName The name of the CSV file (without extension).
     * @return A pair containing the graph and its adjacency matrix.
     */
    std::pair<std::unordered_map<uint16_t, Vertex*>, std::vector<std::vector<double>>> loadToyGraph(const std::string& fileName);

    /**
     * @brief Loads a real-world graph from CSV files.
     * @param fileName The name of the directory containing the CSV files.
     * @return A pair containing the graph and its adjacency matrix.
     */
    std::pair<std::unordered_map<uint16_t, Vertex*>, std::vector<std::vector<double>>> loadRealGraph(const std::string& fileName);

    /**
     * @brief Loads a fully connected graph from a CSV file.
     * @param fileName The name of the CSV file (without extension).
     * @return A pair containing the graph and its adjacency matrix.
     */
    std::pair<std::unordered_map<uint16_t, Vertex*>, std::vector<std::vector<double>>> loadExtraFullGraph(const std::string& fileName);

private:
    /**
     * @brief Parses a string into a double.
     * @param str The string to parse.
     * @return The parsed double.
     */
    double parseDouble(const std::string& str);
};

#endif // GRAPH_LOADER_H
