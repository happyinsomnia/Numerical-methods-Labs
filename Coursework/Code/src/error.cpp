#include <error.hpp>
#include <iostream>

double globalError(double yExact, double yMethod)
{
    return std::abs(yExact - yMethod);
}

double maxError(const std::vector<double> &exactValues, const std::vector<double> &methodValues)
{
    if (exactValues.size() != methodValues.size())
    {
        std::cerr << "Function maxError sizes ain't equal" << std::endl;
        return 0.0;
    }

    double _maxError = 0.0;
    for (size_t i = 0; i < exactValues.size(); i++)
    {
        double step = std::abs(exactValues[i] - methodValues[i]);

        if (step > _maxError)
            _maxError = step;
    }

    return _maxError;
}