#pragma once
#include <vector>
#include <memory>
#include <cmath>
#include "point.h"
#include "concepts.h"

template <Scalar T>
double PolygonArea(const std::vector<std::unique_ptr<Point<T>>> &vertices) {
    double area = 0.0;
    size_t n = vertices.size();
    for (size_t i = 0; i < n; ++i) {
        double x1 = static_cast<double>(vertices[i]->x);
        double y1 = static_cast<double>(vertices[i]->y);
        double x2 = static_cast<double>(vertices[(i + 1) % n]->x);
        double y2 = static_cast<double>(vertices[(i + 1) % n]->y);
        area += (x1 * y2 - x2 * y1);
    }
    return area / 2.0; // Возвращаем подписанную площадь
}

template <Scalar T>
std::unique_ptr<Point<double>> PolygonCenter(const std::vector<std::unique_ptr<Point<T>>> &vertices) {
    double cx = 0.0;
    double cy = 0.0;
    double area = PolygonArea(vertices);
    size_t n = vertices.size();
    double factor = 1.0 / (6.0 * area); // Используем подписанную площадь
    for (size_t i = 0; i < n; ++i) {
        double xi = static_cast<double>(vertices[i]->x);
        double yi = static_cast<double>(vertices[i]->y);
        double xi1 = static_cast<double>(vertices[(i + 1) % n]->x);
        double yi1 = static_cast<double>(vertices[(i + 1) % n]->y);
        double cross = xi * yi1 - xi1 * yi;
        cx += (xi + xi1) * cross;
        cy += (yi + yi1) * cross;
    }
    cx *= factor;
    cy *= factor;
    return std::make_unique<Point<double>>(cx, cy);
}
