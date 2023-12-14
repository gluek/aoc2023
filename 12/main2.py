from itertools import product

def check_condition(springs, numbers):
    springs_split = [i for i in springs.split('.') if i]
    numbers_split = list(map(int, numbers.strip().split(',')))
    if len(springs_split) != len(numbers_split):
        return False
    for i in range(len(springs_split)):
        if len(springs_split[i]) != numbers_split[i]:
            return False
    return True

def parse_line(line: str):
    valid = 0
    springs = line.split(" ")[0]
    numbers = line.strip().split(" ")[1]
    question_marks = line.count('?')
    possibilities = list(product('#.', repeat=question_marks))
    for case in possibilities:
        if case.count("#") + springs.count("#") != sum(map(int, numbers.split(","))):
            continue
        tmp_springs = springs
        for symbol in case:
            tmp_springs = tmp_springs.replace("?", symbol, 1)
        if check_condition(tmp_springs, numbers):
            valid += 1
    return valid




puzzle = []

with open("puzzle.txt", 'r') as file:
    for line in file.readlines():
        puzzle.append(line)


print(*puzzle)
test = "#.#.### 1,1,3"
test2 = "???.### 1,1,3"
result = 0
for line in puzzle:
    line_result = parse_line(line)
    result += line_result
    print(f"{line.strip():<50} | {line_result}")

print(f"Result: {result}")