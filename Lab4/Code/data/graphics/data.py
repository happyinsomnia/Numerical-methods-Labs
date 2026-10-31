from pathlib import Path
from parse import parse, parse_delta_error

filepathNumericalSolution = Path("../plot_data/Numerical_function.txt")
filepathNumericalSolutionError = Path("../plot_data/Numerical_function_error.txt")
filepathStepError = Path("../plot_data/h_vs_error.txt")
filepathDeltaError = Path("../plot_data/delta_vs_error.txt")
filepathActualFunction = Path("../plot_data/actual_function.txt")

numericalSolution = parse(filepathNumericalSolution)
numericalSolutionError = parse(filepathNumericalSolutionError)
stepError = parse(filepathStepError)
deltaError = parse_delta_error(filepathDeltaError)
actualFunction = parse(filepathActualFunction)
