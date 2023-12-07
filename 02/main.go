package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"slices"
	"strconv"
	"strings"
)

const RED int = 12
const GREEN int = 13
const BLUE int = 14

func main() {
	file, err := os.Open("puzzle.txt")
	if err != nil {
		fmt.Print(err)
	}
	defer file.Close()

	var result int = 0
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		result += evalLineAdvanced(scanner.Text())
		fmt.Println(scanner.Text(), "|", evalLineAdvanced(scanner.Text()))
	}
	fmt.Printf("Result: %d", result)
}

func evalLine(line string) int {
	var gameID int = 0
	gameSplit := strings.Split(line, ":")
	gameID, _ = strconv.Atoi(gameSplit[0][5:])
	sets := strings.Split(gameSplit[1], ";")
	var gameResults []bool
	for _, set := range sets {
		gameResults = append(gameResults, evalSet(set))
	}
	if checkAll(gameResults) {
		return gameID
	} else {
		return 0
	}
}

func evalLineAdvanced(line string) int {
	var reds, greens, blues []int

	gameSplit := strings.Split(line, ":")
	sets := strings.Split(gameSplit[1], ";")
	for _, set := range sets {
		red, green, blue := evalSetAdvanced(set)
		reds = append(reds, red)
		greens = append(greens, green)
		blues = append(blues, blue)
	}
	return slices.Max(reds) * slices.Max(greens) * slices.Max(blues)
}

func evalSet(game string) bool {
	re := regexp.MustCompile("[0-9]+")
	splitColors := strings.Split(game, ",")
	for _, color := range splitColors {
		switch {
		case strings.Contains(color, "red"):
			numRed, _ := strconv.Atoi(re.FindString(color))
			if numRed > RED {
				return false
			}
		case strings.Contains(color, "blue"):
			numRed, _ := strconv.Atoi(re.FindString(color))
			if numRed > BLUE {
				return false
			}
		case strings.Contains(color, "green"):
			numRed, _ := strconv.Atoi(re.FindString(color))
			if numRed > GREEN {
				return false
			}
		}
	}
	return true
}

func evalSetAdvanced(game string) (red, green, blue int) {
	red, green, blue = 0, 0, 0
	re := regexp.MustCompile("[0-9]+")
	splitColors := strings.Split(game, ",")
	for _, color := range splitColors {
		switch {
		case strings.Contains(color, "red"):
			red, _ = strconv.Atoi(re.FindString(color))
		case strings.Contains(color, "green"):
			green, _ = strconv.Atoi(re.FindString(color))
		case strings.Contains(color, "blue"):
			blue, _ = strconv.Atoi(re.FindString(color))
		}
	}
	return
}

func checkAll(bools []bool) bool {
	for _, item := range bools {
		if !item {
			return false
		}
	}
	return true
}
