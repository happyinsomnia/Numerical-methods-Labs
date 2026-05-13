#import "utils.typ": *

#set page(
  number-align: center,
  columns: 1,
  paper: "a4",
  margin: (x: 1.5cm, y: 1.7cm),
)

#set text(
  font: "New Computer Modern Math",
  lang: "ru",
  size: 14pt,
  style: "normal",
  weight: "light",
)
#show regex("\b(vector|list|optional|Grid|function|string)\b"): it => { text(green)[#it] }

#align(
  center,
  text(
    size: 18pt,
    [* Министерство образования и науки Российской Федерации Санкт-Петербургский политехнический университет Петра Великого Институт прикладной математики и информатики \ \ \ \ \ \ Курсовой проект по дисциплине "Численные методы" *],
  ),
)

#show heading.where(level: 1): it => block[
  #set text(size: 20pt, weight: "black")
  #set align(left)
  #block(smallcaps(it.body))
]

#show heading.where(level: 2): it => [
  #set text(size: 18pt, weight: "bold")
  #block(smallcaps(it.body))
]

#align(center)[Отчет по лабораторной работе №1 \ #strong("Приближение табличных функций")]

#grid(
  columns: (1fr, 1fr),
  align(center)[Выполнил студент гр. 5030102/30004\ Преподаватель:], align(center)[Зернов.К.В\ Курц. В.В],
)

#align(bottom + center)[Санкт-Петербург\ 2026]

#pagebreak()
#set page(numbering: "1")
#counter(page).update(1)
#text(size: 14pt)[#outline()]
#pagebreak()

= Формулировка задачи и ее формализация

== Формулировка задачи

Дано две функции:

+ $x log(x+1)$
+ $|x^2 - 2x - 3|$

Необходимо провести исследования:

+ Исследовать влияние гладкости функций на качество приближения
+ Исследовать влияние Чебышевской и равномерной сеток

== Формализация задачи

Пусть $x^h = {x_i}^n_i = 0$ -- сетка, $y^h = {y_i}_i^n = 0$ -- сеточная функция.
Пусть табличная функция задана парой элементов $(x^h, y^h)$.
Требуется построить функцию $phi(x)$ в форме интерполяционного полинома Ньютона(вперед), которая
удовлетворяет критерию близости: $phi(x) approx (x^h,y^h)).$

= Алгоритм метода (Ньютона вперед)

== Условия

Узлы $x_i$ различны. Функция $y = f(x)$ определена в узлах $x_i$.
Интерполяционный многочлен приближает функцию только на отрезке $[a,b]$.

== Формула Ньютона вперед

$P_n (x_0 + t h) = y_0 + (Delta y_0) / (1!) t + (Delta^2 y_0) / 2! t(t-1)+ dots +
(Delta^n y_0) / n! t(t-1) dots (t-n+1)$

где \ $t = (x - x_0)/h$ \ $x = x_0 + t h$ -- точка в которой вычисляется интерполяция, \
$h = x_1 - x_0$ -- шаг сетки(равномерная сетка), \
$Delta^k y_0$ -- конечная разность k-го порядка в точке $y_0$

Формула конечных разностей: $ Delta y_k = y_(k+1) - y_k $
$ Delta^m y_k = Delta^(m-1) y_(k+1) - Delta^(m-1) y_k $

= Предварительный анализ задачи
== Условия существования решения

Теорема Вейерштрасса: \ По $n+1$ точке всегда можно построить единственный
интерполяционный многочлен степени $n$.

== Условие единственности
+ Степень полинома на единицу меньше количества точек.
+ $x^j$ попарно различны.

= Тестовый пример метод Ньютона вперед
*функция:* $f(x) = e^x$ на равномерной сетке. Узлы:

#let knots = (0, 0.25, 0.5, 0.75)
#let step = knots.at(1) - knots.at(0)
#let y = ()

#for knot in knots {
  y.push(calc.round(calc.exp(knot) * 100000) / 100000)
}
$x^h = [
  #for (i, x) in knots.enumerate() [
    $x_#i = #x$;

  ]], h = #step$

*Значение функции:*


#let rows = ()

#for (i, x) in knots.enumerate() {
  rows.push(
    $ y_#i = e^#x #h(1mm) approx #h(1mm) #(calc.round(calc.exp(x) * 100000) / 100000) $,
  )
}

#text(size: 18pt)[$cases(..rows)$]

