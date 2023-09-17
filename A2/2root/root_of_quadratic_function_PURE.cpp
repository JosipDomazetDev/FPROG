#include <iostream>
#include <utility>
#include <complex>
#include <cstdint>
#include <functional>

typedef std::complex<double> complex;

auto square = [](const double e) -> double {
    const double dummy = e;
    const double dummy2 = e;
    double result = e;
    for (int i = 1; i < dummy2; i++) {
        result = result + dummy;
    }
    return result;
};

auto squareroot = [](const float number) -> float {
    union Conv {
        float f;
        uint32_t i;
    };
    Conv conv;
    conv.f = number;
    conv.i = 0x5f3759df - (conv.i >> 1);
    conv.f *= 1.5F - (number * 0.5F * conv.f * conv.f);
    return 1 / conv.f;
};

auto solve_quadratic_equation = [](const double a, const double b, const double c) -> std::pair<complex, complex> {
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
};


template<class, class = std::void_t<> >
struct
needs_unapply : std::true_type {
};

template<class T>
struct
needs_unapply<T, std::void_t<decltype(std::declval<T>()())>> : std::false_type {
};

template<typename F>
auto
curry(F &&f) {
    /// Check if f() is a valid function call. If not we need
    /// to curry at least one argument:
    if constexpr (needs_unapply<decltype(f)>::value) {
        return [=](auto &&x) {
            return curry(
                    [=](auto &&...xs) -> decltype(f(x, xs...)) {
                        return f(x, xs...);
                    }
            );
        };
    } else {
        /// If 'f()' is a valid call, just call it, we are done.
        return f();
    }
}

int main() {
    double a = 3;
    double b = 4;
    double c = 5;

    auto curried_solve = curry(solve_quadratic_equation);

    const auto result = curried_solve(a)(b)(c);
    std::cout << result.first << ", " << result.second << std::endl;

    const auto result2 = curried_solve(a)(b)(c);
    std::cout << result2.first << ", " << result2.second << std::endl;
}
