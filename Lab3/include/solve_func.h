#pragma once // говорит компилятору что данный файл должен быть включен только один раз
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Figure
{
public:
    virtual ~Figure() = default;
    virtual pair<double, double> Center() const = 0;
    virtual void Print(ostream &os) const = 0;
    virtual void Read(istream &is) = 0;
    virtual operator double() const = 0;

    friend ostream &operator<<(ostream &os, const Figure &figure)
    {
        figure.Print(os);
        return os;
    }

    friend istream &operator>>(istream &is, Figure &figure)
    {
        figure.Read(is);
        return is;
    }
};

class Trapezoid : public Figure
{
private:
    vector<pair<double, double>> vertices;

public:
    Trapezoid();
    Trapezoid(const vector<pair<double, double>> &vertices);
    Trapezoid(const Trapezoid &other);
    Trapezoid(Trapezoid &&other) noexcept;

    Trapezoid &operator=(const Trapezoid &other);
    Trapezoid &operator=(Trapezoid &&other) noexcept;
    bool operator==(const Trapezoid &other) const;

    pair<double, double> Center() const override;
    void Print(ostream &os) const override;
    void Read(istream &is) override;
    operator double() const override;
};

class Rhombus : public Figure
{
private:
    vector<pair<double, double>> vertices;

public:
    Rhombus();
    Rhombus(const vector<pair<double, double>> &vertices);
    Rhombus(const Rhombus &other);
    Rhombus(Rhombus &&other) noexcept;

    Rhombus &operator=(const Rhombus &other);
    Rhombus &operator=(Rhombus &&other) noexcept;
    bool operator==(const Rhombus &other) const;

    pair<double, double> Center() const override;
    void Print(ostream &os) const override;
    void Read(istream &is) override;
    operator double() const override;
};

class Pentagon : public Figure
{
private:
    vector<pair<double, double>> vertices;

public:
    Pentagon();
    Pentagon(const vector<pair<double, double>> &vertices);
    Pentagon(const Pentagon &other);
    Pentagon(Pentagon &&other) noexcept;

    Pentagon &operator=(const Pentagon &other);
    Pentagon &operator=(Pentagon &&other) noexcept;
    bool operator==(const Pentagon &other) const;

    pair<double, double> Center() const override;
    void Print(ostream &os) const override;
    void Read(istream &is) override;
    operator double() const override;
};