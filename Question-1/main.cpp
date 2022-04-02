#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "half.h" // https://github.com/suruoxi/half

using std::cout;
using std::endl;
#define TYPE template <typename T>

TYPE
T fx(T x) // given function
{ return T(-0.1) * x * x * x * x - T(0.15) * x * x * x - T(0.5) * x * x - T(0.15) * x + T(1.2); }

TYPE
T fx_(T x) // given function derivative
{ return T(-0.4) * x * x * x - T(0.45) * x * x - x - T(0.15); }

TYPE
T central_dif(T x, T h)// central difference formula
{ return (fx(x + h) - fx(x - h)) / (T(2) * h); }

TYPE
T optimal_h(T h, T upper, T inc, std::string filename);

int main()
{
    cout << optimal_h(double(0.0000000001), double(0.5), double(0.0001), "double.txt") << endl;
    cout << optimal_h(float(0.00001), float(0.5), float(0.002), "float.txt") << endl;
    cout << optimal_h(half_float::half(0.001), half_float::half(0.5), half_float::half(0.002), "half.txt") << endl;
    return 0;
}

TYPE
T optimal_h(T h, T upper, T inc, std::string filename)
{// compare double vs float
    std::ofstream outfile;
    outfile.open(filename); // used for creating graph of derivative
    T actual = fx_(T(0.5)), error = T(1.), best_h = T(0.);

    for (T i = h; i <= upper; i += inc)
    {// loop different h values
        T predicted = central_dif(T(0.5), T(i));
        T true_error = fabs((actual - predicted));
        outfile << log10(i) << " " << log10(true_error) << endl;

        if (true_error < error) 
        {// update current best h
            error = true_error;
            best_h = i;
        }
    }
    return best_h; // optimal h
    outfile.close();
}