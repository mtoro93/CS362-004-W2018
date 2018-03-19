
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
	//great_hall

	int card_array[10] = {gardens, village, mine, embargo, minion, cutpurse, sea_hag, tribute, smithy, adventurer};

	int player = 1;
	int handCount = 0;
	int deckCount = 0;
	int result = 0;
	int randomNum = 0;
	int failCounter = 0;
	int passCounter = 0;

	struct gameState randG;

	//cycle through 4 rounds 
	for(int i = 0; i < 4; i++){

		//600 runs per round
		for(int x = 0; x < 600; x++){
			
			int seedNum = rand() % 5001;
			int totalPlayers = rand() % 4;
			
			initializeGame(totalPlayers, card_array, seedNum, &randG);
			
			randomNum = rand() % 10;

			if(randomNum == 5){
				randG.deckCount[player] = 0;
				deckCount = 0;
			}

			else{
				randomNum = rand() % MAX_DECK;
				randG.deckCount[player] = randomNum;
				//keep track of deck count
				deckCount = randomNum;
			}
			
			randomNum = rand() % MAX_DECK;
			randG.handCount[player] = rand() % MAX_HAND;
			//keep track of hand count
			handCount = randomNum;
			
			randG.discardCount[player] = rand() % MAX_DECK;
			
			result = playVillage(player, &randG, handCount);
			if(result != 0){
				failCounter++;
			}
			else{
				passCounter++;
			}
		}
	}

	//print results of random testing
	if(passCounter > failCounter){
		printf("Majority of tests were successful!\n");
		return 0;
	}

	else{
		printf("Error: Majority of tests failed!\n");
		return 1;
	}



	return 0;
}

