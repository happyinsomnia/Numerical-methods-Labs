from plotting import pars
from pathlib import Path

save_directory_smooth_name = Path("smoothGraphics")
save_directory_non_smooth_name = Path("nonSmoothGraphics")


file_smooth_path = {
    "actual": "../smoothFunction/actual_function.txt",
    "uniform": {
        "knots": "../smoothFunction/uniform/knots_uniform.txt",
        "newton": "../smoothFunction/uniform/newton_frontward_values.txt",
        "error": "../smoothFunction/uniform/newton_uniform_error.txt",
    },
    "cheb": {
        "knots": "../smoothFunction/chebeshivsy/knots_chebeshivsy.txt",
        "newton": "../smoothFunction/chebeshivsy/newton_chebeshivsy_values.txt",
        "error": "../smoothFunction/chebeshivsy/newton_chebeshivsy_error.txt",
    },
}

file_non_smooth_path = {
    "actual": "../nonSmoothFunction/actual_function.txt",
    "uniform": {
        "knots": "../nonSmoothFunction/uniform/knots_uniform.txt",
        "newton": "../nonSmoothFunction/uniform/newton_frontward_values.txt",
        "error": "../nonSmoothFunction/uniform/newton_uniform_error.txt",
    },
    "cheb": {
        "knots": "../nonSmoothFunction/chebeshivsy/knots_chebeshivsy.txt",
        "newton": "../nonSmoothFunction/chebeshivsy/newton_chebeshivsy_values.txt",
        "error": "../nonSmoothFunction/chebeshivsy/newton_chebeshivsy_error.txt",
    },
}


# end SmoothFunction files

smooth = {
    "actual": pars(file_smooth_path["actual"]),
    "uniform": {
        "knots": pars(file_smooth_path["uniform"]["knots"]),
        "newton": pars(file_smooth_path["uniform"]["newton"]),
        "error": pars(file_smooth_path["uniform"]["error"]),
    },
    "cheb": {
        "knots": pars(file_smooth_path["cheb"]["knots"]),
        "newton": pars(file_smooth_path["cheb"]["newton"]),
        "error": pars(file_smooth_path["cheb"]["error"]),
    },
}
non_smooth = {
    "actual": pars(file_non_smooth_path["actual"]),
    "uniform": {
        "knots": pars(file_non_smooth_path["uniform"]["knots"]),
        "newton": pars(file_non_smooth_path["uniform"]["newton"]),
        "error": pars(file_non_smooth_path["uniform"]["error"]),
    },
    "cheb": {
        "knots": pars(file_non_smooth_path["cheb"]["knots"]),
        "newton": pars(file_non_smooth_path["cheb"]["newton"]),
        "error": pars(file_non_smooth_path["cheb"]["error"]),
    },
}
