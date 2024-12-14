#pragma once
#include "figure.h"
#include "geometry_utils.h"
#include <vector>
#include <memory>

template <Scalar T>
class Rhombus : public Figure<T> {
private:
    std::vector<std::unique_ptr<Point<T>>> vertices;
public:
    Rhombus();
    Rhombus(const std::vector<Point<T>> &points);
    Rhombus(const Rhombus<T> &other);
    Rhombus(Rhombus<T> &&other) noexcept;

    Rhombus<T> &operator=(const Rhombus<T> &other);
    Rhombus<T> &operator=(Rhombus<T> &&other) noexcept;
    bool operator==(const Rhombus<T> &other) const;

    std::unique_ptr<Point<double>> Center() const override;
    void Print(std::ostream &os) const override;
    void Read(std::istream &is) override;
    operator double() const override;
};

// Реализация методов Rhombus

template <Scalar T>
Rhombus<T>::Rhombus() {}

template <Scalar T>
Rhombus<T>::Rhombus(const std::vector<Point<T>> &points) {
    for (const auto &pt : points) {
        vertices.push_back(std::make_unique<Point<T>>(pt.x, pt.y));
    }
}

template <Scalar T>
Rhombus<T>::Rhombus(const Rhombus<T> &other) {
    for (const auto &pt : other.vertices) {
        vertices.push_back(std::make_unique<Point<T>>(pt->x, pt->y));
    }
}

template <Scalar T>
Rhombus<T>::Rhombus(Rhombus<T> &&other) noexcept : vertices(std::move(other.vertices)) {}

template <Scalar T>
Rhombus<T> &Rhombus<T>::operator=(const Rhombus<T> &other) {
    if (this != &other) {
        vertices.clear();
        for (const auto &pt : other.vertices) {
            vertices.push_back(std::make_unique<Point<T>>(pt->x, pt->y));
        }
    }
    return *this;
}

template <Scalar T>
Rhombus<T> &Rhombus<T>::operator=(Rhombus<T> &&other) noexcept {
    if (this != &other) {
        vertices = std::move(other.vertices);
    }
    return *this;
}

template <Scalar T>
bool Rhombus<T>::operator==(const Rhombus<T> &other) const {
    if (vertices.size() != other.vertices.size()) {
        return false;
    }
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (vertices[i]->x != other.vertices[i]->x || vertices[i]->y != other.vertices[i]->y) {
            return false;
        }
    }
    return true;
}

template <Scalar T>
std::unique_ptr<Point<double>> Rhombus<T>::Center() const {
    return PolygonCenter(vertices);
}

template <Scalar T>
void Rhombus<T>::Print(std::ostream &os) const {
    os << "Rhombus vertices: ";
    for (const auto &vertex : vertices) {
        os << *vertex << " ";
    }
    os << std::endl;
}

template <Scalar T>
void Rhombus<T>::Read(std::istream &is) {
    vertices.clear();
    std::cout << "Введите 4 вершины (x y): ";
    for (int i = 0; i < 4; ++i) {
        T x, y;
        is >> x >> y;
        vertices.push_back(std::make_unique<Point<T>>(x, y));
    }
}

template <Scalar T>
Rhombus<T>::operator double() const {
    return PolygonArea(vertices);
}
