#include <stdio.h>
#include <signal.h>
#include <stdlib.h> // exit(1)
#include <unistd.h> //read , write pipe

#include "parent.h"

void main_parent(int fdRead, int fdWrite, short range, short timeout) {
    short guess;
    short response;

    // calculates value to display
    short displayRange = range - 1;
    while ((1)) {
        printf("Enter a number between 0-%hi (you have %hi seconds to make a "
               "guess): ",
               displayRange, timeout);
        // reads guess from user
        fscanf(stdin, "%hi", &guess);

        // write to child process
        write(fdWrite, &guess, sizeof(guess));

        // read from child process
        read(fdRead, &response, sizeof(response));

        // checks the response
        if (processResponse(response)) {
            // if process response returns 1,
            // user won, break out of loop
            // so that main can close read and write
            break;
        }
    }
}

// Verifies what the response tell us about our previous guess
int processResponse(short result) {
    // 0 means got it right
    if (result == 0) {
        fprintf(stderr, "You got the right number\n");
        return 1;
    } else if (result > 0) { // greater than 0 mean too high
        fprintf(stderr, "You guessed too high\n");
    } else { // less than zero means too low
        fprintf(stderr, "You guessed too low\n");
    }
    return 0;
}

// Handler to test and process the signal coming from child
void mySignalHandler(int signum) {

    if (signum == SIGUSR2) {
        fprintf(stderr, "\nAre you still there? Time is running out!\n");
    }
}

void endProgramHandler(int signum) {
    if (signum == SIGUSR1) {
        fprintf(stderr, "Sorry you ran out of time\n");
        exit(1);
    }

}