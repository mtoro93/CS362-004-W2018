#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>


/******** UNIT TEST FOR GARDEN CARD ***********/


int main (int argc, char** argv) {
    
     printf ("GARDEN TEST:\n");
    

    struct gameState G;

    //initialize test variables to known state 0
    int handPos, bonus, random = 0;
    int initState, card = 0;

    //variables to hold 3 cards
    int draw1, draw2, draw3 = 0; 
    
    int Card_Array[10] = {gardens, minion, mine, cutpurse, adventurer, village, embargo, sea_hag, tribute, smithy};
     
    random = rand() % 10;

    initState = initializeGame(2, Card_Array, random, &G);
    assert(initState == 0);
    
    //set card to an invalid value, int
    card = 4;
    handPos = 4;
    
    initState = cardEffect(card, draw1, draw2, draw3, &G, handPos, bonus);
    assert(initState == -1);

    printf("SUCCESSFUL TEST FOR GARDEN (CARD 2)!\n");
    return 0;


}