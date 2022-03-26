#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <math.h>

using std::cout;
using std::endl;

double central_dif(double x, double h);
double fn(double x);
double rich_extrap(double x, double h);

int main()
{
    std::ofstream outfile;
    outfile.open("output.txt"); // used for creating graph

    double x = 0.5, h = 0.25;

    for (int i = 1; i <= 100; i++)
    { // experiment with different h values for central difference formula
        double temp = central_dif(x, h / i);
        cout << "Central Difference at h(" << h / i << ") = "
             << std::setprecision(8) << temp << endl;
        outfile << temp << endl;
    }
    outfile.close();

    cout << "Richardson Extrapolation at = " << std::setprecision(8)
         << rich_extrap(x, h) << endl
         << "Actual Derivative = -2.275" << endl;

    return 0;
}

double central_dif(double x, double h)
{ // central difference formula
    double fxh_plus = x + h;
    double fxh_minus = x - h;
    return (fn(fxh_plus) - fn(fxh_minus)) / (2 * h);
}

double fn(double x)
{ // calculates given function x
    return -0.2 * x * x * x * x - 0.3 * x * x * x -
           1.5 * x * x - 0.45 * x + 2.6;
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

        int x_next = 4;
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