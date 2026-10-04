#include <experiments.hpp>

using namespace std;

int main(int argc, char **argv)
{
    RunSmoothFunctionExperiment(1.0, 4.0, 35, 200);
    RunNonSmoothFunctionExperiment(2.0, 4.0, 35, 200);

    return 0;
}