#include "../include/rhombus.h"
#include "../include/geometry_utils.h"
#include <iostream>
using namespace std;

Rhombus::Rhombus() : vertices(4) {}

Rhombus::Rhombus(const vector<pair<double,double>> &vertices) : vertices(vertices) {}

Rhombus::Rhombus(const Rhombus &other) : vertices(other.vertices) {}

Rhombus::Rhombus(Rhombus &&other) noexcept : vertices(std::move(other.vertices)) {}

Rhombus &Rhombus::operator=(const Rhombus &other) {
    if (this != &other) {
        vertices = other.vertices;
    }
    return *this;
}

Rhombus &Rhombus::operator=(Rhombus &&other) noexcept {
    if (this != &other) {
        vertices = move(other.vertices);
    }
    return *this;
}

bool Rhombus::operator==(const Rhombus &other) const {
    return vertices == other.vertices;
}

pair<double,double> Rhombus::Center() const {
    return PolygonCenter(vertices);
}

void Rhombus::Print(ostream &os) const {
    os << "Rhombus vertices: ";
    for (const auto &vertex : vertices) {
        os << "(" << vertex.first << ", " << vertex.second << ") ";
    }
}

void Rhombus::Read(istream &is) {
    vertices.resize(4);
    cout << "Введите 4 вершины (x y): ";
    for (auto &vertex : vertices) {
        is >> vertex.first >> vertex.second;
    }
}

Rhombus::operator double() const {
    return PolygonArea(vertices);
}
