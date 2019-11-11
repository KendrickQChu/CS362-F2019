/*******************************
 CS 362 - Assignment 3
 Author: Kendrick Chu
 Date: 11/9/19
 Description: Unit test for baron card in dominion game.
 *****************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

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
    int i;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    
    struct gameState state, test;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, estate};
    
    //initialize game state and player cards
    initializeGame(numPlayers, k, seed, &state);
    state.hand[thisPlayer][0] = baron;
    state.hand[thisPlayer][1] = state.hand[thisPlayer][2] = state.hand[thisPlayer][3] = state.hand[thisPlayer][4] = smithy;
    handpos = 0;
    printf("----------------- Testing Card: %s -----------------\n", TESTCARD);
    
    //Test 1: baron card with no Estate in hand -> +1 buy
    printf("\nTest 1: No Estate in hand -> +1 buy\n\n");
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    //not discarding Estate
    choice1 = 0;
    cardEffect(baron, choice1, choice2, choice3, &test, handpos, &bonus);
    printf("Number of buys incremented by 1\n");
    assert(state.numBuys + 1, test.numBuys);
    
    //test state should have one more estate in hand than state
    int stateNumEstates = 0;
    int testNumEstates = 0;
    for(i = 0; i < state.handCount[thisPlayer]; ++i) {
        if(state.hand[thisPlayer][i] == estate) {
            ++stateNumEstates;
        }
    }
    for(i = 0; i < test.handCount[thisPlayer]; ++i) {
        if(test.hand[thisPlayer][i] == estate) {
            ++testNumEstates;
        }
    }
    printf("Player gained Estate card because Estate card wasn't discarded\n");
    assert(stateNumEstates + 1, testNumEstates);
    
    printf("Estate card taken from Estate supply pile\n");
    assert(state.supplyCount[estate] - 1, test.supplyCount[estate]);
    
    printf("Player corrently gained and discarded cards\n");
    assert(state.handCount[thisPlayer], test.handCount[thisPlayer]);
    
    printf("Player discard pile increased by 1\n");
    assert(state.discardCount[thisPlayer] + 1, test.discardCount[thisPlayer]);
    
    printf("Card on top of discard pile is Baron\n");
    assert(baron, test.discard[thisPlayer][test.discardCount[thisPlayer] - 1]);
    
    
    //Test 2: baron card and player chooses to discard estate when no estate in hand
    printf("\nTest 2: No Estate in hand but Player tries to discard -> +1 buy\n\n");
    
    memcpy(&test, &state, sizeof(struct gameState));
    //discarding Estate
    choice1 = 1;
    cardEffect(baron, choice1, choice2, choice3, &test, handpos, &bonus);
    printf("Number of buys incremented by 1\n");
    assert(state.numBuys + 1, test.numBuys);
    
    //test state should have one more estate in hand than state
    stateNumEstates = 0;
    testNumEstates = 0;
    for(i = 0; i < state.handCount[thisPlayer]; ++i) {
        if(state.hand[thisPlayer][i] == estate) {
            ++stateNumEstates;
        }
    }
    for(i = 0; i < test.handCount[thisPlayer]; ++i) {
        if(test.hand[thisPlayer][i] == estate) {
            ++testNumEstates;
        }
    }
    printf("Player gained Estate card because Estate card wasn't discarded\n");
    assert(stateNumEstates + 1, testNumEstates);
    
    printf("Estate card taken from Estate supply pile\n");
    assert(state.supplyCount[estate] - 1, test.supplyCount[estate]);
    
    printf("Player corrently gained and discarded cards\n");
    assert(state.handCount[thisPlayer], test.handCount[thisPlayer]);
    
    printf("Player discard pile increased by 1\n");
    assert(state.discardCount[thisPlayer] + 1, test.discardCount[thisPlayer]);
    
    printf("Card on top of discard pile is Baron\n");
    assert(baron, test.discard[thisPlayer][test.discardCount[thisPlayer] - 1]);
    
    
    //play baron card with estate in hand, discard for 4 coins
    printf("\nTest 3: Estate in hand -> +1 buy, +4 coins\n\n");
    //set player hands and coins to better catch bugs
    state.hand[thisPlayer][0] = baron;
    state.hand[thisPlayer][1] = estate;
    state.hand[thisPlayer][2] = state.hand[thisPlayer][3] = state.hand[thisPlayer][4] = smithy;
    state.coins = 1;
    
    memcpy(&test, &state, sizeof(struct gameState));
    
    choice1 = 1;
    cardEffect(baron, choice1, choice2, choice3, &test, handpos, &bonus);
    printf("Number of buys incremented by 1\n");
    assert(state.numBuys + 1, test.numBuys);
    
    //test state should have one less estate in hand than state
    stateNumEstates = 0;
    testNumEstates = 0;
    for(i = 0; i < state.handCount[thisPlayer]; ++i) {
        if(state.hand[thisPlayer][i] == estate) {
            ++stateNumEstates;
        }
    }
    for(i = 0; i < test.handCount[thisPlayer]; ++i) {
        if(test.hand[thisPlayer][i] == estate) {
            ++testNumEstates;
        }
    }
    printf("Player discarded Estate card from hand\n");
    assert(stateNumEstates - 1, testNumEstates);
    
    printf("Plater gained 4 coins from discarding Estate card\n");
    assert(state.coins + 4, test.coins);
    
    printf("Estate supply pile unchanged\n");
    assert(state.supplyCount[estate], test.supplyCount[estate]);
    
    printf("Player corrently gained and discarded cards\n");
    assert(state.handCount[thisPlayer] - 2, test.handCount[thisPlayer]);
    
    printf("Player discard pile increased by 2\n");
    assert(state.discardCount[thisPlayer] + 2, test.discardCount[thisPlayer]);
    
    printf("Card on top of discard pile is Baron\n");
    assert(baron, test.discard[thisPlayer][test.discardCount[thisPlayer] - 1]);
    
    
    //Test 4: baron card with estate card in hand, but choose not to discard
    printf("\nTest 4: Estate in hand but not discarded -> +1 buy\n\n");
    
    memcpy(&test, &state, sizeof(struct gameState));
    //not discarding Estate
    choice1 = 0;
    cardEffect(baron, choice1, choice2, choice3, &test, handpos, &bonus);
    printf("Number of buys incremented by 1\n");
    assert(state.numBuys + 1, test.numBuys);
    
    //test state should have one more estate in hand than state
    stateNumEstates = 0;
    testNumEstates = 0;
    for(i = 0; i < state.handCount[thisPlayer]; ++i) {
        if(state.hand[thisPlayer][i] == estate) {
            ++stateNumEstates;
        }
    }
    for(i = 0; i < test.handCount[thisPlayer]; ++i) {
        if(test.hand[thisPlayer][i] == estate) {
            ++testNumEstates;
        }
    }
    printf("Player gained Estate card because Estate card wasn't discarded\n");
    assert(stateNumEstates + 1, testNumEstates);
    
    printf("Estate card taken from Estate supply pile\n");
    assert(state.supplyCount[estate] - 1, test.supplyCount[estate]);
    
    printf("Player corrently gained and discarded cards\n");
    assert(state.handCount[thisPlayer], test.handCount[thisPlayer]);
    
    printf("Player discard pile increased by 1\n");
    assert(state.discardCount[thisPlayer] + 1, test.discardCount[thisPlayer]);
    
    printf("Card on top of discard pile is Baron\n");
    assert(baron, test.discard[thisPlayer][test.discardCount[thisPlayer] - 1]);
    
    printf("\n----------------- End Testing Card: %s -----------------\n", TESTCARD);
    
    
    return 0;
}
