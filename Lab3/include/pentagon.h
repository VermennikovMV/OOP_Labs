#pragma once
#include "figure.h"
#include <vector>
#include <utility>

class Pentagon : public Figure {
private:
    std::vector<std::pair<double, double>> vertices;
public:
    Pentagon();
    Pentagon(const std::vector<std::pair<double, double>> &vertices);
    Pentagon(const Pentagon &other);
    Pentagon(Pentagon &&other) noexcept;

    Pentagon &operator=(const Pentagon &other);
    Pentagon &operator=(Pentagon &&other) noexcept;
    bool operator==(const Pentagon &other) const;

    std::pair<double, double> Center() const override;
    void Print(std::ostream &os) const override;
    void Read(std::istream &is) override;
    operator double() const override;
};
