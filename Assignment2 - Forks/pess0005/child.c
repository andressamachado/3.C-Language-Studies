#include <signal.h> // kill
#include <unistd.h> // getppid, sleep, write, read, close
#include <errno.h>
#include <fcntl.h>
#include <stdio.h> // sdterr, stdin, printf, fscanf
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>

#include "child.h"

void main_child(int fdRead, int fdWrite, short range, short timeout) {
    short totalTime = timeout;
    short counterVariable = totalTime;
    srand(time(0));

    short targetNumber = rand() % range;
    short parentGuess;

    // set flag to non-blocking reads
    int flags = fcntl(fdRead, F_GETFL, 0);
    if (fcntl(fdRead, F_SETFL, flags | O_NONBLOCK))
        fprintf(stderr, "\nCould not set non-blocking flag\n");

    while (1) {
        // reads from parent
        int nBytes = read(fdRead, &parentGuess, sizeof(parentGuess));
        if (nBytes > 0) {
            // resets counter when receiving a guess
            counterVariable = 10;
            // check if user is right
            short response = processGuess(targetNumber, parentGuess);
            // write back to parent the result of guess
            write(fdWrite, &response, sizeof(response));
        } else if (nBytes == 0) {
            // no bytes read, parent ended, break out of loop
            break;
        } else if (errno == EAGAIN) {
            // if receives the "try again" code
            // sleeps, does iddle task and check to send signals
            sleep(1);
            // decreases the variable timer
            doIdleTask(&counterVariable);
            // if half time, warn parent
            if (counterVariable == totalTime / 2) {
                int parentID = getppid();
                kill(parentID, SIGUSR2);
            }
            // if no time left, send kill to end program
            if (counterVariable == 0) {
                int parentID = getppid();
                kill(parentID, SIGUSR1);
            }
        } else {
            // some error occurred, break out of loop
            break;
        }
    }
}

// CHecks to see if guess matches the number we have.
// If not, say if it is bigger or smaller
short processGuess(short targetNumber, short parentGuess) {
    short resp;
    if (parentGuess == targetNumber) {
        resp = 0;
    } else if (parentGuess > targetNumber) {
        resp = 1;
    } else {
        resp = -1;
    }
    return resp;
}

// decreases the times variable
void doIdleTask(short *counterVariable) { (*counterVariable)--; }
