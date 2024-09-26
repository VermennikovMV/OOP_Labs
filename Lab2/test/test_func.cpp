// test_func.cpp

#include "test_func.h"
#include "../include/solve_func.h"
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cctype>
#include <iostream>

// Helper function to split a string into tokens
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
            // Number token
            token.clear();
            while (i < str.length() && isdigit(str[i]))
            {
                token += str[i++];
            }
            tokens.push_back(token);
        }
        else if (str[i] == '<' || str[i] == '>' || str[i] == '=' || str[i] == '!')
        {
            // Comparison operator
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
            // Arithmetic operator
            token = str[i++];
            tokens.push_back(token);
        }
        else
        {
            // Invalid character
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
            // Format: number comparison_operator number
            Six num1(tokens[0]);
            std::string comp_op = tokens[1];
            Six num2(tokens[2]);

            if (comp_op == "==")
                return num1 == num2;
            else if (comp_op == "!=")
                return num1 != num2;
            else if (comp_op == "<")
                return num1 < num2;
            else if (comp_op == "<=")
                return num1 <= num2;
            else if (comp_op == ">")
                return num1 > num2;
            else if (comp_op == ">=")
                return num1 >= num2;
            else
                throw std::invalid_argument("Invalid comparison operator");
        }
        else if (tokens.size() == 5)
        {
            // Format: number arithmetic_operator number comparison_operator number
            Six num1(tokens[0]);
            std::string arith_op = tokens[1];
            Six num2(tokens[2]);
            std::string comp_op = tokens[3];
            Six num3(tokens[4]);

            Six arith_result;
            if (arith_op == "+")
                arith_result = num1 + num2;
            else if (arith_op == "-")
                arith_result = num1 - num2;
            else
                throw std::invalid_argument("Invalid arithmetic operator");

            if (comp_op == "==")
                return arith_result == num3;
            else if (comp_op == "!=")
                return arith_result != num3;
            else if (comp_op == "<")
                return arith_result < num3;
            else if (comp_op == "<=")
                return arith_result <= num3;
            else if (comp_op == ">")
                return arith_result > num3;
            else if (comp_op == ">=")
                return arith_result >= num3;
            else
                throw std::invalid_argument("Invalid comparison operator");
        }
        else
        {
            throw std::invalid_argument("Invalid expression format");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return false;
    }
}