//
// Created by admin1 on 16-05-2024.
//
#include "Vertex.h"

Vertex::Vertex(uint16_t id) {
    this->vertexId = id;
    this->adj.clear();
    this->visited = false;
}

Vertex::Vertex(uint16_t id, std::vector<Edge *> adj_, Coordinate coo) {
    this->vertexId = id;
    this->adj = adj_;
    this->coordinates = coo;
}

Vertex::~Vertex() {
    for(Edge* edge: this->adj){
        delete(edge);
    }
}

Coordinate Vertex::getCoordinates() const {
    return this->coordinates;
}

void Vertex::setCoordinates(double latitude, double longitude) {
    this->coordinates = {latitude, longitude};
}

void Vertex::setCoordinates(Coordinate newCoo) {
    this->coordinates = newCoo;
}

std::vector<Edge *> Vertex::getAdj() const {
    return this->adj;
}
void Vertex::addEdge(Edge *newEdge) {
    this->adj.push_back(newEdge);
}

void Vertex::setAdj(const std::vector<Edge *> adj_) {
    this->adj = adj_;
}

bool Vertex::isVisited() const {
    return this->visited;
}

void Vertex::setVisited(bool visited_) {
    this->visited = visited_;
}

uint16_t Vertex::getId() const {
    return this->vertexId;
}

Vertex *Vertex::getPath() const {
    return this->path;
}

void Vertex::setPath(Vertex *pred) {
    this->path = pred;
}

double Vertex::getDistance() const {
    return this->distance;
}

void Vertex::setDistance(double newDistance) {
    this->distance = newDistance;
}

bool Vertex::operator<(const Vertex &other) {
    return this->distance <= other.distance;
}

Vertex *Vertex::getChild() const {
    return this->child;
}

void Vertex::setChild(Vertex *child_) {
    this->child = child_;
}



