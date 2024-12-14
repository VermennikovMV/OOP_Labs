#pragma once
#include "figure.h"
#include <vector>
#include <utility>

class Rhombus : public Figure {
private:
    std::vector<std::pair<double, double>> vertices;
public:
    Rhombus();
    Rhombus(const std::vector<std::pair<double, double>> &vertices);
    Rhombus(const Rhombus &other);
    Rhombus(Rhombus &&other) noexcept;

    Rhombus &operator=(const Rhombus &other);
    Rhombus &operator=(Rhombus &&other) noexcept;
    bool operator==(const Rhombus &other) const;

    std::pair<double, double> Center() const override;
    void Print(std::ostream &os) const override;
    void Read(std::istream &is) override;
    operator double() const override;
};
