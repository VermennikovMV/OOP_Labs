#include "../include/solve_func.h"
#include <cmath>
#include <algorithm>

using namespace std;

double PolygonArea(const vector<pair<double, double>> &vertices)
{
    double area = 0;
    size_t n = vertices.size();
    for (size_t i = 0; i < n; ++i)
    {
        double x1 = vertices[i].first;
        double y1 = vertices[i].second;
        double x2 = vertices[(i + 1) % n].first;
        double y2 = vertices[(i + 1) % n].second;
        area += (x1 * y2 - x2 * y1);
    }
    return abs(area) / 2.0;
}

pair<double, double> PolygonCenter(const vector<pair<double, double>> &vertices)
{
    double cx = 0;
    double cy = 0;
    double area = PolygonArea(vertices);
    size_t n = vertices.size();
    for (size_t i = 0; i < n; ++i)
    {
        double xi = vertices[i].first;
        double yi = vertices[i].second;
        double xi1 = vertices[(i + 1) % n].first;
        double yi1 = vertices[(i + 1) % n].second;
        double cross = xi * yi1 - xi1 * yi;
        cx += (xi + xi1) * cross;
        cy += (yi + yi1) * cross;
    }
    double factor = 1 / (6 * area);
    cx *= factor;
    cy *= factor;
    return {cx, cy};
}

// Реализация класса Trapezoid

Trapezoid::Trapezoid() : vertices(4) {}

Trapezoid::Trapezoid(const vector<pair<double, double>> &vertices) : vertices(vertices) {}

Trapezoid::Trapezoid(const Trapezoid &other) : vertices(other.vertices) {}

Trapezoid::Trapezoid(Trapezoid &&other) noexcept : vertices(move(other.vertices)) {}

Trapezoid &Trapezoid::operator=(const Trapezoid &other)
{
    if (this != &other)
    {
        vertices = other.vertices;
    }
    return *this;
}

Trapezoid &Trapezoid::operator=(Trapezoid &&other) noexcept
{
    if (this != &other)
    {
        vertices = move(other.vertices);
    }
    return *this;
}

bool Trapezoid::operator==(const Trapezoid &other) const
{
    return vertices == other.vertices;
}

pair<double, double> Trapezoid::Center() const
{
    return PolygonCenter(vertices);
}

void Trapezoid::Print(ostream &os) const
{
    os << "Trapezoid vertices: ";
    for (const auto &vertex : vertices)
    {
        os << "(" << vertex.first << ", " << vertex.second << ") ";
    }
}

void Trapezoid::Read(istream &is)
{
    vertices.resize(4);
    cout << "Введите 4 вершины (x y): ";
    for (auto &vertex : vertices)
    {
        is >> vertex.first >> vertex.second;
    }
}

Trapezoid::operator double() const
{
    return PolygonArea(vertices);
}

// Реализация класса Rhombus

Rhombus::Rhombus() : vertices(4) {}

Rhombus::Rhombus(const vector<pair<double, double>> &vertices) : vertices(vertices) {}

Rhombus::Rhombus(const Rhombus &other) : vertices(other.vertices) {}

Rhombus::Rhombus(Rhombus &&other) noexcept : vertices(move(other.vertices)) {}

Rhombus &Rhombus::operator=(const Rhombus &other)
{
    if (this != &other)
    {
        vertices = other.vertices;
    }
    return *this;
}

Rhombus &Rhombus::operator=(Rhombus &&other) noexcept
{
    if (this != &other)
    {
        vertices = move(other.vertices);
    }
    return *this;
}

bool Rhombus::operator==(const Rhombus &other) const
{
    return vertices == other.vertices;
}

pair<double, double> Rhombus::Center() const
{
    return PolygonCenter(vertices);
}

void Rhombus::Print(ostream &os) const
{
    os << "Rhombus vertices: ";
    for (const auto &vertex : vertices)
    {
        os << "(" << vertex.first << ", " << vertex.second << ") ";
    }
}

void Rhombus::Read(istream &is)
{
    vertices.resize(4);
    cout << "Введите 4 вершины (x y): ";
    for (auto &vertex : vertices)
    {
        is >> vertex.first >> vertex.second;
    }
}

Rhombus::operator double() const
{
    return PolygonArea(vertices);
}

// Реализация класса Pentagon

Pentagon::Pentagon() : vertices(5) {}

Pentagon::Pentagon(const vector<pair<double, double>> &vertices) : vertices(vertices) {}

Pentagon::Pentagon(const Pentagon &other) : vertices(other.vertices) {}

Pentagon::Pentagon(Pentagon &&other) noexcept : vertices(move(other.vertices)) {}

Pentagon &Pentagon::operator=(const Pentagon &other)
{
    if (this != &other)
    {
        vertices = other.vertices;
    }
    return *this;
}

Pentagon &Pentagon::operator=(Pentagon &&other) noexcept
{
    if (this != &other)
    {
        vertices = move(other.vertices);
    }
    return *this;
}

bool Pentagon::operator==(const Pentagon &other) const
{
    return vertices == other.vertices;
}

pair<double, double> Pentagon::Center() const
{
    return PolygonCenter(vertices);
}

void Pentagon::Print(ostream &os) const
{
    os << "Pentagon vertices: ";
    for (const auto &vertex : vertices)
    {
        os << "(" << vertex.first << ", " << vertex.second << ") ";
    }
}

void Pentagon::Read(istream &is)
{
    vertices.resize(5);
    cout << "Введите 5 вершин (x y): ";
    for (auto &vertex : vertices)
    {
        is >> vertex.first >> vertex.second;
    }
}

Pentagon::operator double() const
{
    return PolygonArea(vertices);
}