\
== Таблица конечных разностей

#let diff = buildDiff(y)

#for (k, arr) in diff.enumerate() {
  for (i, val) in arr.enumerate() [
    #if k == 0 {
      continue
    }
    #if k == 1 {
      $Delta^#(k) y_#i = y_#(i + 1) - y_#i approx #val$
      [ \ ]
      v(0.1em)
      continue
    }
    $Delta^#(k) y_#i = Delta^#(k - 1) y_#(i + 1) - Delta^#(k - 1) y_#i approx #val$
    #v(0.1em)
  ]

  v(1em)
}

#create_table(knots, y, diff)

*Вычисление в точке $x = 0.6$*

$t = frac(x - x_0, h) = frac(0.6, 0.25) = #{ 0.6 / 0.25 }$
#let t = 0.6 / 0.25
$P_3(x_0 + t h) = 1 + frac(#str(diff.at(0).at(0)), 1!) dot #t + frac(#str(diff.at(1).at(0)), 2!) dot #t dot (#t - 1) + frac(#str(diff.at(2).at(0)), 3!) dot #t dot (#t - 1) dot (#t - 2) approx 1.82232$

Истинное значение:

$f(0.6) = e^0.6 approx 1.8221$

*Ошибка*

$E = |f(0.6) - P_3(0.6)| approx 2.0 dot 10^(-4)$

Таким образом интерполяционный полином Ньютона вперед степени 3 дает хорошее приближение: ошибка менее $2.0 dot 10^(-4).$

== Тестовый пример метода Ньютона на Чебышевской сетке

Берем те же узлы что и в предыдущем примере

*функция:* $f(x) = e^x$ на равномерной сетке. Узлы:

#let knots = (0, 0.25, 0.5, 0.75)
#let _h = knots.at(1) - knots.at(0)
#let y = ()

#for knot in knots {
  y.push(calc.round(calc.exp(knot) * 100000) / 100000)
}
$x^h = [
  #for (i, x) in knots.enumerate() [
    $x_#i = #x$;

  ]], h = #_h$

*Считаем узлы Чебышева: *

#let x_cheb = ()

// Calculate Cheb knots
#for i in range(knots.len()) {
  x_cheb.push(calc.round((0.75 / 2 * calc.cos(calc.pi * (2 * i + 1) / 8) + 0.75 / 2) * 1000000) / 1000000)
}

*Формула: * $x_i = cos((pi (2i+1)) / (2n)) , i = 0, dots ,n - 1$

Переход от $[-1, 1] -> [a,b]: x_i = frac(b - a, 2) x_i + frac(a + b, 2)$

$x_0 = cos(frac(pi, 2 dot 4)) = #{ calc.cos(calc.pi / 8) }$

$x_1 = cos(frac(pi dot 3, 2 dot 4)) = #{ calc.cos(calc.pi * 3 / 8) }$

$x_2 = cos(frac(pi dot 5, 2 dot 4)) = #{ calc.cos(calc.pi * 5 / 8) }$

$x_3 = cos(frac(pi dot 7, 2 dot 4)) = #{ calc.cos(calc.pi * 7 / 8) }$

*Переход: *

$x_0 = frac(0.75, 2) * #{ calc.cos(calc.pi / 8) } + frac(0.75, 2) = #x_cheb.at(0)$

$x_1 = #x_cheb.at(1)$

$x_2 = #x_cheb.at(2)$

$x_3 = #x_cheb.at(3)$

*Значение функции: *

#let rows = ()
#let y_cheb = ()
#for (i, x) in x_cheb.enumerate() {
  y_cheb.push(calc.round(calc.exp(x) * 100000) / 100000)
  rows.push(
    $ y_#i = e^#x #h(1mm) approx #h(1mm) #y_cheb.at(i) $,
  )
}

#text(size: 18pt)[$cases(..rows)$]

Так как формула Ньютона вперед работает только на равномерной сетке, то посчитаем Чебышивские узлы
формулой Ньютона через разделенные разности.

* Формула разделенных разностей: *

