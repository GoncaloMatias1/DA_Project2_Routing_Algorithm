//
// Created by admin1 on 16-05-2024.
//
#include "Edge.h"

Edge::Edge(double weight_, Vertex* origin_,Vertex *destination_) {
    this->weight = weight_;
    this->origin = origin_;
    this->destination = destination_;
}

Edge::~Edge() {
    delete(destination);
}

double Edge::getWeight() const {
    return this->weight;
}

void Edge::setWeight(double newWeight) {
    this->weight = newWeight;
}

Vertex *Edge::getDestination() const {
    return this->destination;
}

void Edge::setDestination(Vertex *newDest) {
    this->destination = newDest;
}

Vertex *Edge::getOrigin() const {
    return this->origin;
}

void Edge::setOrigin(Vertex *newOrigin) {
    this->origin = newOrigin;
}


