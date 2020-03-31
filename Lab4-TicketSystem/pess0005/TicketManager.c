#include <stdio.h>
#include <stdlib.h>
#include "TicketManager.h"
#include "time.h"

//Allocates one extra space in ticketArray list, add new ticket, increase list size.
void addTicketToList(Category *category, Ticket ticket) {

    int listSize = (*category).listSize;
    (*category).ticketArray = realloc((*category).ticketArray, (listSize + 1) * sizeof(Ticket));
    (*category).ticketArray[listSize] = ticket;
    (*category).listSize++;
}

//Chose a category at random and assign the ticket to it
void distributeTickets(Category *categoriesArray, int nNumTickets, int nCategoriesToUse) {

    srand(time(0));

    //loop to assign tickets
    for (int i = 0; i < nNumTickets; i++) {

        // From the X number of categories chosen (Eg 3.)
        // pick from the first X elements of the randomized array
        Ticket t = {i + 1, 0};

        int currentCategory = rand() % nCategoriesToUse;
        addTicketToList(&(categoriesArray[currentCategory]), t);
    }
}

//creates a random list of ints to be the order of removed tickets
void randomizeList(int *ticketsToRemove, int size) {

    srand(time(0));

    for (int i = 0; i < size; i++) {
        ticketsToRemove[i] = i;
    }

    // randomizing by swap
    for (int i = 0; i < size; i++) {
        int newPos = rand() % size;
        int temp = ticketsToRemove[newPos];
        ticketsToRemove[newPos] = ticketsToRemove[i];
        ticketsToRemove[i] = temp;
    }
}

//for each int in ticketsToRemove find the relative ticket in the categories tickets Arrays.
void removeTickets(Category *categoriesArray, int nNumTickets, int nCategoriesToUse) {

    int *ticketsToRemove = malloc(nNumTickets * sizeof(int));
    randomizeList(ticketsToRemove, nNumTickets);

    // Considers all tickets to be a in a sequencial list
    // The upper bound is the acculation of each category ticket list size
    // The lower bound is the size of previous category list size
    for (int i = 0; i < nNumTickets; i++) {
        int ticketToRemove = ticketsToRemove[i];
        int upperBound = 0;
        int lowerBound = 0;

        for (int i = 0; i < nCategoriesToUse; i++) {
            Category *current = &categoriesArray[i];
            upperBound += (*current).listSize;

            // Checks to see if the toRemove is within bounds of current category
            if (ticketToRemove < upperBound) {
                printf("Removed ticket ");

                // If it is, select it using the lowerBound offset print and remove
                printTicket((*current).ticketArray[ticketToRemove - lowerBound], (*current).code);

                //set ID to -1 to indicate it is removed.
                (*current).ticketArray[ticketToRemove - lowerBound].ID = -1;
                printSelectedCategories(categoriesArray, nCategoriesToUse, 0);

                break;
            } else {
                lowerBound = upperBound;
            }
        }
    }
}
