#set page(
  numbering: "1",
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
  weight: "light",)

#show regex("\b(double|void|int|long)\b"):name =>{text(blue)[#name]}

#show regex("\b(map|function|optional|tuple|vector|class)\b"):name => {text(green)[#name]}

#align(
  center,
  text(size: 18pt,
  [*Министерство образования и науки Российской Федерации Санкт-Петербургский политехнический университет Петра Великого Институт приклданой математики и информатики \ \ \ \ \ \ Курсовой проект по дисциплине "Численные методы"*])
)

#show heading.where(level: 1): it => block[
  #set text(size:18pt,weight: "black",)
  #set align(left)
  #block(smallcaps(it.body))
]

#show heading.where(level: 2): it => [
  #set text(size: 14pt, weight: "bold")
  #block(smallcaps(it.body))
]

#align(center)[Отчет по лабораторной работе №1 \ #strong("Приближение табличных функций")]

#grid(columns: (1fr,1fr), align(center)[Выполнил студент гр. 5030102/30004\ Преподователь:], align(center)[Зернов.К.В\ Курц. В.В])

#align(bottom + center)[Санкт-Петербург\ 2026]

#pagebreak()
#text(size: 14pt)[#outline()]
#pagebreak()

= Формулировка задачи и ее формализация

Построить функцию по заданной сетке значений $(x^h,y^h)$ используя метод Ньютона(слева направо). В рамках исследования требуется анализировать погрешности вычислений. 
