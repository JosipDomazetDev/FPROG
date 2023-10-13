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

template<typename T>
using Maybe = std::optional<T>;

auto readIntegersFromFile = [](const std::string &filename) -> Maybe<std::vector<int>> {
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
auto sumIntegers = [](const std::vector<int> &numbers) -> Maybe<int> {
    int sum = 0;
    for (int num: numbers) {
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


// Example 2

#include "doctest.h"
#include <cmath>
#include <string>

template<typename T>
class Result {
public:
    Result(const T &value) : hasValue(true), value(value) {}

    Result(const std::string &error) : hasValue(false), error(error) {}

    bool hasValue;
    T value;
    std::string error;
};

using Matrix = std::vector<std::vector<double>>;

// Calculate the determinant of a 2x2 matrix
double determinant2x2(const Matrix &mat) {
    if (mat.size() != 2 || mat[0].size() != 2 || mat[1].size() != 2) {
        return 0.0; // Return 0 for an invalid matrix
    }
    return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}

// Calculate the determinant of a square matrix recursively
double determinant(const Matrix &mat) {
    int size = mat.size();
    if (size == 1) {
        return mat[0][0];
    } else if (size == 2) {
        return determinant2x2(mat);
    } else {
        double det = 0.0;
        for (int i = 0; i < size; i++) {
            Matrix submatrix;
            for (int j = 1; j < size; j++) {
                submatrix.push_back({});
                for (int k = 0; k < size; k++) {
                    if (k != i) {
                        submatrix[j - 1].push_back(mat[j][k]);
                    }
                }
            }
            det += mat[0][i] * determinant(submatrix) * (i % 2 == 0 ? 1 : -1);
        }
        return det;
    }
}

// Lambda function to invert a matrix
auto invertMatrix = [](const Matrix &mat) -> Result<Matrix> {
    double det = determinant(mat);
    if (std::abs(det) < 1e-6) {
        return Result<Matrix>("Matrix is singular, cannot be inverted.");
    }

    int size = mat.size();
    Matrix inverted(size, std::vector<double>(size, 0.0));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Matrix submatrix(size - 1, std::vector<double>(size - 1, 0.0));
            int subi = 0, subj = 0;

            for (int k = 0; k < size; k++) {
                if (k != i) {
                    subj = 0;
                    for (int l = 0; l < size; l++) {
                        if (l != j) {
                            submatrix[subi][subj] = mat[k][l];
                            subj++;
                        }
                    }
                    subi++;
                }
            }

            inverted[j][i] = determinant(submatrix) / det * ((i + j) % 2 == 0 ? 1 : -1);
        }
    }

    return Result<Matrix>(inverted);
};

TEST_CASE("Matrix Inversion Test") {
    Matrix sampleMatrix = {{4, 7},
                           {2, 6}};
    Result<Matrix> maybeInverted = invertMatrix(sampleMatrix);

    if (maybeInverted.hasValue) {
        // Matrix inversion successful
        Matrix inverted = maybeInverted.value;
        CHECK(inverted[0][0] == 0.6);
        CHECK(inverted[0][1] == -0.7);
        CHECK(inverted[1][0] == -0.2);
        CHECK(inverted[1][1] == 0.4);
    } else {
        std::cout << "Error: " << maybeInverted.error << std::endl;
    }
}

// Example 3

// Define a simple QuadraticSolution struct to represent the solutions
struct QuadraticSolution {
    std::optional<double> root1;
    std::optional<double> root2;
};

// Lambda function to solve a quadratic equation
auto solve_quadratic = [](double a, double b, double c) -> std::optional<QuadraticSolution> {
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return std::nullopt; // No real roots (complex roots)
    } else if (discriminant == 0) {
        double root = -b / (2 * a);
        return QuadraticSolution{root, std::nullopt}; // One real root
    } else {
        double root1 = (-b + std::sqrt(discriminant)) / (2 * a);
        double root2 = (-b - std::sqrt(discriminant)) / (2 * a);
        return QuadraticSolution{root1, root2}; // Two real roots
    }
};

