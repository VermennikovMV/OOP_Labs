#include <gtest/gtest.h>
#include "../include/solve_func.h"

TEST(TrapezoidTest, AreaTest)
{
    std::vector<Point<int>> vertices = {
        {0, 0}, {4, 0}, {3, 2}, {1, 2}};
    Trapezoid<int> trap(vertices);
    double area = trap;
    EXPECT_DOUBLE_EQ(area, 6.0);
}

TEST(TrapezoidTest, CenterTest)
{
    std::vector<Point<int>> vertices = {
        {0, 0}, {4, 0}, {3, 2}, {1, 2}};
    Trapezoid<int> trap(vertices);
    auto center = trap.Center();
    EXPECT_NEAR(center->x, 2.0, 1e-6);
    EXPECT_NEAR(center->y, 0.8888888888888888, 1e-6);
}

TEST(RhombusTest, AreaTest)
{
    std::vector<Point<int>> vertices = {
        {0, 0}, {2, -2}, {4, 0}, {2, 2}};
    Rhombus<int> rhomb(vertices);
    double area = rhomb;
    EXPECT_DOUBLE_EQ(area, 8.0);
}

TEST(RhombusTest, CenterTest)
{
    std::vector<Point<int>> vertices = {
        {0, 0}, {2, -2}, {4, 0}, {2, 2}};
    Rhombus<int> rhomb(vertices);
    auto center = rhomb.Center();
    EXPECT_NEAR(center->x, 2.0, 1e-6);
    EXPECT_NEAR(center->y, 0.0, 1e-6);
}

TEST(PentagonTest, AreaTest)
{
    std::vector<Point<int>> vertices = {
        {0, 0}, {2, -2}, {4, -1}, {5, 1}, {2, 2}};
    Pentagon<int> pent(vertices);
    double area = pent;
    EXPECT_DOUBLE_EQ(area, 11.5);
}

TEST(PentagonTest, CenterTest)
{
    std::vector<Point<int>> vertices = {
        {0, 0}, {2, -2}, {4, -1}, {5, 1}, {2, 2}};
    Pentagon<int> pent(vertices);
    auto center = pent.Center();
    EXPECT_NEAR(center->x, 2.507246376811594, 1e-6);
    EXPECT_NEAR(center->y, 0.08695652173913043, 1e-6);
}

TEST(FigureTest, ComparisonTest)
{
    std::vector<Point<int>> vertices1 = {
        {0, 0}, {4, 0}, {3, 2}, {1, 2}};
    Trapezoid<int> trap1(vertices1);

    std::vector<Point<int>> vertices2 = {
        {0, 0}, {4, 0}, {3, 2}, {1, 2}};
    Trapezoid<int> trap2(vertices2);

    EXPECT_TRUE(trap1 == trap2);

    std::vector<Point<int>> vertices3 = {
        {0, 0}, {2, -2}, {4, 0}, {2, 2}};
    Rhombus<int> rhomb(vertices3);

    EXPECT_FALSE(trap1 == rhomb); // Ожидается, что это сравнение всегда будет false
}

TEST(ArrayTest, PushBackAndAccess)
{
    Array<Figure<int>> figures;
    std::vector<Point<int>> vertices = {
        {0, 0}, {4, 0}, {3, 2}, {1, 2}};
    auto trap = make_shared<Trapezoid<int>>(vertices);
    figures.push_back(trap);
    EXPECT_EQ(figures.get_size(), 1);
    double area = *figures[0];
    EXPECT_DOUBLE_EQ(area, 6.0);
}

TEST(ArrayTest, RemoveAt)
{
    Array<Figure<int>> figures;
    std::vector<Point<int>> vertices1 = {
        {0, 0}, {4, 0}, {3, 2}, {1, 2}};
    auto trap1 = make_shared<Trapezoid<int>>(vertices1);

    std::vector<Point<int>> vertices2 = {
        {1, 1}, {5, 1}, {4, 3}, {2, 3}};
    auto trap2 = make_shared<Trapezoid<int>>(vertices2);

    figures.push_back(trap1);
    figures.push_back(trap2);

    figures.remove_at(0);
    EXPECT_EQ(figures.get_size(), 1);
    double area = *figures[0];
    EXPECT_DOUBLE_EQ(area, 6.0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
