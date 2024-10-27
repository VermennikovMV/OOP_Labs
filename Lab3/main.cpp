#include <iostream>
#include "include/solve_func.h"
#include <vector>
#include <memory>

using namespace std;

int main()
{
  vector<shared_ptr<Figure>> figures;

  while (true)
  {
    cout << "\nМеню:\n";
    cout << "1. Добавить трапецию\n";
    cout << "2. Добавить ромб\n";
    cout << "3. Добавить пятиугольник\n";
    cout << "4. Вывести фигуры\n";
    cout << "5. Вывести центры фигур\n";
    cout << "6. Вывести площади фигур\n";
    cout << "7. Вывести общую площадь\n";
    cout << "8. Удалить фигуру\n";
    cout << "9. Выйти\n";
    cout << "Выберите опцию: ";

    int option;
    cin >> option;

    if (option == 1)
    {
      auto fig = make_shared<Trapezoid>();
      cin >> *fig;
      figures.push_back(fig);
    }
    else if (option == 2)
    {
      auto fig = make_shared<Rhombus>();
      cin >> *fig;
      figures.push_back(fig);
    }
    else if (option == 3)
    {
      auto fig = make_shared<Pentagon>();
      cin >> *fig;
      figures.push_back(fig);
    }
    else if (option == 4)
    {
      for (size_t i = 0; i < figures.size(); ++i)
      {
        cout << i << ": " << *figures[i] << endl;
      }
    }
    else if (option == 5)
    {
      for (size_t i = 0; i < figures.size(); ++i)
      {
        auto center = figures[i]->Center();
        cout << i << ": Центр в (" << center.first << ", " << center.second << ")\n";
      }
    }
    else if (option == 6)
    {
      for (size_t i = 0; i < figures.size(); ++i)
      {
        double area = static_cast<double>(*figures[i]);
        cout << i << ": Площадь = " << area << "\n";
      }
    }
    else if (option == 7)
    {
      double total_area = 0;
      for (const auto &fig : figures)
      {
        total_area += static_cast<double>(*fig);
      }
      cout << "Общая площадь: " << total_area << "\n";
    }
    else if (option == 8)
    {
      cout << "Введите индекс для удаления: ";
      size_t index;
      cin >> index;
      if (index < figures.size())
      {
        figures.erase(figures.begin() + index);
        cout << "Фигура с индексом " << index << " удалена\n";
      }
      else
      {
        cout << "Неверный индекс\n";
      }
    }
    else if (option == 9)
    {
      break;
    }
    else
    {
      cout << "Неверная опция\n";
    }
  }

  return 0;
}
