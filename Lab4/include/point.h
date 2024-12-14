#pragma once
#include <iostream>
#include "concepts.h"

template <Scalar T>
class Point {
public:
    T x;
    T y;

    Point() : x(0), y(0) {}
    Point(T x_coord, T y_coord) : x(x_coord), y(y_coord) {}

    friend std::ostream &operator<<(std::ostream &os, const Point<T> &point) {
        os << "(" << point.x << ", " << point.y << ")";
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Point<T> &point) {
        is >> point.x >> point.y;
        return is;
    }
};
