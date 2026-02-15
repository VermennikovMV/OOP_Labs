#include <bits/stdc++.h>
using namespace std;

struct Pixel { int x, y; };

void circle(int r, function<void(int x, int y)> set_pixel) {
    if (r <= 0) {
        if (r == 0) {
            set_pixel(0, 0);
        }
        return;
    }

    int x = r;
    int y = 0;
    int d = 1 - r;

    auto plot = [&](int x, int y) {
        set_pixel(x, y);
        set_pixel(-x, y);
        set_pixel(x, -y);
        set_pixel(-x, -y);

        if (x != y) {
            set_pixel(y, x);
            set_pixel(-y, x);
            set_pixel(y, -x);
            set_pixel(-y, -x);
        }
    };

    while (x >= y) {
        plot(x, y);

        if (d < 0) {
            y++;
            d += 2 * y + 1;
        } else {
            y++;
            x--;
            d += 2 * (y - x) + 1;
        }
    }
}

int main() {
    int r;
    cout << "Введите радиус окружности: ";
    cin >> r;

    // Размер сетки: от -r до +r по обеим осям
    // Ширину удваиваем (*2), потому что символы в терминале выше, чем шире
    // Это компенсирует пропорции и делает круг визуально круглым
    int height = 2 * r + 1;
    int width  = 2 * r + 1;

    // Сетка символов: '.' — пусто, '*' — пиксель окружности
    vector<string> grid(height, string(width, '.'));

    // Наш set_pixel: переводит координаты (x, y) с центром в (0,0)
    // в индексы сетки и ставит символ '*'
    auto set_pixel = [&](int x, int y) {
        // Переводим из координат окружности в индексы массива
        // Центр окружности = (r, r) в индексах
        int gx = r + x;   // столбец
        int gy = r - y;   // строка (ось Y инвертирована: вверх = меньший индекс)

        if (gx >= 0 && gx < width && gy >= 0 && gy < height) {
            grid[gy][gx] = '*';
        }
    };

    // Рисуем окружность
    circle(r, set_pixel);

    // Выводим сетку
    cout << "\nОкружность радиуса " << r << ":\n\n";
    for (const auto& row : grid) {
        for (char c : row) {
            // Печатаем каждый символ с пробелом, чтобы компенсировать
            // соотношение ширины/высоты символа в терминале
            cout << c << ' ';
        }
        cout << '\n';
    }

    return 0;
}
