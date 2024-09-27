// solve_func.h

#include <string>
#include <initializer_list>

class Six
{
public:
    // Конструкторы
    Six();
    Six(const size_t &n, unsigned char t = 0);
    Six(const std::initializer_list<unsigned char> &t);
    Six(const std::string &t);
    Six(const Six &other);
    Six(Six &&other) noexcept;
    virtual ~Six() noexcept;

    // Методы присваивания
    void assign(const Six &other);
    void assignMove(Six &&other) noexcept;

    // Арифметические методы
    Six add(const Six &other) const;
    void addAssign(const Six &other);

    Six subtract(const Six &other) const;
    void subtractAssign(const Six &other);

    // Методы сравнения
    bool isEqual(const Six &other) const;
    bool isNotEqual(const Six &other) const;
    bool isLessThan(const Six &other) const;
    bool isLessThanOrEqual(const Six &other) const;
    bool isGreaterThan(const Six &other) const;
    bool isGreaterThanOrEqual(const Six &other) const;

    // Метод для вывода числа в виде строки
    std::string toString() const;

private:
    unsigned char *digits; // Динамический массив цифр
    size_t size;           // Количество цифр

    void copyFrom(const Six &other);
    void moveFrom(Six &&other);
    void release();

    void normalize(); // Удаление незначащих нулей

    // Вспомогательные методы
    void addDigits(const Six &other);
    void subtractDigits(const Six &other);
};