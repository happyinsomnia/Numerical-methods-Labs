#pragma once
#include <method.hpp>
#include <string>

void RunExperiments(const std::string path,
                    double a,
                    double b,
                    const DifferentialEquation &equations,
                    const BoundaryConditions &conditions);