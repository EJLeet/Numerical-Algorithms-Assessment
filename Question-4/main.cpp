#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>

using std::endl;
using std::cout;

double romberg(double t1, double t2, double tolerance);
double ft(double t)
{
    return ((9 + 4 * (cos(0.4 * t) * cos(0.4 * t))) * 
            (5 * exp(-0.5 * t) + 2 * exp(0.15 * t)));
}
double multi_trap(double a, double b, double seg);

int main()
{
    double t1 = 2., t2 = 8., tolerance = 0.001;
    cout << "Romberg Inegration = " << std::setprecision(8) 
         << romberg(t1, t2, tolerance) << endl;
    return 0;
}

double romberg(double t1, double t2, double tolerance)
{
    int n = 1, row = 0, col = 0;
    double curr_approx = 1, prev_approx = 0,
           rel_err = fabs((curr_approx - prev_approx) / curr_approx);

    // create matrix and assign first cell memory (0,0)
    std::vector<std::vector<double>> matrix;
    matrix.push_back(std::vector<double>(1));

    while (rel_err > tolerance)
    {// loop until tolerance met
        double x_next = 4.;
        for (col = 0; col <= row; col++)
        {// fill rest of row
            if (col == 0) // if in column 0 use multi trap
                matrix[row][col] = multi_trap(t1, t2, n);
            else
            {// use rombert formula
                matrix[row][col] = (x_next * matrix[row][col - 1] - 
                                    matrix[row - 1][col - 1]) / (x_next - 1);
                x_next *= 4;
            }
        }
        // work out error tolerance
        curr_approx = matrix[row][col - 1];
        prev_approx = matrix[row - 1][col - 2];
        rel_err = fabs((curr_approx - prev_approx) / curr_approx);

        row++;
        n *= 2;
        matrix.push_back(std::vector<double>(row + 1)); // allocate memory for the correct amount of columns
    }
    return curr_approx;
}

double multi_trap(double a, double b, double seg)
{ // calculate multi-trapezoidal rule for integral ranges a and b on some function

    double ans = 0, h = (b - a) / seg;

    for (int i = 1; i <= seg - 1; i++)
    { // sum part of formula
        double res = a + h * i;
        ans += ft(res);
    }
    return ((ans * 2) + ft(a) + ft(b)) * ((b - a) / (2 * seg));
}
