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
    // Use double to increase overall precision of result using <TYPE> epsilon
    double dbl_h_opt = cbrt((double(3) * __DBL_EPSILON__) / abs(third_derivative(double(0.5))));
    double flt_h_opt = cbrt((double(3) * __FLT_EPSILON__) / abs(third_derivative(double(0.5))));
    double hlf_h_opt = cbrt((double(3) * __FLT16_EPSILON__ / abs(third_derivative(double(0.5)))));
                                       
    /*

        Note to marker: __FLT16_EPSILON__ works with clang++.
        If using gcc a define as follows will be needed:
        #define __FLT16_EPSILON__ half_float::half(0.000976562)
        Note that this value is explicit from printing the 
        value of __FLT16_EPSILON__ in clang.     

                                                                    */
    /*

        Line equations and optimal h (x value from solving quadratic) 
        derived from python trendline fitting:

        Half = y=0.502896x^2 + -0.095061x + 0.012796 = h opt = 0.09451
        Float = y=0.352463x^2 + -0.000297x + 0.000007 = h opt = 0.00042
        Double = y=0.357730803912x^2 + -0.000000929785x + 0.000000000023 = h opt = 0.00000128751

                                                                                                    */
                                                                                            
    cout << "Double Precision Predicted H = \t\t\t\t\t" << dbl_h_pred << endl << 
            "Single Precision Predicted H = \t\t\t\t\t" << flt_h_pred << endl << 
            "Half Precision Predicted H = \t\t\t\t\t" << hlf_h_pred << endl << endl;

    cout << "Theoretical Optimal H Using Double Machine Epsilon = \t\t" << dbl_h_opt 
         << endl << "Theoretical Optimal H Using Float Machine Epsilon = \t\t" 
         << flt_h_opt << endl << "Theoretical Optimal H Using Half Machine Epsilon = \t\t" 
         << hlf_h_opt << endl << endl; 

    // As h_opts are cast to double, need to pass the x as double to the templated class                              
    cout << "Central Difference Derivative Using Theoretical H as Double = \t" 
         << central_dif(double(0.5), dbl_h_opt) << endl 
         << "Central Difference Derivative Using Theoretical H as Float = \t" 
         << central_dif(double(0.5), flt_h_opt) << endl
         << "Central Difference Derivative Using Theoretical H as Half = \t" 
         << central_dif(double(0.5), hlf_h_opt) << endl << endl;
    
    cout << "Central Difference Derivative Using Line Equation H as Double = " 
         << central_dif(double(0.5), double(0.00000128751)) << endl 
         << "Central Difference Derivative Using Line Equation H as Float = \t" 
         << central_dif(float(0.5), float(0.00042)) << endl
         << "Central Difference Derivative Using Line Equation H as Half = \t" 
         << central_dif(half_float::half(0.5), half_float::half(0.09451)) << endl;

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