#include <iostream>

using std::cout;
using std::endl;

double multi_app_simpson(double a, double b, int seg);
double fn(double x);
double power(double x, int y);

int main()
{

    return 0;
}

double multi_app_simpson(double a, double b, int seg)
{ // multi application simpsons 1/3

    double step = (b - a) / seg; // h
    double odd_sum = 0, even_sum = 0, ans = 0;

    for (int i = 1; i <= seg - 1; i += 2)
    { // even sum part of formula
        double res = a + step * i;
        odd_sum += fn(res);
    }

    for (int i = 2; i <= seg - 2; i += 2)
    { // odd sum part of formula
        double res = a + step * i;
        even_sum += fn(res);
    }

    return (step / 3) * (fn(a) + 4 * odd_sum + 2 * even_sum + fn(b));
}

double fn(double x)
{ // calculates above function for some x
    return 0.2 + 25 * x - 200 * power(x, 2) + 675 * power(x, 3) -
           900 * power(x, 4) + 400 * power(x, 5);
}

double power(double x, int y)
{ // O(logn) power approach recursive. logic is that x^3 = x * x^2
    if (y == 0)
        return 1;

    double temp = power(x, y / 2);

    if (y % 2 == 0)
        return temp * temp;

    else
        return y > 0 ? x * temp * temp : (temp * temp) / x;
}