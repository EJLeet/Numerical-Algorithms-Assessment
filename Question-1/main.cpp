#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "half.h" // https://github.com/suruoxi/half

using std::cout;
using std::endl;

template <typename T>
T fx(T x) // given function
{ return -0.1 * x * x * x * x - 0.15 * x * x * x - 0.5 * x * x - 0.15 * x + 1.2; }

template <typename T>
T fx_(T x) // given function derivative
{ return -0.4 * x * x * x - 0.45 * x * x - x - 0.15; }

template <typename T>
T central_dif(T x, T h)// central difference formula
{ return (fx(x + h) - fx(x - h)) / (2 * h); }

template <typename T>
T optimal_h();

half_float::half optimal_h_hf();

int main()
{
    // experiment with different h values for central difference formula and find optimal h
    cout << optimal_h<double>() << endl;
    cout << optimal_h<float>() << endl;
    //cout << optimal_h_hf() << endl;

    return 0;
}
template <typename T>
T optimal_h()
{// compare double vs float
    std::ofstream outfile;
    outfile.open("outfile.txt"); // used for creating graph of derivative

    T actual = fx_<T>(0.5), error = 1., best_h = 0.;
    for (T h = 0.001; h <= 10; h += 0.001)
    {// loop 10k different h values
        T predicted = central_dif<T>(0.5, h);
        T true_error = fabs(log10(actual - predicted));
        outfile << true_error << endl;
        if (true_error < error) 
        {// update current best h
            error = true_error;
            best_h = h;
        }
    }
    return best_h; // optimal h
    outfile.close();
}

// half_float::half optimal_h_hf()
// {
//     half_float::half x(0.5), hf_actual(fx_(0.5)), hf_err(1.), hf_h(0.0);
//     for (half_float::half h(0.027); h <= 3.99; h += 0.001)
//     {// as short float
//         half_float::half predicted(central_dif(x, h));
//         half_float::half true_error (fabs(log10(hf_actual - predicted)));
//         outfile << true_error << endl;
//         if (true_error < hf_err) 
//         {
//             hf_err = true_error;
//             hf_h = h;
//         }
//     }
//     return << hf_h << endl;

// }