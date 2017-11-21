package main

import (
	"errors"
	"flag"
	"fmt"
)

type interactor interface {
	start()
	pushPrompt(Prompt) int
	notifyFailure(string)
	notifySuccess(string)
}

var (
	filename string
	mode     string

	out interactor
)

func main() {
	if err := parseArguments(); err != nil {
		fmt.Println(err)
		return
	}

	if err := loadData(); err != nil {
		fmt.Println(err)
		return
	}

	out.start()
}

func parseArguments() error {
	flag.StringVar(&filename, "filepath", "", "Path to file with knowledges.")
	flag.StringVar(&mode, "mode", "cli", "Choose between cli and web.")
	flag.Parse()

	if filename == "" {
		return errors.New("--filepath must be provided")
	}

	if mode != "cli" && mode != "web" {
		return errors.New("--mode is not set properly")
	}
	if mode == "cli" {
		out = cliInteractor{}
	} else {
		out = newWebInteractor()
	}

	return nil
}
