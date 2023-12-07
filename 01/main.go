package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
)

const NUMBERS string = "0123456789"

var STRINGNUMBERS []string = []string{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"}

var X string = "XXXXXXXXX"

func main() {
	file, err := os.Open("puzzle.txt")
	if err != nil {
		fmt.Print(err)
	}
	defer file.Close()

	var result int = 0
	var lineNumber int = 1
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		text := scanner.Text()
		number := evaluateLineAdvanced(text)
		result += number

		fmt.Println(lineNumber, ":", text, ":", number)
		lineNumber += 1
	}

	fmt.Printf("Result: %d", result)

}

// func evaluateLine(line string) int {
// 	var numbersInLine []int

// 	for _, v := range line {
// 		if strings.ContainsRune(NUMBERS, v) {
// 			number, _ := strconv.Atoi(string(v))
// 			numbersInLine = append(numbersInLine, number)
// 		}
// 	}
// 	return numbersInLine[0]*10 + numbersInLine[len(numbersInLine)-1]
// }

func evaluateLineAdvanced(line string) int {
	first, last := lookForNumbersInLine(line)
	return first*10 + last
}

type IndexObject struct {
	index    int
	numAsStr string
	num      int
}

type ByIndex []IndexObject

func (a ByIndex) Len() int           { return len(a) }
func (a ByIndex) Swap(i, j int)      { a[i], a[j] = a[j], a[i] }
func (a ByIndex) Less(i, j int) bool { return a[i].index < a[j].index }

func lookForNumbersInLine(line string) (int, int) {
	var bufferLine string
	var matchList []IndexObject

	// Look for written numbers
	for i, v := range STRINGNUMBERS {
		bufferLine = line
		for { // Repeat written number lookup until all instances are found
			index := strings.Index(bufferLine, v)
			if index == -1 {
				break
			}
			matchList = append(matchList, IndexObject{index: index, numAsStr: v, num: i})
			// replace first instance of number with X of equal length to prevent indexing problem
			bufferLine = strings.Replace(bufferLine, v, X[:len(v)], 1)
		}
	}
	// Look for numbers
	for i, v := range line {
		if strings.ContainsRune(NUMBERS, v) {
			number, _ := strconv.Atoi(string(v))
			matchList = append(matchList, IndexObject{index: i, numAsStr: "", num: number})
		}
	}

	sort.Sort(ByIndex(matchList))

	return matchList[0].num, matchList[len(matchList)-1].num
}
