/*
* Name: Matthew Toro
* onid: torom
* Class: CS 362 Software Engineering II
* Program: cardtest1.c
* Due Date: 2/4/2018
* Description: A unit test for the card 'Adventurer' in dominion.c
*/

/*
FUNCTION TO BE TESTED: playAdventurer
REQUIREMENTS FOR FUNCTION: 

WHAT IS THIS FUNCTION SUPPOSED TO DO?
Takes cards from the top of the current player's deck.
If it is a treasure card, it puts it in the player's hand.
If it is a non-treasure card, it sets it aside to be discarded.
It keeps revealing until two treasure cards have been kept.

HOW DOES ADVENTURER AFFECT THE GAME STATE?
affects the current player's hand, deck, and discard
*/

/*
WHAT TO TEST:
1. Current player should receive exactly 2 treasures.
priorHand + 2 = currentHand 

2. x cards should come from his own pile.
priorDeck - x = current Deck Count

3. the adventurer card should be discarded
and the non-treasure cards should be discarded
priorDiscardCount - x = currentDiscardCount

4. No state change should occur for other players.
for each other player
	prior value = current value

5. No state change should occur to the victory card piles and kingdom card piles.
for each card
	prior supply count = current supply count

*/

/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
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
int const NUM_PASSES = 35;
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
	
    printf ("TESTING Adventurer:\n");
	
	// initialize a new game using starting decks for these tests
	// since initialize also draws their starting hands then the starting deck begins with 5 cards
	success = initializeGame(playerCount, kingdomCards, randomSeed, &state);

	// add adventurer card to hand
	state.hand[0][5] = adventurer;
	state.handCount[0]++;
	
	struct gameState priorState;
	memcpy(&priorState, &state, sizeof(struct gameState));
	
	
	success = cardEffect(adventurer, 0, 0, 0, &state, state.handCount[0] - 1, 0);
	
	// might need to re-work this calculation since you can shuffle during the card's effect
	int cardsFound = priorState.deckCount[0] - state.deckCount[0];
	
	// these two tests should fail because of the bug introduced in assignment-2
	passedTests+=assertTrue(priorState.handCount[0] + 1 == state.handCount[0], "Current hand contains exactly 2 more cards");
	
	passedTests+=assertTrue(state.hand[0][state.handCount[0] - 1] == copper || 
		state.hand[0][state.handCount[0] - 1] == silver || 
		state.hand[0][state.handCount[0] - 1] == gold, "1st new card is a treasure");
		
	passedTests+=assertTrue(state.hand[0][state.handCount[0] - 2] == copper || 
		state.hand[0][state.handCount[0] - 2] == silver || 
		state.hand[0][state.handCount[0] - 2] == gold, "2nd new card is a treasure");
	
	
	// might need to add something to account for the potential
	// like || state.deckCount + discard pile or something
	passedTests+=assertTrue(priorState.deckCount[0] - cardsFound == state.deckCount[0], "Current player deck count decremented by revealed cards");
	
	passedTests+=assertTrue(priorState.discardCount[0] + 1 == state.discardCount[0], "Current player discard count incremented");
	
	passedTests+=assertTrue(state.discard[0][state.discardCount[0] - 1] == adventurer, "Adventurer card in current player discard");
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