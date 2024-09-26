// main.cpp

#include "../Lab2/include/solve_func.h"
#include <iostream>
#include <string>

int main()
{
  std::string input1, input2;
  char operation;

  std::cout << "Введите первое шестиричное число: ";
  std::cin >> input1;
  std::cout << "Введите второе шестиричное число: ";
  std::cin >> input2;
  std::cout << "Выберите операцию (+, -, ==, !=, <, >): ";
  std::cin >> operation;

  try
  {
    Six num1(input1);
    Six num2(input2);

    if (operation == '+')
    {
      Six result = num1 + num2;
      std::cout << "Результат сложения: " << result << std::endl;
    }
    else if (operation == '-')
    {
      Six result = num1 - num2;
      std::cout << "Результат вычитания: " << result << std::endl;
    }
    else if (operation == '=')
    {
      std::cout << (num1 == num2 ? "Числа равны" : "Числа не равны") << std::endl;
    }
    else if (operation == '!')
    {
      std::cout << (num1 != num2 ? "Числа не равны" : "Числа равны") << std::endl;
    }
    else if (operation == '<')
    {
      std::cout << (num1 < num2 ? "Первое число меньше второго" : "Первое число не меньше второго") << std::endl;
    }
    else if (operation == '>')
    {
      std::cout << (num1 > num2 ? "Первое число больше второго" : "Первое число не больше второго") << std::endl;
    }
    else
    {
      std::cout << "Неверная операция" << std::endl;
    }
  }
  catch (const std::exception &e)
  {
    std::cout << "Ошибка: " << e.what() << std::endl;
  }

  return 0;
}
