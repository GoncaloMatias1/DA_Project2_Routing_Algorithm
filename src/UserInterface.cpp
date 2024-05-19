#include "UserInterface.h"

UserInterface::UserInterface() {
    this->graphLoader = new GraphLoader();
    this->controller = nullptr;
}

void UserInterface::bootload() {
    this->displayMainMenu();
}

void UserInterface::displayMainMenu() {
    std::string choice;
    while (true) {
        std::cout << "1. Load Graph\n";
        std::cout << "2. Execute TSP Backtracking\n";
        std::cout << "3. Execute Triangular Approximation\n";
        std::cout << "4. Execute Cluster Approximation\n";
        std::cout << "5. Execute TSP for Disconnected Graph\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice.length() != 1 || choice[0] < '1' || choice[0] > '6') {
            std::cout << "Invalid key!\n";
            continue;
        }

        switch (choice[0] - '0') {
            case 1:
                this->displayLoadGraphMenu();
                break;
            case 2:
                this->displayBacktrackingResult();
                break;
            case 3:
                this->displayTriangularApproximationResult();
                break;
            case 4:
                this->displayClusterApproximationResult();
                break;
            case 5:
                this->displayTSPForDisconnectedGraphResult();
                break;
            case 6:
                this->displayFarewell();
                return;
            default:
                std::cout << "Invalid key!\n";
        }
    }
}

void UserInterface::displayLoadGraphMenu() {
    std::string choice;
    while (true) {
        std::cout << "1. Load Toy Graph\n";
        std::cout << "2. Load Real World Graph\n";
        std::cout << "3. Load Extra Fully Connected Graphs\n";
        std::cout << "4. Back to Main Menu\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice.length() != 1 || choice[0] < '1' || choice[0] > '4') {
            std::cout << "Invalid key!\n";
            continue;
        }

        switch (choice[0] - '0') {
            case 1:
                this->getToyGraph();
                return;
            case 2:
                this->getRealGraph();
                return;
            case 3:
                this->getExtraFullGraph();
                return;
            case 4:
                return;
            default:
                std::cout << "Invalid key!\n";
        }
    }
}

void UserInterface::displayTriangularApproximationResult() {
    if (this->controller == nullptr) {
        std::cout << "No graph loaded. Please load a graph first.\n";
        this->displayLoadGraphMenu();
    }
    auto result = this->controller->triangleInequalityApp();
    std::cout << "The cost is " << result.first << std::endl;
    savePathToFile("triangular", result.second, result.first);
}

const std::string& UserInterface::getToyGraph() {
    static std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;
    this->filename_ = filename;
    auto pair = this->graphLoader->loadToyGraph(filename);
    this->controller = new GraphController(pair.first, pair.second);
    std::cout << "Graph loaded successfully.\n";
    return filename;
}

const std::string& UserInterface::getRealGraph() {
    static std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;
    this->filename_ = filename;
    auto pair = this->graphLoader->loadRealGraph(filename);
    this->controller = new GraphController(pair.first, pair.second);
    std::cout << "Graph loaded successfully.\n";
    return filename;
}

const std::string& UserInterface::getExtraFullGraph() {
    static std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;
    this->filename_ = filename;
    auto pair = this->graphLoader->loadExtraFullGraph(filename);
    this->controller = new GraphController(pair.first, pair.second);
    std::cout << "Graph loaded successfully.\n";
    return filename;
}

void UserInterface::displayBacktrackingResult() {
    if (this->controller == nullptr) {
        std::cout << "No graph loaded. Please load a graph first.\n";
        this->displayLoadGraphMenu();
    }
    std::pair<double, std::vector<uint16_t>> path = controller->minHamiltonianCicle();
    std::cout << "For the given graph the minimum cost for a hamiltonian cycle is " << path.first << std::endl;
    savePathToFile("backtracking", path.second, path.first);
}

void UserInterface::displayClusterApproximationResult() {
    if (this->controller == nullptr) {
        std::cout << "No graph loaded. Please load a graph first.\n";
        this->displayLoadGraphMenu();
    }
    std::pair<double, std::vector<uint16_t>> path = controller->clusterHeuristic();
    std::cout << "For the given graph the cluster approximation is " << path.first << std::endl;
    savePathToFile("cluster", path.second, path.first);
}

void UserInterface::displayTSPForDisconnectedGraphResult() {
    if (this->controller == nullptr) {
        std::cout << "No graph loaded. Please load a graph first.\n";
        this->displayLoadGraphMenu();
    }
    uint16_t startNode;
    std::cout << "Enter starting node: ";
    std::cin >> startNode;
    auto result = this->controller->solveTSPForDisconnectedGraph(startNode);
    if (result.first == std::numeric_limits<double>::infinity()) {
        std::cout << "No path exists that visits all nodes and returns to the origin.\n";
    } else {
        std::cout << "The cost is " << result.first << std::endl;
        savePathToFile("disconnected", result.second, result.first);
    }
}

void UserInterface::displayFarewell() {
    const std::string RESET_COLOR = "\033[0m";
    const std::string BOLD = "\033[1m";
    const std::string GREEN_COLOR = "\033[32m";

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

void UserInterface::savePathToFile(std::string functionName, std::vector<uint16_t> path, double cost) {
    std::string dirName = "../output";

    if (!fs::exists(dirName)) {
        std::cout << "Creating output directory...\n";
        if (!fs::create_directory(dirName)) {
            std::cout << "Couldn't create directory, please manually create 'output' directory" << std::endl;
        }
    }

    std::ofstream file("../output/" + functionName + "_" + this->filename_ + ".txt");

    if (file.is_open()) {
        file << "Function Name: " << functionName << std::endl;
        file << "Path: ";
        for (uint16_t node : path) {
            file << node << " ";
        }
        file << std::endl;
        file << "Cost: " << cost << std::endl;
        file << "---------------------" << std::endl;

        file.close();
        std::cout << "Path data saved to file successfully." << std::endl;
    } else {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
    }
}
