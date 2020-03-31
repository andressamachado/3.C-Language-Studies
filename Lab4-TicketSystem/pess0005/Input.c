#include "Input.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//get input from the user and validates type and range of entry.
int getInput(char *message, int min, int max) {

    char *inputString = malloc(5);
    int nChosenNumber;
    int checker = 0;

    printf("%s", message);

    do {
        checker = 0;

        //Read input of max length of 5.
        // 4 chars for the value and the 5th for the end of the string.
        fgets(inputString, 5, stdin);

        //If entry less than five, or greater than five,
        // clear the buffer by reading the rest of the characters until \n
        if (!strchr(inputString, '\n')) {
            while (fgetc(stdin) != '\n') {
            }
        }

        //variable to control the result from strtol.
        char *pError;

        nChosenNumber = (int) strtol(inputString, &pError, 10);

        //if pError equals the input String, means no conversion was done.
        //Hence we have an error
        if (pError == inputString) {
            printf("Please enter valid numbers between %d - %d: ", min, max);
            checker = 1;
        } else {

            //cheeck for range validity
            if (nChosenNumber < min || nChosenNumber > max) {
                printf("Please enter valid numbers between %d - %d: ", min, max);
                checker = 1;
            }
        }
    } while (checker == 1);

    return nChosenNumber;
}
