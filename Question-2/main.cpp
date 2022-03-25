#include <iostream>
#include <iomanip>
#include <vector>

using std::cout;
using std::endl;

double multi_app_simpson(double a, double b, int seg);
double fn(double x);

int main()
{
    std::vector<double> t1, t2, t3;

    for (int i = 1; i <= 30; i++)
    {   
        if (i <= 10) 
            t1.push_back(multi_app_simpson(0, 10, i));
        else if (i <= 20)
            t2.push_back(multi_app_simpson(10, 20, i));
        else
            t3.push_back(multi_app_simpson(20, 30, i));
    }

    for (int i = 0; i < 10; i++)
        cout << "Distance Using Multi-Application Simpsons for Segment " << i + 1 << 
                " = " << std::setprecision(10) << t1[i] + t2[i] + t3[i] << endl;

    cout << "Analytical Distance = " << std::setprecision(10) 
         << double(80500) / double(3) << endl;
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
{
    if (x <= 10) 
        return 11 * (x * x) - 5 * x;
    else if (x <= 20)
        return 1100 - 5 * x;
    else
        return 50 * x + 2 * ((x - 20) * (x - 20));
}

