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
struct Coordinate {
    double latitude;
    double longitude;
};

// Vertex data structure to hold a specific vertex
class Vertex{
private:
    uint16_t vertexId;
    std::vector<Edge*> adj;
    Coordinate coordinates = {std::numeric_limits<double>::infinity(),std::numeric_limits<double>::infinity()};

    Vertex* path;
    Vertex* child; // used in prims

    double distance = std::numeric_limits<double>::infinity();

    bool visited = false;

    friend class MutablePriorityQueue<Vertex>;
protected:
    int queueIndex = 0;
public:
    Vertex(uint16_t id);
    Vertex(uint16_t id, std::vector<Edge*> adj, Coordinate coo);
    ~Vertex();

    // Member functions
    Coordinate getCoordinates() const;
    void setCoordinates(double latitude, double longitude);
    void setCoordinates(Coordinate newCoo);

    std::vector<Edge*> getAdj() const;
    void addEdge(Edge* newEdge);
    void setAdj(const std::vector<Edge*> adj);

    bool isVisited() const;
    void setVisited(bool visited);

    uint16_t getId() const;

    Vertex* getPath() const;
    void setPath(Vertex* pred);

    Vertex* getChild() const;
    void setChild(Vertex* child_);

    double getDistance() const;
    void setDistance(double newDistance);



    bool operator<(const Vertex& other);

};

#endif //ROUTE_X86_VERTEX_H
