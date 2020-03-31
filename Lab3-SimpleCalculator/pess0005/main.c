#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* PROGRAM: Simple calculator
   AUTHORs:   AUTHORS: Andressa Machado [040923007]
   DATE:   03.Feb.2019
   PURPOSE: Takes 2 operands to be used in an operation chosen by the user.
   LEVEL OF DIFFICULTY: 8
   CHALLENGES: Cleaning the input buffer.
   HOURS SPENT: 8 hours
*/

// functions to be called and to perform the operations
float subtract(float firstOperator, float secondOperator) {
    return firstOperator - secondOperator;
}

float add(float firstOperator, float secondOperator) {
    return firstOperator + secondOperator;
}

float divide(float firstOperator, float secondOperator) {
    return firstOperator / secondOperator;
}

float multiply(float firstOperator, float secondOperator) {
    return firstOperator * secondOperator;
}

// structure of a group af variables representing the operations that will be used.
struct Hotkey {
    char *name;
    int symbol;
    float (*pFunction)(float a, float b);
};

//array of Hotkey structure to allow the access to the appropriate operation.
struct Hotkey Hotkeys[] = {
        {"Divide",   '/', &divide},
        {"Multiply", '*', &multiply},
        {"Add",     '+', &add},
        {"Subtract", '-', &subtract},
};

//function used to generate an array with random order numbers to be used to display a different order of options every time.
int *getRandomArray() {
    int random;
    srand(time(0));

    //number of options available.
    static int randomOrder[] = {0, 1, 2, 3};

    //reordering the array with the values at different positions.
    for (int i = 0; i < 4; i++) {
        random = rand() % 4;
        int temp = randomOrder[random];
        randomOrder[random] = randomOrder[i];
        randomOrder[i] = temp;
    }
    return randomOrder;
}

//function to print the menu of hotkeys.
void printingHotkeys(int *randomOrder) {
    printf("\nHotkeys: ");

    for (int i = 0; i < 4; i++) {
        //getting the hotkeys from the struct Hotkeys array.
        struct Hotkey *pHotkey = &Hotkeys[randomOrder[i]];
        printf("\n%d or %c: %s", i, pHotkey->symbol, pHotkey->name);
    }
}

//Reading the operands and validating for correctness.
float readOperand(char *str) {
    float operand;
    //variable to be used as a boolean in the validation.
    int isValid = 1;
    //used to allow us to compare the relation between char and int in the ASCII table.
    char c;

    do {
        isValid = 1;
        //str is a array of chars that is been used to write the correct sentence. (Enter first operand: ) or (Enter second operand:)
        printf(str);
        //read an int.
        scanf("%c", &c);

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            isValid = 0;
            printf("You must enter a float point number. Try again.");
        }

        //normalizing the user entry based in the ASCII table
        operand = c - '0';

        //Used to clean the input buffer of the next line character.
        //Reference: https://stackoverflow.com/questions/26192830/what-does-this-do-whilec-getchar-n-c-eof
        while ((c = getchar()) != EOF && c != '\n');
        //while the input is not valid, do the loop again.
    } while (isValid == 0);

    return operand;
}

//Reading the hotkey and validating for correctness.
char readInputHotkey() {
    char inputHotkey;
    int isValid;

    do {
        isValid = 1;
        char c;

        printf("\nEnter Hotkey: ");
        scanf("%c", &c);

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            isValid = 0;
        }

        if (!(c == '/' || c == '*' || c == '+' || c == '-') && !(c == '0' || c == '1' || c == '2' || c == '3')) {
            isValid = 0;
        }

        if(isValid == 0) {
            printf("You must enter a number between 0 and 3. Try again.");
        }

        inputHotkey = c;

        //Used to clean the input buffer of the next line character.
        //Reference: https://stackoverflow.com/questions/26192830/what-does-this-do-whilec-getchar-n-c-eof
        while ((c = getchar()) != EOF && c != '\n');
        //while the input is not valid, do the loop again.
    } while (isValid == 0);

    return inputHotkey;
}

//function to print results.
void printResult(char inputHotkey, int *randomOrder, float firstOperand, float secondOperand) {

    //if the input option was chosen as a number
    if (inputHotkey >= 48 && inputHotkey <= 52) {
        printf("\nResult is: %f ", Hotkeys[randomOrder[inputHotkey - 48]].pFunction(firstOperand, secondOperand));
    }

    //if the input was chosen as a symbol
    if (inputHotkey == '+' || inputHotkey == '-' || inputHotkey == '*' || inputHotkey == '/') {
        for (int j = 0; j < 4; ++j) {
            if (Hotkeys[j].symbol == inputHotkey) {
                printf("\nResult is: %.3f ", Hotkeys[j].pFunction(firstOperand, secondOperand));
                break;
            }
        }
    }
}

int main() {
    float firstOperand = readOperand("Enter first operand: ");
    float secondOperand = readOperand("Enter second operand: ");
    int *randomOrder = getRandomArray();
    printingHotkeys(randomOrder);
    char inputHotkey = readInputHotkey();
    printResult(inputHotkey, randomOrder, firstOperand, secondOperand);
}
