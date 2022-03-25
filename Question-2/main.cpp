#include <iostream>

using std::cout;
using std::endl;

double multi_app_simpson(double a, double b, int seg);
double fn_t10(double x);
double fn_t20(double x);
double fn_t30(double x);

int main()
{// loop from t = 0 to 30 = seg
 // check in function what range seg (t) is in
 // apply appropriate function

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

double fn_t10(double x)
{ // calculates given function for interval 0 <= t <=  10
    return 0.2 + 25 * x - 200 * power(x, 2) + 675 * power(x, 3) -
           900 * power(x, 4) + 400 * power(x, 5);
}

double fn_t10(double x)
{ // calculates given function for interval 10 <= t <=  20
    return 0.2 + 25 * x - 200 * power(x, 2) + 675 * power(x, 3) -
           900 * power(x, 4) + 400 * power(x, 5);
}
double fn_t10(double x)
{ // calculates given function for interval 20 <= t <=  30
    return 0.2 + 25 * x - 200 * power(x, 2) + 675 * power(x, 3) -
           900 * power(x, 4) + 400 * power(x, 5);
}
