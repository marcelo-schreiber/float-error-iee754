all:
	gcc main.c -Wall -lm -o main
check:
	./main < input.txt > output.txt
	diff -w output.txt expected.txt
