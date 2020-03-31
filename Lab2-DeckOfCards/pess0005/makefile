CC = gcc
CC_fLAGS = -g -std=c99 -pedantic -W -Wall
FILES = deck.c format.c inputoutput.c main.c 
OUT_EXE = lab2

build: $(FILES)
		$(CC) $(CC_FLAGS) -o $(OUT_EXE) $(FILES)

clean:
		rm -f *.o core *.exe *~

rebuild: clean build