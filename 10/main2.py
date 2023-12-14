from copy import deepcopy
import numpy as np

valid_target_moves = {
    "-1,-1": "",
    "1,1": "",
    "-1,1": "",
    "1,-1": "",
    "0,1": "|JL",
    "0,-1": "|F7",
    "-1,0": "-LF",
    "1,0": "-J7",
    "0,0": "",
}

valid_origin_moves = {
    "|": [( 0, -1),( 0, 1)],
    "7": [(-1,  0),( 0, 1)],
    "J": [( 0, -1),(-1, 0)],
    "-": [(-1,  0),( 1, 0)],
    "F": [( 1,  0),( 0, 1)],
    "L": [( 0, -1),( 1, 0)],
}

valid_previous = {
    "|": "",
    "7": "",
    "J": "",
    "-": "",
    "F": "",
    "L": "",
}


def look_for_start(puzzle):
    for y, line in enumerate(puzzle):
        for x, symbol in enumerate(line):
            if symbol == "S":
                return x,y 
    raise ValueError("Start not found")

def look_for_maximum(puzzle):
    cur_number = 0
    cur_coord = (0,0)
    for y, line in enumerate(puzzle):
        for x, symbol in enumerate(line):
            if isinstance(symbol, int) and symbol > cur_number:
                cur_number = symbol
                cur_coord = (x,y) 
    return cur_number

def first_moves(puzzle: list, start: tuple):
    moves = []
    offset = [-1, 0 , 1]
    for x in offset:
        for y in offset:
            cur_x = start[0]+x
            cur_y = start[1]+y
            if  cur_x < 0 or cur_x >= len(puzzle[0]):
                continue  
            if  cur_y < 0 or cur_y >= len(puzzle):
                continue  
            if puzzle[cur_y][cur_x] in valid_target_moves[f"{x},{y}"]:
                moves.append((cur_x, cur_y))
                return moves


def move(puzzle: list, coord: tuple, current_step: int):
    moves = []
    offset = [-1, 0 , 1]
    coord_symbol = puzzle[coord[1]][coord[0]]
    turn = ""
    for x in offset:
        for y in offset:
            cur_x = coord[0]+x
            cur_y = coord[1]+y
            
            if  cur_x < 0 or cur_x >= len(puzzle[0]):
                continue  
            if  cur_y < 0 or cur_y >= len(puzzle):
                continue
            
            cur_value = puzzle[cur_y][cur_x]
            if isinstance(cur_value,int):
                continue  
            if  cur_value in valid_target_moves[f"{x},{y}"]:
                if (x,y) in valid_origin_moves[coord_symbol]:
                    moves.append((cur_x, cur_y))

    puzzle[coord[1]][coord[0]] = "#"
    return moves

def shoelace(moves):
    area = 0
    for i in range(len(moves)-1):
        xi, yi = moves[i]
        xii, yii = moves[i+1]
        area += np.linalg.det(np.array([[xi, xii],[-yi, -yii]]))
    xi, yi = moves[-1]
    xii, yii = moves[0]
    area += np.linalg.det(np.array([[xi, xii],[-yi, -yii]]))
    return area/2

def print_puzzle(puzzle):
    for line in puzzle:
        print("".join([f"{i:<2}" for i in line])+"\n")

puzzle = []
next_move_in_step = []
next_move_next_step = ["start"]

with open("puzzle.txt", 'r') as file:
    for line in file.readlines():
        puzzle.append([i for i in str(line).strip()])

puzzle_prigin = deepcopy(puzzle)

xdim = len(puzzle[0])
ydim = len(puzzle)

xstart, ystart = look_for_start(puzzle)
next_move_in_step += first_moves(puzzle, (xstart, ystart))


moves = [(xstart, ystart)]
moves += next_move_in_step

current_step = 1
while any(next_move_next_step):
    next_move_next_step = []
    while any(next_move_in_step):
        for one_move in move(puzzle, next_move_in_step.pop(), current_step):
            next_move_next_step.insert(0, one_move)
            moves.append(one_move)

    current_step += 1
    next_move_in_step = next_move_next_step
    # print_puzzle(puzzle)
    # print("------------------------------------")
   
boundary_points = len(moves)
area = np.abs(shoelace(moves))
print(f"Area: {area-(boundary_points/2)+1}")
print()