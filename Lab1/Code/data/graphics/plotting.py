import matplotlib.pyplot as plt
import numpy as np
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


def draw_graph(x, y, color="blue", label="graph", linestyle="-", linewidth=2):
    plt.plot(x, y, color=color, label=label, linestyle=linestyle, linewidth=linewidth)


def draw_knots(x, y, color="red", label="knots", size=40):
    plt.scatter(x, y, color=color, label=label, s=size)

