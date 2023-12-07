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

  console.log("Initial Seeds:", seeds);

  seedRanges = [];
  remainingRanges = [];
  tempSeedRange = [];
  populateSeedRanges();
  console.log("Updated Seeds:", seedRanges);

  targets = seeds;
  changed = Array(seeds.length).fill(0);
  i = 3;
  j = 0;
  while (i < lines.length) {
    if (lines[i].trim()) {
      if (lines[i].includes(":")) {
        // console.log("New Paragraph:");
        seedRanges = [...tempSeedRange].concat(seedRanges);
        tempSeedRange = [];
      } else {
        // console.log("-------------------Line:", i + 1);
        values = lines[i]
          .trim()
          .split(" ")
          .map((seed) => {
            return parseInt(seed);
          });
        while (seedRanges.length) {
          updateTargets(values[0], values[1], values[2]);
        }
        seedRanges = [...remainingRanges];
        remainingRanges = [];
      }
      // console.log(
      //   "Seed:",
      //   ...seedRanges,
      //   "   Remain:",
      //   ...remainingRanges,
      //   "   Temp:",
      //   ...tempSeedRange
      // );
    }
    i++;
  }
  seedRanges = [...tempSeedRange].concat(seedRanges);
  tempSeedRange = [];
  console.log("SeedRange:", ...seedRanges);
  lowerBounds = [];
  seedRanges.forEach((element) => {
    lowerBounds.push(element[0]);
  });
  console.log("LowerBounds:", ...lowerBounds);
  console.log("Result:", Math.min.apply(null, lowerBounds));
});

function updateTargets(dest, src, range) {
  currentRange = seedRanges.pop();
  dest = parseInt(dest);
  src = parseInt(src);
  range = parseInt(range);
  // console.log(
  //   "Current Range:",
  //   currentRange,
  //   "Lower:",
  //   src,
  //   "Upper:",
  //   src + range - 1,
  //   "Shift:",
  //   dest - src
  // );

  if (
    src <= currentRange[0] &&
    src <= currentRange[1] &&
    currentRange[0] <= src + range - 1 &&
    currentRange[1] <= src + range - 1
  ) {
    // console.log("Case1");
    currentRange[0] += dest - src;
    currentRange[1] += dest - src;
    tempSeedRange.push(currentRange);
  } else if (
    currentRange[0] < src &&
    src <= currentRange[1] &&
    currentRange[1] <= src + range - 1
  ) {
    // console.log("Case2");
    remainingRanges.push([currentRange[0], src - 1]);
    tempSeedRange.push([dest, currentRange[1] + dest - src]);
  } else if (
    src <= currentRange[0] &&
    currentRange[0] <= src + range - 1 &&
    src + range - 1 < currentRange[1]
  ) {
    // console.log("Case3");
    remainingRanges.push([src + range, currentRange[1]]);
    tempSeedRange.push([
      currentRange[0] + dest - src,
      src + range - 1 + dest - src,
    ]);
  } else if (currentRange[0] < src && src + range - 1 < currentRange[1]) {
    // console.log("Case4");
    tempSeedRange.push([dest, dest + range]);
    remainingRanges.push([currentRange[0], src - 1]);
    remainingRanges.push([src + range, currentRange[1]]);
  } else {
    // console.log("CaseDefault");
    remainingRanges.push(currentRange);
  }
}

function populateSeedRanges() {
  i = 0;
  while (i < seeds.length) {
    start = seeds[i];
    end = seeds[i] + seeds[i + 1];
    seedRanges.push([start, end]);
    i += 2;
  }
}
