/*
* Name: Matthew Toro
* onid: torom
* Class: CS 362 Software Engineering II
* Program: unittest2.c
* Due Date: 2/4/2018
* Description: A unit test for the function 'fullDeckCount' in dominion.c
*/

/*
FUNCTION TO BE TESTED: FULLDECKCOUNT
REQUIREMENTS FOR FUNCTION: 

WHAT IS THIS FUNCTION SUPPOSED TO DO?
Count the passed in card argument among a player's deck, hand, and discard pile

HOW DOES FULLDECKCOUNT AFFECT THE GAME STATE?
It does not affect the game's state.
It checks if a card is present in state.deck, state.hand, and state.discard but it does not modify those values
There are no apparent edge cases in this function.
*/

/*
WHAT TO TEST:
DECK COUNT REMAIN THE SAME
priorDeckCount == afterDeckCount:
where priorDeckCount = state->deckCount[player] before calling fullDeckCount
and afterDeckCount = state->deckCount[player] after calling fullDeckCount

AND
LIST OF CARDS IN DECK REMAIN THE SAME
priorCardList[deckCount] == afterCardList[deckCount]
where priorCardList = state->deck[player][i=0...deckCount] before calling fullDeckCount
and afterCardList = state->deck[player][i=0...deckCount] after calling fullDeckCount

AND
HAND COUNT REMAIN THE SAME
priorHandCount == afterHandCount:
where priorHandCount = state->handCount[player] before calling fullDeckCount
and afterDeckCount = state->handCount[player] after calling fullDeckCount

AND
LIST OF CARDS IN HAND REMAIN THE SAME
priorHandList[handCount] == afterHandList[handCount]
where priorHandList = state->hand[player][i=0...handCount] before calling fullDeckCount
and afterHandList = state->hand[player][i=0...handCount] after calling fullDeckCount

AND
DISCARD COUNT REMAINS THE SAME
priorDiscardCount == afterDiscardCount:
where priorDiscardCount = state->discardCount[player] before calling fullDeckCount
and afterDiscardCount = state->discardCount[player] after calling fullDeckCount

AND
LIST OF CARDS IN DISCARD REMAINS THE SAME
priorDiscardList[discardCount] == afterDiscardList[discardCount]
where priorDiscardList = state->discard[player][i=0...discardCount] before calling fullDeckCount
and afterDiscardList = state->discard[player][i=0...discardCount] after calling fullDeckCount

AND
RETURNS CORRECT 'CARD' COUNT
That is, if the player has seven coppers, then count should return 7

*/




/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
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
int const NUM_PASSES = 7;
int assertTrue(int booleanExpression, char* testCase);

int main() {
    int i;
    int randomSeed = 1000;
    int playerCount = 2;
	int success;
    int kingdomCards[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState state;
	int priorDeckCount, priorHandCount, priorDiscardCount;
	int priorCardList[5];
	int priorHandList[5];
	int priorDiscardList[5];
	int passedTests = 0;
	
    printf ("TESTING fullDeckCount():\n");
	
	// initialize a new game using starting decks for these tests
	// since initialize also draws their starting hands then the starting deck begins with 5 cards
	success = initializeGame(playerCount, kingdomCards, randomSeed, &state);
	
	
	// store number of cards in deck
	priorDeckCount = state.deckCount[0];
#if (NOISY_TEST == 1)
	printf("Testing DECK\n");
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
	
	// call fullDeckCount()
	success = fullDeckCount(0, 4, &state);
	
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
	
// store number of cards in hand
	priorHandCount = state.handCount[0];
#if (NOISY_TEST == 1)
	printf("Testing HAND\n");
	printf("Test player %d with %d cards in his hand.\n", 0, priorHandCount);
#endif

	// count the card counts
	numCoppers = 0;
	numEstates = 0;

	// store types of cards in deck
	for (i = 0; i < priorHandCount; i++)
	{
		priorHandList[i] = state.hand[0][i];
		if (priorHandList[i] == 1)
			numEstates++;
		else if (priorHandList[i] == 4)
			numCoppers++;
#if (NOISY_TEST == 1)
		printf("Test player %d\tCard: %d\n", 0, priorHandList[i]);
#endif
	}
	
	
	// call fullDeckCount()
	success = fullDeckCount(0, 4, &state);
	
#if (NOISY_TEST == 1)
	printf("Test player %d with %d cards in his hand.\n", 0, state.handCount[0]);
#endif
	passedTests+=assertTrue(priorHandCount == state.handCount[0], "Hand Counts are Equal");
	
	// test if the number of estates and coppers changed; if so, something went wrong
	for (i = 0; i < state.handCount[0]; i++)
	{
		if (state.hand[0][i] == 1)
			numEstates--;
		else if (state.hand[0][i] == 4)
			numCoppers--;
#if (NOISY_TEST == 1)
		printf("Test player %d\tCard: %d\n", 0, state.hand[0][i]);
#endif
	}
	passedTests+=assertTrue(numEstates == 0 && numCoppers == 0, "Card Lists are Equal");
	
	//**********
	// set up discard pile for testing
	//**********
	state.discardCount[0] = 5;
	for (i = 0; i < state.discardCount[0]; i++)
	{
		// set discard pile to 5 coppers
		state.discard[0][i] = 4;
	}
	
	// store number of cards in discard pile
	priorDiscardCount = state.discardCount[0];
#if (NOISY_TEST == 1)
	printf("Testing DISCARD\n");
	printf("Test player %d with %d cards in his discard.\n", 0, priorDiscardCount);
#endif

	// count the # of coppers
	numCoppers = 0;

	// store types of cards in deck
	for (i = 0; i < priorDiscardCount; i++)
	{
		priorDiscardList[i] = state.discard[0][i];
		if (priorDiscardList[i] == 4)
			numCoppers++;
#if (NOISY_TEST == 1)
		printf("Test player %d\tCard: %d\n", 0, priorDiscardList[i]);
#endif
	}
	
	// call fullDeckCount()
	success = fullDeckCount(0, 4, &state);
	
#if (NOISY_TEST == 1)
	printf("Test player %d with %d cards in his discard.\n", 0, state.discardCount[0]);
#endif
	passedTests+=assertTrue(priorDiscardCount == state.discardCount[0], "Discard Counts are Equal");
	
	// test if the number of coppers changed; if so, something went wrong
	for (i = 0; i < state.discardCount[0]; i++)
	{
		if (state.discard[0][i] == 4)
			numCoppers--;
#if (NOISY_TEST == 1)
		printf("Test player %d\tCard: %d\n", 0, state.discard[0][i]);
#endif
	}
	
	passedTests+=assertTrue(numCoppers == 0, "Card Lists are Equal");	
	
	
	// call fullDeckCount to check for correct count of coppers
	
	success = fullDeckCount(0, 4, &state);
	passedTests+=assertTrue(success == 12, "Correct Count Returned");
	
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