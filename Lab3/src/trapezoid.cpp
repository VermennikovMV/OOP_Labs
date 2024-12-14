#include "../include/trapezoid.h"
#include "../include/geometry_utils.h"
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

Trapezoid::Trapezoid() : vertices(4) {}

Trapezoid::Trapezoid(const vector<pair<double, double>> &vertices) : vertices(vertices) {}

Trapezoid::Trapezoid(const Trapezoid &other) : vertices(other.vertices) {}

Trapezoid::Trapezoid(Trapezoid &&other) noexcept : vertices(std::move(other.vertices)) {}

Trapezoid &Trapezoid::operator=(const Trapezoid &other) {
    if (this != &other) {
        vertices = other.vertices;
    }
    return *this;
}

Trapezoid &Trapezoid::operator=(Trapezoid &&other) noexcept {
    if (this != &other) {
        vertices = move(other.vertices);
    }
    return *this;
}

bool Trapezoid::operator==(const Trapezoid &other) const {
    return vertices == other.vertices;
}

pair<double, double> Trapezoid::Center() const {
    return PolygonCenter(vertices);
}

void Trapezoid::Print(ostream &os) const {
    os << "Trapezoid vertices: ";
    for (const auto &vertex : vertices) {
        os << "(" << vertex.first << ", " << vertex.second << ") ";
    }
}

void Trapezoid::Read(istream &is) {
    vertices.resize(4);
    cout << "Введите 4 вершины (x y): ";
    for (auto &vertex : vertices) {
        is >> vertex.first >> vertex.second;
    }
}

Trapezoid::operator double() const {
    return PolygonArea(vertices);
}
