#include <iostream>
#include <fileIO.hpp>
#include <method.hpp>
#include <functions.hpp>
#include <cmath>

using namespace std;

int main()
{
    double a = 2;
    double b = 5;
    double actualValueFunc1 = (pow(b, 2) / 2 + 3 * b) - (pow(a, 2) / 2 + 3 * a);
    double actualValueFunc2 = (3 * (pow(b, 4) / 4) + (pow(b, 3) / 3) - 5 * (pow(b, 2) / 2) + 2 * b) -
                              (3 * (pow(a, 4) / 4) + (pow(a, 3) / 3) - 5 * (pow(a, 2) / 2) + 2 * a);

    WriteData("../data/function1 data/data.csv", a, b, TrapezoidalRule, Function1, actualValueFunc1);
    WriteData("../data/function2 data/data.csv", a, b, TrapezoidalRule, Function2, actualValueFunc2);
    
    
    return 0;
}