#include <iostream>
#include <cmath>
#include <vector>

using std::cout;
using std::endl;

double f(double x) // given function
{ return (exp(-x) - x + x * x) - 4; }
std::tuple<double, int> bisection(double a, double b, double tolerance);
double central_dif(double x, double h) // central difference formula
{ return (f(x + h) - f(x - h)) / (2 * h); }
std::tuple<double, int> newton_raphson(double x, double tolerance);
double rich_extrap(double x, double h);
std::tuple<double, int> secant(double a, double b, double tolerance);

int main()
{
    double a = -1., b = 0., tolerance = 0.00001, res;
    int count;
    
    std::tie(res, count) = bisection(a, b, tolerance);
    cout << "Bisection Method Root = " << res << " \t"
         << "Iterations needed = " << count << endl;

    std::tie(res, count) = newton_raphson(a, tolerance);
    cout << "Newton-Raphson Method Root = " << res << " \t"
         << "Iterations needed = " << count << endl;

    std::tie(res, count) = secant(a, b, tolerance);
    cout << "Secant Method Root = " << res << " \t"
         << "Iterations needed = " << count << endl;

    return 0;
}

std::tuple<double, int> bisection(double a, double b, double tolerance)
{
    double c;
    int count = 0;
    while ((b - a) >= tolerance)
    {// loop until the interval is less than the tolerance
        c = (a + b) / 2; // find midpoint

        if (f(c) == 0.0) // if midpoint is a root
            break;
        // otherwise change intervals
        else if ((f(c) * f(a)) < 0)
            b = c;
        else
            a = c;
        count++;
    }
    return {c, count};
}

double rich_extrap(double x, double h)
{ // richard extrapolation

    // fill in first column/row
    std::vector<std::vector<double>> matrix;
    matrix.push_back(std::vector<double>(1));
    matrix[0][0] = central_dif(x, h);

    // error tolerance to 6 significant figs (10^2-6)
    double err_tol = 0.5 * (1 / (10.0 * 10.0 * 10.0 * 10.0)),
           curr_approx = 1, prev_approx = 0,
           rel_err = fabs((curr_approx - prev_approx) / curr_approx);

    int col = 0, row = 0;
    while (rel_err > err_tol)
    { // loop until tolerance is met
        // move to next cell and decrease h
        row++;
        col++;
        h /= 2;
        matrix.push_back(std::vector<double>(row)); // allocate memory for the correct amount of columns
        matrix[row][0] = (central_dif(x, h));       // add first column value

        double x_next = 4.0;
        for (int i = 1; i <= col; i++)
        { // compute rest of row
            matrix[row][i] = (x_next / (x_next - 1)) * matrix[row][i - 1] -
                             (1 / (x_next - 1)) * matrix[row - 1][i - 1];
            x_next *= 4;
        }

        // check if low enough error margin
        curr_approx = matrix[row][col];
        prev_approx = matrix[row - 1][col - 1];
        rel_err = fabs((curr_approx - prev_approx) / curr_approx);
    }
    return matrix[row][col];
}

std::tuple<double, int> newton_raphson(double x, double tolerance)
{
    double z = 1.;
    int count = 0;
    while (fabs(f(z)) > tolerance)
    { // loop until tolerance met
        // update x with f(x) - f'(x)
        z = x - (f(x) / rich_extrap(x, 0.05));
        x = z;
        count++;
    }
    return {x, count};
}

std::tuple<double, int> secant(double a, double b, double tolerance)
{
    double c;
    int count = 0;
    while (fabs(b - a) >= tolerance)
    { // loop until the interval is less than the tolerance
        // calculate the intermediate
        c = b - (f(b) * (b - a)) / (f(b) - f(a));
        // update intervals
        a = b;
        b = c;
        count++;
    }
    return {c, count};
}