TEST_CASE("Solve Quadratic Equation - Two Real Roots") {
    double a = 1.0;
    double b = -3.0;
    double c = 2.0;

    std::optional<QuadraticSolution> result = solve_quadratic(a, b, c);

    REQUIRE(result);
    REQUIRE(result.value().root1);
    REQUIRE(result.value().root2);
    CHECK(result.value().root1.value() == 2.0);
    CHECK(result.value().root2.value() == 1.0);
}

TEST_CASE("Solve Quadratic Equation - One Real Root") {
    double a = 1.0;
    double b = -4.0;
    double c = 4.0;

    std::optional<QuadraticSolution> result = solve_quadratic(a, b, c);

    REQUIRE(result);
    REQUIRE(result.value().root1);
    CHECK(result.value().root1.value() == 2.0);
    REQUIRE_FALSE(result.value().root2.has_value());
}

TEST_CASE("Solve Quadratic Equation - Complex Roots") {
    double a = 1.0;
    double b = 2.0;
    double c = 5.0;

    std::optional<QuadraticSolution> result = solve_quadratic(a, b, c);

    REQUIRE_FALSE(result);
}


// Example 4

// Define the Maybe monad as an optional
template<typename T>
using Maybe = std::optional<T>;

// Lambda function for integer division
auto divide_integers = [](int numerator, int denominator) -> Maybe<int> {
    if (denominator == 0) {
        return Maybe<int>{}; // Error: division by zero
    }
    return Maybe<int>(numerator / denominator);
};

// Lambda function to print the result of division
auto print_result = [](const Maybe<int> &result) -> void {
    if (result) {
        std::cout << "Result: " << result.value() << std::endl;
    } else {
        std::cout << "Error: Division by zero." << std::endl;
    }
};

TEST_CASE("Integer Division Test - Valid") {
    int numerator = 10;
    int denominator = 2;
    Maybe<int> result = divide_integers(numerator, denominator);

    REQUIRE(result);
    CHECK(result.value() == 5);
}

TEST_CASE("Integer Division Test - Division by Zero") {
    int numerator = 5;
    int denominator = 0;
    Maybe<int> result = divide_integers(numerator, denominator);

    REQUIRE_FALSE(result);
}

TEST_CASE("Print Result - Valid") {
    int numerator = 15;
    int denominator = 3;
    Maybe<int> result = divide_integers(numerator, denominator);

    print_result(result);
}

TEST_CASE("Print Result - Division by Zero") {
    int numerator = 8;
    int denominator = 0;
    Maybe<int> result = divide_integers(numerator, denominator);

    print_result(result);
}

// Example 5

// Define the Maybe monad as an optional
template<typename T>
using Maybe = std::optional<T>;

// Lambda function to read the contents of a file
auto readFile = [](const std::string &filename) -> Maybe<std::string> {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return Maybe<std::string>{}; // Error: File not found or cannot be opened
    }

    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n";
    }

    return Maybe<std::string>(content);
};

// Lambda function to check if the file content is ASCII
auto isASCII = [](const std::string &content) -> bool {
    for (char c: content) {
        if (static_cast<unsigned char>(c) > 127) {
            return false; // Non-ASCII character found
        }
    }
    return true; // All characters are ASCII
};

// Lambda function to process the file content
auto processFileContent = [](const std::string &filename) -> bool {
    Maybe<std::string> maybeContent = readFile(filename);

    if (maybeContent) {
        bool isAscii = isASCII(maybeContent.value());

        if (isAscii) {
            std::cout << "File content (ASCII):\n" << maybeContent.value() << std::endl;
            return true; // ASCII content
        } else {
            std::cout << "Error: File contains non-ASCII characters." << std::endl;
            return false; // Non-ASCII content
        }
    } else {
        std::cout << "Error: File not found or cannot be opened." << std::endl;
        return false; // Error
    }
};

TEST_CASE("Process ASCII File") {
    std::string filename = "ascii.txt";
    bool isAscii = processFileContent(filename);
    CHECK(isAscii);
}

TEST_CASE("Process Non-ASCII File") {
    std::string filename = "nonascii.txt";
    bool isAscii = processFileContent(filename);
    CHECK_FALSE(isAscii);
}

TEST_CASE("Process Missing File") {
    std::string filename = "missing.txt";
    bool isAscii = processFileContent(filename);
    CHECK_FALSE(isAscii);
}