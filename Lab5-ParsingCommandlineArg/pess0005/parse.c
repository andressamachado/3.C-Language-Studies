#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include "types.h"
#include "sort.h"
#include "rental.h"

/* PROGRAM: Command line parser.
   AUTHORS: Andressa Machado [040923007]
   DATE: 18.March.2019
   PURPOSE: A program to receive, parse, and treat command line arguments.
   LEVEL OF DIFFICULTY: 6
   CHALLENGES: reducing to a single switch statement. Dealing with the control flow of the arguments.
   HOURS SPENT: 5 hours
*/

void parseGNUCommand(char **gnu);

char getGNUFirstChar(char *gnu);

char *getGNUParam(char *argEntry);

char *getParam(char *argEntry, char separator);

void parseNumericParam(int *dest, char *argEntry, char *strCommand, char separator);

void setReverse(bool *pbReverse, SORT_METHOD *peSortMethod, bool hasReverse);

void parseSort(SORT_METHOD *peSortMethod, char *argEntry, char *strCommand, char separator);

/************************************************
 * Note, this function always exits the program!
 ************************************************/
void printHelpAndExit(char *strCommand, int exitCode) {
    if (exitCode == EXIT_SUCCESS)
        printf("\n%s - print some rental properties with user-selectable formatting options.\n", strCommand);

    // Added arguments to message
    printf("\nUsage: %s -s <SORT> [-l <NUM>] [-m <NUM>] [-M <number] [-r]\n\n", strCommand);
    printf("Arguments:\n\n");
    printf("    -r, --reverse\t\tPrint the results in reverse order\n");
    // Added option and explanation of usage
    printf("    -m <NUM>, --min=<NUM>\tOnly show values that are greater than or equal to the NUM\n");
    printf("\t\t\t\t\tIf sort is set to byAddress, this argument");
    printf("\n\t\t\t\t\tshould not be used\n");
    printf("    -M <NUM>, --max=<NUM>\tOnly show values that are lesser than or equal to the NUM\n");
    printf("\t\t\t\t\tIf sort is set to byAddress, this argument");
    printf("\n\t\t\t\t\tshould not be used\n");
    printf("    -s <SORT>, --sort=<SORT>\tMandatory: Use one of the following SORT methods:\n");
    printf("\t\t\t\t\tbyRooms - sort by the number of rooms\n");
    printf("\t\t\t\t\tbyAddress - sort by address\n");
    printf("\t\t\t\t\tbyRent - sort by address\n");
    printf("    -l <NUM>, --limit=<NUM>\tDisplay a limit of NUM rental properties\n");
    printf("    -h, --help\t\t\tPrint this message\n");

    exit(exitCode);
}

bool parseArguments(int argc, char *argv[], bool *pbReverse, SORT_METHOD *peSortMethod, int *pnNumResults, int *pnMin,
                    int *pnMax) {
    // Does the program name start with a local path specifier?
    char *strCommand = argv[0];

    if (strncmp("./", strCommand, 2) == 0)
        strCommand += 2;

    // To control mandatory argument
    bool hasSorting = false;
    bool hasReverse = false;
    // To control sorting + min/max interaction
    bool hasMin = false;
    bool hasMax = false;

    printf("\n");

    // Defaults
    *pnMin = 0;
    *pnMax = INT_MAX;
    *pnNumResults = INT_MAX;

    for (int i = 1; i < argc; i++) {
        char *argEntry = argv[i];
        // Checks the "-"
        // Will be used in the switch statement
        char option;
        // Holds the GNU argument
        char *gnu;
        // "g" or "p" for GNU typo or POSIX type arg
        char typeOfParam = 'x';
        // Char that separates a command from its parameter
        // GNU "=", POSIX " "
        char separator;

        // If the first char in the arg is a "-", set POSIX related variables
        if (argEntry[0] == '-') {
            option = argEntry[1];
            typeOfParam = 'p';
            separator = ' ';
            // If second char is also "-", overwrites variables with GNU values
            if (argEntry[1] == '-') {
                // Allocates memory to GNU in the same size of argEntry
                // i.e. argEntry = --sort=byRooms
                gnu = malloc(sizeof(argEntry));
                // Copy value
                strcpy(gnu, argEntry);
                // Walks pointer to remove "--". Just command and value left.
                // i.e. GNU = sort=byRooms
                gnu = gnu + 2;
                typeOfParam = 'g';
                separator = '=';
            }
        } else {
            // If first char is not "-" error out
            printf("Missing '-' character before '%s'\n", argEntry);
            printHelpAndExit(strCommand, EXIT_FAILURE);
        }

        // If the param type is "p" (POSIX), test for chars after argument.
        if (typeOfParam == 'p') {
            // After argument, require space. If does not have space, or end of string (in case of the argument does not have a parameter. i.e. "-r"), error.
            if (argEntry[2] != '\0' && argEntry[2] != ' ') {
                // Error
                printf("\n\nUnexpected character: '%c' at param -%c\n", argEntry[2],
                       option);
                printHelpAndExit(strCommand, EXIT_FAILURE);
            }
        }

        // If the parameter type is GNU, get the first char of the GNU command (i.e. "sort=byRooms" returns "s")
        if (typeOfParam == 'g') {
            option = getGNUFirstChar(gnu);
        }

        // For each option, parse the command argument and parameter
        switch (option) {
            case 'r': {
                hasReverse = true;
                break;
            }
            case 's': {
                hasSorting = true;
                parseSort(peSortMethod, argEntry, strCommand, separator);
                break;
            }
            case 'm': {
                hasMin = true;
                parseNumericParam(pnMin, argEntry, strCommand, separator);
                break;
            }
            case 'M': {
                hasMax = true;
                parseNumericParam(pnMax, argEntry, strCommand, separator);
                break;
            }
            case 'l': {
                parseNumericParam(pnNumResults, argEntry, strCommand, separator);
                break;
            }
            default:
                printf("Argument -%c invalid\n", option);
                printHelpAndExit(strCommand, EXIT_FAILURE);
                break;
        }
    }

    // Has sorting?
    if (!hasSorting) {
        printf("Mandatory argument -s or --sort is missing.\n");
        printHelpAndExit(strCommand, EXIT_FAILURE);
    }

    if (*peSortMethod == sortByAddress) {
        if (hasMin || hasMax) {
            printf("Sorting by address and setting min and/or max value is invalid.\n");
            printHelpAndExit(strCommand, EXIT_FAILURE);
        }
    }

    // Dealing with reverse ordering
    setReverse(pbReverse, peSortMethod, hasReverse);
    return true;
}

