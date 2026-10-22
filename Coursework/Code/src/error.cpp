#include <error.hpp>

double norm(const std::vector<double> exact, const std::vector<double> yMethod)
{
    double maxNorm = 0.0;

    for (size_t i = 0; i < exact.size(); i++)
    {
        double steNorm = std::abs(exact[i] - yMethod[i]);

        if (maxNorm < steNorm)
            maxNorm = steNorm;
    }

    return maxNorm;
}

double stepError(double y_method, double y_actual)
{
    return std::abs(y_actual - y_method);
}
