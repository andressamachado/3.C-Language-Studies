#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>

#include "parse.h"

void printHelpAndExit(char *strCommand, int exitCode) {
    if (exitCode == EXIT_SUCCESS)
        printf("\n%s - Guessing game options: .\n", strCommand);

    printf("\nUsage: %s [-m <NUM>] [-t <NUM>]\n\n", strCommand);
    printf("Arguments:\n\n");
    printf("    -m <NUM>, --max=<NUM>\tThe max number available for guessing "
           "0-value\n");
    printf("    -t <NUM>, --timeout=<NUM>\tThe amount of time - in seconds - for "
           "each guess\n");
    printf("    -h, --help\t\t\tPrint this message\n");

    exit(exitCode);
}
// Parse the arguments give the number of args, the list of args and the pointers to the values we need to set
void parseArguments(int argc, char *argv[], short *prange, short *ptimeout) {
    char *strCommand = argv[0];
    if (strncmp("./", strCommand, 2) == 0)
        strCommand += 2;

    // For each param
    for (int i = 1; i < argc; i++) {
        // initializes control variables
        char *argEntry = argv[i];
        // checks the "-"
        char option;
        char *gnu;
        char typeOfParam = 'x';
        char separator;


        // Starts testing - and sets the type of param to p and separator to ' '
        if (argEntry[0] == '-') {
            option = argEntry[1];
            typeOfParam = 'p';
            separator = ' ';

            // if second character of param is also -, it is GNU format
            if (argEntry[1] == '-') {
                // two -
                gnu = malloc(sizeof(argEntry));
                strcpy(gnu, argEntry);
                // walks pointer forward to remove --
                gnu = gnu + 2;
                typeOfParam = 'g';

                // updates separator for later process
                separator = '=';
            }
        } else {
            printf("Missing '-' character before '%s'\n", argEntry);
            printHelpAndExit(strCommand, EXIT_FAILURE);
        }

        if (typeOfParam == 'p') {
            // after arg, require space. If not a space = error
            if (argEntry[2] != '\0' && argEntry[2] != ' ') {
                // error
                printf("\n\nUnexpected character: '%c' at param -%c\n", argEntry[2],
                       option);
                printHelpAndExit(strCommand, EXIT_FAILURE);
            }
        }

        // if param is GNU, I need to extract a letter from the argument text to process in a switch
        if (typeOfParam == 'g') {
            option = getGNUFirstChar(gnu);
        }

        // depending on option, perform action
        switch (option) {
            case 'm': { // set the max number
                parseNumericParam(prange, argEntry, strCommand, separator);
                break;
            }
            case 't': { // set the timeout
                parseNumericParam(ptimeout, argEntry, strCommand, separator);
                break;
            }
            case 'h': { // show help
                printHelpAndExit(strCommand, EXIT_FAILURE);
                break;
            }
            default:
                printf("Argument %s invalid\n", argEntry);
                printHelpAndExit(strCommand, EXIT_FAILURE);
                break;
        }
    }
}

// Given a pointer to pinter
void parseGNUCommand(char **gnu) {
    // finds the occurence of '='
    char *ch = strchr(*gnu, '=');
    // Calculates the position on gnu of the character '='
    int pos = ch - *gnu;
    if (ch != NULL) {
        // if the character was found, we put the string terminator to be left with just the "argument"
        (*gnu)[pos] = '\0';
    }
}
// Method receives the whole argument eg: "--max=30", we parse to get just the name and then test
char getGNUFirstChar(char *gnu) {
    // this parses the argument "name" (eg: max)
    parseGNUCommand(&gnu);
    if (strcmp(gnu, "max") == 0) {
        return 'm';
    }
    if (strcmp(gnu, "timeout") == 0) {
        return 't';
    }
    if (strcmp(gnu, "help") == 0) {
        return 'h';
    }

    // return an unsupported letter
    return 'x';
}

// Giver a text representation of a number eg : "30" parses it to an int
void parseNumericParam(short *dest, char *argEntry, char *strCommand,
                       char separator) {
    // this splits an argument eg: "--max=30" into "30"
    char *paramText = getParam(argEntry, separator);
    char *error;
    // parse and test for error
    *dest = (int)strtol(paramText, &error, 10);
    if (*error != '\0') {
        printf("Argument value '%s' invalid. Integer expected.\n", paramText);
        printHelpAndExit(strCommand, EXIT_FAILURE);
    }
}

// this splits an argument eg: "--max=30" into "30" or "-m 30" into "30"
char *getParam(char *argEntry, char separator) {
    // finds separator
    char *ch = strchr(argEntry, separator);
    // finds position of separator in argument
    int pos = ch - argEntry;
    // creates new string
    char *param = malloc(sizeof(argEntry));
    // copies it
    strcpy(param, argEntry);
    // moves start to right after the separator pos
    param = param + pos + 1;
    return param;
}
