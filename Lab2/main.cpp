// main.cpp

#include "../Lab2/include/solve_func.h"
#include <iostream>
#include <string>

int main()
{
  std::string input1, input2;
  std::string operation;

  std::cout << "Введите первое шестиричное число: ";
  std::cin >> input1;
  std::cout << "Введите второе шестиричное число: ";
  std::cin >> input2;
  std::cout << "Выберите операцию (+, -, ==, !=, <, >, <=, >=): ";
  std::cin >> operation;

  Six num1(input1);
  Six num2(input2);

  if (operation == "+")
  {
    Six result = num1.add(num2);
    std::cout << "Результат сложения: " << result.toString() << std::endl;
  }
  else if (operation == "-")
  {
    Six result = num1.subtract(num2);
    std::cout << "Результат вычитания: " << result.toString() << std::endl;
  }
  else if (operation == "==")
  {
    std::cout << (num1.isEqual(num2) ? "Числа равны" : "Числа не равны") << std::endl;
  }
  else if (operation == "!=")
  {
    std::cout << (num1.isNotEqual(num2) ? "Числа не равны" : "Числа равны") << std::endl;
  }
  else if (operation == "<")
  {
    std::cout << (num1.isLessThan(num2) ? "Первое число меньше второго" : "Первое число не меньше второго") << std::endl;
  }
  else if (operation == ">")
  {
    std::cout << (num1.isGreaterThan(num2) ? "Первое число больше второго" : "Первое число не больше второго") << std::endl;
  }
  else if (operation == "<=")
  {
    std::cout << (num1.isLessThanOrEqual(num2) ? "Первое число меньше или равно второму" : "Первое число больше второго") << std::endl;
  }
  else if (operation == ">=")
  {
    std::cout << (num1.isGreaterThanOrEqual(num2) ? "Первое число больше или равно второму" : "Первое число меньше второго") << std::endl;
  }
  else
  {
    std::cout << "Неверная операция" << std::endl;
  }
  return 0;
}