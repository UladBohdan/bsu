package main

import (
	"testing"
)

func init() {
	lang = "en"
}

func TestEncryptTextVigenere(t *testing.T) {
	tests := []struct {
		desc          string
		keyword, lang string
		text          string
		want          string
	}{{
		desc:    "tc1",
		text:    "hello world",
		lang:    "en",
		keyword: "aa",
		want:    "hello world",
	}, {
		desc:    "tc2",
		text:    "hello world",
		lang:    "en",
		keyword: "ab",
		want:    "hflmo wprmd",
	}, {
		desc:    "tc3",
		text:    "прывітанне",
		lang:    "be",
		keyword: "аа",
		want:    "прывітанне",
	}, {
		desc:    "be-ab",
		text:    "прывітанне",
		lang:    "be",
		keyword: "аб",
		want:    "псыгіуаонё",
	}}

	for _, tc := range tests {
		t.Run(tc.desc, func(*testing.T) {
			keyword = []rune(tc.keyword)
			lang = tc.lang
			result := encryptTextVigenere(tc.text)
			if result != tc.want {
				t.Errorf("test failed: got: %v, want: %v", result, tc.want)
			}
		})
	}
}
