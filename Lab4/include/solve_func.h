#pragma once // говорит компилятору что данный файл должен быть включен только один раз
#include <iostream>
#include <vector>
#include <memory>
#include <concepts>
#include <cmath>
#include <type_traits>

using namespace std;

// Проверка, что T является скалярным типом
template <class T>
concept Scalar = is_arithmetic_v<T>;

template <Scalar T>
class Point
{
public:
    T x;
    T y;

    Point() : x(0), y(0) {}
    Point(T x_coord, T y_coord) : x(x_coord), y(y_coord) {}

    friend ostream &operator<<(ostream &os, const Point<T> &point)
    {
        os << "(" << point.x << ", " << point.y << ")";
        return os;
    }

    friend istream &operator>>(istream &is, Point<T> &point)
    {
        is >> point.x >> point.y;
        return is;
    }
};

template <Scalar T>
class Figure
{
public:
    virtual ~Figure() = default;
    virtual unique_ptr<Point<double>> Center() const = 0;
    virtual void Print(ostream &os) const = 0;
    virtual void Read(istream &is) = 0;
    virtual operator double() const = 0;

    friend ostream &operator<<(ostream &os, const Figure<T> &figure)
    {
        figure.Print(os);
        return os;
    }

    friend istream &operator>>(istream &is, Figure<T> &figure)
    {
        figure.Read(is);
        return is;
    }
};

template <Scalar T>
class Trapezoid : public Figure<T>
{
private:
    vector<unique_ptr<Point<T>>> vertices;

public:
    Trapezoid();
    Trapezoid(const vector<Point<T>> &points);
    Trapezoid(const Trapezoid<T> &other);
    Trapezoid(Trapezoid<T> &&other) noexcept;

    Trapezoid<T> &operator=(const Trapezoid<T> &other);
    Trapezoid<T> &operator=(Trapezoid<T> &&other) noexcept;
    bool operator==(const Trapezoid<T> &other) const;

    unique_ptr<Point<double>> Center() const override;
    void Print(ostream &os) const override;
    void Read(istream &is) override;
    operator double() const override;
};

// Реализация методов Trapezoid

template <Scalar T>
Trapezoid<T>::Trapezoid() {}

template <Scalar T>
Trapezoid<T>::Trapezoid(const vector<Point<T>> &points)
{
    for (const auto &pt : points)
    {
        vertices.push_back(make_unique<Point<T>>(pt.x, pt.y));
    }
}

template <Scalar T>
Trapezoid<T>::Trapezoid(const Trapezoid<T> &other)
{
    for (const auto &pt : other.vertices)
    {
        vertices.push_back(make_unique<Point<T>>(pt->x, pt->y));
    }
}

template <Scalar T>
Trapezoid<T>::Trapezoid(Trapezoid<T> &&other) noexcept : vertices(move(other.vertices)) {}

template <Scalar T>
Trapezoid<T> &Trapezoid<T>::operator=(const Trapezoid<T> &other)
{
    if (this != &other)
    {
        vertices.clear();
        for (const auto &pt : other.vertices)
        {
            vertices.push_back(make_unique<Point<T>>(pt->x, pt->y));
        }
    }
    return *this;
}

template <Scalar T>
Trapezoid<T> &Trapezoid<T>::operator=(Trapezoid<T> &&other) noexcept
{
    if (this != &other)
    {
        vertices = move(other.vertices);
    }
    return *this;
}

template <Scalar T>
bool Trapezoid<T>::operator==(const Trapezoid<T> &other) const
{
    if (vertices.size() != other.vertices.size())
    {
        return false;
    }
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        if (vertices[i]->x != other.vertices[i]->x || vertices[i]->y != other.vertices[i]->y)
        {
            return false;
        }
    }
    return true;
}

template <Scalar T>
unique_ptr<Point<double>> Trapezoid<T>::Center() const
{
    return PolygonCenter(vertices);
}

template <Scalar T>
void Trapezoid<T>::Print(ostream &os) const
{
    os << "Trapezoid vertices: ";
    for (const auto &vertex : vertices)
    {
        os << *vertex << " ";
    }
    os << endl;
}

template <Scalar T>
void Trapezoid<T>::Read(istream &is)
{
    vertices.clear();
    cout << "Введите 4 вершины (x y): ";
    for (int i = 0; i < 4; ++i)
    {
        T x, y;
        is >> x >> y;
        vertices.push_back(make_unique<Point<T>>(x, y));
    }
}

