package main

import (
	"flag"
	"fmt"
	"io/ioutil"
	"math/rand"
	"os"
	"time"
	"unicode"
)

var (
	encrypt, decrypt  bool
	filename, out     string
	lang              string
	keyword           []rune
	vigenereKeyword   string
	kasiskiDecryption bool

	mostFreq = map[string]int{
		"be": 1, // А
		"en": 5, // E
	}

	alphabets = map[string][]rune{
		"be": []rune("абвгдеёжзійклмнопрстуўфхцчшыьэюя"),
		"en": []rune("abcdefghijklmnopqrstuvwxyz"),
	}
)

func main() {
	rand.Seed(time.Now().UnixNano())

	flag.BoolVar(&encrypt, "encrypt", false, "Enable to encrypt a file.")
	flag.BoolVar(&decrypt, "decrypt", false, "Enable to decrypt a file.")
	flag.StringVar(&filename, "file", "", "File to encrypt/decrypt.")
	flag.StringVar(&out, "out", "", "Output destination.")
	flag.StringVar(&lang, "lang", "en", "Text language.")
	flag.StringVar(&vigenereKeyword, "vigenere_keyword", "", "Keyword for Vigenere cipher.")
	flag.BoolVar(&kasiskiDecryption, "kasiski_decryption", false, "Use Kasiski method to decode.")
	flag.Parse()

	keyword = []rune(vigenereKeyword)

	if encrypt == decrypt {
		fmt.Println("It's either encrypt or decrypt. You must specify.")
		return
	}

	if lang != "en" && lang != "be" {
		fmt.Println("Language must be either 'en' (default) or 'be'.")
		return
	}

	file, err := os.Open(filename)
	defer file.Close()
	if err != nil {
		fmt.Printf("Error when opening file: %v\n", err)
		return
	}

	buf, err := ioutil.ReadAll(file)
	if err != nil {
		fmt.Printf("Error when reading file: %v\n", err)
		return
	}
	text := string(buf)

	var result string
	subst := rand.Int() % 26
	if encrypt {
		fmt.Println("TEXT LENGTH: ", len(text))
		if len(keyword) == 0 {
			fmt.Printf("Encrypting file %q with a randomly-chosen shift %d\n", filename, subst)
			result = encryptText(text, subst)
		} else {
			fmt.Printf("Encrypting file %q with a keyword %q using Vigenere method\n", filename, vigenereKeyword)
			result = encryptTextVigenere(text)
		}
	} else {
		if kasiskiDecryption {
			fmt.Printf("Decrypting file %q using Kasiski method\n", filename)
			result = decryptKasiski(text)
		} else {
			fmt.Printf("Decrypting file %q\n", filename)
			result = decryptText(text)
		}
	}

	if err := ioutil.WriteFile(out, []byte(result), os.ModePerm); err != nil {
		fmt.Printf("Failed to write to out: %v with frequency analysis", err)
	}
}

func isLowerCase(l rune) bool {
	if lang == "en" {
		return l >= 'a' && l <= 'z'
	} else if lang == "be" {
		return (l >= 'а' && l <= 'я') || l == 'ў' || l == 'ё' || l == 'і'
	}
	return false
}

func isUpperCase(l rune) bool {
	if lang == "en" {
		return l >= 'A' && l <= 'Z'
	} else if lang == "be" {
		return (l >= 'А' && l <= 'Я') || l == 'Ў' || l == 'Ё' || l == 'І'
	}
	return false
}

func indexOf(l rune) int {
	for i, r := range alphabets[lang] {
		if l == r {
			return i
		}
	}
	return -1
}

func isText(s string) bool {
	for _, r := range s {
		if !isLowerCase(r) && !isUpperCase(r) {
			return false
		}
	}
	return true
}

func shiftRune(l rune, n int) rune {
	isUpper := false
	if isUpperCase(l) {
		isUpper = true
		l = unicode.ToLower(l)
	}
	idx := indexOf(l)
	if idx == -1 {
		panic(fmt.Sprintf("NOT A LETTER: failed to get index of: %v", string(l)))
	}
	idx += n
	if idx >= len(alphabets[lang]) {
		idx -= len(alphabets[lang])
	}
	if isUpper {
		return unicode.ToUpper(alphabets[lang][idx])
	}
	return alphabets[lang][idx]
}

func encryptText(text string, subst int) string {
	var result string
	for _, l := range text {
		if isLowerCase(l) || isUpperCase(l) {
			result += string(shiftRune(l, subst))
		} else {
			result += string(l)
		}
	}
	return result
}

func decryptText(text string) string {
	freq := make([]int, len(alphabets[lang]))
	for _, l := range text {
		if !isLowerCase(l) && !isUpperCase(l) {
			continue
		}
		l = unicode.ToLower(l)
		freq[indexOf(l)]++
	}

	eIdx := 0
	for i, v := range freq {
		if v > freq[eIdx] {
			eIdx = i
		}
	}

	var subst int
	if eIdx == mostFreq[lang]-1 {
		subst = 0
	} else if eIdx < mostFreq[lang]-1 {
		subst = mostFreq[lang] - 1 - eIdx
	} else {
		subst = len(alphabets[lang]) - (eIdx - (mostFreq[lang] - 1))
	}

	return encryptText(text, subst) // 'E' is the 5th in the alphabet.
}

func encryptTextVigenere(txt string) string {
	text := []rune(txt)
	shifts := make([]int, len(keyword))
	for i, l := range keyword {
		shifts[i] = indexOf(unicode.ToLower(l))
	}

	var result string

	for i, l := range text {
		if !isLowerCase(l) && !isUpperCase(l) {
			result += string(l)
			continue
		}
		result += string(shiftRune(l, shifts[i%len(keyword)]))
	}

	return result
}

func decryptKasiski(txt string) string {
	text := []rune(txt)
	k := 3

	m := make(map[string]int)

	for i := 0; i < len(text)-k; i++ {
		s := text[i : i+k]
		if !isText(string(s)) {
			continue
		}
		m[string(s)]++
	}

	var mxRepeated int
	var bestSubstr string

	for k, v := range m {
		if v > mxRepeated {
			mxRepeated = v
			bestSubstr = k
		}
	}

	var idxs []int

	for i := 0; i < len(text)-k; i++ {
		if string(text[i:i+k]) != bestSubstr {
			continue
		}
		idxs = append(idxs, i)
	}

	distances := make([]int, len(idxs)-1)
	for i := range idxs[:len(idxs)-1] {
		distances[i] = idxs[i+1] - idxs[i]
	}

	g := gcdArray(distances...)

	fmt.Println("Kasiski's predicted keyword length:", g)

	texts := make([]string, g)
	for i, r := range text {
		texts[i%g] += string(r)
	}
	decrypted := make([]string, g)
	for i := range decrypted {
		decrypted[i] = decryptText(texts[i])
	}

	result := make([]rune, len(text))
	for i := 0; i < g; i++ {
		for j, r := range []rune(decrypted[i]) {
			result[j*g+i] = r
		}
	}

	return string(result)
}

func gcdArray(ar ...int) int {
	if len(ar) == 0 {
		return 1
	}
	def := ar[0]
	for _, a := range ar[1:] {
		def = gcd(def, a)
	}
	return def
}

func gcd(a, b int) int {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}
