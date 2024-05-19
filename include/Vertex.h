//
// Created by admin1 on 16-05-2024.
//

#ifndef ROUTE_X86_VERTEX_H
#define ROUTE_X86_VERTEX_H

#include "Edge.h"
#include <vector>
#include <limits>
#include <cinttypes>
#include "MutablePriorityQueue.h"

/**
 * @struct Coordinate
 * @brief Represents a geographical coordinate with latitude and longitude.
 */
struct Coordinate {
    double latitude; /**< Latitude of the coordinate. */
    double longitude; /**< Longitude of the coordinate. */
};

/**
 * @class Vertex
 * @brief Represents a vertex in the graph.
 */
class Vertex {
private:
    uint16_t vertexId; /**< The ID of the vertex. */
    std::vector<Edge*> adj; /**< The adjacency list of edges. */
    Coordinate coordinates = {std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()}; /**< Coordinates of the vertex. */

    Vertex* path; /**< The previous vertex in the path. */
    Vertex* child; /**< Used in Prim's algorithm to store the child vertex. */

    double distance = std::numeric_limits<double>::infinity(); /**< The distance from the source vertex. */

    bool visited = false; /**< Indicates if the vertex has been visited. */

    friend class MutablePriorityQueue<Vertex>;

protected:
    int queueIndex = 0; /**< The index of the vertex in the priority queue. */

public:
    /**
     * @brief Constructs a vertex with the given ID.
     * @param id The ID of the vertex.
     */
    Vertex(uint16_t id);

    /**
     * @brief Constructs a vertex with the given ID, adjacency list, and coordinates.
     * @param id The ID of the vertex.
     * @param adj The adjacency list of edges.
     * @param coo The coordinates of the vertex.
     */
    Vertex(uint16_t id, std::vector<Edge*> adj, Coordinate coo);

    /**
     * @brief Destroys the vertex and its edges.
     */
    ~Vertex();

    /**
     * @brief Gets the coordinates of the vertex.
     * @return The coordinates of the vertex.
     */
    Coordinate getCoordinates() const;

    /**
     * @brief Sets the coordinates of the vertex.
     * @param latitude The latitude to set.
     * @param longitude The longitude to set.
     */
    void setCoordinates(double latitude, double longitude);

    /**
     * @brief Sets the coordinates of the vertex.
     * @param newCoo The new coordinates to set.
     */
    void setCoordinates(Coordinate newCoo);

    /**
     * @brief Gets the adjacency list of the vertex.
     * @return The adjacency list of edges.
     */
    std::vector<Edge*> getAdj() const;

    /**
     * @brief Adds an edge to the adjacency list.
     * @param newEdge The edge to add.
     */
    void addEdge(Edge* newEdge);

    /**
     * @brief Sets the adjacency list of the vertex.
     * @param adj_ The new adjacency list to set.
     */
    void setAdj(const std::vector<Edge*> adj_);

    /**
     * @brief Checks if the vertex has been visited.
     * @return True if the vertex has been visited, false otherwise.
     */
    bool isVisited() const;

    /**
     * @brief Sets the visited status of the vertex.
     * @param visited_ The visited status to set.
     */
    void setVisited(bool visited_);

    /**
     * @brief Gets the ID of the vertex.
     * @return The ID of the vertex.
     */
    uint16_t getId() const;

    /**
     * @brief Gets the previous vertex in the path.
     * @return The previous vertex in the path.
     */
    Vertex* getPath() const;

    /**
     * @brief Sets the previous vertex in the path.
     * @param pred The previous vertex to set.
     */
    void setPath(Vertex* pred);

    /**
     * @brief Gets the distance from the source vertex.
     * @return The distance from the source vertex.
     */
    double getDistance() const;

    /**
     * @brief Sets the distance from the source vertex.
     * @param newDistance The new distance to set.
     */
    void setDistance(double newDistance);

    /**
     * @brief Compares the distance of this vertex with another vertex.
     * @param other The other vertex to compare with.
     * @return True if this vertex has a smaller or equal distance, false otherwise.
     */
    bool operator<(const Vertex& other);

    /**
     * @brief Gets the child vertex (used in Prim's algorithm).
     * @return The child vertex.
     */
    Vertex* getChild() const;

    /**
     * @brief Sets the child vertex (used in Prim's algorithm).
     * @param child_ The child vertex to set.
     */
    void setChild(Vertex* child_);
};

#endif //ROUTE_X86_VERTEX_H
