package main

import (
	"flag"
	"fmt"
	"io/ioutil"
	"math/rand"
	"net/http"
	"strconv"
	"strings"
	"time"
)

var (
	port    string
	storage map[string]struct{}

	users = map[string]string{
		"test1": "password1",
		"test2": "password2",
	}

	permissions = map[string][]string{
		"test1": []string{"file0.txt", "file1.txt"},
		"test2": []string{"file1.txt", "file2.txt"},
	}

	sessions map[string]session
)

type session struct {
	user       string
	expiration time.Time
	key        string
}

func main() {
	flag.StringVar(&port, "port", "8080", "Port to run on.")
	flag.Parse()

	if err := indexStorage(); err != nil {
		fmt.Println("failed to index storage:", err)
		return
	}
	fmt.Printf("Storage indexed successfully! files found: %v\n", len(storage))

	sessions = make(map[string]session)

	http.HandleFunc("/login", handleLogin)
	http.HandleFunc("/note/", handleNote)

	fmt.Printf("Listening on https://localhost:%v\n", port)
	http.ListenAndServe(":"+port, nil)
}

func indexStorage() error {
	files, err := ioutil.ReadDir("data")
	if err != nil {
		return err
	}
	storage = make(map[string]struct{})
	for _, file := range files {
		storage[file.Name()] = struct{}{}
	}
	return nil
}

func handleLogin(w http.ResponseWriter, r *http.Request) {
	hdr := r.Header
	username, ok := hdr["Username"]
	if !ok {
		fmt.Fprint(w, "no username")
		return
	}
	password, ok := hdr["Password"]
	if !ok {
		fmt.Fprint(w, "no password in header")
		return
	}
	if psw, ok := users[username[0]]; ok {
		if psw != password[0] {
			fmt.Fprint(w, "user was found, but password is incorrect")
			return
		}
		fmt.Fprint(w, "success!")
		s := session{
			user:       username[0],
			expiration: time.Now().Add(time.Minute),
			key:        strconv.Itoa(rand.Int()),
		}
		http.SetCookie(w, &http.Cookie{
			Name:  "session_key",
			Value: s.key,
		})
		fmt.Println("Response", w)
		fmt.Fprint(w, "ololo")
		return
	}
	fmt.Fprint(w, "failed to login, no such user")
}

func handleNote(w http.ResponseWriter, r *http.Request) {
	if auth(r) == false {
		return
	}
	ss := strings.Split(r.URL.Path, "/")
	file := ss[len(ss)-1]
	fmt.Println("file requested:", file)
	if _, ok := storage[file]; ok {
		fmt.Fprintf(w, "Hello, file %q exists!", file)
		return
	}
	fmt.Fprintf(w, "file %q not found", file)
}

func auth(r *http.Request) bool {
	sKey := r.Header["SessionKey"][0]
	_, ok := sessions[sKey]
	return ok
}
