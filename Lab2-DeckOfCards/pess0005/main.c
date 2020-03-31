#include <stdio.h>
#include "deck.h"
#include "inputoutput.h"
#include "format.h"

/* PROGRAM: A simple card game.
   AUTHORS: Andressa Machado [040923007]
   DATE: 28.January.2019
   PURPOSE: A program to create a deck of cards, shuffle it and deal cards to players.
   LEVEL OF DIFFICULTY: 5
   CHALLENGES: use of pointers, work with files and 2D array.
   HOURS SPENT: 10 hours
*/

int main(void) {

    deck();
    shuffle();
    int *inputs =  input();
    printCards(inputs);
    printRemainder(inputs);

    return 0;
}