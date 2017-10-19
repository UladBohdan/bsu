# !/bin/bash
TMP_FILE="temp.txt"
go build

echo "-- EN TEST Caesar"
EN_FILE="data/en2.txt"
./lab1-substitutions -encrypt -file=$EN_FILE -out=$TMP_FILE
./lab1-substitutions -decrypt -file=$TMP_FILE -out=result.txt
echo "Comparing the result with source file..."
diff -s result.txt $EN_FILE
rm $TMP_FILE
rm result.txt

echo "-- BE TEST Caesar"
BE_FILE="data/be2.txt"
./lab1-substitutions -encrypt -file=$BE_FILE -out=$TMP_FILE -lang=be
./lab1-substitutions -decrypt -file=$TMP_FILE -out=result.txt -lang=be
echo "Comparing the result with source file..."
diff -s result.txt $BE_FILE
rm $TMP_FILE
rm result.txt

echo "-- EN TEST Vigenere/Kasiski"
EN_FILE="data/en2.txt"
./lab1-substitutions -encrypt -file=$EN_FILE -out=$TMP_FILE -vigenere_keyword="plot"
./lab1-substitutions -decrypt -file=$TMP_FILE -out=result.txt -kasiski_decryption
echo "Comparing the result with source file..."
diff -s result.txt $EN_FILE
rm $TMP_FILE
rm result.txt

echo "-- BE TEST Vigenere/Kasiski"
BE_FILE="data/be2.txt"
./lab1-substitutions -encrypt -file=$BE_FILE -out=$TMP_FILE -lang=be -vigenere_keyword="сонца"
./lab1-substitutions -decrypt -file=$TMP_FILE -out=result.txt -lang=be -kasiski_decryption
echo "Comparing the result with source file..."
diff -s result.txt $BE_FILE
rm $TMP_FILE
rm result.txt
