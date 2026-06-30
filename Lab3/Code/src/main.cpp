#include <experiments.hpp>
#include <functions.hpp>
#include <method.hpp>

int main()
{
    RunExperiment("../data/plot_data/", 0.0, 1.0, 4.0, function, exactFunction, modifiedEulerMethod, 2);
    return 0;
}