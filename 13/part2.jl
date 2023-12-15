module day13

function almost_equal(line1::String, line2::String)
    line1 = [c for c in line1]
    line2 = [c for c in line2]
    differences = 0
    diff_index = -1
    for (index, char) in enumerate(line1)
        if char != line2[index]
            differences += 1
            diff_index = index
        end
    end
    if differences > 1
        return false
    end
    return differences
end

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

function validate_new(puzzle, x)
    k = 1
    differences = 0
    while x - k > 0 && x + 1 + k <= length(puzzle)
        diff = almost_equal(puzzle[x-k], puzzle[x+1+k])
        if typeof(diff) == Bool
            return false
        end
        differences += diff
        k += 1
        if differences > 1
            return false
        end
    end
    return true
end


function solve_puzzle(puzzle)
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

function solve_puzzle_new(puzzle::Vector{Any}, old_symmetry::Float64)
    xi, xj = 0, 0
    for (i, line) in enumerate(puzzle)
        for (j, cmp_line) in enumerate(puzzle[i+1:end])
            diff = almost_equal(line, cmp_line)
            equal = !(typeof(diff) == Bool)
            neighbours = i + 1 == i + j
            new_symmetry = i != old_symmetry
            if equal && neighbours && new_symmetry
                xi = i
                xj = i + j
                break
            end
        end
        if xi != 0 && xj != 0
            if validate_new(puzzle, xi)
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
    old_symmetry = []
    for (i, puzzle) in enumerate(puzzles)
        rows = (solve_puzzle(puzzle)) * 100
        cols = solve_puzzle(transpose_puzzle(puzzle))
        # println("Puzzle $i, Rows: $rows or Cols: $cols")
        push!(old_symmetry, [rows / 100, cols])
        if cols != 0 && rows != 0
            println("Error!")
        end
        result += rows + cols
    end
    # println("Result: $result")
    return old_symmetry
end

function solve_new(puzzles, old_symmetries)
    result = 0
    for (i, puzzle) in enumerate(puzzles)
        rows = (solve_puzzle_new(puzzle, old_symmetries[i][1])) * 100
        cols = solve_puzzle_new(transpose_puzzle(puzzle), old_symmetries[i][2])
        println("Puzzle $i, Rows: $rows or Cols: $cols, Old: $(old_symmetries[i])")
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
old_syms = solve(puzzles)

solve_new(puzzles, old_syms)

end