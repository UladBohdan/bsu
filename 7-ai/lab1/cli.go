package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
)

type cliInteractor struct{}

func (c cliInteractor) start() {
	run()
}

func (c cliInteractor) pushPrompt(pr Prompt) int {
	fmt.Println(pr.Question)
	for i, ans := range pr.Answers {
		fmt.Printf("%d  %s\n", i+1, ans)
	}
	var resp int
	for {
		fmt.Printf("your answer (0 if you don't know): ")
		reader := bufio.NewReader(os.Stdin)
		text, _ := reader.ReadString('\n')
		n, err := fmt.Sscanf(text, "%d", &resp)
		if err != nil || n != 1 {
			log.Printf("bad response, try again.")
			continue
		}
		if resp > len(pr.Answers) || resp <= 0 {
			log.Printf("bad response, try again.")
			continue
		}
		break
	}
	return resp - 1
}

func (c cliInteractor) notifyFailure(s string) {
	fmt.Println("Unable to identify the object:", s)
}

func (c cliInteractor) notifySuccess(s string) {
	fmt.Println("The answer is:", s)
}
