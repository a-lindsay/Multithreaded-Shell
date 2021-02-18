shell: main.cpp lineParser.cpp runPrograms.cpp getLine.cpp excessParser.cpp
	g++ -o shell main.cpp lineParser.cpp runPrograms.cpp getLine.cpp excessParser.cpp -ggdb -Wall

cat: cat.c
	gcc -o cat cat.c -ggdb -Wall

ls: ls.c
	gcc -o ls ls.c -ggdb -Wall
clean:
	rm -f ls cat shell
