/*
Python3 and matplotlib are required for this file.
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>

using std::cout;
using std::endl;

double central_dif(double x, double h);
double fn(double x);
double power(double x, int y);
double rich_extrap(double x, double h);

int main()
{
    std::ofstream outfile;
    outfile.open("output.txt");

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
         << "Actual Result = -2.275" << endl;

    system("python3 plot.py");

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
    return -0.2 * power(x, 4) - 0.3 * power(x, 3) -
           1.5 * power(x, 2) - 0.45 * x + 2.6;
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

double rich_extrap(double x, double h)
{ // richard extrapolation

    // fill in first column/row
    std::vector<std::vector<double>> matrix;
    matrix.push_back(std::vector<double>(1));
    matrix[0][0] = central_dif(x, h);

    // error tolerance to 8 significant figs
    double err_tol = 0.5 * (power(10, 2 - 8)), curr_approx = 1,
           prev_approx = 0, rel_err = abs(curr_approx - prev_approx);

    int col = 0, row = 0;
    while (rel_err > err_tol)
    { // loop until tolerance is met
        row++;
        col++;
        h /= 2;                                     // decrease h every time
        matrix.push_back(std::vector<double>(col)); // allocate memory for the correct amount of columns
        matrix[0][row] = central_dif(x, h);         // add first column value

        for (int i = 1; i <= col; i++) // compute rest of row
            matrix[i][row] = power(4, i) / (power(4, i) - 1) * matrix[i - 1][row] -
                             1 / (power(4, i) - 1) * matrix[i - 1][row - 1];

        // check if low enough error margin
        curr_approx = matrix[col][row];
        prev_approx = matrix[col - 1][row];
        rel_err = abs(curr_approx - prev_approx);
    }
    return matrix[col][row];
}