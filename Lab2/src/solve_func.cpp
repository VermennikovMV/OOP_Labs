// solve_func.cpp

#include "../include/solve_func.h"

#include <cstring>   // For memcpy
#include <algorithm> // For std::max
#include <sstream>

// Default constructor
Six::Six()
    : digits(nullptr), size(0)
{
}

// Constructor with size and default digit
Six::Six(const size_t &n, unsigned char t)
    : size(n)
{
    if (t > 5)
        throw std::invalid_argument("Digit must be between 0 and 5");

    digits = new unsigned char[size];
    for (size_t i = 0; i < size; ++i)
    {
        digits[i] = t;
    }

    normalize();
}

// Constructor from initializer list
Six::Six(const std::initializer_list<unsigned char> &t)
    : size(t.size())
{
    digits = new unsigned char[size];
    size_t index = 0;
    for (auto it = t.begin(); it != t.end(); ++it, ++index)
    {
        if (*it > 5)
            throw std::invalid_argument("Digit must be between 0 and 5");

        digits[index] = *it;
    }

    normalize();
}

// Constructor from string
Six::Six(const std::string &t)
{
    // Assuming the string is a base-6 number, with most significant digit first
    size = t.length();
    digits = new unsigned char[size];

    for (size_t i = 0; i < size; ++i)
    {
        char c = t[size - i - 1]; // Reverse the string to store least significant digit first
        if (c < '0' || c > '5')
            throw std::invalid_argument("Invalid digit in string");

        digits[i] = c - '0';
    }

    normalize();
}

// Copy constructor
Six::Six(const Six &other)
    : digits(nullptr), size(0)
{
    copyFrom(other);
}

// Move constructor
Six::Six(Six &&other) noexcept
    : digits(nullptr), size(0)
{
    moveFrom(std::move(other));
}

// Destructor
Six::~Six() noexcept
{
    release();
}

// Assignment operator
Six &Six::operator=(const Six &other)
{
    if (this != &other)
    {
        release();
        copyFrom(other);
    }
    return *this;
}

// Move assignment operator
Six &Six::operator=(Six &&other) noexcept
{
    if (this != &other)
    {
        release();
        moveFrom(std::move(other));
    }
    return *this;
}

// Arithmetic operators

// Addition
Six Six::operator+(const Six &other) const
{
    Six result = *this;
    result += other;
    return result;
}

Six &Six::operator+=(const Six &other)
{
    addDigits(other);
    return *this;
}

// Subtraction
Six Six::operator-(const Six &other) const
{
    Six result = *this;
    result -= other;
    return result;
}

Six &Six::operator-=(const Six &other)
{
    subtractDigits(other);
    return *this;
}

// Comparison operators

bool Six::operator==(const Six &other) const
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

bool Six::operator!=(const Six &other) const
{
    return !(*this == other);
}

bool Six::operator<(const Six &other) const
{
    if (size != other.size)
    {
        return size < other.size;
    }
    for (size_t i = size; i > 0; --i)
    {
        if (digits[i - 1] != other.digits[i - 1])
            return digits[i - 1] < other.digits[i - 1];
    }
    return false; // Equal
}

bool Six::operator<=(const Six &other) const
{
    return *this < other || *this == other;
}

bool Six::operator>(const Six &other) const
{
    return !(*this <= other);
}

bool Six::operator>=(const Six &other) const
{
    return !(*this < other);
}

// Friend function for output
std::ostream &operator<<(std::ostream &os, const Six &obj)
{
    if (obj.size == 0)
    {
        os << '0';
        return os;
    }
    for (size_t i = obj.size; i > 0; --i)
    {
        os << static_cast<char>('0' + obj.digits[i - 1]);
    }
    return os;
}

// Private helper methods

void Six::copyFrom(const Six &other)
{
    size = other.size;
    digits = new unsigned char[size];
    std::memcpy(digits, other.digits, size * sizeof(unsigned char));
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
    // Remove leading zeros (from the highest index)
    while (size > 0 && digits[size - 1] == 0)
    {
        --size;
    }
    if (size == 0)
    {
        // Number is zero, keep one digit zero
        delete[] digits;
        digits = new unsigned char[1];
        digits[0] = 0;
        size = 1;
    }
    else
    {
        // Resize the digits array
        unsigned char *newDigits = new unsigned char[size];
        std::memcpy(newDigits, digits, size * sizeof(unsigned char));
        delete[] digits;
        digits = newDigits;
    }
}

void Six::addDigits(const Six &other)
{
    size_t maxSize = std::max(size, other.size) + 1; // +1 for possible carry over
    unsigned char *resultDigits = new unsigned char[maxSize];
    std::memset(resultDigits, 0, maxSize * sizeof(unsigned char));

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
    // Assuming *this >= other
    if (*this < other)
        throw std::underflow_error("Result would be negative");

    size_t maxSize = size;
    unsigned char *resultDigits = new unsigned char[maxSize];
    std::memset(resultDigits, 0, maxSize * sizeof(unsigned char));

    size_t i = 0;
    unsigned char borrow = 0;
    while (i < size)
    {
        unsigned char aDigit = digits[i];
        unsigned char bDigit = (i < other.size) ? other.digits[i] : 0;
        unsigned char diff;
        if (aDigit < bDigit + borrow)
        {
            diff = (unsigned char)(aDigit + 6 - bDigit - borrow);
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
        throw std::underflow_error("Result would be negative");
    }

    delete[] digits;
    digits = resultDigits;
    size = maxSize;
    normalize();
}