/* Chernyackov Eugeny chernyackov.eugeny@yandex.ru
stl_circular_list
*/

#include "circular_list.hpp"
#include <gtest/gtest.h>

TEST(CircularListTest, DefaultConstructor) {
    CircularList<int> list;
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.begin(), list.end());
}

TEST(CircularListTest, PushBackAndFront) {
    CircularList<int> list;
    list.push_back(10);
    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 10);
    list.push_front(20);
    EXPECT_EQ(list.front(), 20);
    EXPECT_EQ(list.back(), 10);
    EXPECT_EQ(list.size(), 2);
}

TEST(CircularListTest, PopFrontAndBack) {
    CircularList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
    list.pop_front();
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.size(), 2);
    list.pop_back();
    EXPECT_EQ(list.back(), 2);
    EXPECT_EQ(list.size(), 1);
}

TEST(CircularListTest, CopyConstructorAndAssignment) {
    CircularList<int> list1;
    for (int i = 1; i <= 5; ++i) {
        list1.push_back(i);
    }
    CircularList<int> list2 = list1;
    EXPECT_EQ(list2.size(), list1.size());
    EXPECT_TRUE(list2 == list1);
    list2.pop_back();
    EXPECT_NE(list2.size(), list1.size());
    CircularList<int> list3;
    list3 = list1;
    EXPECT_EQ(list3.size(), list1.size());
    EXPECT_TRUE(list3 == list1);
}

TEST(CircularListTest, ClearAndEmpty) {
    CircularList<int> list = {1, 2, 3};
    EXPECT_FALSE(list.empty());
    list.clear();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
    EXPECT_EQ(list.begin(), list.end());
}

TEST(CircularListTest, IteratorTraversal) {
    CircularList<int> list = {1, 2, 3, 4};
    int sum = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 10);
}

TEST(CircularListTest, ConstIteratorTraversal) {
    const CircularList<int> list = {5, 6, 7};
    int sum = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 18);
}

TEST(CircularListTest, ReverseIterator) {
    CircularList<int> list = {1, 2, 3};
    std::vector<int> rev;
    for (auto it = list.rbegin(); it != list.rend(); ++it) {
        rev.push_back(*it);
    }
    std::vector<int> expected = {3, 2, 1};
    EXPECT_EQ(rev, expected);
}

TEST(CircularListTest, FrontBackExceptions) {
    CircularList<int> list;
    EXPECT_THROW(list.front(), std::out_of_range);
    EXPECT_THROW(list.back(), std::out_of_range);
    EXPECT_THROW(list.pop_front(), std::out_of_range);
    EXPECT_THROW(list.pop_back(), std::out_of_range);
}
