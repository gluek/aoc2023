const fs = require("node:fs");

fs.readFile("puzzle.txt", "utf8", (err, data) => {
  if (err) {
    console.log(err);
    return;
  }
  let lines = data.split("\n");
  console.log(lines[0], "\n", lines[1]);

  times = lines[0]
    .split(":")[1]
    .trim()
    .split(" ")
    .filter((e) => String(e).trim());
  distances = lines[1]
    .split(":")[1]
    .trim()
    .split(" ")
    .filter((e) => String(e).trim());

  endResult = 1;
  Array(times.length)
    .fill("")
    .forEach((_, index) => {
      endResult *= getWinningStrategies(times[index], distances[index]);
    });

  console.log("Times:", times);
  console.log("Distances:", distances);
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
