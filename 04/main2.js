const { open } = require("node:fs/promises");

(async () => {
    const file = await open("puzzle.txt");

    let entireText = [];
    let scratchcards = [];

    let i = 0;
    for await (const line of file.readLines()) {
        entireText.push(line);
        scratchcards[i] = 1;
        i++;
    }

    i = 0;
    entireText.map((line) => {
        var lineResult = evaluateWins(line);
        var j = 1;
        while (j <= lineResult) {
            if (i + j < entireText.length) {
                scratchcards[i + j] += scratchcards[i];
            }
            j++;
        }
        i++;
    });
    const sum = scratchcards.reduce((endResult, item) => endResult + item, 0);
    console.log("End Result:", sum);
})();

function evaluateWins(line) {
    console.log(line);
    var winning_numbers = line.split(":")[1].split("|")[0].trim().split(" ");
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
        return wins;
    } else {
        return 0;
    }
}
