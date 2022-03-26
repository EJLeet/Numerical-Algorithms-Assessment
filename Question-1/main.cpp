#include <iostream>
#include <iomanip>
#include <fstream>

using std::cout;
using std::endl;

double fn(double x);
double central_dif(double x, double h)// central difference formula
{ return (fn(x + h) - fn(x - h)) / (2 * h); }

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

double fn(double x)
{
    return -0.1 * x * x * x * x - 0.15 * x * x * x -
           0.5 * x * x - 0.15 * x + 1.2;
}