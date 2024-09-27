// test_func.cpp

#include "test_func.h"
#include "../include/solve_func.h"
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cctype>
#include <iostream>

// Функция для разбиения строки на токены
std::vector<std::string> tokenize(const std::string &str)
{
    std::vector<std::string> tokens;
    std::string token;
    size_t i = 0;
    while (i < str.length())
    {
        if (isspace(str[i]))
        {
            ++i;
            continue;
        }

        if (isdigit(str[i]))
        {
            token.clear();
            while (i < str.length() && isdigit(str[i]))
            {
                token += str[i++];
            }
            tokens.push_back(token);
        }
        else if (str[i] == '<' || str[i] == '>' || str[i] == '=' || str[i] == '!')
        {
            token = str[i++];
            if (i < str.length() && str[i] == '=')
            {
                token += '=';
                ++i;
            }
            tokens.push_back(token);
        }
        else if (str[i] == '+' || str[i] == '-')
        {
            token = str[i++];
            tokens.push_back(token);
        }
        else
        {
            throw std::invalid_argument("Invalid character in expression");
        }
    }
    return tokens;
}

bool test_func(const std::string &expression)
{
    try
    {
        std::vector<std::string> tokens = tokenize(expression);

        if (tokens.size() == 3)
        {
            // Формат: число оператор_сравнения число
            Six num1(tokens[0]);
            std::string comp_op = tokens[1];
            Six num2(tokens[2]);

            if (comp_op == "==")
                return num1.isEqual(num2);
            else if (comp_op == "!=")
                return num1.isNotEqual(num2);
            else if (comp_op == "<")
                return num1.isLessThan(num2);
            else if (comp_op == "<=")
                return num1.isLessThanOrEqual(num2);
            else if (comp_op == ">")
                return num1.isGreaterThan(num2);
            else if (comp_op == ">=")
                return num1.isGreaterThanOrEqual(num2);
            else
                throw std::invalid_argument("Недопустимый оператор сравнения");
        }
        else if (tokens.size() == 5)
        {
            // Формат: число оператор_арифметики число оператор_сравнения число
            Six num1(tokens[0]);
            std::string arith_op = tokens[1];
            Six num2(tokens[2]);
            std::string comp_op = tokens[3];
            Six num3(tokens[4]);

            Six arith_result;
            if (arith_op == "+")
                arith_result.assign(num1.add(num2));
            else if (arith_op == "-")
                arith_result.assign(num1.subtract(num2));
            else
                throw std::invalid_argument("Недопустимый арифметический оператор");

            if (comp_op == "==")
                return arith_result.isEqual(num3);
            else if (comp_op == "!=")
                return arith_result.isNotEqual(num3);
            else if (comp_op == "<")
                return arith_result.isLessThan(num3);
            else if (comp_op == "<=")
                return arith_result.isLessThanOrEqual(num3);
            else if (comp_op == ">")
                return arith_result.isGreaterThan(num3);
            else if (comp_op == ">=")
                return arith_result.isGreaterThanOrEqual(num3);
            else
                throw std::invalid_argument("Недопустимый оператор сравнения");
        }
        else
        {
            throw std::invalid_argument("Неверный формат выражения");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return false;
    }
}