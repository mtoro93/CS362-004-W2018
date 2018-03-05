/*
* Name: Matthew Toro
* onid: torom
* Class: CS 362 Software Engineering II
* Program: cardtest3.c
* Due Date: 2/4/2018
* Description: A unit test for the card 'Great Hall' in dominion.c
*/

/*
FUNCTION TO BE TESTED: playGreatHall
REQUIREMENTS FOR FUNCTION: 

WHAT IS THIS FUNCTION SUPPOSED TO DO?
draws 1 card from the current player's deck and adds to their hand
also adds 1 action to the current player's action
great hall is then discard

HOW DOES GREAT HALL AFFECT THE GAME STATE?
affects current player's hand, deck, and discard
affects state.numActions
*/

/*
WHAT TO TEST:
1. Current player should receive exactly 1 card.
priorHand = currentHand after great hall is discarded

2. 1 card should come from his own pile.
priorDeck - 1 = current Deck Count

3. the great hall card should be discarded
state.discardCount = prior count + 1
state.discard[0][discardCount - 1] = great hall card number

4. the current player should receive exactly 1 action

5. No state change should occur for other players.
for each other player
	prior value = current value

6. No state change should occur to the victory card piles and kingdom card piles.
for each card
	prior supply count = current supply count

*/

/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
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
	
    printf ("TESTING Great Hall:\n");
	
	// initialize a new game using starting decks for these tests
	// since initialize also draws their starting hands then the starting deck begins with 5 cards
	success = initializeGame(playerCount, kingdomCards, randomSeed, &state);

	// add great hall card to hand
	state.hand[0][5] = great_hall;
	state.handCount[0]++;
	
	struct gameState priorState;
	memcpy(&priorState, &state, sizeof(struct gameState));
	
	success = cardEffect(great_hall, 0, 0, 0, &state, state.handCount[0] - 1, 0);
	
	passedTests+=assertTrue(priorState.handCount[0] == state.handCount[0], "Current hand contains exactly 3 more cards");
	passedTests+=assertTrue(priorState.deckCount[0] - 1 == state.deckCount[0], "Current player deck count decremented by 3");
	
	passedTests+=assertTrue(priorState.discardCount[0] + 1 == state.discardCount[0], "Current player discard count incremented");
	
	passedTests+=assertTrue(priorState.numActions + 1 == state.numActions, "Number of actions incremented");
	
	passedTests+=assertTrue(state.discard[0][state.discardCount[0] - 1] == great_hall, "Great Hall card in current player discard");
	passedTests+=assertTrue(success == 0, "Function returned successfully");
	
	for ( i = 1; i < playerCount; i++)
	{
		printf("Player %d:\n", i);
		passedTests+=assertTrue(priorState.handCount[i] == state.handCount[i], "Hand remains the same");
		passedTests+=assertTrue(priorState.deckCount[i] == state.deckCount[i], "Deck remains the same");
		passedTests+=assertTrue(priorState.discardCount[i] == state.discardCount[i], "Discard remains the same");	
	}

	for (i = 0; i < 25; i++)
	{
		printf("Kingdom Card: %d\n", i);
		passedTests+=assertTrue(priorState.supplyCount[i] == state.supplyCount[i], "Kingdom card supply remains the same");
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