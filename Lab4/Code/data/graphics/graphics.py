import os
import matplotlib.pyplot as plt
import numpy as np
from data import *


def show_graphics():
    dirname = "png/"

    os.makedirs(dirname, exist_ok=True)

    # Figure 1 actual function and approximate solution
    plt.figure("Actual function and approximate solution")
    plt.title("График точного и численного решения")
    plt.xlabel("x")
    plt.ylabel("y")

    y_actual = [y for x, y in actualFunction]

    x_method = [x for x, y in numericalSolution]
    y_method = [y for x, y in numericalSolution]

    plt.plot(x_method, y_actual, label="Точное решение", color="blue", linestyle="-")
    plt.plot(x_method, y_method, label="Численное решение", color="red", linestyle="--")
    plt.grid()
    plt.legend()

    plt.savefig(dirname + "Actual function and approximate function.png")

    # Figure 2 approximate solution error

    plt.figure("Approximate function error")
    plt.title("Ошибка аппроксимации")
    plt.xlabel("x")
    plt.ylabel("error")

    x_method = [x for x, y in numericalSolutionError]
    error = [y for x, y in numericalSolutionError]

    plt.plot(x_method, error, label="Ошибка", color="red", linestyle="-")
    plt.grid()
    plt.legend()

    plt.savefig(dirname + "Approximate function error.png")

    # Figure 3 h vs error

    plt.figure("Step dependence on error")
    plt.title("Зависимость шага от ошибки(log-log)")
    plt.xlabel("h")
    plt.ylabel("error")

    h = np.array([x for x, y in stepError])
    error = [y for x, y in stepError]

    plt.loglog(h, error, label="Максимальная ошибка", color="red", linestyle="-")
    plt.loglog(h, h**2, label=r"$\mathcal{O}(h^2)$", color="purple", linestyle="--")
    plt.grid()
    plt.legend()

    plt.savefig(dirname + "Step dependence on error.png")

    # Figure 4 Delta dependence on error

    plt.figure("Delta dependence on error")
    plt.title("Зависимость погрешности в исходных данных от ошибки(log-log)")
    plt.xlabel("δ")
    plt.ylabel("error")

    delta = [x for x, y in deltaError]
    error = [y for x, y in deltaError]

    plt.loglog(delta, error, label="Максимальная ошибка", color="blue", linestyle="-")
    plt.grid()
    plt.legend()

    plt.savefig(dirname + "Step dependence on error.png")

    plt.show()
