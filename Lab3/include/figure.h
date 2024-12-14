#pragma once
#include <iostream>
#include <utility>

class Figure {
public:
    virtual ~Figure() = default;
    virtual std::pair<double, double> Center() const = 0;
    virtual void Print(std::ostream &os) const = 0;
    virtual void Read(std::istream &is) = 0;
    virtual operator double() const = 0;

    friend std::ostream &operator<<(std::ostream &os, const Figure &figure) {
        figure.Print(os);
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Figure &figure) {
        figure.Read(is);
        return is;
    }
};
