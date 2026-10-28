from pathlib import Path

import matplotlib.pyplot as plt

from data import load_exact_function, load_experiments
from parse import ExperimentData, GraphData


_GRAPH_SETTINGS = {
    1: ("Actual function and approximate function.png", "Решения методов", False, None),
    2: ("Approximate function error.png", "Ошибка по x", False, None),
    3: ("Step dependence on error.png", "Зависимость ошибки от шага h", True, "o"),
    4: ("Time dependence on error.png", "Зависимость ошибки от времени", True, "o"),
}


def _plot_graph(
    experiments: list[ExperimentData],
    graph_number: int,
    filename: str,
    title: str,
    use_log_scale: bool,
    marker: str | None,
    output_dir: Path,
    exact_points: list[tuple[float, float]] | None = None,
) -> None:
    figure, axes = plt.subplots()
    axes.set_title(title)

    if graph_number == 1 and exact_points is not None:
        exact_x, exact_y = zip(*exact_points)
        axes.plot(
            exact_x,
            exact_y,
            color="black",
            linestyle="-",
            label="Точное решение",
        )

    plotted_graph: GraphData | None = None
    method_colors = plt.rcParams["axes.prop_cycle"].by_key()["color"]
    for index, experiment in enumerate(experiments):
        graph = experiment.graphs.get(graph_number)
        if graph is None:
            continue

        x_values, y_values = zip(*graph.points)
        axes.plot(
            x_values,
            y_values,
            color=method_colors[index % len(method_colors)],
            marker=marker,
            linestyle="--" if graph_number == 1 else "-",
            label=experiment.method,
        )
        plotted_graph = graph

    if plotted_graph is not None:
        axes.set_xlabel(plotted_graph.x_label)
        axes.set_ylabel(plotted_graph.y_label)

    if use_log_scale:
        axes.set_xscale("log")
        axes.set_yscale("log")

    axes.grid(True, which="both" if use_log_scale else "major")
    axes.legend()
    figure.savefig(output_dir / filename, bbox_inches="tight")


def show_graphics() -> None:
    output_dir = Path(__file__).resolve().parent / "png"
    output_dir.mkdir(parents=True, exist_ok=True)
    experiments = load_experiments()
    exact_function = load_exact_function()

    for graph_number, (filename, title, use_log_scale, marker) in _GRAPH_SETTINGS.items():
        _plot_graph(
            experiments,
            graph_number,
            filename,
            title,
            use_log_scale,
            marker,
            output_dir,
            exact_points=exact_function if graph_number == 1 else None,
        )

    plt.show()
