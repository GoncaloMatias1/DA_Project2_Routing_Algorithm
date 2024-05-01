#include <iostream>
#include "GraphLoader.h"
#include "TSPBacktracking.h"

int main() {
    GraphLoader loader;
    TSPBacktracking tsp;

    int choice;
    std::string filePath;

    do {
        std::cout << "1. Load Graph\n";
        std::cout << "2. Execute TSP Backtracking\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter file path: ";
                std::cin >> filePath;
                loader.loadGraphFromCSV(filePath);
                break;
            case 2:
                std::cout << "Shortest Tour Cost: " << tsp.findShortestTour(loader.getGraph()) << std::endl;
                break;
            case 3:
                return 0;
            default:
                std::cout << "Invalid choice." << std::endl;
        }
    } while (true);
}
