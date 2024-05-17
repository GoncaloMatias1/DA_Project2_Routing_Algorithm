//
// Created by admin1 on 16-05-2024.
//

#ifndef ROUTE_X86_EDGE_H
#define ROUTE_X86_EDGE_H

class Vertex;
class Edge{
private:
    double weight;
    Vertex* destination;
    Vertex* origin;
public:
    Edge(double weight_, Vertex* origin ,Vertex* destination_);
    ~Edge();

    double getWeight() const;
    void setWeight(double newWeight);

    Vertex* getDestination() const;
    void setDestination(Vertex* newDest);

    Vertex* getOrigin() const;
    void setOrigin(Vertex* newOrigin);

};

#endif //ROUTE_X86_EDGE_H
