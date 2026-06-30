import matplotlib.pyplot as plt
import numpy as np
from data import *
import math
import os


def exact_function(x):
    return (2 * x + 1) * math.log(abs(2 * x + 1)) + 1


def show_graphics():

    dirname = "png/"

    os.makedirs(dirname, exist_ok=True)

    # Figure 1 actual function and approximate solution
    plt.figure("Actual function and approximate solution")
    plt.title("График точного и численного решения")
    plt.xlabel("x")
    plt.ylabel("y")

    x_actual = np.linspace(0, 4, 1000)
    y_actual = [exact_function(xi) for xi in x_actual]

    x_method = [x for x, y in numericalSolution]
    y_method = [y for x, y in numericalSolution]

    plt.plot(x_actual, y_actual, label="Точное решение", color="blue", linestyle="-")
    plt.plot(x_method, y_method, label="Численное решение", color="red", linestyle="--")
    plt.grid()
    plt.legend()

    plt.savefig(dirname + "Actual function and approximate function.png")

    # Figure 2 x vs numerical solution error

    plt.figure("x and approximate function")
    plt.title("График ошибки")
    plt.xlabel("x")
    plt.ylabel("error")

    x_method = [x for x, y in numericalSolutionError]
    y_method = [y for x, y in numericalSolutionError]

    plt.plot(x_method, y_method, label="График ошибки", color="red")
    plt.grid()
    plt.legend()

    plt.savefig(dirname + "Numerical solution error.png")

    # Figure 3 h vs local and global error
    
    plt.figure("Local and Global error vs h")
    plt.title("Зависимость глобальной и локальной ошибки от шага h (log-log)")
    plt.xlabel("Шаг интегрирования h")
    plt.ylabel("Ошибка")

    h = np.array([x for x, y in stepLocalError])
    localError = np.array([y for x, y in stepLocalError])
    globalError = np.array([y for x, y in stepGlobalError])

    plt.loglog(h, localError, marker="o", label="Локальная ошибка", color="green")
    plt.loglog(h, globalError, marker="o", label="Глобальная ошибка", color="red")
    plt.loglog(h, h**2, linestyle="--", label=r"$\mathcal{O}(h^2)$", color="blue")
    plt.loglog(h, h**3, linestyle="--", label=r"$\mathcal{O}(h^3)$", color="orange")

    plt.grid()
    plt.legend()

    plt.savefig(dirname + "Local And Global Error vs h.png")

    # Figure 4 Delta vs error
    
    plt.figure("Delta and global error")
    plt.title("Зависимость дельты от глобальной ошибки")
    plt.xlabel("δ")
    plt.ylabel("error")

    delta = [x for x, y in deltaGlobalError]
    error = [y for x, y in deltaGlobalError]

    plt.loglog(delta, error, marker="o", label="ошибка и точность", color="steelblue")
    plt.grid()
    plt.legend()

    plt.savefig(dirname + "Delta vs global error.png")

    plt.show()
