package main

import (
	"bufio"
	"errors"
	"fmt"
	"log"
	"os"
	"regexp"
	"strings"
)

type statement struct {
	// attribute IS value
	attribute, value string
}

type rule struct {
	num        int
	conditions []statement
	conclusion statement
}

// Prompt represents Question with Answers.
// Exported in order to be able to Marshal the type.
type Prompt struct {
	Attribute string
	Question  string
	Answers   []string
}

var (
	rules []rule
	// maps attributes to prompts.
	prompts = make(map[string]Prompt)

	countriesISO = make(map[string]string)

	naturalLanguage = make(map[string]string)

	langRgxp = `[a-zA-Z0-9'?_ ]+`

	ruleRgxp    = regexp.MustCompile(`^IF` + langRgxp + `\.$`)
	promptRgxp  = regexp.MustCompile(`^PROMPT` + langRgxp + `\.$`)
	commentRgxp = regexp.MustCompile(`^#` + langRgxp + `\.$`)
	isoRgxp     = regexp.MustCompile(`^ISO` + langRgxp + `\.$`)
	mappingRgxp = regexp.MustCompile(`^MAP` + langRgxp + `\.$`)
)

func loadData() error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		if err := processLine(scanner.Text()); err != nil {
			return err
		}
	}

	if err := scanner.Err(); err != nil {
		return err
	}

	log.Printf("Knowledges have been loaded successfully.")
	return nil
}

func processLine(line string) error {
	if ruleRgxp.MatchString(line) {
		return processRuleString(line)
	} else if promptRgxp.MatchString(line) {
		return processPromptString(line)
	} else if commentRgxp.MatchString(line) {
		return nil
	} else if isoRgxp.MatchString(line) {
		return processISOString(line)
	} else if mappingRgxp.MatchString(line) {
		return processMapString(line)
	}
	return fmt.Errorf("line %q can't be parsed", line)
}

func processISOString(line string) error {
	ss := strings.Split(line[:len(line)-1], " ")
	if len(ss) != 3 {
		return fmt.Errorf("failed to split ISO line %q", line)
	}
	countriesISO[ss[1]] = ss[2]
	return nil
}

func processMapString(line string) error {
	ss := strings.SplitN(line[:len(line)-1], " ", 3)
	if len(ss) != 3 {
		return fmt.Errorf("failed to split MAP line: %q", line)
	}
	naturalLanguage[ss[1]] = ss[2]
	return nil
}

func processPromptString(line string) error {
	ss := strings.Split(line[6:len(line)-1], "QUESTION")
	ss[0] = strings.Trim(ss[0], " ")
	qa := strings.Split(ss[1], "ANSWERS")
	qa[0] = strings.Trim(qa[0], " ")
	pr := Prompt{
		Attribute: ss[0],
		Question:  qa[0],
		Answers:   []string{},
	}
	qa[1] = strings.Trim(qa[1], " ")
	for _, a := range strings.Split(qa[1], " ") {
		pr.Answers = append(pr.Answers, strings.Trim(a, " "))
	}
	prompts[ss[0]] = pr
	return nil
}

func processRuleString(line string) error {
	ss := strings.Split(line[2:len(line)-1], "THEN")
	if len(ss) != 2 {
		return errors.New("THEN must occur exactly once in a line")
	}
	ss[0] = strings.Trim(ss[0], " ")
	ss[1] = strings.Trim(ss[1], " ")

	conditions, err := processConditions(ss[0])
	if err != nil {
		return err
	}
	conclusion, err := stringToStatement(ss[1])
	if err != nil {
		return err
	}

	rules = append(rules, rule{
		num:        len(rules),
		conditions: conditions,
		conclusion: conclusion,
	})

	return nil
}

func processConditions(s string) ([]statement, error) {
	ss := strings.Split(s, "AND")
	resp := []statement{}
	for _, str := range ss {
		stat, err := stringToStatement(str)
		if err != nil {
			return nil, err
		}
		resp = append(resp, stat)
	}
	return resp, nil
}

// processing 'a IS b' strings.
func stringToStatement(s string) (statement, error) {
	ss := strings.Split(s, "IS")
	if len(ss) != 2 {
		return statement{}, fmt.Errorf("failed to parse %q as a statement", s)
	}

	ss[0] = strings.Trim(ss[0], " ")
	ss[1] = strings.Trim(ss[1], " ")

	return statement{ss[0], ss[1]}, nil
}
