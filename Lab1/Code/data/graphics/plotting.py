from dataclasses import dataclass


@dataclass
class GraphData:
    x: list
    y: list


def pars(filename):
    x_values = []
    y_values = []

    with open(filename, "r") as file:
        lines = file.readlines()

    lines = lines[1:]

    for line in lines:
        x, y = line.split()

        x_values.append(float(x))
        y_values.append(float(y))

    return GraphData(x_values, y_values)
