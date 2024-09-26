// solve_func.h

#include <iostream>
#include <string>
#include <initializer_list>
#include <stdexcept>

class Six
{
public:
    Six();                                              // Default constructor
    Six(const size_t &n, unsigned char t = 0);          // Constructor with size and default digit
    Six(const std::initializer_list<unsigned char> &t); // Constructor from initializer list
    Six(const std::string &t);                          // Constructor from string
    Six(const Six &other);                              // Copy constructor
    Six(Six &&other) noexcept;                          // Move constructor
    virtual ~Six() noexcept;                            // Destructor

    // Assignment operator
    Six &operator=(const Six &other);
    Six &operator=(Six &&other) noexcept;

    // Arithmetic operators
    Six operator+(const Six &other) const;
    Six &operator+=(const Six &other);

    Six operator-(const Six &other) const;
    Six &operator-=(const Six &other);

    // Comparison operators
    bool operator==(const Six &other) const;
    bool operator!=(const Six &other) const;
    bool operator<(const Six &other) const;
    bool operator<=(const Six &other) const;
    bool operator>(const Six &other) const;
    bool operator>=(const Six &other) const;

    // Friend function for output
    friend std::ostream &operator<<(std::ostream &os, const Six &obj);

private:
    unsigned char *digits; // Dynamic array of digits
    size_t size;           // Number of digits

    void copyFrom(const Six &other);
    void moveFrom(Six &&other);
    void release();

    void normalize(); // Remove leading zeros

    // Helper methods
    void addDigits(const Six &other);
    void subtractDigits(const Six &other);
};