#include "../include/pentagon.h"
#include "../include/geometry_utils.h"
#include <iostream>
using namespace std;

Pentagon::Pentagon() : vertices(5) {}

Pentagon::Pentagon(const vector<pair<double,double>> &vertices) : vertices(vertices) {}

Pentagon::Pentagon(const Pentagon &other) : vertices(other.vertices) {}

Pentagon::Pentagon(Pentagon &&other) noexcept : vertices(std::move(other.vertices)) {}

Pentagon &Pentagon::operator=(const Pentagon &other) {
    if (this != &other) {
        vertices = other.vertices;
    }
    return *this;
}

Pentagon &Pentagon::operator=(Pentagon &&other) noexcept {
    if (this != &other) {
        vertices = move(other.vertices);
    }
    return *this;
}

bool Pentagon::operator==(const Pentagon &other) const {
    return vertices == other.vertices;
}

pair<double,double> Pentagon::Center() const {
    return PolygonCenter(vertices);
}

void Pentagon::Print(ostream &os) const {
    os << "Pentagon vertices: ";
    for (const auto &vertex : vertices) {
        os << "(" << vertex.first << ", " << vertex.second << ") ";
    }
}

void Pentagon::Read(istream &is) {
    vertices.resize(5);
    cout << "Введите 5 вершин (x y): ";
    for (auto &vertex : vertices) {
        is >> vertex.first >> vertex.second;
    }
}

Pentagon::operator double() const {
    return PolygonArea(vertices);
}
