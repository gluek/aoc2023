import numpy as np

def print_space(space):
    for line in space:
        print(line)

def expand_space(space):
    empty_space_rows = []
    for i in range(len(space)):
        if '#' not in space[i]:
            empty_space_rows.append(i)
    space = list(map(list, zip(*space)))
    
    empty_space_cols = []
    for i in range(len(space)):
        if '#' not in space[i]:
            empty_space_cols.append(i)
    return empty_space_rows, empty_space_cols

def find_all_galaxies(space):
    galaxy_coords = []
    for y in range(len(space)):
        for x in range(len(space[0])):
            if space[y][x] == '#':
                galaxy_coords.append((x,y))
    return galaxy_coords

def eval_distance(galaxy_coords, empty_rows, emtpy_cols):
    sum_of_distances = 0
    for i, galaxy in enumerate(galaxy_coords):
        for second_galaxy in galaxy_coords[i:]:
            distance = abs(galaxy[0] - second_galaxy[0]) + abs(galaxy[1] - second_galaxy[1])
            count_empty_rows = sum([1 for i in empty_rows if
                                     second_galaxy[1]< i < galaxy[1] or second_galaxy[1] > i > galaxy[1]])
            count_empty_cols = sum([1 for i in emtpy_cols if
                                     second_galaxy[0]< i < galaxy[0] or second_galaxy[0] > i > galaxy[0]])
            sum_of_distances += distance + 999999 * (count_empty_rows + count_empty_cols)
    return sum_of_distances

space = []

with open("puzzle.txt", 'r') as file:
    for line in file.readlines():
        space.append(line.strip())


# print_space(space)
empty_rows, emtpy_cols = expand_space(space)
# print_space(space)
galaxies = find_all_galaxies(space)
print(f"Result: {eval_distance(galaxies, empty_rows, emtpy_cols)}")