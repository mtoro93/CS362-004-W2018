#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>



//test village card

int main (int argc, char** argv) {

    printf ("VILLAGE TEST:\n");
    
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

    //invalid
    initState = playVillage(-1, &G, 4);
    assert(initState == 0);
    
    //valid
    initState = playVillage(1, &G, 4);
    assert(initState == 0);
    
    printf("SUCCESSFUL TEST FOR VILLAGE CARD!\n");
    return 0;


}