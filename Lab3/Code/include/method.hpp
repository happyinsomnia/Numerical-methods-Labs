#pragma once
#include <functional>

/// @brief Метод Эйлера с шагом h/2
/// @param x_k 
/// @param y_k 
/// @param h 
/// @param func 
/// @return значение y, полученное методом Эйлера
double methodEuler(double x_k, double y_k, double h, std::function<double(double, double)> func);

/// @brief Модифицированный метод Эйлера(метод средней точки)
/// @param x_k 
/// @param y_k 
/// @param h 
/// @param func 
/// @return значение y, полученное модифицированным методом
double modifiedEulerMethod(double x_k, double y_k, double h, std::function<double(double, double)> func);