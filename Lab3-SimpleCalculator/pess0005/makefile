CC = gcc
CC_fLAGS = -g -std=c99 -pedantic -W -Wall
FILES = main.c 
OUT_EXE = lab3

build: $(FILES)
		$(CC) $(CC_FLAGS) -o $(OUT_EXE) $(FILES)

clean:
		rm -f *.o core *.exe *~

rebuild: clean build