//
// Created by admin1 on 10-05-2024.
//

#include "UserInterface.h"

UserInterface::UserInterface() {
    this->graphLoader = new GraphLoader();
}

void UserInterface::bootload() {
    this->displayMainMenu();
}


void UserInterface::displayMainMenu() {
    char choice;
    std::cout << "1. Load Graph\n";
    std::cout << "2. Execute TSP Backtracking\n";
    std::cout << "3. Exit\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;
    switch (choice - '0') {
        case 1:
            this->getGraph();
            displayMainMenu();
        case 2:
            //this->displayBacktrackingResult();
            displayMainMenu();
        case 3:
            this->displayFarewell();
            break;
        default:
            std::cout << "Invalid key!\n";
            displayMainMenu();
    }
}

const std::string & UserInterface::getGraph() {
    std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;
    this->controller = new GraphController(this->graphLoader->loadToyGraph(filename));
    std::cout << "Graph loaded successfully.\n";
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





