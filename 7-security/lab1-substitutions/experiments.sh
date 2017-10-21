# !/bin/bash
go build
cd utils
go build
cd ..

TMP_FILE="temp.txt"
RESULT_FILE="result.txt"
FILE="data/be4.txt"

# words=("ab" "hey" "word" "hello" "safari" "encrypt")
words=("не" "так" "кава" "сонца" "скрыня" "тыдзень")
for word in "${words[@]}"
do
  echo "     RUNNING with word ${word}"
  ./lab1-substitutions -encrypt -file=$FILE -out=$TMP_FILE -lang=be -vigenere_keyword=$word
  ./lab1-substitutions -decrypt -file=$TMP_FILE -out=$RESULT_FILE -lang=be -kasiski_decryption
  echo "Comparing the result with source file..."
  ./utils/utils $RESULT_FILE $FILE
  rm $TMP_FILE
  rm $RESULT_FILE
done
