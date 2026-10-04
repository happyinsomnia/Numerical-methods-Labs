#pragma once

#include <functional>
#include <cmath>

/// @brief Считает ожидаемую точность по правилу Рунге
/// @param a Левая граница
/// @param b Правая граница
/// @param m Порядок метода
/// @param N Число разбиений
/// @param method Метод, которым считаем
/// @param func Функция, которой считаем интеграл
double RungeError(double a,
                  double b,
                  int m,
                  int N,
                  std::function<double(double, double, int, std::function<double(double)>)> method,
                  std::function<double(double)> func);

/// @brief Считает ошибку Рунге, используя сохраненное значение для N
/// @param approximation При входе значение метода для N, при выходе значение для 2*N
double RungeError(double a,
                  double b,
                  int m,
                  int N,
                  std::function<double(double, double, int, std::function<double(double)>)> method,
                  std::function<double(double)> func,
                  double &approximation);

double AbsoluteError(double absoluteValue, double calculatedValue);
