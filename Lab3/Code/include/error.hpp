#pragma once
#include <functional>

double rungeRule(
    int s,
    double x_k,
    double y_k,
    double h,
    std::function<double(double, double)> func,
    std::function<double(double, double, double, std::function<double(double, double)>)> method);

double absoluteError(double exactValue, double methodValue);

double localError(double yActual, double yMethod);

double globalError(double yActual, double yMethod);