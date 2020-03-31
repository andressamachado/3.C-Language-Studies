#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "base64_tables.h"

/* PROGRAM: Base 64 converter
   AUTHORS: Andressa Machado [040923007]
   DATE: 01.April.2019
   PURPOSE: A program that converts a ASCII file into base 64 encoding.
   LEVEL OF DIFFICULTY: 6
   CHALLENGES: Dealing with bytes array in conversion.
   HOURS SPENT: 5 hours
*/

int main(int argc, char *argv[]) {
    // variables of program
    // File pointer
    FILE *fileIn;
    // variable to hold char read from input
    int a = 0;
    // array of 0s and 1s representing input
    int *bits;

    // Set filein to stdin if no file name passed as argument
    if (argc == 1) {
        fileIn = stdin;
    }

    // if 2nd argument is passed, try open it as file wirh read binary
    if (argc == 2) {
        fileIn = fopen(argv[1], "rb");
    }

    // variable to control number characters bytes read
    int bytesCount = 1;

    initializeLookupTables();

    // if tried to open file, but it is null, error and exit
    if (fileIn != NULL) {
        // initialize bits array size 8 (for 8 "bits" of 0s and 1s ints)
        bits = malloc(8 * sizeof(int));
        int index = 0;
        do {
            // read one character at a time
            a = fgetc(fileIn);

            if (a != EOF) {
                // Transform ASCII int value TO array of bits
                int n = a;
                // Converts an int to an array of 0 and 1s
                // it goes from higher bit to lower bit
                // starts at 128, does bit AND (&) with n to see if higher bit match
                // Then divide by 2 (to 64) and so on
                unsigned i;
                for (i = 1<< 7; i > 0; i = i / 2, index++) {
                    if (n & i) {
                        bits[index] = 1;
                    } else {
                        bits[index] = 0;
                    };
                }

                // Grow the bits array by another 8 size
                bytesCount++;
                int *temp = (int *)realloc(bits, (8 * (bytesCount) * sizeof(int)));
                bits = temp;
            }
        } while (a != EOF);

        // Since the bytesCount grow before reading, it always add one extra,
        // so have to remove after loop ends
        bytesCount--;

        // calculates padding needed
        int remain = bytesCount % 3;
        int padding = 0;
        if (remain != 0) {
            padding = 3 - remain;
        }

        // reading blocks in groups of 6 (increment on i)
        for (int i = 0; i < 8 * bytesCount; i += 6) {
            int sextetbytesCounter = 0;
            int value = 0;
            // convert bits to int value by only looking at 6 bits at a time
            // the i in bits[i +sextet] is to move the position (offset) for each byte
            // read
            for (; sextetbytesCounter < 6; sextetbytesCounter++) {
                value = value * 2 + bits[i+sextetbytesCounter];
            }
           
            printf("%c", lookupChar(value));
        }

        // print extra padding
        for (int i = 0; i < padding; i++) {
            printf("=");
        }

        // finalize program by freeing array and closing file
        printf("\n");
        free(bits);
        if (argc == 2) {
            fclose(fileIn);
        }
        return 0;
    } else {
        printf("The file '%s' could not be read\n", argv[1]);
        exit(-1);
    }
}
