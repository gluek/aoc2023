const { open } = require("node:fs/promises");

(async () => {
    const file = await open("puzzle.txt");

    let endResult = 0;

    for await (const line of file.readLines()) {
        console.log(line);
        var winning_numbers = line
            .split(":")[1]
            .split("|")[0]
            .trim()
            .split(" ");
        var drawn_numbers = line.split(":")[1].split("|")[1].trim().split(" ");

        var wins = 0;

        drawn_numbers.map((number) => {
            if (number != "") {
                if (winning_numbers.includes(number)) {
                    wins += 1;
                }
            }
        });
        if (wins > 0) {
            console.log("Game Result: ", Math.pow(2, wins - 1));
            endResult += Math.pow(2, wins - 1);
        } else {
            console.log("Game Result: ", 0);
        }
    }
    console.log("Final result: ", endResult);
})();
