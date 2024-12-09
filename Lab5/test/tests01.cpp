#include <gtest/gtest.h>
#include "../include/solve_func.h"

CustomMemoryResource customResource(500);
std::pmr::polymorphic_allocator<int> allocator(&customResource);

TEST(test_01, basic_test_set) {
    Stack<int> stack(4, allocator);
    stack.push(10);
    stack.push(20);
    stack.push(30);
    ASSERT_TRUE(stack.get_size() == 3);
}

TEST(test_02, basic_test_set) {
    Stack<int> stack(4, allocator);
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.pop();
    ASSERT_TRUE(stack.get_size() == 2);
}

TEST(test_03, basic_test_set) {
    Stack<int> stack(4, allocator);
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.pop();
    stack.pop();
    stack.pop();
    ASSERT_TRUE(stack.get_size() == 0);
}

TEST(test_04, basic_test_set) {
    Stack<int> stack(4, allocator);
    stack.push(10);
    stack.push(20);

    Stack<int> stack2(4, allocator);
    stack2.push(10);
    stack2.push(20);
    ASSERT_TRUE(stack == stack2);
}

TEST(test_05, basic_test_set) {
    Stack<int> stack(4, allocator);
    stack.push(10);
    stack.push(20);

    Stack<int> stack2(4, allocator);
    stack2.push(10);
    stack2.push(20);
    ASSERT_TRUE(stack.top() == stack2.top());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
