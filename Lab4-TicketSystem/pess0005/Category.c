#include <stdio.h>
#include <stdlib.h>
#include "Category.h"
#include "time.h"


//Creates all 5 categories setting name, code, and list size equal 0.
void initializeCategories(Category *categoriesArray) {

    categoriesArray[0].name = "Academic Registrar";
    categoriesArray[0].code = "AR";

    categoriesArray[1].name = "Financial Services";
    categoriesArray[1].code = "FS";

    categoriesArray[2].name = "IT Support";
    categoriesArray[2].code = "IT";

    categoriesArray[3].name = "Parking Police";
    categoriesArray[3].code = "PP";

    categoriesArray[4].name = "Coop Placement";
    categoriesArray[4].code = "CP";

    for (int i = 0; i < 5; i++) {
        categoriesArray[i].listSize = 0;
    }
}

//Shuffle the categoriesArray to easily pick random ones after
//Will use the first n categories from the shuffle list.
void randomizeCategories(Category *categoriesArray, int size, int nCategoriesToUse) {

    //rand has always different values
    srand(time(0));

    // randomizing by swap
    for (int i = 0; i < size; i++) {
        int newPos = rand() % 5;
        Category temp = categoriesArray[newPos];
        categoriesArray[newPos] = categoriesArray[i];
        categoriesArray[i] = temp;
    }

    // For each of the n categories we want to use, initialize ticketArray.
    //saves memory by only initializing what we need.
    for (int i = 0; i < nCategoriesToUse; i++) {
        categoriesArray[i].ticketArray = malloc(sizeof(Ticket));
    }
}

//Prints all the categories chosen and the tickets available
//If it is the first call, we print the initial text.
void printSelectedCategories(Category *categoriesArray, int nCategoriesToUse, int initial) {

    printf("\n");

    //if first distribution, print initial message.
    if (initial == 1) {
        printf("Initial ticket distribution\n");
    }

    //prints each specific category
    for (int i = 0; i < nCategoriesToUse; i++) {
        printCategory(categoriesArray[i]);
    }

    printf("\n");
}

//Prints one category information
void printCategory(Category category) {

    printf("%s:\n", category.name);

    //variable used as a boolean. Initialized as true.
    int empty = 1;

    int isFirst = 1;

    //pass by the ticketArray printing if the ID is valid.
    //ID is update to be -1 in removeTickets to indicate it has been removed
    for (int i = 0; i < category.listSize; i++) {

        //if the ticket has not been removed print it.
        if (category.ticketArray[i].ID != -1) {
            if (isFirst) {
                isFirst = 0;
            } else {
                printf(",");
            };

            printTicket(category.ticketArray[i], category.code);

            //if not the last ticket add a comma.
            empty = 0;
        }
    }

    //if all tickets have ID = -1, print the "no ticket message"
    if (empty) {
        printf("- no tickets –");
    }

    printf("\n");
}

//Allocates memory for all 5 categories.
Category *createCategoryList(int nTotalCategories) {

    return malloc(nTotalCategories * sizeof(Category));
}

//Free the ticket list for the used categories and free the categoriesArray.
void freeAllMemory(Category *categoriesArray, int nCategoriesToUse) {

    for (int i = 0; i < nCategoriesToUse; i++) {
        free(categoriesArray[i].ticketArray);
    }

    free(categoriesArray);
}
