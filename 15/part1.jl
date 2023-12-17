module Day15

function hash_cipher(cipher)
    result = 0
    for char in cipher
        ascii_value = Int(char)
        result = ((result + ascii_value) * 17) % 256
    end
    println("Cipher: $cipher | $result")
    return result
end


file = open("input.txt", "r")
input = readlines(file)
close(file)

input = split(input[1], ',')

let
    final_result = 0
    for cipher in input
        final_result += hash_cipher(cipher)
    end
    println("Result: $final_result")
end


end
