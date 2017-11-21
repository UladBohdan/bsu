package main

func naturalizePrompt(pr Prompt) Prompt {
	p := Prompt{
		Question: naturalizeString(pr.Question),
	}
	p.Answers = make([]string, len(pr.Answers))
	for i := range pr.Answers {
		p.Answers[i] = naturalizeString(pr.Answers[i])
	}
	return p
}

func naturalizeString(str string) string {
	if v, ok := naturalLanguage[str]; ok {
		return v
	}
	return str
}