template <Scalar T>
Trapezoid<T>::operator double() const
{
    return abs(PolygonArea(vertices));
}

// Реализация класса Rhombus

template <Scalar T>
class Rhombus : public Figure<T>
{
private:
    vector<unique_ptr<Point<T>>> vertices;

public:
    Rhombus();
    Rhombus(const vector<Point<T>> &points);
    Rhombus(const Rhombus<T> &other);
    Rhombus(Rhombus<T> &&other) noexcept;

    Rhombus<T> &operator=(const Rhombus<T> &other);
    Rhombus<T> &operator=(Rhombus<T> &&other) noexcept;
    bool operator==(const Rhombus<T> &other) const;

    unique_ptr<Point<double>> Center() const override;
    void Print(ostream &os) const override;
    void Read(istream &is) override;
    operator double() const override;
};

// Реализация методов Rhombus

template <Scalar T>
Rhombus<T>::Rhombus() {}

template <Scalar T>
Rhombus<T>::Rhombus(const vector<Point<T>> &points)
{
    for (const auto &pt : points)
    {
        vertices.push_back(make_unique<Point<T>>(pt.x, pt.y));
    }
}

template <Scalar T>
Rhombus<T>::Rhombus(const Rhombus<T> &other)
{
    for (const auto &pt : other.vertices)
    {
        vertices.push_back(make_unique<Point<T>>(pt->x, pt->y));
    }
}

template <Scalar T>
Rhombus<T>::Rhombus(Rhombus<T> &&other) noexcept : vertices(move(other.vertices)) {}

template <Scalar T>
Rhombus<T> &Rhombus<T>::operator=(const Rhombus<T> &other)
{
    if (this != &other)
    {
        vertices.clear();
        for (const auto &pt : other.vertices)
        {
            vertices.push_back(make_unique<Point<T>>(pt->x, pt->y));
        }
    }
    return *this;
}

template <Scalar T>
Rhombus<T> &Rhombus<T>::operator=(Rhombus<T> &&other) noexcept
{
    if (this != &other)
    {
        vertices = move(other.vertices);
    }
    return *this;
}

template <Scalar T>
bool Rhombus<T>::operator==(const Rhombus<T> &other) const
{
    if (vertices.size() != other.vertices.size())
    {
        return false;
    }
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        if (vertices[i]->x != other.vertices[i]->x || vertices[i]->y != other.vertices[i]->y)
        {
            return false;
        }
    }
    return true;
}

template <Scalar T>
unique_ptr<Point<double>> Rhombus<T>::Center() const
{
    return PolygonCenter(vertices);
}

template <Scalar T>
void Rhombus<T>::Print(ostream &os) const
{
    os << "Rhombus vertices: ";
    for (const auto &vertex : vertices)
    {
        os << *vertex << " ";
    }
    os << endl;
}

template <Scalar T>
void Rhombus<T>::Read(istream &is)
{
    vertices.clear();
    cout << "Введите 4 вершины (x y): ";
    for (int i = 0; i < 4; ++i)
    {
        T x, y;
        is >> x >> y;
        vertices.push_back(make_unique<Point<T>>(x, y));
    }
}

template <Scalar T>
Rhombus<T>::operator double() const
{
    return PolygonArea(vertices);
}

// Реализация класса Pentagon

template <Scalar T>
class Pentagon : public Figure<T>
{
private:
    vector<unique_ptr<Point<T>>> vertices;

public:
    Pentagon();
    Pentagon(const vector<Point<T>> &points);
    Pentagon(const Pentagon<T> &other);
    Pentagon(Pentagon<T> &&other) noexcept;

    Pentagon<T> &operator=(const Pentagon<T> &other);
    Pentagon<T> &operator=(Pentagon<T> &&other) noexcept;
    bool operator==(const Pentagon<T> &other) const;

    unique_ptr<Point<double>> Center() const override;
    void Print(ostream &os) const override;
    void Read(istream &is) override;
    operator double() const override;
};

// Реализация методов Pentagon

template <Scalar T>
Pentagon<T>::Pentagon() {}

template <Scalar T>
Pentagon<T>::Pentagon(const vector<Point<T>> &points)
{
    for (const auto &pt : points)
    {
        vertices.push_back(make_unique<Point<T>>(pt.x, pt.y));
    }
}

template <Scalar T>
Pentagon<T>::Pentagon(const Pentagon<T> &other)
{
    for (const auto &pt : other.vertices)
    {
        vertices.push_back(make_unique<Point<T>>(pt->x, pt->y));
    }
}

