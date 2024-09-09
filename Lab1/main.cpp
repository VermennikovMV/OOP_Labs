#include <iostream>
#include "include/solve_func.h"

int main()
{
  int lhv, rhv;
  std::cout << "введите ширину: ";
  std::cin >> lhv;
  if (is_valid_int_input(lhv))
  {
    std::cout << "введите длину: ";
    std::cin >> rhv;
    if (!is_valid_int_input(lhv))
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }

  std::cout << "результат: " << solve_func(lhv, rhv) << std::endl;

  return 0;
}
