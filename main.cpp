#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include "doctest.h"

using SortingFunction = std::function<void(std::vector<int>&)>;

SortingFunction BucketSort = [](std::vector<int>& arr) {
    if (arr.empty()) return;

    int minVal = *min_element(arr.begin(), arr.end());
    int maxVal = *max_element(arr.begin(), arr.end());

    std::vector<std::vector<int>> buckets(maxVal - minVal + 1);

    for (int num : arr) {
        buckets[num - minVal].push_back(num);
    }

    int index = 0;
    for (const auto& bucket : buckets) {
        for (int num : bucket) {
            arr[index++] = num;
        }
    }
};

SortingFunction InsertionSort = [](std::vector<int>& arr) {
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

SortingFunction BubbleSort = [](std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        for (size_t j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
};

SortingFunction SelectionSort = [](std::vector<int>& arr) {
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

SortingFunction QuickSort = [](std::vector<int>& arr) {
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

int xerer(){
    return 4;
}

int main() {
    std::vector<int> arr = {5, 2, 9, 1, 5, 6};


    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}

TEST_CASE("X wins on board"){

    CHECK(true);

}
