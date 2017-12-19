package main

import (
	"encoding/csv"
	"os"
)

var fields []string
var data [][]string

func readData(filename string) error {
	var err error
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	csvReader := csv.NewReader(file)

	fields, err = csvReader.Read()
	if err != nil {
		return err
	}

	data, err = csvReader.ReadAll()
	if err != nil {
		return err
	}

	return nil
}
