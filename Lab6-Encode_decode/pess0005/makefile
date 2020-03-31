CC = gcc
CC_FLAGS = -g -pedantic -Wall -W -std=c99
FILES = base64_tables.c 
.DEFAULT_GOAL := all

base64encode: $(FILES)
	$(CC) $(CC_FLAGS) -o encode $(FILES) encode.c

base64decode: $(FILES)
	$(CC) $(CC_FLAGS) -o decode $(FILES) decode.c

all: base64encode base64decode

clean:
	rm -f *.o core *.exe *~ *.out *.stackdump

rebuild: clean base64encode base64decode
