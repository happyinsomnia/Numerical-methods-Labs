def parse(filename):
    data = []

    with open(filename, "r") as file:
        next(file, None)

        for line in file:

            x, y = map(float, line.split())
            data.append((x, y))

    return data


def parse_delta_error(filename):
    series = []
    current_h = None
    current_data = []

    with open(filename, "r") as file:
        for line_number, line in enumerate(file, start=1):
            line = line.strip()
            if not line:
                continue

            if line.startswith("#"):
                fields = line[1:].split()
                if fields and fields[0] == "h:":
                    if len(fields) != 2:
                        raise ValueError(f"Invalid h header on line {line_number}")
                    if current_h is not None:
                        series.append((current_h, current_data))
                    current_h = float(fields[1])
                    current_data = []
                continue

            if current_h is None:
                raise ValueError(f"Data found before an h header on line {line_number}")

            fields = line.split()
            if len(fields) != 2:
                raise ValueError(f"Invalid delta/error data on line {line_number}")
            delta, error = map(float, fields)
            current_data.append((delta, error))

    if current_h is not None:
        series.append((current_h, current_data))

    return series
