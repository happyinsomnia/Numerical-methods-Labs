import re
from dataclasses import dataclass, field
from pathlib import Path


@dataclass
class GraphData:
    number: int
    title: str
    x_label: str
    y_label: str
    points: list[tuple[float, float]] = field(default_factory=list)


@dataclass
class ExperimentData:
    method: str
    graphs: dict[int, GraphData] = field(default_factory=dict)


_METHOD_HEADER = re.compile(r"^([A-Za-z][A-Za-z0-9_]*)\s*:\s*$")
_GRAPH_HEADER = re.compile(
    r"^Graphic\s+(\d+)\s*:\s*(.*?)\s+vs\s+(.*?)\s*$", re.IGNORECASE
)


def parse(filename: str | Path) -> list[ExperimentData]:
    experiments: list[ExperimentData] = []
    current_experiment: ExperimentData | None = None
    current_graph: GraphData | None = None

    with Path(filename).open(encoding="utf-8") as file:
        for line_number, raw_line in enumerate(file, start=1):
            line = raw_line.strip()
            if not line:
                continue

            method_match = _METHOD_HEADER.fullmatch(line)
            if method_match:
                current_experiment = ExperimentData(method=method_match.group(1))
                experiments.append(current_experiment)
                current_graph = None
                continue

            graph_match = _GRAPH_HEADER.fullmatch(line)
            if graph_match:
                if current_experiment is None:
                    raise ValueError(
                        f"Graphic header before method at line {line_number}"
                    )

                graph_number = int(graph_match.group(1))
                if graph_number in current_experiment.graphs:
                    raise ValueError(
                        f"Duplicate graphic {graph_number} at line {line_number}"
                    )

                x_label, y_label = graph_match.group(2, 3)
                current_graph = GraphData(
                    number=graph_number,
                    title=f"{x_label} vs {y_label}",
                    x_label=x_label,
                    y_label=y_label,
                )
                current_experiment.graphs[graph_number] = current_graph
                continue

            if current_graph is None:
                raise ValueError(f"Data row outside a graphic at line {line_number}")

            values = line.split()
            if len(values) != 2:
                raise ValueError(
                    f"Expected two numeric values at line {line_number}, "
                    f"got {len(values)}"
                )

            try:
                point = (float(values[0]), float(values[1]))
            except ValueError as error:
                raise ValueError(
                    f"Invalid numeric data at line {line_number}: {line!r}"
                ) from error

            current_graph.points.append(point)

    if not experiments:
        raise ValueError(f"No experiment data found in {filename}")

    for experiment in experiments:
        if not experiment.graphs:
            raise ValueError(f"Experiment {experiment.method!r} has no graphics")
        for graph in experiment.graphs.values():
            if not graph.points:
                raise ValueError(
                    f"Graphic {graph.number} in {experiment.method!r} has no data"
                )

    return experiments


def parse_points(filename: str | Path) -> list[tuple[float, float]]:
    points: list[tuple[float, float]] = []

    with Path(filename).open(encoding="utf-8") as file:
        header = next(file, None)
        if header is None or "vs" not in header:
            raise ValueError(f"Expected a graph header in {filename}")

        for line_number, raw_line in enumerate(file, start=2):
            line = raw_line.strip()
            if not line:
                continue

            values = line.split()
            if len(values) != 2:
                raise ValueError(
                    f"Expected two numeric values at line {line_number}, "
                    f"got {len(values)}"
                )

            try:
                points.append((float(values[0]), float(values[1])))
            except ValueError as error:
                raise ValueError(
                    f"Invalid numeric data at line {line_number}: {line!r}"
                ) from error

    if not points:
        raise ValueError(f"No point data found in {filename}")

    return points
