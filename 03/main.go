package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
	"time"
	"unicode"
)

type Number struct {
	num   int
	line  int
	start int
	end   int
	valid bool
	coord [2]int
}

var text []string = []string{}
var numList []Number = []Number{}
var gearList []Number = []Number{}

func timeTrack(start time.Time, name string) {
	elapsed := time.Since(start)
	log.Printf("%s took %s", name, elapsed)
}

func main() {
	defer timeTrack(time.Now(), "Main")
	file, err := os.Open("puzzle.txt")
	if err != nil {
		fmt.Print(err)
	}
	defer file.Close()

	parseText(file)
	checkPerimeter()
	var result int = 0
	for _, num := range numList {
		fmt.Print(num, "\n")
		if num.valid {
			result += num.num
		}
	}
	result2 := evalGears()

	fmt.Printf("\n\nFinished. Result First: %d\n", result)
	fmt.Printf("Finished. Result Second: %d\n", result2)
}

func parseText(file *os.File) {
	i := 0
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		text = append(text, scanner.Text())
		parseLine(scanner.Text(), i)
		i++
	}
}

func checkPerimeter() {
	fmt.Println("Checking Perimeters...")
	for indexNum, num := range numList {
		var firstRange, endRange, firstLine, endLine int
		if firstRange = num.start - 1; firstRange < 0 {
			firstRange = 0
		}

		if endRange = num.end + 2; endRange >= len(text[num.line]) {
			endRange = len(text[num.line]) - 1
		}

		if firstLine = num.line - 1; firstLine < 0 {
			firstLine = 0
		}

		if endLine = num.line + 1; endLine >= len(text) {
			endLine = len(text) - 1
		}

		i := firstLine
		fmt.Println("------------")
		for i <= endLine {
			fmt.Printf("%s\n", text[i][firstRange:endRange])
			for j, char := range text[i][firstRange:endRange] {
				if isSymbol(char) {
					numList[indexNum].valid = true
					if strings.ContainsRune("*", char) {
						numList[indexNum].coord = [2]int{i, j + firstRange}
						gearList = append(gearList, numList[indexNum])
					}
				}
			}
			i++
		}
		fmt.Printf("----- %v \n", numList[indexNum].valid)
	}
	fmt.Println("... done.")
}

func evalGears() int {
	var result int = 0
	i := 0
	for i < len(gearList) {
		j := i + 1
		for j < len(gearList) {
			if gearList[i].coord == gearList[j].coord {
				result += gearList[i].num * gearList[j].num
			}
			j++
		}
		i++
	}
	return result
}

func parseLine(line string, lineNum int) {
	i := 0
	for i < len(line) {
		if isNumber(line[i]) {
			j := i + 1
			for j < len(line) && isNumber(line[j]) {
				j++
			}
			num, _ := strconv.Atoi(line[i:j])
			numList = append(numList,
				Number{
					num:   num,
					line:  lineNum,
					start: i,
					end:   j - 1,
					valid: false,
				})
			i = j
		}
		i++
	}
}

func isNumber(char byte) bool {
	if strings.ContainsRune(".", rune(char)) {
		return false
	}
	return unicode.IsDigit(rune(char))
}

func isSymbol(char rune) bool {
	if strings.ContainsRune(".", rune(char)) {
		return false
	}
	return !unicode.IsDigit(rune(char))
}
