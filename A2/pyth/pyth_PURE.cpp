#include <iostream>

using namespace std;

const int square(const int e)
{
    int result = e;
    int dummy2 = e;
    for (int i = 1; i < dummy2; i++)
    {
        result += e;
    }

    return result;
}

const double squareroot(const double x)
{
    if (x == 0)
        return 0;

    double xhi = x;
    double xlo = 0;
    double guess = x / 2;

    while (abs(guess * guess - x) > 0.00001)
    {
        if (guess * guess > x)
        {
            xhi = guess;
        }
        else
        {
            xlo = guess;
        }

        guess = (xhi + xlo) / 2;
    }

    return guess;
}

const double pythagoras(const int x, const int y)
{
    return squareroot(square(x) + square(y));
}

int main(int argc, char *argv[])
{
    const int x = 3;
    const int y = 4;
    const double z = pythagoras(x, y);
    cout << "euklid:" << z << endl;
    return 0;
}
