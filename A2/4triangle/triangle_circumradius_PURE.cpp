#include <iostream>
#include <functional>

const auto square_root = [](const double x, const double epsilon = 1e-10, const int max_iterations = 1000) -> double {
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

const double calculate_circumradius(const double a, const double b, const double c) {
    const double s = (a + b + c) / 2;
    const double area = square_root(s * (s - a) * (s - b) * (s - c));
    return (a * b * c) / (4 * area);
}

int main() {
    const double a = 3, b = 4, c = 5;
    std::cout << "Triangle sides: a = " << a << ", b = " << b << ", c = " << c << "\n";

    const auto curried_circumradius = curry(calculate_circumradius);

    double circumradius = curried_circumradius(a)(b)(c);

    std::cout << "Circumradius: " << circumradius << "\n";

    circumradius = curried_circumradius(a)(b)(c);

    std::cout << "Circumradius: " << circumradius << "\n";

    return 0;
}
