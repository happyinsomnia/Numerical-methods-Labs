from pathlib import Path


def parse(filename):
    
    data = {}
    current_section = None

    with open(filename, "r") as file:
        for line in file:
            line = line.strip()

            if not line:
                continue

            if "vs" in line:
                current_section = line
                data[current_section] = []
                continue

            x, y = map(float, line.split(','))

            data[current_section].append((x, y))

    return data


save_directory_function1 = Path("function1 graphics")
save_directory_function2 = Path("function2 graphics")

function1_file_data = Path("../function1 data/data.csv")
function2_file_data = Path("../function2 data/data.csv")

data_function1 = parse(function1_file_data)
data_function2 = parse(function2_file_data)
