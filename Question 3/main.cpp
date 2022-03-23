#include <iostream>
#include <iomanip>

using std::endl;
using std::cout;
double central_dif(double x, double h);
double fn(double x);
double power(double x, int y);
double rich_extrap(double x, double h);

int main()
{
    double x = 0.5, h = 1;

    for (int i = 1; i < 100; i++)
    { // test 100 decreasing h values
        cout << "Central Difference at h(" << h / i << ") = " <<
                std::setprecision(8) << central_dif(x, h / i) << endl;
        cout << "Richardson Extrapolation at h(" << h / i << ") = " <<
                std::setprecision(8) << rich_extrap(x, h / i) << endl;

    }
    return 0;
}

double central_dif(double x, double h)
{// central difference formula
    double fxh_plus = x + h;
    double fxh_minus = x - h;
    return (fn(fxh_plus) - fn(fxh_minus)) / (2 * h);
}

double fn(double x)
{// calculates above function for some x
     return -0.2 * power(x, 4) - 0.3 * power(x, 3) -
             1.5 * power(x, 2) - 0.45 * x + 2.6;
}

double power(double x, int y) 
{// O(logn) power approach recursive
 // logic is that x^3 = x * x^2

    double temp;  
    if(y == 0)
        return 1; 
    temp = power(x, y / 2); 

    if (y % 2 == 0)
        return temp * temp; 

    else
    {
        if(y > 0)
            return x * temp * temp; 
        else 
            return (temp * temp) / x; 
    } 
} 

double rich_extrap(double x, double h)
{// richard extrapolation
    double matrix[20][20] = {0};
    matrix[0][0] = central_dif(x, h); // fill in first column/row

    double err_tol = 0.5 * (power(10, 2 - 4));// error tolerance to 4 significant figs
    double curr_approx = 1;
    double prev_approx = 0;
    double rel_err = abs(curr_approx - prev_approx);

    int col = 1, row = 1;
    while(1)
    {
        h /= 2; // decrease h every time
        matrix[0][row] = central_dif(x, h);// add first column value
        
        for(int i = 1; i <= col; i++)
        {// compute rest of row
            matrix[i][row] = power(4, i) / (power(4, i) - 1) * matrix[i-1][row] - 
                             1 / (power(4, i) - 1) * matrix[i-1][row-1];
        }

        // check if low enough error margin
        double curr_approx = matrix[col][row];
        double prev_approx = matrix[col-1][row];
        double rel_err = abs(curr_approx - prev_approx);
        if(rel_err < err_tol)
            return matrix[col][row];
        row++;
        col++;
    }
    return EXIT_FAILURE;
}



