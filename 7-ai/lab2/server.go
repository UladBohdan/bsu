package main

import (
	"fmt"
	"log"
	"net/http"
	"strings"
)

const (
	port = "8080"
)

func runServer() {
	handlePaths()
}

func handlePaths() {
	http.Handle("/static/", http.StripPrefix("/static/", http.FileServer(http.Dir("./web_client/static/"))))

	http.HandleFunc("/train/", func(w http.ResponseWriter, r *http.Request) {
		initTraining()
		fmt.Fprint(w, "trained successfully")
	})

	http.HandleFunc("/validate/", func(w http.ResponseWriter, r *http.Request) {
		rate := validateTraining()
		fmt.Fprintf(w, "validation rate: %d%%", int(rate*100))
	})

	http.HandleFunc("/recognize/", func(w http.ResponseWriter, r *http.Request) {
		ss := strings.Split(r.URL.Path, "/")
		var x int
		fmt.Sscanf(ss[len(ss)-2], "%d", &x)
		log.Printf("recognition of mushroom %d was requested", x)

		class, err := recognize(data[x][1:])
		if err != nil {
			log.Printf("error in recognition: %v", err)
			fmt.Fprintf(w, "error in recognition: %v", err)
		}
		fmt.Fprintf(w, "class recognized: %s", class)
	})

	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		http.ServeFile(w, r, "./web_client/index.html")
	})

	log.Printf("available on http://localhost:%s\n", port)
	http.ListenAndServe(":"+port, nil)
}
