import matplotlib.pyplot as plt
import os
from data import save_directory_function2, data_function2
import numpy as np


def show_function2_graphics():
    # Figure 1: Error vs eps
    os.makedirs(save_directory_function2, exist_ok=True)

    plt.figure("Error vs eps function2")
    plt.title("Зависимость погрешности от заданной точности для f2(x)")
    plt.xlabel("epsilon (log scale)")
    plt.ylabel("error (log scale)")

    pairs = data_function2["error vs epsilon"]

    x = [p[0] for p in pairs]
    y = [p[1] for p in pairs]

    line = np.linspace(min(y), max(y), 100)
    plt.plot(line, line, "--", color="black", label="y = x")
    # main graphic
    plt.plot(y, x, marker="o", label="f2", color="blue")
    plt.xscale("log")
    plt.yscale("log")
    plt.grid(True, which="both")
    plt.legend()

    plt.savefig(save_directory_function2 / "function2_error_vs_eps.png")

    # Figure 2: N vs epsilon

    plt.figure("N vs epsilon function2")
    plt.xlabel("epsilon (log scale)")
    plt.ylabel("N (log scale)")
    plt.title("Зависимость количества разбиений от заданной точности f2(x)")

    pairs = data_function2["N vs epsilon"]

    x = [p[0] for p in pairs]
    y = [p[1] for p in pairs]

    plt.plot(y, x, marker="o", label="f2", color="blue")
    plt.xscale("log")
    plt.yscale("log")
    plt.grid(True, which="both")
    plt.legend()

    plt.savefig(save_directory_function2 / "function2_N_vs_epsilon.png")

    # Figure 3: error vs h

    plt.figure("Error vs h function2")
    plt.title("Зависимость погрешности от h f2(x)")
    plt.xlabel("h (log scale)")
    plt.ylabel("error (log scale)")

    pairs = data_function2["error vs h"]

    x = [p[0] for p in pairs]
    y = [p[1] for p in pairs]

    plt.plot(y, x, marker="o", label="f2", color="blue")
    plt.xscale("log")
    plt.yscale("log")
    plt.grid(True, which="both")
    plt.legend()

    plt.savefig(save_directory_function2 / "function2_error_vs_epsilon.png")

    # Figure 4: algebraic degree of accuracy
    plt.figure("Algebraic degree vs accuracy function2")
    plt.xlabel("degree")
    plt.ylabel("error")
    plt.title("Зависимость погрешности от алгебраической степени")

    pairs = data_function2["degree vs absolute_error"]

    x = [p[0] for p in pairs]
    y = [p[1] for p in pairs]

    plt.plot(x, y, marker="o", color="blue")
    plt.grid(True, which="both")
    plt.legend()

    plt.savefig(save_directory_function2 / "function2_algebraic_degree_vs_accuracy.png")

    plt.show()
