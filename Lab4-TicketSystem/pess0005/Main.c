#include "Ticket.h"
#include "Category.h"
#include "TicketManager.h"
#include "Input.h"
#include <stdio.h>
#include <stdlib.h>

/* PROGRAM: Ticket System
   AUTHORS: Andressa Machado [040923007] & Kruti Parmar [040914603]
   DATE: 18.February.2019
   PURPOSE: A program to simulate a ticketing system.
   LEVEL OF DIFFICULTY: 9
   CHALLENGES: dealing with structs in arrays.
   HOURS SPENT: 10 hours
*/

int main() {

    int nTotalCategories = 5;
    int nCategoriesToUse = getInput("Enter the number of categories to use: ", 1, 5);
    int nNumTickets = getInput("Enter the number of tickets to generate: ", 0, 1000);

    Category *categoriesArray = createCategoryList(nTotalCategories);

    initializeCategories(categoriesArray);
    randomizeCategories(categoriesArray, nTotalCategories, nCategoriesToUse);

    distributeTickets(categoriesArray, nNumTickets, nCategoriesToUse);
    printSelectedCategories(categoriesArray, nCategoriesToUse, 1);

    removeTickets(categoriesArray, nNumTickets, nCategoriesToUse);

    freeAllMemory(categoriesArray, nCategoriesToUse);

    return 0;
}











