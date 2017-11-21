package main

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"strings"
)

const (
	port = "8080"
)

type webInteractor struct {
	started                   bool
	finishSuccess, finishFail chan string
	nextPrompt                chan Prompt
	nextResp                  chan int
}

func newWebInteractor() *webInteractor {
	return &webInteractor{
		finishSuccess: make(chan string),
		finishFail:    make(chan string),
		nextPrompt:    make(chan Prompt),
		nextResp:      make(chan int),
	}
}

func (c *webInteractor) start() {
	c.startServer()
}

func (c *webInteractor) pushPrompt(pr Prompt) int {
	c.nextPrompt <- pr
	return <-c.nextResp
}

func (c *webInteractor) notifyFailure(s string) {
	c.finishFail <- s
}

func (c *webInteractor) notifySuccess(s string) {
	c.finishSuccess <- s
}

func (c *webInteractor) startServer() {
	http.Handle("/static/", http.StripPrefix("/static/", http.FileServer(http.Dir("./web_client/static/"))))

	http.HandleFunc("/next/", c.nextHandler)

	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		http.ServeFile(w, r, "./web_client/index.html")
	})

	log.Printf("available on http://localhost:%s\n", port)
	http.ListenAndServe(":"+port, nil)
}

func (c *webInteractor) nextHandler(w http.ResponseWriter, r *http.Request) {
	ss := strings.Split(r.URL.Path, "/")
	if ss[len(ss)-2] == "next" {
		// Initial call.
		if !c.started {
			go run()
			c.started = true
		}
	} else {
		var resp int
		fmt.Sscanf(ss[len(ss)-2], "%d", &resp)
		log.Printf("response %d is received", resp)
		c.nextResp <- resp
	}
	select {
	case pr := <-c.nextPrompt:
		pr = naturalizePrompt(pr)
		m, _ := json.Marshal(pr)
		fmt.Fprint(w, string(m))
		log.Printf("question %q is pushed to the client", pr.Question)
	case ans := <-c.finishSuccess:
		c.started = false
		log.Printf("the country we were looking for: %q", ans)
		fmt.Fprintf(w, `{"Answer":"%v", "CountryCode":"%v"}`, naturalizeString(ans), countriesISO[ans])
	case msg := <-c.finishFail:
		c.started = false
		log.Printf("failed: %v", msg)
		fmt.Fprintf(w, `{"Failure":"%v"}`, msg)
	}
}
