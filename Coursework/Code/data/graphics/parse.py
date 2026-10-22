def parse(filename):
    data = []

    with open(filename, "r") as file:
        next(file, None)

        for line in file:

            x, y = map(float, line.split())
            data.append((x, y))

    return data
