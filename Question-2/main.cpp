#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>

using std::cout;
using std::endl;

double multi_app_simpson(double a, double b, int seg);
double fn(double x);
double rich_extrap(double x, double h);
double central_dif(double x, double h);

int main()
{
    std::vector<double> t1, t2, t3;
    std::ofstream outfile;

    for (int i = 1; i <= 30; i++)
    { // 10 segments for 3 different t values  
        if (i <= 10) 
            t1.push_back(multi_app_simpson(0, 10, i));
        else if (i <= 20)
            t2.push_back(multi_app_simpson(10, 20, i));
        else
            t3.push_back(multi_app_simpson(20, 30, i));
    }

    for (int i = 0; i < 10; i++) // evaluate distance for each segment
        cout << "Distance Using Multi-Application Simpsons for Segment " << i + 1 << 
                " = " << std::setprecision(10) << t1[i] + t2[i] + t3[i] << endl;

    cout << "Analytical Distance = " << std::setprecision(10) 
         << double(80500) / double(3) << endl;

    outfile.open("output.txt"); // used for creating graph
    for (int i = 1; i <= 30; i++)
    { // 10 segments for 3 different t values  
        // remove cout
        cout << "dv/dt at t = " << i << " = " << rich_extrap(i, 0.25) << endl;
        outfile << rich_extrap(i, 0.25) << endl;
    }

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
{// apply applicable function for approriate t
    if (x <= 10) 
        return 11 * (x * x) - 5 * x;
    else if (x <= 20)
        return 1100 - 5 * x;
    else
        return 50 * x + 2 * ((x - 20) * (x - 20));
}

double rich_extrap(double x, double h)
{ // richard extrapolation

    // fill in first column/row
    std::vector<std::vector<double>> matrix;
    matrix.push_back(std::vector<double>(1));
    matrix[0][0] = central_dif(x, h);

    // error tolerance to 10 significant figs (10^2-8)
    double err_tol = 0.5 * (1 / (10.0 * 10.0 * 10.0 * 10.0 * 10.0 * 10.0 * 10.0 * 10.0)), 
                     curr_approx = 1, prev_approx = 0, 
                     rel_err = abs((curr_approx - prev_approx) / curr_approx);

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
        rel_err = abs((curr_approx - prev_approx) / curr_approx);
    }
        return matrix[row][col];
}

double central_dif(double x, double h)
{
    double fxh_plus = x + h;
    double fxh_minus = x - h;
    return (fn(fxh_plus) - fn(fxh_minus)) / (2 * h);
}
