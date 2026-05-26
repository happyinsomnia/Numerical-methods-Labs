#pragma once
#include <functional>

/// @brief Обобщенная формула трапеций
/// @param a Левая граница
/// @param b Правая граница
/// @param N Количество разбиений
/// @param func Функция, в которой считаем интеграл по интервалу [a,b]
/// @return Значение интеграла
double TrapezoidalRule(double a, double b, int N, std::function<double(double)> func);