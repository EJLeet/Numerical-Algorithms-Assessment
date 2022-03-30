#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "half.h" // https://github.com/suruoxi/half

using std::cout;
using std::endl;

template <typename T>
T fx(T x) // given function
{ return T(-0.1) * x * x * x * x - T(0.15) * x * x * x - T(0.5) * x * x - T(0.15) * x + T(1.2); }

template <typename T>
T fx_(T x) // given function derivative
{ return T(-0.4) * x * x * x - T(0.45) * x * x - x - T(0.15); }

template <typename T>
T central_dif(T x, T h)// central difference formula
{ return (fx(x + h) - fx(x - h)) / (T(2) * h); }

template <typename T>
T optimal_h(T h, T upper, T inc);



int main()
{
    cout << optimal_h<double>(0.001, 3, 0.001) << endl;
    cout << optimal_h<float>(0.001, 3, 0.001) << endl;
    half_float::half h(0.001), upper(3), inc(0.001);
    cout << optimal_h<half_float::half>(h, upper, inc) << endl;
    return 0;
}

template <typename T>
T optimal_h(T h, T upper, T inc)
{// compare double vs float
    std::ofstream outfile;
    outfile.open("outfile.txt", std::ofstream::app); // used for creating graph of derivative
    T actual = fx_<T>(T(0.5)), error = T(1.), best_h = T(0.);

    for (T i = h; i <= upper; i += inc)
    {// loop 10k different h values
        T predicted = central_dif<T>(T(0.5), i);
        T true_error = fabs(log10(actual - predicted));
        outfile << true_error << endl;

        if (true_error < error) 
        {// update current best h
            error = true_error;
            best_h = i;
        }
    }
    return best_h; // optimal h
    outfile.close();
}