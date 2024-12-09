#include "include/solve_func.h"
#include <iostream>

// Структура, аналогичная той, что у другого студента, для демонстрации
struct AB {
    int a;
    int b;
};

int main() {
    // Создаём наш ресурс памяти фиксированного размера
    CustomMemoryResource customResource(500);

    // Создаем полиморфные аллокаторы разных типов
    std::pmr::polymorphic_allocator<int> allocatorInt(&customResource);
    std::pmr::polymorphic_allocator<char> allocatorChar(&customResource);
    std::pmr::polymorphic_allocator<AB> allocatorAB(&customResource);

    // Создаем стеки с использованием наших аллокаторов
    Stack<int> stack1(&customResource);
    Stack<char> stack2(&customResource);
    Stack<AB> stack3(&customResource);

    // Добавляем элементы
    stack1.push(10);
    stack1.push(20);

    stack2.push('a');
    stack2.push('b');

    stack3.push({101, 202});
    stack3.push({303, 404});

    // Выводим содержимое стеков с помощью итераторов
    std::cout << "Stack1:\n";
    for (auto it = stack1.begin(); it != stack1.end(); ++it) {
        std::cout << *it << '\n';
    }

    std::cout << "Stack2:\n";
    for (auto it = stack2.begin(); it != stack2.end(); ++it) {
        std::cout << *it << '\n';
    }

    std::cout << "Stack3:\n";
    for (auto it = stack3.begin(); it != stack3.end(); ++it) {
        std::cout << it->a << ' ' << it->b << '\n';
    }

    std::cout << "End!\n";

    return 0;
}
