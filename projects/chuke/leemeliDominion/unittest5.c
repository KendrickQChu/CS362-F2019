/*******************************
 CS 362 - Assignment 3
 Author: Kendrick Chu
 Date: 11/9/19
 Description: Unit test for mine card in dominion game.
 *****************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define TESTCARD "mine"

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
    int k[10] = {adventurer, ambassador, duchy, gardens, mine, tribute, treasure_map, village, baron, estate};
    
    //initialize game state and player cards
    initializeGame(numPlayers, k, seed, &state);
    state.hand[thisPlayer][0] = mine;
    state.hand[thisPlayer][1] = state.hand[thisPlayer][2] = state.hand[thisPlayer][3] = copper;
    state.hand[thisPlayer][4] = silver;
    
    handpos = 0;
    //set coins to better detect bugs
    state.coins = 1;
    printf("----------------- Testing Card: %s -----------------\n", TESTCARD);
    
    //Test 1: Player trashes treasure for treasure cost costing at most 3 more
    printf("\nTest 1: Player correcly trashes treasure card for another treasure card costing at most 3 more\n\n");
    choice1 = 1;
    choice2 = silver;
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    
    cardEffect(mine, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's hand should be decremented by 1\n");
    assert(state.handCount[thisPlayer] - 1, test.handCount[thisPlayer]);
    
    printf("Player's discard pile should be incremented by 1\n");
    assert(state.discardCount[thisPlayer] + 1, test.discardCount[thisPlayer]);
    
    int stateCount = 0;
    int testCount = 0;
    
    for(i = 0; i < state.handCount[thisPlayer]; ++i) {
        if(state.hand[thisPlayer][i] == silver) {
            stateCount++;
        }
    }
    
    for(i = 0; i < test.handCount[thisPlayer]; ++i) {
        if(test.hand[thisPlayer][i] == silver) {
            testCount++;
        }
    }
    
    printf("Player has gained the chosen treasure card to their hand\n");
    assert(stateCount + 1, testCount);
    
    //Test 2: Player trashes treasure for treasure cost costing more than 3
    printf("\nTest 2: Player trashes treasure card for another treasure card costing more than 3 more\n\n");
    choice1 = 1;
    choice2 = gold;
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    
    cardEffect(mine, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's hand should be unchanged\n");
    assert(state.handCount[thisPlayer], test.handCount[thisPlayer]);
    
    printf("Player's discard pile should be unchanged\n");
    assert(state.discardCount[thisPlayer], test.discardCount[thisPlayer]);
    
    stateCount = 0;
    testCount = 0;
    
    for(i = 0; i < state.handCount[thisPlayer]; ++i) {
        if(state.hand[thisPlayer][i] == gold) {
            stateCount++;
        }
    }
    
    for(i = 0; i < test.handCount[thisPlayer]; ++i) {
        if(test.hand[thisPlayer][i] == gold) {
            testCount++;
        }
    }
    
    printf("Player has not gained the chosen treasure card to their hand\n");
    assert(stateCount , testCount);
    
    
    //Test 3: Player trashes treasure for treasure map
    printf("\nTest 3: Player correcly trashes treasure card for treasure map card\n\n");
    choice1 = 4;
    choice2 = treasure_map;
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    
    cardEffect(mine, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's hand should be decremented by 1\n");
    assert(state.handCount[thisPlayer] - 1, test.handCount[thisPlayer]);
    
    printf("Player's discard pile should be incremented by 1\n");
    assert(state.discardCount[thisPlayer] + 1, test.discardCount[thisPlayer]);
    
    stateCount = 0;
    testCount = 0;
    
    for(i = 0; i < state.handCount[thisPlayer]; ++i) {
        if(state.hand[thisPlayer][i] == treasure_map) {
            stateCount++;
        }
    }
    
    for(i = 0; i < test.handCount[thisPlayer]; ++i) {
        if(test.hand[thisPlayer][i] == treasure_map) {
            testCount++;
        }
    }
    
    printf("Player has gained the chosen treasure card to their hand\n");
    assert(stateCount + 1, testCount);
    
    
    //Test 4: Player plays mine with no treasure cards
    printf("\nTest 4: Player plays Mine without any treasure cards in hand\n\n");
    state.hand[thisPlayer][0] = mine;
    state.hand[thisPlayer][1] = state.hand[thisPlayer][2] = state.hand[thisPlayer][3] = state.hand[thisPlayer][4] = estate;
    choice1 = 1;
    choice2 = silver;
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    
    cardEffect(mine, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's hand should be unchanged\n");
    assert(state.handCount[thisPlayer], test.handCount[thisPlayer]);
    
    printf("Player's discard pile should be unchanged\n");
    assert(state.discardCount[thisPlayer], test.discardCount[thisPlayer]);
    
    stateCount = 0;
    testCount = 0;
    
    for(i = 0; i < state.handCount[thisPlayer]; ++i) {
        if(state.hand[thisPlayer][i] == silver) {
            stateCount++;
        }
    }
    
    for(i = 0; i < test.handCount[thisPlayer]; ++i) {
        if(test.hand[thisPlayer][i] == silver) {
            testCount++;
        }
    }
    
    printf("Player has not gained the chosen treasure card to their hand\n");
    assert(stateCount, testCount);
    
    printf("\n----------------- End Testing Card: %s -----------------\n", TESTCARD);
    
    return 0;
}
