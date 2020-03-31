#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "deck.h"


int Deck[52][2];

void deck() {

    for (int i = 0; i < 52; i++) {
        Deck[i][0] = (i % 13);
        Deck[i][1] = i / 13;
    }

    return;
}

void shuffle(){

    int random;
    int temp[2];
    srand(time(0));

    for (int i = 0; i < 52; i++) {
        random = rand()%52;
        temp[0] = Deck[random][0];
        temp[1] = Deck[random][1];
        Deck[random][0] = Deck[i][0];
        Deck[random][1] = Deck[i][1];
        Deck[i][0] = temp[0];
        Deck[i][1] = temp[1];
    }

    return;
}
