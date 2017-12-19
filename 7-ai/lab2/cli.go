package main

import "log"

func runCLI() {
	if err := initTraining(); err != nil {
		log.Printf("training failed.")
		return
	}
	log.Printf("trained successfully.")

	validateTraining()
}
