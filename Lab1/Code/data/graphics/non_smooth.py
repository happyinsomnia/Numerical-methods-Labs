import matplotlib.pyplot as plt
from data import non_smooth, save_directory_non_smooth_name
import os


def show_non_smooth_graphs():
    os.makedirs(save_directory_non_smooth_name, exist_ok=True)
    # Figure 1
    plt.figure("Actual non-smooth function with NewtonFrontward interpolation")
    plt.title("Интерполяция негладкой функции методом Ньютона вперед")
    plt.xlabel("x")
    plt.ylabel("y")

    plt.semilogy(
        non_smooth["actual"].x,
        non_smooth["actual"].y,
        color="red",
        label="Actual function",
        linestyle="-",
    )
    plt.semilogy(
        non_smooth["uniform"]["newton"].x,
        non_smooth["uniform"]["newton"].y,
        color="blue",
        label="NewtonFrontward Interpolation",
        linestyle="--",
    )
    plt.scatter(
        non_smooth["uniform"]["knots"].x,
        non_smooth["uniform"]["knots"].y,
        color="orange",
        label="NewtonFrontward knots",
    )

    plt.grid()
    plt.legend()

    plt.savefig(
        save_directory_non_smooth_name
        / "Actual non-smooth function with NewtonFrontward interpolation.png"
    )

    # Figure 2
    plt.figure("Actual non-smooth function with Newton Chebyshev interpolation")
    plt.title("Интерполяция негладкой функции на Чебышевской сетке")
    plt.xlabel("x")
    plt.ylabel("y")

    plt.plot(
        non_smooth["actual"].x,
        non_smooth["actual"].y,
        color="red",
        label="Actual function",
        linestyle="-",
    )
    plt.plot(
        non_smooth["cheb"]["newton"].x,
        non_smooth["cheb"]["newton"].y,
        color="green",
        label="Newton Chebyshev Interpolation",
        linestyle="--",
    )
    plt.scatter(
        non_smooth["cheb"]["knots"].x,
        non_smooth["cheb"]["knots"].y,
        color="orange",
        label="Newton Chebyshev knots",
    )

    plt.grid()
    plt.legend()

    plt.savefig(
        save_directory_non_smooth_name
        / "Actual non-smooth function with Newton Chebyshev interpolation.png"
    )
    # Figure 3
    plt.figure("Actual non-smooth function error")
    plt.title("Ошибка интерполяции негладкой функции")
    plt.xlabel("x")
    plt.ylabel("error")

    plt.plot(
        non_smooth["uniform"]["error"].x,
        non_smooth["uniform"]["error"].y,
        color="red",
        label="NewtonFrontward Interpolation error",
        linestyle="-",
    )
    plt.plot(
        non_smooth["cheb"]["error"].x,
        non_smooth["cheb"]["error"].y,
        color="blue",
        label="Newton Chebyshev interpolation error",
        linestyle="-",
    )

    plt.grid()
    plt.legend()

    plt.savefig(save_directory_non_smooth_name / "Actual non-smooth function error.png")

    # Figure 4 knots count vs max error (Uniform)
    plt.figure("Knots count vs max error")
    plt.title("Зависимость ошибки от количества узлов негладкая функция")
    plt.xlabel("Knots count")
    plt.ylabel("Max error")

    plt.semilogy(
        non_smooth["uniform"]["max_error"].x,
        non_smooth["uniform"]["max_error"].y,
        color="red",
        label="NewtonFrontward Interpolation max error",
        linestyle="-",
    )

    plt.scatter(
        non_smooth["uniform"]["max_error"].x,
        non_smooth["uniform"]["max_error"].y,
        color="orange",
    )

    plt.semilogy(
        non_smooth["cheb"]["max_error"].x,
        non_smooth["cheb"]["max_error"].y,
        color="blue",
        label="Newton Chebyshev interpolation max error",
        linestyle="-",
    )

    plt.scatter(
        non_smooth["cheb"]["max_error"].x,
        non_smooth["cheb"]["max_error"].y,
        color="pink",
    )

    plt.legend()
    plt.grid()

    plt.savefig(
        save_directory_non_smooth_name
        / "Actual non-smooth function max error Uniform and Chebyshev.png"
    )

    plt.show()
