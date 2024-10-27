#include <gtest/gtest.h>
#include "../include/solve_func.h"

using namespace std;

TEST(TrapezoidTest, AreaTest)
{
    vector<pair<double, double>> vertices = {
        {0, 0}, {4, 0}, {3, 2}, {1, 2}};
    Trapezoid trap(vertices);
    double area = static_cast<double>(trap);
    EXPECT_DOUBLE_EQ(area, 6.0);
}

TEST(TrapezoidTest, CenterTest)
{
    vector<pair<double, double>> vertices = {
        {0, 0}, {4, 0}, {3, 2}, {1, 2}};
    Trapezoid trap(vertices);
    auto center = trap.Center();
    EXPECT_DOUBLE_EQ(center.first, 2.0);
    EXPECT_DOUBLE_EQ(center.second, 0.8888888888888888);
}

TEST(RhombusTest, AreaTest)
{
    vector<pair<double, double>> vertices = {
        {0, 0}, {2, 2}, {4, 0}, {2, -2}};
    Rhombus rhombus(vertices);
    double area = static_cast<double>(rhombus);
    EXPECT_DOUBLE_EQ(area, 8.0);
}

TEST(RhombusTest, CenterTest)
{
    vector<pair<double, double>> vertices = {
        {0, 0}, {2, 2}, {4, 0}, {2, -2}};
    Rhombus rhombus(vertices);
    auto center = rhombus.Center();
    EXPECT_DOUBLE_EQ(center.first, -2.0);
    EXPECT_DOUBLE_EQ(center.second, 0.0);
}

TEST(PentagonTest, AreaTest)
{
    vector<pair<double, double>> vertices = {
        {0, 0}, {2, 0}, {3, 2}, {1, 3}, {-1, 2}};
    Pentagon pentagon(vertices);
    double area = static_cast<double>(pentagon);
    EXPECT_DOUBLE_EQ(area, 8.0);
}

TEST(PentagonTest, CenterTest)
{
    vector<pair<double, double>> vertices = {
        {0, 0}, {2, 0}, {3, 2}, {1, 3}, {-1, 2}};
    Pentagon pentagon(vertices);
    auto center = pentagon.Center();
    EXPECT_DOUBLE_EQ(center.first, 1.0);
    EXPECT_DOUBLE_EQ(center.second, 1.4166666666666667);
}

TEST(FigureTest, ComparisonTest)
{
    vector<pair<double, double>> vertices1 = {
        {0, 0}, {2, 0}, {3, 2}, {1, 3}, {-1, 2}};
    vector<pair<double, double>> vertices2 = vertices1;
    Pentagon pentagon1(vertices1);
    Pentagon pentagon2(vertices2);
    EXPECT_TRUE(pentagon1 == pentagon2);
}

TEST(FigureTest, CopyAssignmentTest)
{
    vector<pair<double, double>> vertices = {
        {0, 0}, {2, 0}, {3, 2}, {1, 3}, {-1, 2}};
    Pentagon pentagon1(vertices);
    Pentagon pentagon2;
    pentagon2 = pentagon1;
    EXPECT_TRUE(pentagon1 == pentagon2);
}

TEST(FigureTest, MoveAssignmentTest)
{
    vector<pair<double, double>> vertices = {
        {0, 0}, {2, 0}, {3, 2}, {1, 3}, {-1, 2}};
    Pentagon pentagon1(vertices);
    Pentagon pentagon2;
    pentagon2 = move(pentagon1);
    EXPECT_TRUE(pentagon2 == Pentagon(vertices));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
