#include <stdio.h>
#include "inputoutput.h"
#include "format.h"
#include "deck.h"


int * input(){

    //An array[2] that holds the number of players in the index [0] and the number of cards per player in the index [1]
    static int inputFromUser[2];
    //Variable to work as a boolean to validate the input.
    // True
    int valid = 1;

    //Using a do-while loop so the user just goes out the loop once enter a valid number (valid == 1)
    do{
        printf("Enter the number of players: ");
        //Setting the number of players to the first index.
        scanf("%d", &inputFromUser[0]);

        //invalid entry, set valid to 0 (false)
        if(inputFromUser[0] < 1){
            printf("Number of players must be more than zero. Try again.\n");
            valid = 0;
        } else if(inputFromUser[0] > 52){
            printf("You cannot enter a number of players greater than the number of cards. Try again. \n");
            valid = 0;
        } else if(!inputFromUser[0]){
            printf("You must enter a number. Try again. \n");
            valid = 0;
        } else if(inputFromUser[0] >= 1 && inputFromUser[0] <= 52){
            printf("You have entered %d players.\n", inputFromUser[0]);
            valid = 1;
        }

    }while (valid == 0);

    printf("\n");

    //do-while loop to check if the user entered a valid number of cards.
    do{
        printf("Enter the number of cards per player: ");
        scanf("%d", &inputFromUser[1]);

        //invalid entry, set valid to 0 (false)
        if(inputFromUser[1] < 1) {
            printf("Number of cards must be more than zero. Try again.\n");
            valid = 0;
        } else if(inputFromUser[1] > 52){
            printf("Number of cards in a Deck is 52. Cannot be greater than this. Try again.\n");
            valid=0;
        } else if((inputFromUser[1])*(inputFromUser[0]) > 52) {
            printf("That number of cards cannot be divided by the number of players you have entered. Try again.\n");
            valid=0;
        } else if (inputFromUser[1] > 1 && inputFromUser[1] < 52 && inputFromUser[1]* inputFromUser[0] < 52){
            printf("You have entered %d cards per player.\n", *(inputFromUser + 1));
            valid = 1;
        }

    }while (valid == 0);

    return inputFromUser;
}


    void printCards(int inputFromUser[]) {

        printf("\n");

        //dealing the cards according to the number of players and cards per player
        //inputFromUser[0] holds the number of players.
        for(int j = 0; j < inputFromUser[0]; j++){
            printf("Hand #%d is:\n", j+1);
            //inputFromUser[1] holds the number of cards per player
            for (int i = j*inputFromUser[1]; i < (j+1) * inputFromUser[1]; i++) {
                printCard(Deck[i][0], Deck[i][1]);
            }
            printf("\n");
        }

    }

    void printRemainder( int inputFromUser[]){

        printf("Remainder of deck: \n");

        //printing the remaining cards. Control variable was set to the number of players * number of cards per player and
        //the loop start to print from that result.
        for(int i = inputFromUser[0] * inputFromUser[1]; i < 52; i++){
            printCard(Deck[i][0], Deck[i][1]);
        }
}


