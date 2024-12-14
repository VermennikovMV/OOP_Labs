#pragma once
#include "figure.h"
#include "geometry_utils.h"
#include <vector>
#include <memory>

template <Scalar T>
class Pentagon : public Figure<T> {
private:
    std::vector<std::unique_ptr<Point<T>>> vertices;
public:
    Pentagon();
    Pentagon(const std::vector<Point<T>> &points);
    Pentagon(const Pentagon<T> &other);
    Pentagon(Pentagon<T> &&other) noexcept;

    Pentagon<T> &operator=(const Pentagon<T> &other);
    Pentagon<T> &operator=(Pentagon<T> &&other) noexcept;
    bool operator==(const Pentagon<T> &other) const;

    std::unique_ptr<Point<double>> Center() const override;
    void Print(std::ostream &os) const override;
    void Read(std::istream &is) override;
    operator double() const override;
};

// Реализация методов Pentagon

template <Scalar T>
Pentagon<T>::Pentagon() {}

template <Scalar T>
Pentagon<T>::Pentagon(const std::vector<Point<T>> &points) {
    for (const auto &pt : points) {
        vertices.push_back(std::make_unique<Point<T>>(pt.x, pt.y));
    }
}

template <Scalar T>
Pentagon<T>::Pentagon(const Pentagon<T> &other) {
    for (const auto &pt : other.vertices) {
        vertices.push_back(std::make_unique<Point<T>>(pt->x, pt->y));
    }
}

template <Scalar T>
Pentagon<T>::Pentagon(Pentagon<T> &&other) noexcept : vertices(std::move(other.vertices)) {}

template <Scalar T>
Pentagon<T> &Pentagon<T>::operator=(const Pentagon<T> &other) {
    if (this != &other) {
        vertices.clear();
        for (const auto &pt : other.vertices) {
            vertices.push_back(std::make_unique<Point<T>>(pt->x, pt->y));
        }
    }
    return *this;
}

template <Scalar T>
Pentagon<T> &Pentagon<T>::operator=(Pentagon<T> &&other) noexcept {
    if (this != &other) {
        vertices = std::move(other.vertices);
    }
    return *this;
}

template <Scalar T>
bool Pentagon<T>::operator==(const Pentagon<T> &other) const {
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
std::unique_ptr<Point<double>> Pentagon<T>::Center() const {
    return PolygonCenter(vertices);
}

template <Scalar T>
void Pentagon<T>::Print(std::ostream &os) const {
    os << "Pentagon vertices: ";
    for (const auto &vertex : vertices) {
        os << *vertex << " ";
    }
    os << std::endl;
}

template <Scalar T>
void Pentagon<T>::Read(std::istream &is) {
    vertices.clear();
    std::cout << "Введите 5 вершин (x y): ";
    for (int i = 0; i < 5; ++i) {
        T x, y;
        is >> x >> y;
        vertices.push_back(std::make_unique<Point<T>>(x, y));
    }
}

template <Scalar T>
Pentagon<T>::operator double() const {
    return std::abs(PolygonArea(vertices));
}
