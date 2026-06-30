#pragma once
#include <functional>
#include <string>

void RunExperiment(
    std::string path,
    double x0,
    double y0,
    double right,
    std::function<double(double, double)> func,
    std::function<double(double)> exactFunc,
    std::function<double(double, double, double, std::function<double(double, double)>)> method,
    int s);