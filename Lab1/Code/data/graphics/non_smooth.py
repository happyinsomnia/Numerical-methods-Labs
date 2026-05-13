import matplotlib.pyplot as plt
from plotting import draw_graph, draw_knots
from data import non_smooth, save_directory_non_smooth_name
import os


def show_non_smooth_graphs():
    os.makedirs(save_directory_non_smooth_name, exist_ok=True)
    # Figure 1
    plt.figure("Actual non-smooth function with NewtonFrontward interpolation")
    plt.title("Интерполяция негладкой функции методом Ньютона вперед")
    plt.xlabel("x")
    plt.ylabel("y")
    
    draw_graph(
        non_smooth["actual"].x,
        non_smooth["actual"].y,
        color="red",
        label="Actual function",
        linestyle="-",
    )
    draw_graph(
        non_smooth["uniform"]["newton"].x,
        non_smooth["uniform"]["newton"].y,
        color="blue",
        label="NewtonFrontward Interpolation",
        linestyle="--",
    )
    draw_knots(
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
    
    draw_graph(
        non_smooth["actual"].x,
        non_smooth["actual"].y,
        color="red",
        label="Actual function",
        linestyle="-",
    )
    draw_graph(
        non_smooth["cheb"]["newton"].x,
        non_smooth["cheb"]["newton"].y,
        color="green",
        label="Newton Chebyshev Interpolation",
        linestyle="--",
    )
    draw_knots(
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
    
    draw_graph(
        non_smooth["uniform"]["error"].x,
        non_smooth["uniform"]["error"].y,
        color="red",
        label="NewtonFrontward Interpolation error",
    )
    draw_graph(
        non_smooth["cheb"]["error"].x,
        non_smooth["cheb"]["error"].y,
        color="blue",
        label="Newton Chebyshev interpolation error",
    )

    plt.grid()
    plt.legend()

    plt.savefig(save_directory_non_smooth_name / "Actual non-smooth function error.png")
    plt.show()
