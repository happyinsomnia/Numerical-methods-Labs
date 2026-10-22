#pragma once
#include <string>
#include <method.hpp>
using namespace factorization_method;

void RunExperiments(std::string path,
                    double a,
                    double b,
                    const DifferentialEquation &equations,
                    const BoundaryConditions &conditions);