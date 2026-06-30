from parse import parse
from pathlib import Path

filepathNumericalSolution = Path("../plot_data/x_vs_y_numerical.txt")
filepathNumericalSolutionError = Path("../plot_data/numerical_solution_error.txt")
filepathStepGlobalError = Path("../plot_data/h_vs_global_error.txt")
filepathStepLocalError = Path("../plot_data/h_vs_local_error.txt")
filepathEpsilonGlobalError = Path("../plot_data/epsilon_vs_global_error.txt")
filepathDeltaGlobalError = Path("../plot_data/delta_vs_global_error.txt")

numericalSolution = parse(filepathNumericalSolution)
numericalSolutionError = parse(filepathNumericalSolutionError)
stepGlobalError = parse(filepathStepGlobalError)
stepLocalError = parse(filepathStepLocalError)
epsilonGlobalError = parse(filepathEpsilonGlobalError)
deltaGlobalError = parse(filepathDeltaGlobalError)
