module Day15

function hash_cipher(cipher)
    result = 0
    reduced_cipher = '=' in cipher ? cipher[1:end-2] : cipher[1:end-1]
    for char in reduced_cipher
        ascii_value = Int(char)
        result = ((result + ascii_value) * 17) % 256
    end
    println("Cipher: $cipher | $result")
    return result
end

function update_lens(boxes, cipher)
    box_index = hash_cipher(cipher) + 1
    current_box = boxes[box_index]
    remove_or_equal = '=' in cipher ? 1 : 0
    label = cipher[1:end-(1+remove_or_equal)]
    if remove_or_equal == 1
        focal_length = parse(Int64, cipher[end])
    end
    test = map(x -> x[1], boxes[box_index])
    if length(findall(x -> x == label, map(x -> x[1], boxes[box_index]))) > 0 && remove_or_equal == 0
        deleteat!(boxes[box_index], findfirst(x -> x[1] == label, boxes[box_index]))
    elseif length(findall(x -> x == label, map(x -> x[1], boxes[box_index]))) > 0 && remove_or_equal == 1
        boxes[box_index][findfirst(x -> x[1] == label, boxes[box_index])][2] = focal_length
    elseif !(length(findall(x -> x == label, map(x -> x[1], boxes[box_index]))) > 0) && remove_or_equal == 1
        push!(boxes[box_index], [label, focal_length])
    end

    return boxes
end

file = open("puzzle.txt", "r")
input = readlines(file)
close(file)

input = split(input[1], ',')

let
    final_result = 0

    boxes = []
    i = 1
    while i <= 256
        push!(boxes, [])
        i += 1
    end
    for cipher in input
        boxes = update_lens(boxes, cipher)
    end
    for (i, box) in enumerate(boxes)
        if box != []
            println("Box: $(i-1) | $box")
            for (slot, lens) in enumerate(box)
                final_result += i * slot * lens[2]
            end
        end
    end
    println("Result: $final_result")

end


end
