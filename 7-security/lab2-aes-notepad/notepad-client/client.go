package main

import (
	"bufio"
	"errors"
	"flag"
	"fmt"
	"io/ioutil"
	"net/http"
	"net/url"
	"os"
	"strings"
)

var (
	serverAddr string

	sessionKey string
)

func main() {
	flag.StringVar(&serverAddr, "server-addr", "", "Address to reach server.")
	flag.Parse()

	if err := login(); err != nil {
		fmt.Println("failed to login:", err)
		return
	}

	process()
}

func login() error {
	u, err := url.Parse(serverAddr + "/login")
	if err != nil {
		return nil
	}
	req := http.Request{
		Header: map[string][]string{
			"Username": []string{"test1"},
			"Password": []string{"password1"},
		},
		URL: u,
	}
	hc := http.Client{}
	resp, err := hc.Do(&req)
	if err != nil {
		return err
	}
	fmt.Println("login RESPONSE:", resp)
	fmt.Println("login COOKIES:", resp.Cookies())
	fmt.Println("login REQUEST:", req)
	for _, c := range resp.Cookies() {
		if c.Name == "session_key" {
			sessionKey = c.Value
			break
		}
	}
	if sessionKey == "" {
		return errors.New("no session key in the response")
	}
	return nil
}

func process() {
	for {
		fmt.Println("type a filename")
		file, _ := bufio.NewReader(os.Stdin).ReadString('\n')
		file = strings.Trim(file, "\n")
		fmt.Println("file to request:", file)
		text, err := getFile(file)
		if err != nil {
			fmt.Println("failed to get a file:", err)
			continue
		}
		fmt.Println("file received:", text)
	}
}

func getFile(file string) (string, error) {
	resp, err := http.Get(serverAddr + "/note/" + file)
	if err != nil {
		return "", err
	}
	text, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		return "", err
	}
	return string(text), err
}
