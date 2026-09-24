#include <experiments.hpp>

using namespace std;

int main(int argc, char **argv)
{
    // TODO: Зависимость максимальной ошибки от числа узлов

    RunSmoothFunctionExperiment(1.0, 4.0, 20, 500);
    RunNonSmoothFunctionExperiment(2.0, 4.0, 20, 500);

    return 0;
}