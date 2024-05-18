//
// Created by admin1 on 10-05-2024.
//
#include "UserInterface.h"
#include "TriangularApproximation.h"

UserInterface::UserInterface() {
    this->graphLoader = new GraphLoader();
    this->controller = nullptr;
}

void UserInterface::bootload() {
    this->displayMainMenu();
}


void UserInterface::displayMainMenu() {
    char choice;
    std::cout << "1. Load Graph\n";
    std::cout << "2. Execute TSP Backtracking\n";
    std::cout << "3. Execute Triangular Approximation\n";
    std::cout << "4. Execute Cluster Approximation\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;
    switch (choice - '0') {
        case 1:
            this->displayLoadGraphMenu();
            displayMainMenu();
            return;
        case 2:
            this->displayBacktrackingResult();
            displayMainMenu();
            return;
        case 3:
            this->displayTriangularApproximationResult();
            displayMainMenu();
            return;
        case 4:
            this->displayClusterApproximationResult();
            return;
        case 5:
            this->displayFarewell();
            return;
        default:
            std::cout << "Invalid key!\n";
            displayMainMenu();
    }
}

void UserInterface::displayLoadGraphMenu() {
    std::string choice;
    std::cout << "1. Load Toy Graph\n";
    std::cout << "2. Load Real World Graph\n";
    std::cout << "3. Load Extra Fully Connected Graphs\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;
    try{
        std::stoi(choice);
    }catch (const std::invalid_argument& e){
        std::cout << "Invalid choice!\n";
        displayLoadGraphMenu();
    }
    switch (std::stoi(choice)) {
        case 1:
            this->getToyGraph();
            displayMainMenu();
            return;
        case 2:
            this->getRealGraph();
            displayMainMenu();
            return;
        case 3:
            this->getExtraFullGraph();
            displayMainMenu();
            return;
        case 4:
            this->displayMainMenu();
            return;
        default:
            std::cout << "Invalid key!\n";
            displayLoadGraphMenu();
            return;
    }
}


void UserInterface::displayTriangularApproximationResult() {
    if(this->controller == nullptr) this->displayLoadGraphMenu();
    auto result = this->controller->triangleInequalityApp();
    std::cout << "The cost is "  << result.first << std::endl;
    std::cout << "With the following path: ";
    for(Vertex* vertex:result.second ){
        std::cout <<  vertex->getId() <<", ";
    }
    std::cout << std::endl;
}

const std::string & UserInterface::getToyGraph() {
    std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;
    auto pair = this->graphLoader->loadToyGraph(filename);
    this->controller = new GraphController(pair.first, pair.second);
    std::cout << "Graph loaded successfully.\n";

}
const std::string & UserInterface::getRealGraph() {
    std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;
    auto pair = this->graphLoader->loadRealGraph(filename);
    this->controller = new GraphController(pair.first, pair.second);
    std::cout << "Graph loaded successfully.\n";
}
const std::string & UserInterface::getExtraFullGraph() {

    std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;
    auto pair = this->graphLoader->loadExtraFullGraph(filename);
    this->controller = new GraphController(pair.first, pair.second);
    std::cout << "Graph loaded successfully.\n";

}

void UserInterface::displayBacktrackingResult() {
    if(this->controller == nullptr) this->displayLoadGraphMenu();
    std::pair<double, std::vector<uint16_t>> path = controller->minHamiltonianCicle();
    std::cout << "For the given graph the minimum cost for a hamiltonian cycle is " << path.first << std::endl;
    std::cout << "With the following path: ";
    for(uint16_t idx:path.second ){
        std::cout <<  idx <<", ";
    }
    std::cout << std::endl;
}

void UserInterface::displayClusterApproximationResult() {
    if(this->controller == nullptr) this->displayLoadGraphMenu();
    std::pair<double, std::vector<uint16_t>> path = controller->clusterHeuristic();
    std::cout << "For the given graph the cluster approximation is " << path.first << std::endl;
    std::cout << "With the following path: ";
    for(uint16_t idx:path.second ){
        std::cout <<  idx <<", ";
    }
    std::cout << std::endl;
}



void UserInterface::displayFarewell() {
    // Color codes for ANSI escape sequences
    const std::string RESET_COLOR = "\033[0m";
    const std::string BOLD = "\033[1m";
    const std::string GREEN_COLOR = "\033[32m";

    // Farewell message
    std::cout << GREEN_COLOR << BOLD;
    std::cout << std::setw(60) << " ____   ___  _   _ _____ _____    __  _____   __   " << std::endl;
    std::cout << std::setw(60) << "|  _ \\ / _ \\| | | |_   _| ____|   \\ \\/ ( _ ) / /_  " << std::endl;
    std::cout << std::setw(60) << "| |_) | | | | | | | | | |  _|      \\  // _ \\| '_ \\ " << std::endl;
    std::cout << std::setw(60) << "|  _ <| |_| | |_| | | | | |___     /  \\ (_) | (_) |" << std::endl;
    std::cout << std::setw(60) << "|_| \\_\\\\___/ \\___/  |_| |_____|___/_/\\_\\___/ \\___/ " << std::endl;
    std::cout << std::setw(60) << "                             |_____|               " << std::endl;
    std::cout << RESET_COLOR << std::endl;

    std::cout << BOLD;
    std::cout << std::setw(40) << "Thank you for using " << GREEN_COLOR << "ROUTE_X86" << RESET_COLOR << BOLD << "!" << std::endl;
    std::cout << std::setw(80) << "We specialize in Routing Algorithms for Ocean Shipping and Urban Deliveries." << std::endl;
    std::cout << std::setw(48) << "Have a safe journey ahead!" << RESET_COLOR << std::endl;
}







