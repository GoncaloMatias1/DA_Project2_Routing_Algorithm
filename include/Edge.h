//
// Created by admin1 on 16-05-2024.
//

#ifndef ROUTE_X86_EDGE_H
#define ROUTE_X86_EDGE_H

/**
 * @class Edge
 * @brief Represents an edge in a graph.
 *
 * This class represents an edge in a graph with a weight, origin, and destination vertices.
 */
class Vertex;
class Edge {
private:
    double weight; /**< The weight of the edge. */
    Vertex* destination; /**< The destination vertex of the edge. */
    Vertex* origin; /**< The origin vertex of the edge. */

public:
    /**
     * @brief Constructs an edge with the given weight, origin, and destination.
     *
     * @param weight_ The weight of the edge.
     * @param origin The origin vertex of the edge.
     * @param destination The destination vertex of the edge.
     */
    Edge(double weight_, Vertex* origin, Vertex* destination_);

    /**
     * @brief Destructor for the Edge class.
     */
    ~Edge();

    /**
     * @brief Gets the weight of the edge.
     *
     * @return The weight of the edge.
     */
    double getWeight() const;

    /**
     * @brief Sets a new weight for the edge.
     *
     * @param newWeight The new weight to set.
     */
    void setWeight(double newWeight);

    /**
     * @brief Gets the destination vertex of the edge.
     *
     * @return The destination vertex of the edge.
     */
    Vertex* getDestination() const;

    /**
     * @brief Sets a new destination vertex for the edge.
     *
     * @param newDest The new destination vertex to set.
     */
    void setDestination(Vertex* newDest);

    /**
     * @brief Gets the origin vertex of the edge.
     *
     * @return The origin vertex of the edge.
     */
    Vertex* getOrigin() const;

    /**
     * @brief Sets a new origin vertex for the edge.
     *
     * @param newOrigin The new origin vertex to set.
     */
    void setOrigin(Vertex* newOrigin);
};

#endif //ROUTE_X86_EDGE_H
