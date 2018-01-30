/*
* Name: Matthew Toro
* onid: torom
* Class: CS 362 Software Engineering II
* Program: unittest3.c
* Due Date: 2/4/2018
* Description: A unit test for the function 'isGameOver' in dominion.c
*/

/*
FUNCTION TO BE TESTED: ISGAMEOVER
REQUIREMENTS FOR FUNCTION: 

WHAT IS THIS FUNCTION SUPPOSED TO DO?
Returns 1 if the end of game conditions have been met. Otherwise returns 0.
End of Game Conditions
1. All Provinces have been purchased.
2. Three different kingdom card supplies have been depleted.

HOW DOES FULLDECKCOUNT AFFECT THE GAME STATE?
It just checks kingdom cards supply counts. It does not modify them.

*/

/*
WHAT TO TEST:
KINGDOM CARDS SUPPLY CHECK
Ensure kingdom cards supply stays the same before and after call to function.

PROVINCE CHECK
If supply count of provinces > 0, return 0.
Else return 1.

KINGDOM CARDS CHECK
If 3 different supply count of kingdom cards are == 0, return 1.
Else, return 0.

*/

/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
int const NUM_PASSES = 27;
int assertTrue(int booleanExpression, char* testCase);

int main() {
    int i;
    int randomSeed = 1000;
    int playerCount = 2;
	int success;
    int kingdomCards[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState state;
	int priorKingdomCardSupply[25];
	
	int passedTests = 0;
	
    printf ("TESTING isGameOver():\n");
	
	// initialize a new game using starting decks for these tests
	success = initializeGame(playerCount, kingdomCards, randomSeed, &state);
	
	
	// store kingdom cards supply in array
	for (i = 0; i < 25; i++)
	{
		priorKingdomCardSupply[i] = state.supplyCount[i];
	}

	// call isGameOver()
	success = isGameOver(&state);
	
	// test if supply count of cards remains unchanged.
	int supplyCountChanged = 0;
	for (i = 0; i < 25; i++)
	{
		if (priorKingdomCardSupply[i] != state.supplyCount[i])
			supplyCountChanged++;
	}
	
	passedTests+=assertTrue(supplyCountChanged == 0, "Kingdom Cards supply unchanged");
	
	// test if isGameOver returns 0 when game is not yet finished
	success = isGameOver(&state);
	passedTests+=assertTrue(success == 0, "Returns 0 for unfinished game");
	
	// test if isGameOver returns 1 if province count is 0
	state.supplyCount[3] = 0;
	success = isGameOver(&state);
	passedTests+=assertTrue(success == 1, "Returns 1 for finished game");
	
	// reset Provinces back to prior value
	state.supplyCount[3] = priorKingdomCardSupply[3];
	
	// test if isGameOver returns 1 if 3 separate supply counts that are not province (#3) are 0
	
	// run a loop through all kingdom cards?
	// randomly generate numbers?
	// test every possibility?
	
	for (i = 0; i < 25; i++)
	{
		if (i != 3)
		{
			state.supplyCount[i] = 0;
			success = isGameOver(&state);
			if (i < 2)
				passedTests+=assertTrue(success == 0, "Returns 0 for unfinished game");
			else
				passedTests+=assertTrue(success == 1, "Returns 1 for finished game");
		}
	}
	
	if (passedTests == NUM_PASSES)
		printf("All tests passed!\n");
	else
		printf("%d tests passed. %d tests failed.\n", passedTests, NUM_PASSES - passedTests);

    return 0;
}


int assertTrue(int booleanExpression, char* testCase)
{
	if (booleanExpression == 0)
	{
		printf("Test failed: ");
		printf(testCase);
		printf("\n");
		return 0;
	}
	else
	{
		printf("Test passed: ");
		printf(testCase);
		printf("\n");
		return 1;
	}	
}