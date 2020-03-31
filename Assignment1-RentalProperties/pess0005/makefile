CC = gcc
CC_fLAGS = -g -std=c99 -pedantic -W -Wall
FILES = lists.c property.c sort.c main.c
OUT_EXE = ass1

build: $(FILES)
		$(CC) $(CC_FLAGS) -o $(OUT_EXE) $(FILES)

clean:
		rm -f *.o core *.exe *~

rebuild: clean build