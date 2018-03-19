#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>



/******** UNIT TEST FOR ADVENTURER CARD ***********/

int main (int argc, char** argv) {

    printf ("ADVENTURER TEST:\n");
    
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
   
    card = 4;
    handPos = 4;


    //valid
    initState = playAdventurer(&G, handPos, 4, 1, 3, 1);
    assert(initState == 0);
    
    //invalid
    initState = playAdventurer(&G, handPos, 4, 9, -6, 9);
    assert(initState == 0);
    
    printf("SUCCESSFUL TEST FOR ADVENTURER!\n");
    return 0;


}