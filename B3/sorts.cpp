#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <functional>
#include <numeric>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <optional>


using SortingFunction = std::function<void(std::vector<int> &)>;

SortingFunction BucketSort = [](std::vector<int> &arr) {
    if (arr.empty()) return;

    int minVal = *min_element(arr.begin(), arr.end());
    int maxVal = *max_element(arr.begin(), arr.end());

    std::vector<std::vector<int>> buckets(maxVal - minVal + 1);

    for (int num: arr) {
        buckets[num - minVal].push_back(num);
    }

    int index = 0;
    for (const auto &bucket: buckets) {
        for (int num: bucket) {
            arr[index++] = num;
        }
    }
};

SortingFunction InsertionSort = [](std::vector<int> &arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }

        arr[j + 1] = key;
    }
};

SortingFunction BubbleSort = [](std::vector<int> &arr) {
    if (arr.empty()) return;

    for (size_t i = 0; i < arr.size() - 1; ++i) {
        for (size_t j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
};

SortingFunction SelectionSort = [](std::vector<int> &arr) {
    if (arr.empty()) return;

    for (size_t i = 0; i < arr.size() - 1; ++i) {
        size_t minIndex = i;

        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        std::swap(arr[i], arr[minIndex]);
    }
};

SortingFunction QuickSort = [](std::vector<int> &arr) {
    if (arr.size() <= 1) return;

    int pivot = arr[0];
    std::vector<int> left, right;

    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] < pivot) {
            left.push_back(arr[i]);
        } else {
            right.push_back(arr[i]);
        }
    }

    QuickSort(left);
    QuickSort(right);

    std::copy(left.begin(), left.end(), arr.begin());
    arr[left.size()] = pivot;
    std::copy(right.begin(), right.end(), arr.begin() + left.size() + 1);
};


TEST_CASE("Bucket Sort Test") {
    std::vector<int> arr = {4, 2, 7, 1, 9, 3, 8, 6, 5};
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    BucketSort(arr);

    CHECK(arr == expected);
}

TEST_CASE("Insertion Sort Test") {
    std::vector<int> arr = {4, 2, 7, 1, 9, 3, 8, 6, 5};
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    InsertionSort(arr);

    CHECK(arr == expected);
}

TEST_CASE("Bubble Sort Test") {
    std::vector<int> arr = {4, 2, 7, 1, 9, 3, 8, 6, 5};
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    BubbleSort(arr);

    CHECK(arr == expected);
}

TEST_CASE("Selection Sort Test") {
    std::vector<int> arr = {4, 2, 7, 1, 9, 3, 8, 6, 5};
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    SelectionSort(arr);

    CHECK(arr == expected);
}

TEST_CASE("Quick Sort Test") {
    std::vector<int> arr = {4, 2, 7, 1, 9, 3, 8, 6, 5};
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    QuickSort(arr);

    CHECK(arr == expected);
}


TEST_CASE("Bucket Sort Edge Cases") {
    // Edge case: Empty input
    std::vector<int> arr1;
    std::vector<int> expected1;
    BucketSort(arr1);
    CHECK(arr1 == expected1);

    // Edge case: Input with a single element
    std::vector<int> arr2 = {42};
    std::vector<int> expected2 = {42};
    BucketSort(arr2);
    CHECK(arr2 == expected2);
}

TEST_CASE("Insertion Sort Edge Cases") {
    // Edge case: Empty input
    std::vector<int> arr1;
    std::vector<int> expected1;
    InsertionSort(arr1);
    CHECK(arr1 == expected1);

    // Edge case: Input with a single element
    std::vector<int> arr2 = {42};
    std::vector<int> expected2 = {42};
    InsertionSort(arr2);
    CHECK(arr2 == expected2);
}

TEST_CASE("Bubble Sort Edge Cases") {
    // Edge case: Empty input
    std::vector<int> arr1;
    std::vector<int> expected1;
    BubbleSort(arr1);
    CHECK(arr1 == expected1);

    // Edge case: Input with a single element
    std::vector<int> arr2 = {42};
    std::vector<int> expected2 = {42};
    BubbleSort(arr2);
    CHECK(arr2 == expected2);
}

TEST_CASE("Selection Sort Edge Cases") {
    // Edge case: Empty input
    std::vector<int> arr1;
    std::vector<int> expected1;
    SelectionSort(arr1);
    CHECK(arr1 == expected1);

    // Edge case: Input with a single element
    std::vector<int> arr2 = {42};
    std::vector<int> expected2 = {42};
    SelectionSort(arr2);
    CHECK(arr2 == expected2);
}

TEST_CASE("Quick Sort Edge Cases") {
    // Edge case: Empty input
    std::vector<int> arr1;
    std::vector<int> expected1;
    QuickSort(arr1);
    CHECK(arr1 == expected1);

    // Edge case: Input with a single element
    std::vector<int> arr2 = {42};
    std::vector<int> expected2 = {42};
    QuickSort(arr2);
    CHECK(arr2 == expected2);

    // Edge case: Already sorted input
    std::vector<int> arr3 = {1, 2, 3, 4, 5};
    std::vector<int> expected3 = {1, 2, 3, 4, 5};
    QuickSort(arr3);
    CHECK(arr3 == expected3);
}