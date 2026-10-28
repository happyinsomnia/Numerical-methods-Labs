from pathlib import Path

from parse import ExperimentData, parse, parse_points


PLOT_DATA_DIR = Path(__file__).resolve().parent.parent / "plot_data"
EXPERIMENT_FILE = PLOT_DATA_DIR / "experiment.csv"
EXACT_FUNCTION_FILE = PLOT_DATA_DIR / "exact_function.csv"


def load_experiments() -> list[ExperimentData]:
    return parse(EXPERIMENT_FILE)


def load_exact_function() -> list[tuple[float, float]]:
    return parse_points(EXACT_FUNCTION_FILE)
