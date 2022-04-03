#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "half.hpp" // https://github.com/suruoxi/half

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
T predict_h(T h, T upper, T inc, std::string filename);

TYPE
T third_derivative(T x) // third derivative of fx
{ return T(-2.4) * x - T(0.9); }

int main()
{
    // Find optimal H value numerically
    double dbl_h_pred = predict_h(double(0.0000000001), double(0.0001), 
                                  double(0.0000000001), "double.txt");
    float flt_h_pred = predict_h(float(0.00001),float(0.1), float(0.00001), "float.txt");
    half_float::half hlf_h_pred(predict_h(half_float::half(0.001), half_float::half(0.5), 
                                   half_float::half(0.001), "half.txt"));

    // Find theoretical H based on machine epsilon
    double dbl_h_opt = cbrt((double(3) * __DBL_EPSILON__) / abs(third_derivative(double(0.5))));
    float flt_h_opt = cbrt((float(3) * __FLT_EPSILON__) / abs(third_derivative(float(0.5))));
    half_float::half hlf_h_opt = cbrt((half_float::half(3) * half_float::half(__FLT16_EPSILON__) 
                                       / abs(third_derivative(half_float::half(0.5)))));
    /*
        Note to marker: __FLT16_EPSILON__ works with clang++.
        If using gcc a define as follows will be needed:
        #define __FLT16_EPSILON__ half_float::half(0.000976562)
        Note that this value is explicit from printing the 
        value of __FLT16_EPSILON__ in clang.
                                                                */
                                                            
    /*
        Line equations derived from python trendline fitting
        Double: y=0.357730803912x+(-0.000000929785)
        Float: y=0.502896x+(-0.095061)
        Half: y=0.352463x+(-0.000297)

        Solve for x and that is theoretical h opt
                                                                */
    double d_actualh = double(-0.000000929785) / double(0.357730803912);
    float f_actualh = float(-0.095061) / float(0.502896);
    half_float::half h_actualh(half_float::half(-0.000297) / half_float::half(0.352463));

    cout << "Double Precision Predicted H = \t" << dbl_h_pred << endl << 
            "Single Precision Predicted H = \t" << flt_h_pred << endl << 
            "Half Precision Predicted H = \t" << hlf_h_pred << endl << endl;

    cout << "Double Precision Optimal H Using Machine Epsilon = \t" << dbl_h_opt << endl << 
            "Single Precision Optimal H Using Machine Epsilon = \t" << flt_h_opt << endl << 
            "Half Precision Optimal H Using Machine Epsilon = \t" << hlf_h_opt << endl << endl;

    cout << "Double Precision Optimal H Using Line Equation = \t" << abs(d_actualh) << endl <<
            "Single Precision Optimal H Using Line Equation = \t" << abs(f_actualh) << endl <<
            "Half Precision Optimal H Using Line Equation =   \t" << abs(h_actualh) << endl;                                   
    

    return 0;
}

TYPE
T predict_h(T h, T upper, T inc, std::string filename)
{// compare double vs float
    std::ofstream outfile;
    outfile.open(filename); // used for creating graph of derivative
    T actual = fx_(T(0.5)), error = T(1.), best_h = T(0.);

    for (T i = h; i <= upper; i += inc)
    {// loop different h values
        T predicted = central_dif(T(0.5), T(i));
        T true_error = fabs((actual - predicted));
        outfile << log(i) << " " << log(true_error) << endl;

        if (true_error < error) 
        {// update current best h
            error = true_error;
            best_h = i;
        }
    }
    return best_h; // optimal h
    outfile.close();
}