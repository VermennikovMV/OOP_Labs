#pragma once
#include "figure.h"
#include <vector>
#include <utility>

class Trapezoid : public Figure {
private:
    std::vector<std::pair<double, double>> vertices;
public:
    Trapezoid();
    Trapezoid(const std::vector<std::pair<double, double>> &vertices);
    Trapezoid(const Trapezoid &other);
    Trapezoid(Trapezoid &&other) noexcept;

    Trapezoid &operator=(const Trapezoid &other);
    Trapezoid &operator=(Trapezoid &&other) noexcept;
    bool operator==(const Trapezoid &other) const;

    std::pair<double, double> Center() const override;
    void Print(std::ostream &os) const override;
    void Read(std::istream &is) override;
    operator double() const override;
};
