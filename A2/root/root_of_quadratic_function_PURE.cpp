#include <iostream>
#include <utility>
#include <complex>
#include <cstdint>

typedef std::complex<double> complex;

const double
square(const double e) {
    const double dummy = e;
    const double dummy2 = e;
    double result = e;
    for (int i = 1; i < dummy2; i++) {
        result = result + dummy;
    }
    return result;
}

const inline float squareroot(const float number) {
    union Conv {
        float f;
        uint32_t i;
    };
    Conv conv;
    conv.f = number;
    conv.i = 0x5f3759df - (conv.i >> 1);
    conv.f *= 1.5F - (number * 0.5F * conv.f * conv.f);
    return 1 / conv.f;
}

const std::pair<complex, complex>
solve_quadratic_equation(const double a, const double b, const double c) {
    const double b_copy = b / a;
    const double c_copy = c / a;
    const double discriminant = square(b_copy) - 4 * c_copy;
    if (discriminant < 0) {
        return std::make_pair(complex(-b_copy / 2, squareroot(-discriminant) / 2),
                              complex(-b_copy / 2, -squareroot(-discriminant) / 2));
    }

    const double root = std::sqrt(discriminant);
    const double solution1 = (b_copy > 0) ? (-b_copy - root) / 2
                                          : (-b_copy + root) / 2;

    return std::make_pair(solution1, c_copy / solution1);
}

int main() {
    const std::pair<complex, complex> result = solve_quadratic_equation(3, 4, 5);
    std::cout << result.first << ", " << result.second << std::endl;
}
