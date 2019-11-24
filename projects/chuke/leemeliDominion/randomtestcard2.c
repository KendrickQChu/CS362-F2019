/*******************************
 CS 362 - Assignment 4
 Author: Kendrick Chu
 Date: 11/9/19
 Description: Random unit test for minion card in dominion game.
 *****************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TESTCARD "minion"

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
        state.hand[thisPlayer][0] = minion;
        for(j = 1; j < state.handCount[thisPlayer]; ++j) {
            //get a random index of the cards in play in k
            int randomCard = rand() % 10;
            state.hand[thisPlayer][i] = k[randomCard];
        }

        for(j = 1; j < numPlayers; ++j) {
            state.handCount[j] = rand() % 11;
        }
        state.coins = rand() % 100;
        choice1 = rand() % 2;
        if(choice1 == 0) {
            choice2 = 1;
        }
        else {
            choice2 = 0;
        }
        
        state.playedCardCount = rand() % 100;
        //copy the current game state to a test case
        memcpy(&test, &state, sizeof(struct gameState));
        
        cardEffect(minion, choice1, choice2, choice3, &test, handpos, &bonus);
        
        printf("\nTest: Player's number of actions increased by 1\n");
        assert(state.numActions + 1, test.numActions);
        
        //if player chose to gain coins
        if(choice1 == 1) {
            printf("\nTest: Player's coins increased by 2\n");
            assert(state.coins + 2, test.coins);
            
            printf("\nTest: Player's hand count decremented by 1\n");
            assert(state.handCount[thisPlayer] - 1, test.handCount[thisPlayer]);
               
            printf("\nTest: Player's discard count incremented by 1\n");
            assert(state.discardCount[thisPlayer] + 1, test.discardCount[thisPlayer]);
               
            printf("\nTest: Player's top card in discard pile is the minion card\n");
            assert(minion, test.discard[thisPlayer][test.discardCount[thisPlayer] - 1]);
        }
        //else player chose to discard hand and gain 4 cards
        else if(choice2 == 1) {
            printf("\nTest: Player has 4 cards in hand after discard\n");
            assert(4, test.handCount[thisPlayer]);
            
            printf("\nTest: Player has discarded original hand (5 cards)\n");
            assert(state.discardCount[thisPlayer] + 5, test.discardCount[thisPlayer]);
            
            for(j = 1; j < numPlayers; ++j) {
                if(state.handCount[j] >= 5) {
                    printf("\nTest: Other player %d discards and draws 4 new cards\n", j);
                    assert(4, test.handCount[j]);
                    
                    printf("\nTest: Other player %d has discarded original hand (5 cards)\n", j);
                    assert(state.discardCount[j] + 5, test.discardCount[j]);
                }
                else {
                    printf("\nTest: Other player %d's hand is unchanged\n", j);
                    assert(state.handCount[j], test.handCount[j]);
                    
                    printf("\nTest: Other player's discard pile is unchanged\n");
                    assert(state.discardCount[j], test.discardCount[j]);
                }
            }
        }
    }
    
    printf("\n----------------- End Testing Card: %s -----------------\n", TESTCARD);
    
    return 0;
}
