package main

import (
	"errors"
	"flag"
	"fmt"
	"log"
)

const (
	dataFilename string = "data/mushrooms.csv"
)

var (
	mode string
)

func main() {
	if err := parseArguments(); err != nil {
		fmt.Println(err)
		return
	}

	if err := readData(dataFilename); err != nil {
		log.Printf("failed to read data: %v", err)
		return
	}
	log.Printf("data read successfully: %d records", len(data))

	if mode == "cli" {
		runCLI()
	} else {
		runServer()
	}
}

func parseArguments() error {
	flag.StringVar(&mode, "mode", "cli", "Choose between cli and web.")
	flag.Parse()

	if mode != "cli" && mode != "web" {
		return errors.New("--mode is not set properly")
	}

	return nil
}
