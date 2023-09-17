#include <iostream>
#include <functional>

using namespace std;

const auto square = [](const int e) {
    int result = e;
    int dummy2 = e;
    for (int i = 1; i < dummy2; i++) {
        result += e;
    }
    return result;
};

const auto squareroot = [](const double x) {
    if (x == 0)
        return 0.0;

    double xhi = x;
    double xlo = 0.0;
    double guess = x / 2;

    while (abs(guess * guess - x) > 0.00001) {
        if (guess * guess > x)
            xhi = guess;
        else
            xlo = guess;

        guess = (xhi + xlo) / 2;
    }

    return guess;
};

const auto pythagoras = [](const int x, const int y) {
    return squareroot(square(x) + square(y));
};

template<typename Func>
auto curry(Func func) {
    return [func](auto x) {
        return [func, x](auto y) {
            return func(x, y);
        };
    };
}

int main(int argc, char *argv[]) {
    const int x = 3;
    const int y = 4;

    const auto curried_pythagoras = curry(pythagoras);
    double z = curried_pythagoras(x)(y);
    cout << "euklid:" << z << endl;

    z = curried_pythagoras(x)(y);
    cout << "euklid:" << z << endl;

    return 0;
}
