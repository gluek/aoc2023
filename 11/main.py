import numpy as np

def print_space(space):
    for line in space:
        print(line)

def expand_space(space):
    new_space = []
    for line in space:
        new_space.append(line)
        if '#' not in line:
            new_space.append(line)
    space = list(map(list, zip(*new_space)))
    new_space = []
    for line in space:
        new_space.append(line)
        if '#' not in line:
            new_space.append(line)
    space = list(map(list, zip(*new_space)))
    return space

def find_all_galaxies(space):
    galaxy_coords = []
    for y in range(len(space)):
        for x in range(len(space[0])):
            if space[y][x] == '#':
                galaxy_coords.append((x,y))
    return galaxy_coords

def eval_distance(galaxy_coords):
    sum_of_distances = 0
    for i, galaxy in enumerate(galaxy_coords):
        for second_galaxy in galaxy_coords[i:]:
            distance = abs(galaxy[0] - second_galaxy[0]) + abs(galaxy[1] - second_galaxy[1])
            sum_of_distances += distance
    return sum_of_distances

space = []

with open("puzzle.txt", 'r') as file:
    for line in file.readlines():
        space.append(line.strip())


# print_space(space)
space = expand_space(space)
# print_space(space)
galaxies = find_all_galaxies(space)
print(f"Result: {eval_distance(galaxies)}")