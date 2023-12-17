module Day14

function print_puzzle(puzzle)
    for line in puzzle
        println(line)
    end
end

function transpose_puzzle(puzzle)
    tmp_puzzle = []
    for line in puzzle
        push!(tmp_puzzle, [c for c in line])
    end
    tmp_puzzle = zip(tmp_puzzle...)
    return_puzzle = []
    for line in tmp_puzzle
        push!(return_puzzle, join(line))
    end
    return return_puzzle
end

function solve_row(line)
    line = [c for c in line]
    len = length(line)
    b = 1
    symbol_map = Dict('O' => 0, '.' => 1, '#' => 2)
    while b <= len
        k = 1
        while k <= (len - b)
            not_hash = line[k] != '#' && line[k+1] != '#'
            if symbol_map[line[k]] > symbol_map[line[k+1]] && not_hash
                c = line[k]
                line[k] = line[k+1]
                line[k+1] = c
            end
            k += 1
        end
        b += 1
    end
    return join(line)
end

function move_stones(puzzle)
    puzzle = transpose_puzzle(puzzle)
    new_puzzle = []
    for line in puzzle
        push!(new_puzzle, solve_row(line))
    end
    return new_puzzle
end

function is_stone(x)
    if x == 'O'
        return true
    end
    return false
end

function evaluate_load(puzzle)
    result = 0
    for line in puzzle
        result += sum(findall(is_stone, line[end:-1:1]))
    end
    return result
end


file = open("input.txt", "r")
input = readlines(file)
close(file)
puzzles = []

let
    global puzzles
    puzzle = []
    for line in input
        if !isempty(line)
            push!(puzzle, line)
        else
            push!(puzzles, puzzle)
            puzzle = []
        end
    end
    push!(puzzles, puzzle)
end

puzzle = move_stones(puzzles[1])
println("Result: $(evaluate_load(puzzle))")

end