void parseNumericParam(int *dest, char *argEntry, char *strCommand, char separator) {
    char *paramText = getParam(argEntry, separator);
    char *error;
    // Converts o paramText into int using srtol
    *dest = (int) strtol(paramText, &error, 10);
    // If there were an error in conversion, error and exit
    if (*error != '\0') {
        printf("Argument value '%s' invalid. Integer expected.\n", paramText);
        printHelpAndExit(strCommand, EXIT_FAILURE);
    }
}

void parseSort(SORT_METHOD *peSortMethod, char *argEntry, char *strCommand, char separator) {
    // Get parameter from argEntry
    char *sortArg = getParam(argEntry, separator);

    // Compares and sets pointer to correct sorting
    if (strcmp(sortArg, "byRent") == 0) {
        *peSortMethod = sortByRent;
        return;
    }
    if (strcmp(sortArg, "byRooms") == 0) {
        *peSortMethod = sortByRooms;
        return;
    }
    if (strcmp(sortArg, "byAddress") == 0) {
        *peSortMethod = sortByAddress;
        return;
    }

    //If not found, error and exit
    printf("Sorting method '%s' invalid\n", sortArg);
    printHelpAndExit(strCommand, EXIT_FAILURE);
}

void parseGNUCommand(char **gnu) {
    // Search for the separator in GNU, returns from that position until the end
    char *ch = strchr(*gnu, '=');
    // Get position of "="
    int pos = ch - *gnu;
    // Make the string end at the position of "="
    // If entry : "max=12" result is "max"
    (*gnu)[pos] = '\0';
}

// Compares the GNU string with command names, return the correct letter
char getGNUFirstChar(char *gnu) {
    parseGNUCommand(&gnu);
    if (strcmp(gnu, "reverse") == 0) {
        return 'r';
    }
    if (strcmp(gnu, "min") == 0) {
        return 'm';
    }
    if (strcmp(gnu, "max") == 0) {
        return 'M';
    }
    if (strcmp(gnu, "limit") == 0) {
        return 'l';
    }
    if (strcmp(gnu, "sort") == 0) {
        return 's';
    }

    // Return an unsupported letter
    return 'x';
}

//char *getGNUParam(char *argEntry) {
//  char *ch = strchr(argEntry, '=');
//  int pos = ch - argEntry;
//  char *param = malloc(sizeof(argEntry));
//  strcpy(param, argEntry);
//  param = param + pos + 1;
//  return param;
//}

// Given an arg string, and a separator, return the parameter string. (i.e. "--min=15" return "15".)
char *getParam(char *argEntry, char separator) {
    // Search for the separator in argEntry, returns from that position until end
    // i.e. "=15"
    char *ch = strchr(argEntry, separator);
    // Calculates position of separator in argEntry
    int pos = ch - argEntry;
    // Creates a parameter string and copy argEntry to it
    char *param = malloc(sizeof(argEntry));
    strcpy(param, argEntry);
    // Uses walking the pointer forward to get the substring result ( i.e. "15")
    param = param + pos + 1;
    return param;
}

void setReverse(bool *pbReverse, SORT_METHOD *peSortMethod, bool hasReverse) {
    if (((*peSortMethod == sortByAddress) || (*peSortMethod == sortByRent))) {
        *pbReverse = false;
        if (hasReverse) {
            *pbReverse = true;
        }
    }

    if (*peSortMethod == sortByRooms) {
        *pbReverse = true;
        if (hasReverse) {
            *pbReverse = false;
        }
    }
}
