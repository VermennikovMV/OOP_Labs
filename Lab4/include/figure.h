#pragma once
#include <iostream>
#include <memory>
#include "concepts.h"
#include "point.h"

template <Scalar T>
class Figure {
public:
    virtual ~Figure() = default;
    virtual std::unique_ptr<Point<double>> Center() const = 0;
    virtual void Print(std::ostream &os) const = 0;
    virtual void Read(std::istream &is) = 0;
    virtual operator double() const = 0;

    friend std::ostream &operator<<(std::ostream &os, const Figure<T> &figure) {
        figure.Print(os);
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Figure<T> &figure) {
        figure.Read(is);
        return is;
    }
};
