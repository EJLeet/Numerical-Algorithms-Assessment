#include <iostream>
#include <map>
#include <fstream>

using std::endl;
using std::cout;

double rk4(double x, double h);
double rk4_(double y, double h, std::map<double, double> dydx);
double fn(double z) { return (60 / (2 * 1.25*10*10*10*10*10*10*10*10 * 0.05)) * ((30 - z) * (30 - z)); }

int main()
{
    double x = 0, h = 0.25, y = 0;
    std::map<double, double> dydx;
    std::ofstream outfile;

    /* 
        let x = dy/dz -> dx/dz = d^2y/d^2z
        Then run rk4 for x
        Use the datapoints derived to work out dx/dz
                                                        */
    cout << "x(0) = " << x << endl;
    for (double i = 0 + h / 2 ; i <= 30; i+= h / 2)
    {// loop from first step to length of rod
        x = rk4(i, h);
        dydx.insert({i, x});
        cout << "x(" << i << ") = " << x << endl;
    }
    cout << endl << endl;
    
    outfile.open("output.txt"); // used for creating graph
    cout << "y(0) = 0" << endl;
    for (double i = h ; i < 30; i += h)
    {// loop to point before end of rod.
     // we cant include point 30 in the function call
     // x + h (30 + 0.25) will be out of bounds.
        y = rk4_(i, h, dydx);
        outfile << y << endl;
        cout << "y(" << i << ") = " << y << endl;
    }
    outfile.close();
    return 0;
}

double rk4(double x, double h)
{// rk4 algorithm x

    double k1, k2, k3, k4;
    
    k1 = h * fn(x); // eulers

    k2 = h * fn(x + h/2); // midpoint of l1

    k3 = h * fn(x + h/2); // midpoint of l2

    k4 = h * fn(x + h); // 4th
    
    x = (1.0 / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4); // weighted sum

    return x;
}

double rk4_(double y, double h, std::map<double, double> dydx)
{// rk4 algorithm for dy/dz

    double k1, k2, k3, k4;
    
    k1 = h * dydx.at(y); // eulers

    k2 = h * dydx.at(y + h / 2); // midpoint of l1

    k3 = h * dydx.at(y + h / 2); // midpoint of l2

    k4 = h * dydx.at(y + h); // 4th
    
    y = (1.0 / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4); // weighted sum

    return y;
}