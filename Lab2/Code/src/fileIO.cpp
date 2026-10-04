#include "fileIO.hpp"
#include <cmath>
#include <method.hpp>
#include <fstream>
#include <format>
#include <iostream>
#include <error.hpp>
#include <filesystem>

void WriteData(const std::string &filename,
               double a,
               double b,
               std::function<double(double, double, int, std::function<double(double)>)> method,
               std::function<double(double)> func,
               const double actualValue)
{
    std::vector<double> epsilon{10e-2, 10e-3, 10e-4, 10e-5, 10e-6, 10e-7, 10e-8, 10e-9, 10e-10, 10e-11};
    std::filesystem::create_directories("../data/function1 data/");
    std::filesystem::create_directories("../data/function2 data/");

    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cout << std::format("Can not open the file {}", filename) << std::endl;
        return;
    }

    // Graphic 1: Error vs Number of approximation

    file << "error vs epsilon" << '\n';

    for (size_t k = 0; k < epsilon.size(); k++)
    {
        double eps = epsilon[k];

        int N = 1;
        double approximation = TrapezoidalRule(a, b, N, func);
        auto error = RungeError(a, b, 2, N, TrapezoidalRule, func, approximation);
        while (error > eps)
        {
            N *= 2;
            error = RungeError(a, b, 2, N, TrapezoidalRule, func, approximation);
        }

        file << AbsoluteError(actualValue, approximation) << ',' << eps << '\n';
    }

    // Graphic 2: N vs Number of approximation

    file << '\n'
         << "N vs epsilon" << '\n';

    for (size_t k = 0; k < epsilon.size(); k++)
    {
        double eps = epsilon[k];

        int N = 1;
        double approximation = TrapezoidalRule(a, b, N, func);

        auto error = RungeError(a, b, 2, N, TrapezoidalRule, func, approximation);

        while (error > eps)
        {
            N *= 2;
            error = RungeError(a, b, 2, N, TrapezoidalRule, func, approximation);
        }

        file << 2 * N << ',' << eps << '\n';
    }

    // Graphic 3: error vs h

    file << '\n'
         << "error vs h" << '\n';

    for (size_t i = 0; i <= 10; i++)
    {
        int N = pow(2, i);
        double h = (b - a) / N;

        double calculatedValue = TrapezoidalRule(a, b, N, func);

        file << AbsoluteError(actualValue, calculatedValue) << ',' << h << '\n';
    }

    file.close();
}