#pragma once
#include <vector>
#include <string>

class GraphLoader {
public:
    std::vector<std::vector<double>> loadGraphFromCSV(const std::string& filePath);
private:
    double parseDouble(const std::string& str);
};