template <Scalar T>
Pentagon<T>::Pentagon(Pentagon<T> &&other) noexcept : vertices(move(other.vertices)) {}

template <Scalar T>
Pentagon<T> &Pentagon<T>::operator=(const Pentagon<T> &other)
{
    if (this != &other)
    {
        vertices.clear();
        for (const auto &pt : other.vertices)
        {
            vertices.push_back(make_unique<Point<T>>(pt->x, pt->y));
        }
    }
    return *this;
}

template <Scalar T>
Pentagon<T> &Pentagon<T>::operator=(Pentagon<T> &&other) noexcept
{
    if (this != &other)
    {
        vertices = move(other.vertices);
    }
    return *this;
}

template <Scalar T>
bool Pentagon<T>::operator==(const Pentagon<T> &other) const
{
    if (vertices.size() != other.vertices.size())
    {
        return false;
    }
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        if (vertices[i]->x != other.vertices[i]->x || vertices[i]->y != other.vertices[i]->y)
        {
            return false;
        }
    }
    return true;
}

template <Scalar T>
unique_ptr<Point<double>> Pentagon<T>::Center() const
{
    return PolygonCenter(vertices);
}

template <Scalar T>
void Pentagon<T>::Print(ostream &os) const
{
    os << "Pentagon vertices: ";
    for (const auto &vertex : vertices)
    {
        os << *vertex << " ";
    }
    os << endl;
}

template <Scalar T>
void Pentagon<T>::Read(istream &is)
{
    vertices.clear();
    cout << "Введите 5 вершин (x y): ";
    for (int i = 0; i < 5; ++i)
    {
        T x, y;
        is >> x >> y;
        vertices.push_back(make_unique<Point<T>>(x, y));
    }
}

template <Scalar T>
Pentagon<T>::operator double() const
{
    return PolygonArea(vertices);
}

// Шаблон динамического массива

template <class T>
class Array
{
private:
    size_t capacity;
    size_t size;
    unique_ptr<shared_ptr<T>[]> data;

    void resize()
    {
        size_t new_capacity = capacity * 2;
        unique_ptr<shared_ptr<T>[]> new_data(new shared_ptr<T>[new_capacity]);
        for (size_t i = 0; i < size; ++i)
        {
            new_data[i] = move(data[i]);
        }
        data = move(new_data);
        capacity = new_capacity;
    }

public:
    Array() : capacity(4), size(0), data(new shared_ptr<T>[capacity]) {}

    void push_back(shared_ptr<T> value)
    {
        if (size == capacity)
        {
            resize();
        }
        data[size++] = move(value);
    }

    void remove_at(size_t index)
    {
        if (index >= size)
        {
            throw out_of_range("Индекс вне диапазона");
        }
        for (size_t i = index; i < size - 1; ++i)
        {
            data[i] = move(data[i + 1]);
        }
        data[size - 1].reset();
        --size;
    }

    size_t get_size() const
    {
        return size;
    }

    shared_ptr<T> &operator[](size_t index)
    {
        if (index >= size)
        {
            throw out_of_range("Индекс вне диапазона");
        }
        return data[index];
    }

    const shared_ptr<T> &operator[](size_t index) const
    {
        if (index >= size)
        {
            throw out_of_range("Индекс вне диапазона");
        }
        return data[index];
    }
};

// Функции для вычисления площади и центра многоугольника

template <Scalar T>
double PolygonArea(const vector<unique_ptr<Point<T>>> &vertices)
{
    double area = 0.0;
    size_t n = vertices.size();
    for (size_t i = 0; i < n; ++i)
    {
        double x1 = static_cast<double>(vertices[i]->x);
        double y1 = static_cast<double>(vertices[i]->y);
        double x2 = static_cast<double>(vertices[(i + 1) % n]->x);
        double y2 = static_cast<double>(vertices[(i + 1) % n]->y);
        area += (x1 * y2 - x2 * y1);
    }
    return area / 2.0; // Возвращаем подписанную площадь
}

template <Scalar T>
unique_ptr<Point<double>> PolygonCenter(const vector<unique_ptr<Point<T>>> &vertices)
{
    double cx = 0.0;
    double cy = 0.0;
    double area = PolygonArea(vertices);
    size_t n = vertices.size();
    double factor = 1.0 / (6.0 * area); // Используем подписанную площадь
    for (size_t i = 0; i < n; ++i)
    {
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
    return make_unique<Point<double>>(cx, cy);
}