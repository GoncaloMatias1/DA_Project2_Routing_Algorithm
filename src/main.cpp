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
                std::cout << "Graph loaded successfully.\n";
                break;
            case 2:
                if (loader.isGraphLoaded()) {
                    std::cout << "Shortest Tour Cost: " << tsp.findShortestTour(loader.getGraph()) << std::endl;
                } else {
                    std::cout << "Please load a graph first.\n";
                }
                break;
            case 3:
                std::cout << "Exiting program.\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (true);

    return 0;
}
