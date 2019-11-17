/*******************************
 CS 362 - Assignment 4
 Author: Kendrick Chu
 Date: 11/9/19
 Description: Random unit test for baron card in dominion game.
 *****************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TESTCARD "baron"

void assert(int expectedResult, int actualResult) {
    if(expectedResult != actualResult) {
        printf("Test failed\n");
    }
    else {
        printf("Test passed\n");
    }
}

int main() {
    srand(time(NULL));
    int i, j;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int thisPlayer = 0;
    
    struct gameState state, test;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, estate};
    
    for(i = 0; i < 100; ++i) {
        //generate random number of players between 2 and 10
        int numPlayers = (rand() % (10 - 2 + 1)) + 2;
        
        //initialize game state and player cards
        initializeGame(numPlayers, k, seed, &state);
        
        printf("----------------- Testing Card: %s %d/100-----------------\n", TESTCARD, i + 1);
        
        //generate hand size of current player between 1 and 10
        state.handCount[thisPlayer] = (rand() % (10 - 1 + 1) + 1);
        int stateNumEstates = 0;
        int testNumEstates = 0;
        state.hand[thisPlayer][0] = baron;
        for(j = 1; j < state.handCount[thisPlayer]; ++j) {
            //get a random index of the cards in play in k
            int randomCard = rand() % 10;
            state.hand[thisPlayer][i] = k[randomCard];
            if(k[randomCard] == estate) {
                ++stateNumEstates;
            }
        }
        state.coins = rand() % 100;
        choice1 = rand() % 2;
        
        //copy the current game state to a test case
        memcpy(&test, &state, sizeof(struct gameState));
        
        cardEffect(baron, choice1, choice2, choice3, &test, handpos, &bonus);
        
        for(j = 0; j < test.handCount[thisPlayer]; ++j) {
            if(test.hand[thisPlayer][i] == estate) {
                ++testNumEstates;
            }
        }
        
        printf("\nTest: Player's number of buys increased by 1\n");
        assert(state.numBuys + 1, test.numBuys);
        
        //if estate card was discarded, test if player gained 4 coins
        if(stateNumEstates - 1 == testNumEstates) {
            printf("\nTest: Estate discarded, player's coins increased by 4\n");
            assert(state.coins + 4, test.coins);
            
            printf("\nTest: Player has discarded 2 cards (estate and baron)\n");
            assert(state.handCount[thisPlayer] - 2, test.handCount[thisPlayer]);
            
            printf("\nTest: Player's discard pile has increased by 2\n");
            assert(state.discardCount[thisPlayer] + 2, test.discardCount[thisPlayer]);
            
            printf("\nTest: Estate supply pile was unchanged\n");
            assert(state.supplyCount[estate], test.supplyCount[estate]);
        }
        //else player gained estate card
        else {
            printf("\nTest: Estate not discarded, player's coins unchanged\n");
            assert(state.coins, test.coins);
            
            printf("\nTest: Player has discarded 1 card (baron)\n");
            assert(state.handCount[thisPlayer] - 1, test.handCount[thisPlayer]);
            
            printf("\nTest: Player's discard pile has increased by 1\n");
            assert(state.discardCount[thisPlayer] + 1, test.discardCount[thisPlayer]);
            
            printf("\nTest: Player has gained an estate cared\n");
            assert(stateNumEstates + 1, testNumEstates);
            
            printf("\nTest: Player gained estate card from estate supply\n");
            assert(state.supplyCount[estate] - 1, test.supplyCount[estate]);
        }
        printf("\nTest: Top card in player's discard pile is the baron card\n");
        assert(baron, test.discard[thisPlayer][test.discardCount[thisPlayer] - 1]);
    }
    
    printf("\n----------------- End Testing Card: %s -----------------\n", TESTCARD);
    
    return 0;
}
