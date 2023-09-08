#include <iostream>

// Silly square function that is immutable and pure
const double silly_square(const double x) {
    double result = 0;
    for (int i = 0; i < x; ++i) {
        result += x;
    }
    return result;
}

// Helper function to calculate square root without using std::sqrt()
const double square_root(const double x, const double epsilon = 1e-10, const int max_iterations = 1000) {
    if (x < 0) {
        return -1; // Invalid input
    }
    if (x == 0) {
        return 0;
    }

    double low = 0, high = x;
    double mid;
    for (int i = 0; i < max_iterations; ++i) {
        mid = (low + high) / 2.0;
        double mid_square = mid * mid;

        if (mid_square > x) {
            high = mid;
        } else if (mid_square < x) {
            low = mid;
        }

        if (high - low < epsilon) {
            break;
        }
    }

    return mid;
}

const double calculate_median(const double a, const double b, const double c) {
    const double result = 0.5 * square_root(2 * silly_square(b) + 2 * silly_square(c) - silly_square(a));
    return result;
}

int main() {
    const double a_initial = 3;
    const double b_initial = 4;
    const double c_initial = 5;
    std::cout << "Triangle sides: a = " << a_initial << ", b = " << b_initial << ", c = " << c_initial << "\n";

    const double median_a = calculate_median(a_initial, b_initial, c_initial);
    const double median_b = calculate_median(b_initial, c_initial, a_initial);
    const double median_c = calculate_median(c_initial, a_initial, b_initial);

    std::cout << "Medians:\n";
    std::cout << "Median from vertex A: " << median_a << "\n";
    std::cout << "Median from vertex B: " << median_b << "\n";
    std::cout << "Median from vertex C: " << median_c << "\n";

    return 0;
}
