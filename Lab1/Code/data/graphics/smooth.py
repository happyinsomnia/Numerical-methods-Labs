# Figure 1
import matplotlib.pyplot as plt
from plotting import draw_graph, draw_knots
from data import smooth, save_directory_smooth_name
import os


def show_smooth_graphs():
    os.makedirs(save_directory_smooth_name, exist_ok=True)
    # Figure 1
    plt.figure("Actual smooth function with NewtonFrontward interpolation")
    plt.title("Интерполяция гладкой функции методом Ньютона вперед")
    plt.xlabel("x")
    plt.ylabel("y")

    draw_graph(
        smooth["actual"].x,
        smooth["actual"].y,
        color="red",
        label="Actual Function",
        linestyle="-",
    )
    draw_graph(
        smooth["uniform"]["newton"].x,
        smooth["uniform"]["newton"].y,
        color="blue",
        label="NewtonFrontward Interpolation",
        linestyle="--",
    )
    draw_knots(
        smooth["uniform"]["knots"].x,
        smooth["uniform"]["knots"].y,
        color="orange",
        label="NewtonFrontward knots",
    )
    plt.legend()
    plt.grid()

    plt.savefig(
        save_directory_smooth_name
        / "Actual smooth function with NewtonFrontward interpolation.png"
    )

    # Figure 2
    plt.figure("Actual smooth function with Newton Chebyshev Interpolation")
    plt.title("Интерполяция гладкой функции на Чебышевской сетке")
    plt.xlabel("x")
    plt.ylabel("y")

    draw_graph(
        smooth["actual"].x,
        smooth["actual"].y,
        color="red",
        label="Actual Function",
        linestyle="-",
    )
    draw_graph(
        smooth["cheb"]["newton"].x,
        smooth["cheb"]["newton"].y,
        color="green",
        label="Chebyshev Newton Interpolation",
        linestyle="--",
    )

    draw_knots(
        smooth["cheb"]["knots"].x,
        smooth["cheb"]["knots"].y,
        color="orange",
        label="Newton Chebyshev knots",
    )

    plt.legend()
    plt.grid()

    plt.savefig(
        save_directory_smooth_name
        / "Actual smooth function with Newton Chebyshev Interpolation.png"
    )
    # Figure 3
    plt.figure("Actual smooth function error")
    plt.title("Ошибка интерполяции гладкой функции")
    plt.xlabel("x")
    plt.ylabel("error")

    draw_graph(
        smooth["uniform"]["error"].x,
        smooth["uniform"]["error"].y,
        color="red",
        label="NewtonFrontward Interpolation error",
    )
    draw_graph(
        smooth["cheb"]["error"].x,
        smooth["cheb"]["error"].y,
        color="blue",
        label="Newton Chebyshev interpolation error",
    )

    plt.grid()
    plt.legend()

    plt.savefig(save_directory_smooth_name / "Actual smooth function error.png")

    # Figure 4 knots count vs max error (Uniform)

    plt.figure("Actual smooth function max error(Uniform)")
    plt.title("Максимальная ошибка интерполяции гладкой функции от шага сетки")
    plt.xlabel("knots count")
    plt.ylabel("max error")

    draw_graph(
        smooth["uniform"]["max_error"].x,
        smooth["uniform"]["max_error"].y,
        color="red",
        label="NewtonFrontward Interpolation max error",
    )

    draw_knots(
        smooth["uniform"]["max_error"].x,
        smooth["uniform"]["max_error"].y,
        color="orange",
    )

    plt.legend()
    plt.grid()

    plt.savefig(
        save_directory_smooth_name / "Actual smooth function max error Uniform.png"
    )

    # Figure 5 knots count vs max error (Chebyshev)

    plt.figure("Actual smooth function max error(Chebyshev)")
    plt.title("Максимальная ошибка интерполяции гладкой функции от шага сетки")
    plt.xlabel("knots count")
    plt.ylabel("max error")

    draw_graph(
        smooth["cheb"]["max_error"].x,
        smooth["cheb"]["max_error"].y,
        color="blue",
        label="Newton Chebyshev Interpolation max error",
    )

    draw_knots(
        smooth["cheb"]["max_error"].x,
        smooth["cheb"]["max_error"].y,
        color="orange",
    )

    plt.legend()
    plt.grid()

    plt.savefig(
        save_directory_smooth_name / "Actual smooth function max error Chebyshev.png"
    )

    plt.show()
