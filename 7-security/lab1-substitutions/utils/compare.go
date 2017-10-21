package main

import (
	"fmt"
	"io/ioutil"
	"os"
)

func main() {
	if len(os.Args) < 3 {
		fmt.Println("two filenames must be provided")
		return
	}

	filename1 := os.Args[1]
	filename2 := os.Args[2]

	file1, txt1, err := getText(filename1)
	if err != nil {
		fmt.Println("failed to get text:", err)
		return
	}
	defer file1.Close()
	text1 := []rune(txt1)

	file2, txt2, err := getText(filename2)
	if err != nil {
		fmt.Println("failed to get text:", err)
		return
	}
	defer file2.Close()
	text2 := []rune(txt2)

	ln := min(len(text1), len(text2))

	success := 0
	for i := 0; i < ln; i++ {
		if text1[i] == text2[i] {
			success++
		}
	}

	fmt.Printf("Decryption rate: %v%%\n", float64(success)/float64(max(len(text1), len(text2)))*100)
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func getText(filename string) (*os.File, string, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, "", fmt.Errorf("error when opening file: %v\n", err)
	}
	buf, err := ioutil.ReadAll(file)
	if err != nil {
		return nil, "", fmt.Errorf("error when reading file: %v\n", err)
	}
	return file, string(buf), nil
}
