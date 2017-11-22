package main

import (
	"errors"
)

const (
	ruleCorrect   = -1
	ruleIncorrect = -2
	ruleUndefined = 2
)

type contextEntry struct {
	attribute, value string
}

var (
	globalTargetAttribure = "country"

	targetsStack []string
	// maps attributes to appropriate values.
	context = make(map[string]string)

	blockedRules = make(map[int]struct{})

	errNotFound = errors.New("rule/prompt not found")
)

func run() {
	addTarget(globalTargetAttribure)
	for {
		currentTarget := topTarget()
		currentRule, err := searchRule(currentTarget)
		if err == errNotFound {
			pr, err := searchPrompt(currentTarget)
			if err == errNotFound {
				out.notifyFailure("No rule, no prompt found!")
				cleanup()
				return
			}
			resp := out.pushPrompt(pr)
			context[pr.Attribute] = pr.Answers[resp]
			popTarget()
		} else {
			// Rule was found.
			corr := checkRuleCorrectness(currentRule)
			switch corr {
			case ruleCorrect:
				// adding to context.
				context[currentRule.conclusion.attribute] = currentRule.conclusion.value
				popTarget()
				if len(targetsStack) == 0 {
					// It's found, isn't it?
					out.notifySuccess(context[globalTargetAttribure])
					cleanup()
					return
				}
			case ruleIncorrect:
				blockedRules[currentRule.num] = struct{}{}
			default:
				// Rule is not yet evaluatable. Number of condition is returned.
				addTarget(currentRule.conditions[corr].attribute)
			}
		}
	}
}

func addTarget(target string) {
	targetsStack = append(targetsStack, target)
}

func topTarget() string {
	return targetsStack[len(targetsStack)-1]
}

func popTarget() {
	targetsStack = targetsStack[:len(targetsStack)-1]
}

func searchRule(target string) (rule, error) {
	for _, r := range rules {
		if r.conclusion.attribute == target {
			if _, ok := blockedRules[r.num]; !ok {
				// Found and not blocked.
				return r, nil
			}
		}
	}
	return rule{}, errNotFound
}

func searchPrompt(target string) (Prompt, error) {
	if pr, ok := prompts[target]; ok {
		return pr, nil
	}
	return Prompt{}, errNotFound
}

func checkRuleCorrectness(r rule) int {
	for i, c := range r.conditions {
		v, ok := context[c.attribute]
		if !ok {
			// Can't evaluate the condition. Returning it's number.
			return i
		}
		if v != c.value {
			return ruleIncorrect
		}
	}
	return ruleCorrect
}

func cleanup() {
	targetsStack = []string{}
	context = make(map[string]string)
	blockedRules = make(map[int]struct{})
}
