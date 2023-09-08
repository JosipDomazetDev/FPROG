#include <iostream>

// Helper function to calculate square root without using std::sqrt()
const double square_root(const double x, const double epsilon = 1e-10, const int max_iterations = 1000) {
    if (x < 0) {
        return -1; // Invalid input
    }
    if (x == 0) {
        return 0;
    }

    const double initial_x = x;
    double low = 0, high = x;
    double mid;
    for (int i = 0; i < max_iterations; ++i) {
        mid = (low + high) / 2.0;
        const double mid_square = mid * mid;

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

const double calculate_circumradius(const double a, const double b, const double c) {
    const double s = (a + b + c) / 2;
    const double area = square_root(s * (s - a) * (s - b) * (s - c));
    return (a * b * c) / (4 * area);
}

int main() {
    const double a = 3, b = 4, c = 5;
    std::cout << "Triangle sides: a = " << a << ", b = " << b << ", c = " << c << "\n";

    const double circumradius = calculate_circumradius(a, b, c);

    std::cout << "Circumradius: " << circumradius << "\n";


    const double circumradius2 = calculate_circumradius(a, b, c);

    std::cout << "Circumradius: " << circumradius2 << "\n";

    return 0;
}
