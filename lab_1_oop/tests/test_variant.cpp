#include <gtest/gtest.h>
#include "array_ops.h"

TEST(ArrayOperations, CreateAndDelete) {
    int* arr = array_create(3);
    ASSERT_NE(arr, nullptr);

    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[2], 3);

    array_delete(arr);
    EXPECT_EQ(arr, nullptr);
}

TEST(ArrayOperations, InsertIntoEmptyArray) {
    int* arr = nullptr;
    std::size_t size = 0;

    arr = array_insert(arr, size, 0, 7);

    ASSERT_NE(arr, nullptr);
    EXPECT_EQ(size, 1);
    EXPECT_EQ(arr[0], 7);
    array_delete(arr);
}

TEST(ArrayOperations, InsertAtBeginningAndEnd) {
    int* arr = new int[1]{2};
    std::size_t size = 1;

    arr = array_insert(arr, size, 0, 1);
    arr = array_insert(arr, size, size, 3);

    EXPECT_EQ(size, 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    array_delete(arr);
}

TEST(ArrayOperations, InsertInMiddle) {
    int* arr = new int[2]{1, 3};
    std::size_t size = 2;

    arr = array_insert(arr, size, 1, 2);

    EXPECT_EQ(size, 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    array_delete(arr);
}

TEST(ArrayOperations, RemoveFirstAndLast) {
    int* arr = new int[4]{1, 2, 3, 4};
    std::size_t size = 4;

    arr = array_remove(arr, size, 0);
    arr = array_remove(arr, size, size - 1);

    EXPECT_EQ(size, 2);
    EXPECT_EQ(arr[0], 2);
    EXPECT_EQ(arr[1], 3);
    array_delete(arr);
}

TEST(ArrayOperations, RemoveOnlyElement) {
    int* arr = new int[1]{7};
    std::size_t size = 1;

    arr = array_remove(arr, size, 0);

    EXPECT_EQ(size, 0);
    EXPECT_EQ(arr, nullptr);
}

TEST(ArrayOperations, ResizeUpAndDown) {
    int* arr = new int[2]{1, 2};

    arr = array_resize(arr, 2, 4);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 0);
    EXPECT_EQ(arr[3], 0);

    arr = array_resize(arr, 4, 1);
    EXPECT_EQ(arr[0], 1);
    array_delete(arr);
}

TEST(ArrayKthSmallest, ExampleFromAssignment) {
    int arr[] = {4, 2, 7, 1, 9, 3};

    EXPECT_EQ(array_kth_smallest(arr, 6, 3), 3);
    EXPECT_EQ(arr[0], 4);
    EXPECT_EQ(arr[1], 2);
}

TEST(ArrayKthSmallest, FirstAndLast) {
    int arr[] = {4, 2, 7, 1, 9, 3};

    EXPECT_EQ(array_kth_smallest(arr, 6, 1), 1);
    EXPECT_EQ(array_kth_smallest(arr, 6, 6), 9);
}

TEST(ArrayKthSmallest, EmptyAndRepeatedNumbers) {
    int arr[] = {3, 1, 3, 1};

    EXPECT_EQ(array_kth_smallest(nullptr, 0, 1), 0);
    EXPECT_EQ(array_kth_smallest(arr, 4, 2), 1);
    EXPECT_EQ(array_kth_smallest(arr, 4, 3), 3);
}
