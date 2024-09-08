#include <iostream>
#include "include/solve_func.h"
#include "src/solve_func.cpp"

int main()
{
  int lhv,rhv;
  std::cout << "введите ширину:";
  std::cin  >> lhv;
  std::cout << "введите высоту:";
  std::cin  >> rhv;


  std::cout << "результат: " << solve_func(lhv,rhv) << std::endl;

  return 0;
}
