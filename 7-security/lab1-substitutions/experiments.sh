# !/bin/bash
go build

TMP_FILE="temp.txt"
EN_FILE="data/be4.txt"

# words=("ab" "hey" "word" "hello" "safari" "encrypt")
words=("не" "так" "кава" "сонца" "скрыня" "тыдзень")
for word in "${words[@]}"
do
  echo "     RUNNING with word ${word}"
  ./lab1-substitutions -encrypt -file=$EN_FILE -out=$TMP_FILE -lang=be -vigenere_keyword=$word
  ./lab1-substitutions -decrypt -file=$TMP_FILE -out=result.txt -lang=be -kasiski_decryption
  echo "Comparing the result with source file..."
  diff -s -l result.txt $EN_FILE
  rm $TMP_FILE
  rm result.txt
done
