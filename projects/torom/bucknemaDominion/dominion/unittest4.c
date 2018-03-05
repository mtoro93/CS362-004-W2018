/*
* Name: Matthew Toro
* onid: torom
* Class: CS 362 Software Engineering II
* Program: unittest4.c
* Due Date: 2/4/2018
* Description: A unit test for the function 'buyCard' in dominion.c
*/

/*
FUNCTION TO BE TESTED: BUYCARD
REQUIREMENTS FOR FUNCTION: 

WHAT IS THIS FUNCTION SUPPOSED TO DO?
Purchases a card using the player's coins from the kingdom card supply

HOW DOES BUYCARD AFFECT THE GAME STATE?
Checks turn, modifies supply count of kingdomCards, modifies player discard pile,
decrements coins and buys
*/

/*
WHAT TO TEST:
1. correctly determines which player's turn it is
 -subsequently, it does not modify whose turn it is
2. gained correct card
 -subsequently, correct card is now in discard
 -no other player's discard is affected
3. supply count of card decremented
 -no other supply counts affected
4. coins decremented
5. numBuys decremented
6. returns 0 upon success

EDGE CASES:
if state->numBuys < 1 (NOT ENOUGH BUYS)
return -1

if state->supplyCount[card] < 1 (NOT ENOUGH CARDS)
return -1

state->coins < cost of card (NOT ENOUGH COINS)
return -1
*/

/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
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
int const NUM_PASSES = 34;
int assertTrue(int booleanExpression, char* testCase);

int main() {
	
    int i;
    int randomSeed = 1000;
    int playerCount = 2;
	int success;
    int kingdomCards[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState state;
	int passedTests = 0;
	
    printf ("TESTING isGameOver():\n");
	
	// initialize a new game using starting decks for these tests
	success = initializeGame(playerCount, kingdomCards, randomSeed, &state);
	
	struct gameState priorState;
	memcpy(&priorState, &state, sizeof(struct gameState));
	
	// set turn to player 0
	state.whoseTurn = 0;
	
	int correctTurn = state.whoseTurn;
	
	state.coins = 2;
	int priorCoinCount = state.coins;
	
	int priorSupplyCount = state.supplyCount[1];
	
	int priorNumBuys = state.numBuys;
	
	// purchase an estate
	success = buyCard(1, &state);
	
	passedTests+=assertTrue(correctTurn == state.whoseTurn, "Player turn did not change");
	
	passedTests+=assertTrue(state.discard[0][0] == 1, "Correct card purchased and is in discard");
	
	for (i = 1; i < playerCount; i++)
	{
		passedTests+=assertTrue(state.discard[i][0] == 0, "Other players discard pile not changed");
	}
	
	passedTests+=assertTrue(priorCoinCount == state.coins + 2, "Coin count decremented correctly");
	
	passedTests+=assertTrue(priorSupplyCount - 1 == state.supplyCount[1], "Supply count decremented correctly");
	passedTests+=assertTrue(state.supplyCount[0] == priorState.supplyCount[0], "Kingdom card count not changed");
	for (i = 2; i < 25; i++)
	{
		passedTests+=assertTrue(state.supplyCount[i] == priorState.supplyCount[i], "Kingdom card count not changed");
	}
	
	passedTests+=assertTrue(priorNumBuys - 1 == state.numBuys, "Number of buys decremented correctly");
	
	passedTests+=assertTrue(success == 0, "Function returns 0 upon success");
	
	
	// reset states for further testing
	state.coins = priorCoinCount;
	
	state.numBuys = priorNumBuys;
	
	// failure case testing
	
	state.coins = 0;
	
	success = buyCard(1, &state);
	
	passedTests+=assertTrue(success == -1, "Insufficient coins to purchase");
	
	state.coins = priorCoinCount;
	
	state.numBuys = 0;
	
	success = buyCard(1, &state);
	
	passedTests+=assertTrue(success == -1, "Insufficient buys");
	
	state.numBuys = priorNumBuys;
	
	state.supplyCount[1] = 0;
	
	success = buyCard(1, &state);
	
	passedTests+= assertTrue(success == -1, "Insufficient supply count");
	
	
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