$[y_k_1, y_k_2] = frac(y_k_2 - #h(1mm)y_k_1, x_k_2 - #h(1mm) x_k_1)$

$[y_k_0, dots,y_k_m] = frac([y_k_1, dots, y_k_m] - [y_k_0, dots, y_k_(m-1)], x_k_m - #h(1mm)x_k_0)$

*Считаем конечные разности: *

#let coefficients = buildDivid(x_cheb, y_cheb)

$[y_0, y_1] = frac(y_1 - y_0, x_1 - x_0) = #coefficients.at(1)$

$[y_0, y_1, y_2] = frac([y_1,y_2] - [y_0,y_1], x_2 - x_0) = #coefficients.at(2)$

$[y_0, y_1, y_2, y_3] = #coefficients.at(3)$

*Формула Ньютона через разделенные разности: *
$
  P_n(x) = y_0 + [y_0,y_1](x-x_0) + [y_0,y_1,y_2](x-x_0)(x-x_1) + #h(2mm) dots #h(2mm) + [y_0, dots , y_n]product_(i = 0)^(n-1)(x-x_i)
$

Считаем в точке $x = 0.6$

$P_3(x) = #y_cheb.at(0) + #coefficients.at(1) (0.6 - #x_cheb.at(0)) + #coefficients.at(2) (0.6 - #x_cheb.at(0))(0.6 - #x_cheb.at(1)) + #coefficients.at(3) (0.6 - #x_cheb.at(0))(0.6 - #x_cheb.at(1))(0.6 - #x_cheb.at(2)) = 1.82225$

Получили тот же результат.

= Подготовка контрольных тестов
+ Построить графики обычной функции и интерполяционного полинома с 20 узлами.
+ Влияние гладкости на качество приближения. Ожидается, что для гладкой функции будет сильно ниже, чем для функции с изломом.
+ Влияние Чебышевской и равномерной сетки на качество приближения.

= Модульная структура программы

Структура кода программы интерполяции

Функции:

- ```cpp
  double Function1(double x)
  ```*Описание: * гладкая функция
  - Входные данные:
    - значение $x$, в котором считаем значение функции
  - Выходные данные:
    - значении функции $x dot ln(x+1)$

- ```cpp
  double Function2(double x)
  ``` *Описание: * функция с изломом
  - Входные данные:
    - значение x, в котором считаем значение функции
  - Выходные данные:
    - значении функции $|x^2 -2 x - 3|$

- ```cpp std::vector<double> CreateChebeshivsyKnots(double left, double right, int n)
  ``` *Описание:* создает Чебышивские узлы
  - Входные данные:
    - left -- левая граница отрезка
    - right -- правая граница отрезка
    - n -- количество узлов
  - Выходные данные:
    - массив Чебышевских узлов

- ```cpp std::vector<double> CreateUniformKnots(double left, double right, int n)
  ``` *Описание:* создает равномерную сетку
  - Входные данные:
    - left -- левая граница отрезка
    - right -- правая граница отрезка
    - n -- количество узлов
  - Выходные данные:
    - массив $x$-ов равномерно расположенных друг от друга

- ```cpp std::optional<double> CheckUniformGrid(const Grid &grid)
  ``` *Описание:* проверяет что сетка равномерная
  - Входные данные:
    - Структура Grid состоит из двух массивов одинаковой размерности, которые хранят данные $x$ и $y$ соответственно
  - Выходные данные:
    - ```cpp bool ```значение

- ```cpp Grid CreateGrid(const std::vector<double> &x, const std::function<double(double)> &func)
  ``` *Описание:* создает сетку значений(считает значение $y$ в $x$) \ \
  - Входные данные:
    - массив $x$(значения $x$, в которых нужно посчитать значения функции)
    - func -- указатель на функцию, в которой считать значения
  - Выходные данные:
    - объект ```cpp Grid``` с узлами $x$, которые передали и посчитанные значения $y$

- ```cpp void SaveGrid(const std::string &path, const Grid &grid)
  ``` *Описание:* сохраняет данные сетки в файл path
  - Входные данные:
    - path -- путь до файла, в который надо записать данные
    - grid -- сетка, значения которой нужно записать

- ```cpp std::vector<double> FiniteDifference(const std::vector<double> &y)
  ``` *Описание:* считает конечные разности
  - Входные данные:
    - массив $y$, значения в которых считаем
  - Выходные данные:
    - возвращает массив значений, которые хранят $Delta y_0, Delta^2 y_0, dots, Delta^n y_0$

- ```cpp std::vector<double> DividedDifference(const Grid &grid)
  ``` *Описание:* считает разделенные разности
  - Входные данные:
    - сетка Grid, используется для вычисления разделенных разностей
  - Выходные данные:
    - массив, который хранит разделенные разности $[y_0,y_1], [y_0, y_1, y_2], dots,[y_0, y_1, dots, y_n]$

- ```cpp long long Factorial(int n)
  ``` *Описание:* считает факториал n

- ```cpp std::vector<double> NewtonFrontwardInterpolation(const Grid &grid, const std::vector<double> &x)
  ``` *Описание:* метод Ньютона интерполяции вперед
  - Входные данные:
    - grid -- сетка, которая используются для построения полинома
    - $x$ -- значения аргумента для вычисления полинома Ньютона вперед
  - Выходные данные:
    - получившиеся значения интерполяции
\ \
- ```cpp std::vector<double> NewtonDividedInterpolation(const Grid &grid, const std::vector<double> &x)
  ``` *Описание:* метод Ньютона с разделенными разностями(используется для Чебышевской сетки)
  - Входные данные:
    - grid -- сетка, которая используется для построения полинома
    - $x$ -- значения аргумента для вычисления полинома Ньютона
  - Выходные данные:
    - получившиеся значения интерполяции

- ```cpp void ComputeErrorsForNodes(const std::string &path, const Grid &actualGrid, const Grid &newtonGrid)
  ``` *Описание:* Вычисляет ошибку интерполяции и записывает в файл path
  - Входные данные:
    - path -- путь для записи данных,
    - actualGrid -- сетка истинных значений
    - newtonGrid -- сетка значений получившихся методом Ньютона

- ```cpp void RunSmoothFunctionExperiment(double left, double right, int numberKnots, int numberPoints)
  ``` *Описание*: запускает эксперимент интерполяции для гладкой функции
  - Входные данные:
    - left -- левая граница отрезка
    - right -- правая граница отрезка
    - numberKnots -- количество узлов, которые будут использоваться для построения полинома
    - numberPoints -- количество точек используемых для построения графика полинома

- ```cpp void RunNonSmoothFunctionExperiment(double left, double right, int numberKnots, int numberPoints)
  ``` *Описание:* запускает эксперимент интерполяции для негладкой функции
  - Входные данные:
    - left -- левая граница отрезка
    - right -- правая граница отрезка
    - numberKnots -- количество узлов, которые будут использоваться для построения полинома
    - numberPoints -- количество точек используемых для построения графика полинома

= Численный анализ 

== Графики

#image("../Code/data/graphics/smoothGraphics/Actual smooth function with NewtonFrontward interpolation.png", width: 100%)

#image("../Code/data/graphics/nonSmoothGraphics/Actual non-smooth function with NewtonFrontward interpolation.png", width: 100%)

На графике видно что интерполяционный полином Ньютона для функции $|x^2 - 2 x - 3|$ дает значительные осцилляции на краях интервала $[2.0, 4.0].$

#image("../Code/data/graphics/smoothGraphics/Actual smooth function with Newton Chebyshev Interpolation.png", width: 100%)

#image("../Code/data/graphics/nonSmoothGraphics/Actual non-smooth function with Newton Chebyshev interpolation.png", width: 100%)

На Чебышевской сетке, как видно, интерполяционный полином значительно точнее аппроксимирует негладкую функцию. Наибольшее отклонение наблюдается в точке $x = 3.0$.

#image("../Code/data/graphics/smoothGraphics/Actual smooth function error.png")


#image("../Code/data/graphics/nonSmoothGraphics/Actual non-smooth function error.png")

Как мы видим, ошибка при интерполяции гладкой функции не превышает $10^(−12)$
, что говорит о высокой точности приближения функции. Совершенно иная картина наблюдается для негладкой функции: на краях интервала ошибка достигает значений, близких к 16, что можно объяснить эффектом Рунге.
Для Чебышевской сетки ошибка значительно меньше и распределена более равномерно по всему интервалу, что свидетельствует о лучшей устойчивости интерполяции.

= Вывод

Метод Ньютона (слева направо) показал высокую точность вычислений. Для гладких функций интерполяционный полином обеспечивает очень хорошее приближение исходной функции и малую величину ошибки.

Для негладких функций с точками излома при использовании равномерной сетки наблюдаются осцилляции интерполяционного полинома, что связано с эффектом Рунге. Использование Чебышевской сетки позволяет существенно уменьшить величину ошибки и снизить колебания полинома на концах интервала.

Таким образом, Чебышевская сетка обеспечивает более устойчивую и точную интерполяцию как для гладких, так и для негладких функций.