#include <iostream>
#include <functional>

// Silly square function that is immutable and pure
const auto silly_square = [](const double x) {
    double result = 0;
    for (int i = 0; i < x; ++i) {
        result += x;
    }
    return result;
};

// Helper function to calculate square root without using std::sqrt()
const auto square_root = [](const double x, const double epsilon = 1e-10, const int max_iterations = 1000) -> double {
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
};

const auto calculate_median = [](const double a, const double b, const double c) {
    const double result = 0.5 * square_root(2 * silly_square(b) + 2 * silly_square(c) - silly_square(a));
    return result;
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
    const double a_initial = 3;
    const double b_initial = 4;
    const double c_initial = 5;
    std::cout << "Triangle sides: a = " << a_initial << ", b = " << b_initial << ", c = " << c_initial << "\n";

    const auto curried_calculate_median = curry(calculate_median);

    const auto median_a = curried_calculate_median(a_initial)(b_initial)(c_initial);
    const auto median_b = curried_calculate_median(b_initial)(c_initial)(a_initial);
    const auto median_c = curried_calculate_median(c_initial)(a_initial)(b_initial);

    std::cout << "Medians:\n";
    std::cout << "Median from vertex A: " << median_a << "\n";
    std::cout << "Median from vertex B: " << median_b << "\n";
    std::cout << "Median from vertex C: " << median_c << "\n";


    std::cout << "Triangle sides: a = " << a_initial << ", b = " << b_initial << ", c = " << c_initial << "\n";

    const auto median_a2 = curried_calculate_median(a_initial)(b_initial)(c_initial);
    const auto median_b2 = curried_calculate_median(b_initial)(c_initial)(a_initial);
    const auto median_c2 = curried_calculate_median(c_initial)(a_initial)(b_initial);

    std::cout << "Medians:\n";
    std::cout << "Median from vertex A: " << median_a2 << "\n";
    std::cout << "Median from vertex B: " << median_b2 << "\n";
    std::cout << "Median from vertex C: " << median_c2 << "\n";


    return 0;
}
