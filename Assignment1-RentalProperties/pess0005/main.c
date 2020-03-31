#include "sort.h"
#include <time.h>
#include <string.h>

/* PROGRAM: Rental matching
   AUTHORS: Andressa Machado [040923007] & Harsh Patel [040919280]
   DATE: 11.March.2019
   PURPOSE: A program to simulate a matching app for rental properties.
   LEVEL OF DIFFICULTY: 9
   CHALLENGES: comparator function for sorting. Double pointers.
   HOURS SPENT: 15 hours
*/


void printHelpMenu();
void printTableHeader();
void all(ListNode **pHead, char *currentListName, int currentNodeIndex,
         int (*pComparator)(PropertyNode *a, PropertyNode *b));
void propertyToDecide(ListNode *pHead, int currentNodeIndex);
char getInputOption(char* userChoice);

int main() {
    srand(time(NULL));

    // Create empty list
    ListNode *undecided = createList();
    ListNode *favorites = createList();

    // initialize undecided with 6 random items
    initializeList(&undecided);


    // Control variables
    ListNode *currentList = undecided;
    char *currentListName = "Undecided";

    // pComparator pointer to function comes from sort.h
    pComparator = rentCompare;
    int currentNodeIndex = 0;
    char userChoice[8];

    // First display of Message and table menus
    all(&currentList, currentListName, currentNodeIndex, pComparator);

    do {
        //Read user input
        printf("Command ('h' for help): ");
        scanf("%8s", userChoice);
        printf("\n");

        // to use switch statement. Get the first char of the input
        char parsedInput = getInputOption(userChoice);

        switch (parsedInput) {
            case 'h':
                //will display the help menu
                printHelpMenu();
                break;
            case 'a':
                if (isListEmpty(currentList)) {
                    printf("There are no more rental properties\n");
                } else {
                    // when choosing ALL, reset currentNodeIndex and display
                    currentNodeIndex = 0;
                    // Call ALL function
                    all(&currentList, currentListName, currentNodeIndex, pComparator);
                };
                break;
            case 'f':
                // Set current list to favorites, do an all
                currentList = favorites;
                all(&currentList, currentListName, currentNodeIndex, pComparator);
                break;
            case 'u':
                // set current list to undecided, call the random add (50% change), do an all
                currentList = undecided;
                randomAddToList(&currentList);
                all(&currentList, currentListName, currentNodeIndex, pComparator);
                break;
            case 'l':
                // Prints message, removes item , shows next item
                printf("Rental property deleted\n");
                removeNodeAtIndex(&currentList, currentNodeIndex);
                propertyToDecide(currentList, currentNodeIndex);
                break;
            case 'r':
                // Prints correct message, if on favorites dont do anything
                // if on undecided move node from undecided to favorite
                // ask about next property in the list
                if (currentList == favorites) {
                    printf("This rental property is already on your favourites list\n\n");
                } else {
                    printf("Rental property moved to your favourites list\n");
                    moveNodeToList(&currentList, &favorites, currentNodeIndex);
                    propertyToDecide(currentList, currentNodeIndex);
                };
                break;
            case 'n':
                // Goes to next item and ask about next property in the list
                currentNodeIndex++;
                propertyToDecide(currentList, currentNodeIndex);
                break;
            case 's':
                printf("");
                // Since we are in sorting now, lets get the second char
                char sortingType = userChoice[1];
                int choiceValid = 1;

                // USes switch to set correct comparator
                switch (sortingType) {
                    case 'a':
                        pComparator = addressCompare;
                        break;
                    case 'n':
                        pComparator = numberOfRoomsCompare;
                        break;
                    case 'r':
                        pComparator = rentCompare;
                        break;
                    case 'd':
                        pComparator = distanceCompare;
                        break;
                    default:
                        // if no choice was valid, print help
                        choiceValid = 0;
                        printf("That is not a supported command");
                        printHelpMenu();
                        break;
                }

                if (choiceValid) {
                    currentNodeIndex = 0;
                    // redisplays list
                    all(&currentList, currentListName, currentNodeIndex, pComparator);
                }

                break;
            case 'q':
                break;

            default:
                printf("That is not a supported command\n\n");
                printHelpMenu();
                break;
        }
    } while (userChoice[0] != 'q');
}

void printHelpMenu() {
    printf("Valid commands are:\n");
    printf("\t%s", "h - display this help\n");
    printf("\t%s", "a - display all the rental\n");
    printf("\t%s", "f - switch to the favourites list\n");
    printf("\t%s", "u - switch to the undecided list\n");
    printf("\t%s", "l - 'swipe left' on the current rental property\n");
    printf("\t%s", "r - 'swipe right' on the current rental property\n");
    printf("\t%s", "n - skip to the next rental property\n");
    printf("\t%s", "sa - set the sorting to 'by address'\n");
    printf("\t%s", "sn - set the sorting to 'by number of rooms'\n");
    printf("\t%s", "sr - set the sorting to 'by rent'\n");
    printf("\t%s", "sd - set the sorting to 'by distance'\n");
    printf("\t%s", "q - quit the program\n");
    printf("\n");
}

void printTableHeader() {
    printf("%-41s %-9s %-10s %s\n", "Address", "# Rooms", "Rent/Room",
           "Distance");
    printf("%-42s", "-----------------------------");
    printf("%-10s", "-------");
    printf("%-11s", "---------");
    printf("%-10s", "--------");
    printf("\n");
}


// Function that displays a list in table form
// Displays title based on current listName.
// Uses pComparator to sort and then currentNodeIndex to display the correct entry
void all(ListNode **ppHead, char *currentListName, int currentNodeIndex,
         int (*pComparator)(PropertyNode *a, PropertyNode *b)) {

    if (isListEmpty(*ppHead)) {
        printf("There are no more rental properties.\n");
        return;
    }

    bubbleSort(ppHead, pComparator);

    // Print title of list
    printf("%s Rental Properties\n", currentListName);

    // Print table header
    printTableHeader();
    // print items in tabular form
    displayList(*ppHead);
    printf("\n\n");
    // Show property to decide between R/L
    propertyToDecide(*ppHead, currentNodeIndex);
};

// Takes the *pHead ant current node index, and prints that node information
void propertyToDecide(ListNode *pHead, int currentNodeIndex) {
    // Display message and new item to chose
    if (getCount(pHead) <= currentNodeIndex) {
        printf("\nNo more rental properties");
    } else {
        printf("\nWhat do you think about this rental property?\n");
        printf("\t");
        // Prints using the one line (non table) formating
        printFormatted(getNodeAtIndex(pHead, currentNodeIndex)->property);
    }

    printf("\n\n");
}

char getInputOption(char* userChoice) {
    // In case user types more then 1 char AND the 1st is not an 's' (the only case where 2 chars is accepted)
    // force an entry error by setting first char to invalid
    // This prevents program accepting an invalid input that happens to START with a valid one
    // eg: 'love c'
    if(strlen(userChoice) > 1 && userChoice[0] != 's') {
        userChoice[0] = 'x';
    }
    return userChoice[0];
}