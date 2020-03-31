#include <stdio.h>
#include "format.h"


void printCard(int rank, int suit ){

    char *suit_[] = {"D", "H", "S", "C"};
    char *rank_[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10" ,"J", "Q", "K"};

    printf("%s%s ", rank_[rank], suit_[suit] );

    return;
}
