CC = gcc
CC_fLAGS = -g -std=c99 -pedantic -W -Wall
FILES = Category.c Input.c Ticket.c TicketManager.c Main.c 
OUT_EXE = lab4

build: $(FILES)
		$(CC) $(CC_FLAGS) -o $(OUT_EXE) $(FILES)

clean:
		rm -f *.o core *.exe *~

rebuild: clean build