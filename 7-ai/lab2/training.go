package main

import (
	"fmt"
	"log"
)

const (
	parametricTrainingRatio float32 = 0.7

	skipFirstEntries = 10
)

var (
	classes []string

	parametricSet [][]string
	trainingSet   [][]string

	setSize int

	// D is a matrix of distances.
	D [][]int
)

func initTraining() error {
	setSize = len(data)

	parametricSetSize := int(float32(setSize) * parametricTrainingRatio)
	parametricSet = data[skipFirstEntries:parametricSetSize]

	trainingSetSize := setSize - parametricSetSize
	trainingSet = data[parametricSetSize:]

	D = make([][]int, trainingSetSize)
	for i := range D {
		D[i] = make([]int, parametricSetSize)
	}

	var err error
	for i, tData := range trainingSet {
		for j, pData := range parametricSet {
			D[i][j], err = distance(tData[1:], pData[1:])
			if err != nil {
				return err
			}
		}
	}

	// for i := range trainingSet[:10] {
	// 	for j := range parametricSet[:10] {
	// 		fmt.Printf("%d ", D[i][j])
	// 	}
	// 	fmt.Println()
	// }

	return nil
}

func validateTraining() float32 {
	successRate := 0
	for i, tRecord := range trainingSet {
		// implementing MIN. makes it 1-NN.
		mnIdx := 0
		for j := range parametricSet {
			if D[i][j] < D[i][mnIdx] {
				mnIdx = j
			}
		}
		// fmt.Println("MIN distance: ", D[i][mnIdx])
		if tRecord[0] == parametricSet[mnIdx][0] {
			successRate++
		}
	}

	rate := float32(successRate) / float32(len(trainingSet))

	log.Printf("validation results: %d / %d    percentage: %f",
		successRate, len(trainingSet), rate)

	return rate
}

func recognize(data []string) (string, error) {
	// data does not contain class in [0].
	mnClass := ""
	mnDist := 999999
	for _, pRecord := range parametricSet {
		d, err := distance(data, pRecord[1:])
		if err != nil {
			return "", err
		}
		if d < mnDist {
			mnDist = d
			mnClass = pRecord[0]
		}
	}
	return mnClass, nil
}

func distance(a, b []string) (int, error) {
	if len(a) != len(b) {
		return 0, fmt.Errorf("incompatible array sizes: %d vs. %d", len(a), len(b))
	}
	ans := 0
	for i := range a {
		if a[i] != b[i] {
			ans++
		}
	}
	return ans, nil
}
