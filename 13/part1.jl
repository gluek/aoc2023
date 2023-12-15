module day13

function validate(puzzle, x)
    k = 1
    while x - k > 0 && x + 1 + k <= length(puzzle)
        if puzzle[x-k] != puzzle[x+1+k]
            return false
        end
        k += 1
    end
    return true
end

function solve_puzzle(puzzle)
    result = 0
    xi, xj = 0, 0
    for (i, line) in enumerate(puzzle)
        for (j, cmp_line) in enumerate(puzzle[i+1:end])
            if line == cmp_line && i + 1 == i + j
                xi = i
                xj = i + j
                break
            end
        end
        if xi != 0 && xj != 0
            if validate(puzzle, xi)
                return xi
            end
            xi, xj = 0, 0
        end
    end
    return 0
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

function print_puzzle(puzzle)
    for line in puzzle
        println(line)
    end
end

# store old symmetry lines
# check for almost equal
# validate
function solve(puzzles)
    result = 0
    for (i, puzzle) in enumerate(puzzles)
        rows = (solve_puzzle(puzzle)) * 100
        cols = solve_puzzle(transpose_puzzle(puzzle))
        println("Puzzle $i, Rows: $rows or Cols: $cols")
        if cols != 0 && rows != 0
            println("Error!")
        end
        result += rows + cols
    end
    println("Result: $result")
end

file = open("puzzle.txt", "r")
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

# print_puzzle(puzzles[81])
solve(puzzles)

end