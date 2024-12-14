#include <iostream>
#include "include/point.h"
#include "include/trapezoid.h"
#include "include/rhombus.h"
#include "include/pentagon.h"
#include "include/array.h"

using namespace std;

int main()
{
  Array<Figure<int>> figures;

  while (true)
  {
    cout << "Выберите действие:\n";
    cout << "1. Добавить фигуру\n";
    cout << "2. Удалить фигуру\n";
    cout << "3. Вывести все фигуры\n";
    cout << "4. Вычислить общую площадь\n";
    cout << "5. Выход\n";
    int choice;
    cin >> choice;

    if (choice == 1)
    {
      cout << "Выберите тип фигуры:\n";
      cout << "1. Трапеция\n";
      cout << "2. Ромб\n";
      cout << "3. Пятиугольник\n";
      int fig_choice;
      cin >> fig_choice;

      shared_ptr<Figure<int>> fig;

      if (fig_choice == 1)
      {
        fig = make_shared<Trapezoid<int>>();
      }
      else if (fig_choice == 2)
      {
        fig = make_shared<Rhombus<int>>();
      }
      else if (fig_choice == 3)
      {
        fig = make_shared<Pentagon<int>>();
      }
      else
      {
        cout << "Неверный выбор фигуры.\n";
        continue;
      }

      cin >> *fig;
      figures.push_back(fig);
    }
    else if (choice == 2)
    {
      cout << "Введите индекс фигуры для удаления: ";
      size_t index;
      cin >> index;
      if (index >= figures.get_size())
      {
        cout << "Неверный индекс.\n";
      }
      else
      {
        figures.remove_at(index);
        cout << "Фигура удалена.\n";
      }
    }
    else if (choice == 3)
    {
      for (size_t i = 0; i < figures.get_size(); ++i)
      {
        cout << "Фигура " << i << ":\n";
        cout << *figures[i];
        auto center = figures[i]->Center();
        cout << "Центр фигуры: " << *center << endl;
        double area = *figures[i];
        cout << "Площадь фигуры: " << area << endl;
        cout << "-------------------------\n";
      }
    }
    else if (choice == 4)
    {
      double total_area = 0.0;
      for (size_t i = 0; i < figures.get_size(); ++i)
      {
        total_area += static_cast<double>(*figures[i]);
      }
      cout << "Общая площадь фигур: " << total_area << endl;
    }
    else if (choice == 5)
    {
      break;
    }
    else
    {
      cout << "Неверный выбор действия.\n";
    }
  }

  // Пример использования Array для типа-наследника
  // Array<Trapezoid<int>> trapezoids;
  // Trapezoid<int> trap;
  // cin >> trap;
  // trapezoids.push_back(make_shared<Trapezoid<int>>(trap));

  // Вывод информации о трапеции
  // cout << "Трапеция:\n";
  // trapezoids[0]->Print(cout);
  // auto center = trapezoids[0]->Center();
  // cout << "Центр трапеции: " << *center << endl;
  // double area = *trapezoids[0];
  // cout << "Площадь трапеции: " << area << endl;

  return 0;
}
