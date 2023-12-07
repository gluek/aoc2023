const fs = require("node:fs");

fs.readFile("puzzle.txt", "utf8", (err, data) => {
  if (err) {
    console.log(err);
    return;
  }
  let lines = data.split("\n");

  seeds = lines[0]
    .split(":")[1]
    .trim()
    .split(" ")
    .map((seed) => {
      return parseInt(seed);
    });
  console.log(seeds);
  targets = seeds;
  changed = Array(seeds.length).fill(0);

  i = 3;
  j = 0;
  while (i < lines.length) {
    if (lines[i].trim()) {
      if (lines[i].includes(":")) {
        changed = Array(seeds.length).fill(0);
      } else {
        values = lines[i]
          .trim()
          .split(" ")
          .map((seed) => {
            return parseInt(seed);
          });
        targets.forEach((element, index) => {
          updateTargets(index, values[0], values[1], values[2]);
        });
      }
    }
    i++;
  }
  console.log(targets);
  console.log("Result:", Math.min.apply(null, targets));
});

function updateTargets(seedindex, dest, src, range) {
  if (
    src <= targets[seedindex] &&
    targets[seedindex] <= src + range &&
    changed[seedindex] === 0
  ) {
    targets[seedindex] += dest - src;
    changed[seedindex] = 1;
  }
}
