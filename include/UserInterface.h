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

/**
 * @class UserInterface
 * @brief Manages the user interface for the ROUTE_X86 application.
 */
class UserInterface {
private:
    GraphController* controller; /**< The graph controller used for executing algorithms. */
    GraphLoader* graphLoader; /**< The graph loader used for loading graphs from files. */

public:
    /**
     * @brief Constructs a UserInterface object.
     */
    UserInterface();

    /**
     * @brief Boots the application and displays the main menu.
     */
    void bootload();

    /**
     * @brief Loads a toy graph from a file.
     * @return The filename of the loaded toy graph.
     */
    const std::string& getToyGraph();

    /**
     * @brief Loads a real-world graph from a file.
     * @return The filename of the loaded real-world graph.
     */
    const std::string& getRealGraph();

    /**
     * @brief Loads an extra fully connected graph from a file.
     * @return The filename of the loaded extra fully connected graph.
     */
    const std::string& getExtraFullGraph();

    /**
     * @brief Displays the main menu of the application.
     */
    void displayMainMenu();

    /**
     * @brief Displays the menu for loading graphs.
     */
    void displayLoadGraphMenu();

    /**
     * @brief Displays the result of the backtracking TSP algorithm.
     */
    void displayBacktrackingResult();

    /**
     * @brief Displays a farewell message.
     */
    void displayFarewell();

    /**
     * @brief Displays the result of the triangular approximation TSP algorithm.
     */
    void displayTriangularApproximationResult();

    /**
     * @brief Displays the result of the cluster approximation TSP algorithm.
     */
    void displayClusterApproximationResult();

    /**
     * @brief Displays the result of the TSP algorithm for disconnected graphs.
     */
    void displayTSPForDisconnectedGraphResult();
};

#endif //ROUTE_X86_USERINTERFACE_H
