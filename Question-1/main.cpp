#include <iostream>
#include <iomanip>
#include <fstream>

using std::cout;
using std::endl;

double central_dif(double x, double h);
double fn(double x);
double power(double x, int y);

int main()
{
    std::ofstream outfile;
    outfile.open("output.txt"); // used for creating graph

    double x = 0.5, h = 0.25;

    for (int i = 1; i <= 3000; i++)
    { // experiment with different h values for central difference formula
        double temp = central_dif(x, h / i);
        cout << "Central Difference at h(" << h / i << ") = "
             << std::setprecision(8) << temp << endl;
        outfile << temp << endl;
    }
    cout << "Actual Derivative = -0.8125" << endl;
    outfile.close();
    return 0;
}

double central_dif(double x, double h)
{ // central difference formula
    double fxh_plus = x + h;
    double fxh_minus = x - h;
    return (fn(fxh_plus) - fn(fxh_minus)) / (2 * h);
}

double fn(double x)
{ // calculates above function for some x
    return -0.1 * power(x, 4) - 0.15 * power(x, 3) -
           0.5 * power(x, 2) - 0.15 * x + 1.2;
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