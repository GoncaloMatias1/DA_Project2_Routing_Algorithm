//
// Created by admin1 on 10-05-2024.
//

#ifndef ROUTE_X86_USERINTERFACE_H
#define ROUTE_X86_USERINTERFACE_H

#include "GraphController.h"
#include "GraphLoader.h"
#include <string>
#include <iostream>
#include <iomanip>

class UserInterface{
private:
    GraphController* controller;
    GraphLoader* graphLoader;
public:
    UserInterface();
    void bootload();

    const std::string& getToyGraph();
    const std::string& getRealGraph();
    const std::string& getExtraFullGraph();

    void displayMainMenu();
    void displayLoadGraphMenu();
    void displayBacktrackingResult();
    void displayFarewell();
    void displayTriangularApproximationResult();
    void displayClusterApproximationResult();
};

#endif //ROUTE_X86_USERINTERFACE_H
