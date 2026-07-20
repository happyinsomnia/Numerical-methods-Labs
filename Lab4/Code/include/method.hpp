#pragma once
#include <functional>
#include <vector>

struct DifferentialEquation
{
    std::function<double(double)> p;
    std::function<double(double)> q;
    std::function<double(double)> r;
    std::function<double(double)> f;

    DifferentialEquation(
        std::function<double(double)> p,
        std::function<double(double)> q,
        std::function<double(double)> r,
        std::function<double(double)> f)
    {
        this->p = p;
        this->q = q;
        this->r = r;
        this->f = f;
    }
};

struct BoundaryConditions
{
    double alpha_0;
    double alpha_1;
    double beta_0;
    double beta_1;

    double A;
    double B;

    BoundaryConditions(
        double alpha_0,
        double alpha_1,
        double beta_0,
        double beta_1,
        double A,
        double B)
    {
        this->alpha_0 = alpha_0;
        this->alpha_1 = alpha_1;
        this->beta_0 = beta_0;
        this->beta_1 = beta_1;
        this->A = A;
        this->B = B;
    }
};

// for function s
double methodEuler(double x_k, double s_k, double h, std::function<double(double, double)> func);

// for function s
double modifiedEulerMethod(double x_k, double s_k, double h, std::function<double(double, double)> func);

// for function t
double methodEuler(double x_k, double t_k, double s_k, double h, std::function<double(double, double, double)> func);

// for function t
double modifiedEulerMethod(double x_k, double t_k, double s_k, double s_half, double h, std::function<double(double, double, double)> func);

// for y(x) function
double methodEulerBackwards(double x_k, double y_k, double s_k, double t_k, double h, std::function<double(double, double, double)> func);

// for y(x) function
double modifiedEulerMethodBackwards(double x_k, double y_k, double s_k, double s_half, double t_k, double t_half, double h, std::function<double(double, double, double)> func);

std::vector<double> factorizationMethod(double a,
                                        double b,
                                        double h,
                                        const DifferentialEquation &equations,
                                        const BoundaryConditions &conditions,
                                        const double delta = 0.0);