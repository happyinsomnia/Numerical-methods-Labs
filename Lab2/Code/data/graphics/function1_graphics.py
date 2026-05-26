import matplotlib.pyplot as plt
import os
from data import save_directory_function1, data_function1


def show_function1_graphics():
    # Figure 1: Error vs eps
    os.makedirs(save_directory_function1, exist_ok=True)

    plt.figure("Error vs eps function1")
    plt.title("Зависимость погрешности от заданной точности для f1(x)")
    plt.xlabel("epsilon")
    plt.ylabel("error")

    pairs = data_function1["error vs epsilon"]

    x = [p[0] for p in pairs]
    y = [p[1] for p in pairs]

    plt.plot(y, x, marker="o", label="f1", color="red")
    plt.grid()
    plt.legend()

    plt.savefig(save_directory_function1 / "function1_error_vs_eps.png")

    # Figure 2: N vs epsilon

    plt.figure("N vs epsilon function1")
    plt.xlabel("epsilon")
    plt.ylabel("N")
    plt.title("Зависимость количества разбиений от заданной точности f1(x)")

    pairs = data_function1["N vs epsilon"]

    x = [(p[0] - 1) for p in pairs]
    y = [p[1] for p in pairs]

    plt.plot(y, x, marker="o", label="f1", color="red")
    plt.grid()
    plt.legend()

    plt.savefig(save_directory_function1 / "function1_N_vs_epsilon.png")

    # Figure 3: error vs h

    plt.figure("Error vs h function1")
    plt.title("Зависимость погрешности от h f1(x)")
    plt.xlabel("h")
    plt.ylabel("error")

    pairs = data_function1["error vs h"]

    x = [p[0] for p in pairs]
    y = [p[1] for p in pairs]

    plt.plot(y, x, marker="o", label="f1", color="red")

    plt.grid()
    plt.legend()

    plt.savefig(save_directory_function1 / "function1_error_vs_epsilon.png")

    plt.show()
