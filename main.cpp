#include <iostream>

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

const void calculate_area_and_radii(const double a, const double b, const double c, double& s, double& area, double& circumradius, double& inradius)  {
    s = (a + b + c) / 2;
    area = square_root(s * (s - a) * (s - b) * (s - c));
    inradius = area / s;
    circumradius = (a * b * c) / (4 * area);
}

const double calculate_distance(const double circumradius, const double inradius)  {
    return square_root(circumradius * circumradius - 2 * circumradius * inradius);
}

int main() {
    const double a = 3, b = 4, c = 5;
    std::cout << "Triangle sides: a = " << a << ", b = " << b << ", c = " << c << "\n";

    double s, area, circumradius, inradius, distance;
    calculate_area_and_radii(a, b, c, s, area, circumradius, inradius);
    std::cout << "Inradius: " << inradius << "\n";
    std::cout << "Circumradius: " << circumradius << "\n";

    distance = calculate_distance(circumradius, inradius);
    std::cout << "Distance between circumcenter and incenter: " << distance << "\n";

    std::cout << "===================" <<"\n";

    calculate_area_and_radii(a, b, c, s, area, circumradius, inradius);
    std::cout << "Inradius: " << inradius << "\n";
    std::cout << "Circumradius: " << circumradius << "\n";

    distance = calculate_distance(circumradius, inradius);
    std::cout << "Distance between circumcenter and incenter: " << distance << "\n";




    return 0;
}
