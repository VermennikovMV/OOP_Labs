#include "../include/solve_func.h"

bool is_valid_int_input(int value)
{
    char next_char = getchar();
    bool is_next_char_valid = (next_char == '\n' || next_char == EOF);

    if (!is_next_char_valid)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (std::cin.fail() || value < 0 || !is_next_char_valid)
    {
        std::cerr << "ERROR: Invalid input!\n";
        return false;
    }
    return true;
}

int solve_func(int lhv, int rhv)
{
    if (lhv <= 0 || rhv <= 0 || (lhv == 1 && rhv == 1))
    {
        return 0;
    }
    int result;
    result = lhv * rhv - 1;
    return result;
}
