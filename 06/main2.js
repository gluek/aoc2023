const fs = require("node:fs");

fs.readFile("puzzle.txt", "utf8", (err, data) => {
  if (err) {
    console.log(err);
    return;
  }
  let lines = data.split("\n");
  console.log(lines[0], "\n", lines[1]);

  time = parseInt(lines[0].split(":")[1].replace(/\s/g, ""));
  distance = parseInt(lines[1].split(":")[1].replace(/\s/g, ""));
  console.log(time);
  console.log(distance);

  endResult = 1;
  endResult *= getWinningStrategies(time, distance);

  console.log("Result:", endResult);
});

function getWinningStrategies(time, distance) {
  result = [];
  time = parseInt(time);
  winningDistance = parseInt(distance);
  i = 0;
  while (i < time) {
    dist = (time - i) * i;
    result.push(dist);
    i++;
  }
  result.push(0);
  result = result
    .map((item) => {
      if (item > winningDistance) {
        return 1;
      } else {
        return 0;
      }
    })
    .reduce((a, b) => a + b, 0);
  return result;
}
