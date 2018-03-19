#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

/***********UNIT TEST FOR SMITHY CARD**********/


int main (int argc, char** argv) {

    printf ("SMITHY TEST:\n");
    
    struct gameState G;

    //initialize test variables to known state 0
    int handPos, bonus, random = 0;
    int initState, card = 0;

    //variables to hold 3 cards that smithy grants
    int draw1, draw2, draw3 = 0; 

    int Card_Array[10] = {gardens, minion, mine, cutpurse, adventurer, village, embargo, sea_hag, tribute, smithy};
    
    random = rand() % 10;
    
    initState = initializeGame(2, Card_Array, random, &G);
   
    assert(initState == 0);
   
    card = 4;
    handPos = 4;

    //good input
    initState = playSmithy(1, &G, 4);
    assert(initState == 0);


    //give smithy an invalid player number
    initState = playSmithy(-1, &G, 4);
    assert(initState == 0);
    
    
    printf("SUCCESSFUL TEST FOR SMITHY (CARD 1)!\n");
    return 0;
}