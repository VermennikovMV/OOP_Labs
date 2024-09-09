#include <gtest/gtest.h>
#include "../include/solve_func.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(solve_func(1, 1) == 0);
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(solve_func(5, 3) == 14);
}

TEST(test_03, basic_test_set)
{
    ASSERT_TRUE(solve_func(1, 1) == 0);
}

TEST(test_04, basic_test_set)
{
    ASSERT_TRUE(solve_func(12, 3) == 35);
}

TEST(test_05, basic_test_set)
{
    ASSERT_TRUE(solve_func(12, 4) == 35);
}

TEST(test_06, basic_test_set)
{
    ASSERT_TRUE(solve_func(0, 0) == 0); // данные валидны, так как 0 - это неотрицательное целое число, а значит возвращаем 0, так как нет шоколада для разбиения
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}