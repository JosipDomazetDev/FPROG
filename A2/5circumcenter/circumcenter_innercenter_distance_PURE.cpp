#include <iostream>
#include <tuple>

const auto square_root = [](const double x, const double epsilon = 1e-10, const int max_iterations = 1000) {
    if (x < 0) {
        return -1.0; // Invalid input
    }
    if (x == 0) {
        return 0.0;
    }

    double low = 0.0, high = x;
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

const auto calculate_area_and_radii = [](const double a, const double b, const double c) {
    double s = (a + b + c) / 2;
    double area = square_root(s * (s - a) * (s - b) * (s - c));
    double inradius = area / s;
    double circumradius = (a * b * c) / (4 * area);

    return std::make_tuple(s, area, inradius, circumradius);
};

const auto calculate_distance = [](const double circumradius, const double inradius) {
    return square_root(circumradius * circumradius - 2 * circumradius * inradius);
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
    auto curried_calculate_area_and_radii = curry(calculate_area_and_radii);
    auto curried_calculate_distance = curry(calculate_distance);

    const double a = 3, b = 4, c = 5;
    std::cout << "Triangle sides: a = " << a << ", b = " << b << ", c = " << c << "\n";

    auto result = curried_calculate_area_and_radii(a)(b)(c);
    double s = std::get<0>(result);
    double area = std::get<1>(result);
    double inradius = std::get<2>(result);
    double circumradius = std::get<3>(result);


    std::cout << "Inradius: " << inradius << "\n";
    std::cout << "Circumradius: " << circumradius << "\n";

    double distance = curried_calculate_distance(circumradius)(inradius);
    std::cout << "Distance between circumcenter and incenter: " << distance << "\n";


    std::cout << "===========================================" << "\n";

    result = curried_calculate_area_and_radii(a)(b)(c);
    s = std::get<0>(result);
    area = std::get<1>(result);
    inradius = std::get<2>(result);
    circumradius = std::get<3>(result);

    std::cout << "Inradius: " << inradius << "\n";
    std::cout << "Circumradius: " << circumradius << "\n";

    distance = curried_calculate_distance(circumradius)(inradius);
    std::cout << "Distance between circumcenter and incenter: " << distance << "\n";

    return 0;
}
