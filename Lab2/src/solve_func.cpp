// solve_func.cpp

#include "../include/solve_func.h"
#include <cstring>   // Для memcpy, memset
#include <algorithm> // Для std::max
#include <stdexcept>

using namespace std;

// Конструкторы и деструктор

Six::Six()
    : digits(nullptr), size(0) {}

Six::Six(const size_t &n, unsigned char t)
    : size(n)
{
    if (t > 5)
        throw invalid_argument("Цифра должна быть от 0 до 5");

    digits = new unsigned char[size];
    for (size_t i = 0; i < size; ++i)
    {
        digits[i] = t;
    }

    normalize();
}

Six::Six(const std::initializer_list<unsigned char> &t)
    : size(t.size())
{
    digits = new unsigned char[size];
    size_t index = 0;
    try
    {
        for (auto it = t.begin(); it != t.end(); ++it, ++index)
        {
            if (*it > 5)
                throw std::invalid_argument("Цифра должна быть от 0 до 5");

            digits[index] = *it;
        }

        normalize();
    }
    catch (...)
    {
        delete[] digits;
        digits = nullptr;
        size = 0;
        throw;
    }
}


Six::Six(const std::string  &t)
{
    size = t.length();
    digits = new unsigned char[size];

    try
    {
        for (size_t i = 0; i < size; ++i)
        {
            char c = t[size - i - 1];
            if (c < '0' || c > '5')
                throw std::invalid_argument("Недопустимая цифра в строке");

            digits[i] = c - '0';
        }

        normalize();
    }
    catch (...)
    {
        delete[] digits;
        digits = nullptr;
        size = 0;
        throw;
    }
}

Six::Six(const Six &other)
    : digits(nullptr), size(0)
{
    copyFrom(other);
}

Six::Six(Six &&other) noexcept
    : digits(nullptr), size(0)
{
    moveFrom(std::move(other));
}

Six::~Six() noexcept
{
    release();
}

// Методы присваивания

void Six::assign(const Six &other)
{
    if (this != &other)
    {
        release();
        copyFrom(other);
    }
}

void Six::assignMove(Six &&other) noexcept
{
    if (this != &other)
    {
        release();
        moveFrom(std::move(other));
    }
}

// Арифметические методы

Six Six::add(const Six &other) const
{
    Six result = *this;
    result.addAssign(other);
    return result;
}

void Six::addAssign(const Six &other)
{
    if (this == &other) {
        Six temp(other);
        addDigits(temp);
    } else {
        addDigits(other);
    }
}

Six Six::subtract(const Six &other) const
{
    Six result = *this;
    result.subtractAssign(other);
    return result;
}

void Six::subtractAssign(const Six &other)
{
    if (this == &other) {
        Six temp(other);
        subtractDigits(temp);
    } else {
        subtractDigits(other);
    }
}

// Методы сравнения

bool Six::isEqual(const Six &other) const
{
    if (size != other.size)
        return false;
    for (size_t i = 0; i < size; ++i)
    {
        if (digits[i] != other.digits[i])
            return false;
    }
    return true;
}

bool Six::isNotEqual(const Six &other) const
{
    return !isEqual(other);
}

bool Six::isLessThan(const Six &other) const
{
    if (size != other.size)
        return size < other.size;
    for (size_t i = size; i > 0; --i)
    {
        if (digits[i - 1] != other.digits[i - 1])
            return digits[i - 1] < other.digits[i - 1];
    }
    return false;
}

bool Six::isLessThanOrEqual(const Six &other) const
{
    return isLessThan(other) || isEqual(other);
}

bool Six::isGreaterThan(const Six &other) const
{
    return !isLessThanOrEqual(other);
}

bool Six::isGreaterThanOrEqual(const Six &other) const
{
    return !isLessThan(other);
}

// Метод для вывода числа в виде строки

string Six::toString() const
{
    if (size == 0)
    {
        return "0";
    }
    string result;
    for (size_t i = size; i > 0; --i)
    {
        result += static_cast<char>('0' + digits[i - 1]);
    }
    return result;
}

// Вспомогательные методы

void Six::copyFrom(const Six &other)
{
    size = other.size;
    digits = new unsigned char[size];
    memcpy(digits, other.digits, size * sizeof(unsigned char));
}

void Six::moveFrom(Six &&other)
{
    digits = other.digits;
    size = other.size;
    other.digits = nullptr;
    other.size = 0;
}

void Six::release()
{
    delete[] digits;
    digits = nullptr;
    size = 0;
}

void Six::normalize()
{
    while (size > 0 && digits[size - 1] == 0)
    {
        --size;
    }
    if (size == 0)
    {
        delete[] digits;
        digits = new unsigned char[1];
        digits[0] = 0;
        size = 1;
    }
    else
    {
        unsigned char *newDigits = new unsigned char[size];
        memcpy(newDigits, digits, size * sizeof(unsigned char));
        delete[] digits;
        digits = newDigits;
    }
}

void Six::addDigits(const Six &other)
{
    size_t maxSize = std::max(size, other.size) + 1;
    unsigned char *resultDigits = new unsigned char[maxSize];
    memset(resultDigits, 0, maxSize * sizeof(unsigned char));

    size_t i = 0;
    unsigned char carry = 0;
    while (i < size || i < other.size)
    {
        unsigned char aDigit = (i < size) ? digits[i] : 0;
        unsigned char bDigit = (i < other.size) ? other.digits[i] : 0;
        unsigned char sum = aDigit + bDigit + carry;
        carry = sum / 6;
        resultDigits[i] = sum % 6;
        ++i;
    }
    if (carry > 0)
    {
        resultDigits[i] = carry;
        ++i;
    }
    delete[] digits;
    digits = resultDigits;
    size = i;
    normalize();
}

void Six::subtractDigits(const Six &other)
{
    if (isLessThan(other))
        throw std::underflow_error("Результат был бы отрицательным");

    size_t maxSize = size;
    unsigned char *resultDigits = new unsigned char[maxSize];
    memset(resultDigits, 0, maxSize * sizeof(unsigned char));

    size_t i = 0;
    unsigned char borrow = 0;
    while (i < size)
    {
        unsigned char aDigit = digits[i];
        unsigned char bDigit = (i < other.size) ? other.digits[i] : 0;
        unsigned char diff;
        if (aDigit < bDigit + borrow)
        {
            diff = static_cast<unsigned char>(aDigit + 6 - bDigit - borrow);
            borrow = 1;
        }
        else
        {
            diff = aDigit - bDigit - borrow;
            borrow = 0;
        }
        resultDigits[i] = diff;
        ++i;
    }

    if (borrow != 0)
    {
        delete[] resultDigits;
        throw std::underflow_error("Результат был бы отрицательным");
    }

    delete[] digits;
    digits = resultDigits;
    size = maxSize;
    normalize();
}
