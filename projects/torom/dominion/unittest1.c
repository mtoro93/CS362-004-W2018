/*
* Name: Matthew Toro
* onid: torom
* Class: CS 362 Software Engineering II
* Program: unittest1.c
* Due Date: 2/4/2018
* Description: A unit test for the function 'shuffle' in dominion.c
*/

/*
FUNCTION TO BE TESTED: SHUFFLE
REQUIREMENTS FOR FUNCTION: 

WHAT IS THIS FUNCTION SUPPOSED TO DO?
Randomly re-arranges the order of cards in a player's deck
Ideally, the order should change at least once.

HOW DOES SHUFFLE AFFECT THE GAME STATE?
1. game state data member state->deckCount[player] for current player should be equal before and after
2. list of cards in game state data member state->deck[player][i=0...deckCount] should be the same before and after

* EDGE CASE *
If a player has no cards in their deck, then shuffling not possible.
**************************************
  if (state->deckCount[player] < 1)
    return -1;
**************************************
*/

/*
WHAT TO TEST:
DECK COUNTS REMAIN THE SAME
priorDeckCount == afterDeckCount:
where priorDeckCount = state->deckCount[player] before calling shuffle
and afterDeckCount = state->deckCount[player] after calling shuffle

AND
LIST OF CARDS REMAIN THE SAME
priorCardList[deckCount] == afterCardList[deckCount]
where priorCardList = state->deck[player][i=0...deckCount] before calling shuffle
and afterCardList = state->deck[player][i=0...deckCount] after calling shuffle

AND
ORDER OF CARDS HAVE BEEN CHANGED AT LEAST ONCE
priorCardList[i] != afterCardList[i], where i = 0
else, i++

AND
RETURNS 0 UPON SUCCESS

OR
RETURN -1 UPON INAPPROPRIATE PRE-CONDITIONS

*/

/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0
int const NUM_PASSES = 5;
int assertTrue(int booleanExpression, char* testCase);

int main() {
    int i, j;
    int randomSeed = 1000;
    int playerCount = 2;
	int success;
    int kingdomCards[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState state;
	int priorDeckCount;
	int priorCardList[5];
	int passedTests = 0;
	
    printf ("TESTING shuffle():\n");
	
	// initialize a new game using starting decks for these tests
	// since initialize also draws their starting hands then the starting deck begins with 5 cards
	success = initializeGame(playerCount, kingdomCards, randomSeed, &state);
	
	for (j = 0; j < 5; j++)
	{
		int orderChanged = 0;
		printf("Test Pass %d\n", j+1);

		// store number of cards in deck
		priorDeckCount = state.deckCount[0];
#if (NOISY_TEST == 1)
		printf("Test player %d with %d cards in his deck.\n", 0, priorDeckCount);
#endif

		// count the card counts
		int numCoppers = 0;
		int numEstates = 0;

		// store types of cards in deck
		for (i = 0; i < priorDeckCount; i++)
		{
			priorCardList[i] = state.deck[0][i];
			if (priorCardList[i] == 1)
				numEstates++;
			else if (priorCardList[i] == 4)
				numCoppers++;
#if (NOISY_TEST == 1)
			printf("Test player %d\tCard: %d\n", 0, priorCardList[i]);
#endif
		}
	
		// call shuffle()
		success = shuffle(0, &state);
		
		passedTests+=assertTrue(success == 0, "Pre-Conditions Met");
	
#if (NOISY_TEST == 1)
		printf("Test player %d with %d cards in his deck.\n", 0, state.deckCount[0]);
#endif
		passedTests+=assertTrue(priorDeckCount == state.deckCount[0], "Deck Counts are Equal");
	
		// test if the number of estates and coppers changed; if so, something went wrong
		for (i = 0; i < state.deckCount[0]; i++)
		{
			if (state.deck[0][i] == 1)
				numEstates--;
			else if (state.deck[0][i] == 4)
				numCoppers--;
#if (NOISY_TEST == 1)
			printf("Test player %d\tCard: %d\n", 0, state.deck[0][i]);
#endif
		}
	
		passedTests+=assertTrue(numEstates == 0 && numCoppers == 0, "Card Lists are Equal");
	
	
		// this test is tricky. assume it always made the same order change. this test would not detect that
		// but a seed could give you this result
		// also, assume the shuffle keeps the deck the same; this test would fail under such a circumstance
		// that's why I run it multiple times because if the test passes 4/5 times, then arguably shuffle is working as intended
		priorCardList[j] = state.deck[0][j];
		shuffle(0, &state);
		for (i = 0; i < priorDeckCount; i++)
		{
			if (priorCardList[i] != state.deck[0][i])
			{
				orderChanged++;
			}
			
#if (NOISY_TEST == 1)
		printf("Card %d Before: Test player %d\tCard: %d\n", i+1, 0, priorCardList[i]);
		printf("Card %d After: Test player %d\tCard: %d\n", i+1, 0, state.deck[0][i]);
#endif
		}
	

		passedTests+=assertTrue(orderChanged > 0, "Order changed at least once");
	
		
		// TEST EDGE CASE: PRE-CONDITIONS NOT MET
		state.deckCount[0] = 0;
		success = shuffle(0, &state);
		
		passedTests+=assertTrue(success == -1, "Pre-Conditions not Met");
		state.deckCount[0] = priorDeckCount;
	}
	

	
	if (passedTests == NUM_PASSES*5)
		printf("All tests passed!\n");
	else
		printf("%d tests passed. %d tests failed.\n", passedTests, NUM_PASSES*5 - passedTests);

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