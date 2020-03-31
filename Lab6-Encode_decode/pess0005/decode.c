#include <stdio.h>
#include <stdlib.h>
#include "base64_tables.h"

/* PROGRAM: Base 64 converter
   AUTHORS: Andressa Machado [040923007]
   DATE: 01.April.2019
   PURPOSE: A program that converts a base 64 into ASCII encoding.
   LEVEL OF DIFFICULTY: 2
   CHALLENGES: Dealing with bytes array in conversion.
   HOURS SPENT: 1 hours
*/

int main(int argc, char *argv[]) {
  // variables of program
  FILE *fileIn = stdin;
  // File out pointer
  FILE *fileOut;

  // variable to hold char read from input
  int a = 0;
  // array of 0s and 1s representing input
  int *bits;

  // if 2nd argument is passed, try open it as file wirh write binary
  if (argc == 2) {
    fileOut = fopen(argv[1], "wb");
  }
  // variable to control number characters bytes read
  int bytesCount = 1;

  initializeLookupTables();
  if (fileIn != NULL) {
    // initialize bits array size 6 (for 6 "bits" of 0s and 1s ints)
    bits = malloc(6 * sizeof(int));
    int index = 0;
    do {
      // read one character
      a = fgetc(fileIn);

      if (a != EOF && a != '=') {
        // H -> 72 ascii - > 01001000 -> [010010]00 -> 18 -> s
        // Transform ASCII int value TO array of bits
        // Given the current char, find get its int value from base64 table
        int n = lookupInt(a);

        // Converts the int to an array of 0 and 1s
        // it goes from higher bit to lower bit
        // starts at 128, does bit AND (&) with n to see if higher bit match
        // Then divide by 2 (to 64) and so on
        unsigned i;
        for (i = 1 << 5; i > 0; i = i / 2, index++) {
          if (n & i) {
            bits[index] = 1;
          } else {
            bits[index] = 0;
          };
        }

        // Grow the bits array by another 6 size
        bytesCount++;

        int *temp = (int *)realloc(bits, (6 * (bytesCount) * sizeof(int)));
        bits = temp;
      }
    } while (a != EOF);
  } else {
    printf("The file '%s' could not be open\n", argv[1]);
    exit(-1);
  }

  // Since the bytesCount grow before reading the next, it always add one extra,
  // so have to remove after loop ends
  bytesCount--;

  // reading blocks in groups of 8 (increment on i)
  for (int i = 0; i < 6 * bytesCount; i += 8) {
    int sextetbytesCounter = 0;
    int value = 0;
    // convert bits to int value by only looking at 6 bits at a time
    // the i in bits[i +sextet] is to move the position (offset) for each byte
    // read
    for (; sextetbytesCounter < 8; sextetbytesCounter++) {
      value = value * 2 + bits[i + sextetbytesCounter];
    }

    // Write to file if 2nd argument was passed
    if (argc == 2) {
      fprintf(fileOut, "%c", value);
    } else {
      // print to stdout
      printf("%c", value);
    }
  }

  // finalize program by freeing array and closing file
  free(bits);
  if (argc == 2) {
    fclose(fileIn);
  }
  return 0;
  printf("\n");
}
