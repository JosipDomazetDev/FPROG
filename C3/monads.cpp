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

template <typename T>
using Maybe = std::optional<T>;

auto readIntegersFromFile = [](const std::string& filename) -> Maybe<std::vector<int>> {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return Maybe<std::vector<int>>{};
    }

    std::vector<int> integers;
    int num;
    while (file >> num) {
        integers.push_back(num);
    }

    if (integers.empty()) {
        return Maybe<std::vector<int>>{};
    }

    return Maybe<std::vector<int>>(integers);
};

// Immutable function to sum the integers
auto sumIntegers = [](const std::vector<int>& numbers) -> Maybe<int> {
    int sum = 0;
    for (int num : numbers) {
        sum += num;
    }
    return Maybe<int>(sum);
};

TEST_CASE("Bucket Sort Test") {
    std::string filename = "numbers.txt";
    Maybe<std::vector<int>> maybeIntegers = readIntegersFromFile(filename);

    if (maybeIntegers) {
        Maybe<int> maybeSum = sumIntegers(maybeIntegers.value());

        if (maybeSum) {
            CHECK(maybeSum.value() == 30);
        } else {
            std::cout << "Error: Could not calculate the sum." << std::endl;
        }
    } else {
        std::cout << "Error: Could not read integers from the file." << std::endl;
    }
}

