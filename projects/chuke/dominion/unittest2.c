/*******************************
 CS 362 - Assignment 3
 Author: Kendrick Chu
 Date: 11/9/19
 Description: Unit test for minion card in dominion game.
 *****************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

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
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    
    struct gameState state, test;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, estate};
    
    //initialize game state and player cards
    initializeGame(numPlayers, k, seed, &state);
    state.hand[thisPlayer][0] = minion;
    state.hand[thisPlayer][1] = state.hand[thisPlayer][2] = state.hand[thisPlayer][3] = state.hand[thisPlayer][4] = smithy;
    
    //set other player's cards
    state.hand[1][0] = minion;
    state.hand[1][1] = state.hand[1][2] = state.hand[1][3] = state.hand[1][4] = copper;
    
    handpos = 0;
    printf("----------------- Testing Card: %s -----------------\n", TESTCARD);
    
    //Test 1: player chooses to gain 2 coins
    printf("\nTest 1: Player chooses to gain 2 coins\n\n");
    
    //set coins to 1 to better detect issues with adding coins
    state.coins = 1;
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    
    //player chooses to gain 2 coins
    choice1 = 1;
    choice2 = 0;
    
    cardEffect(minion, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's number of actions should be incremented by 1\n");
    assert(state.numActions + 1, test.numActions);
    
    printf("Player's coins incremented by 2\n");
    assert(state.coins + 2, test.coins);
    
    printf("Player's hand count decremented by 1\n");
    assert(state.handCount[thisPlayer] - 1, test.handCount[thisPlayer]);
    
    printf("Player's discard count incremented by 1\n");
    assert(state.discardCount[thisPlayer] + 1, test.discardCount[thisPlayer]);
    
    printf("Player's top card in discard pile is the minion card\n");
    assert(minion, test.discard[thisPlayer][test.discardCount[thisPlayer] - 1]);
    
    
    //Test 2: player chooses to discard hand and gain 4 new cards, other players also discard (have 5 cards or more)
    printf("\nTest 2: Player chooses to discard hand and gain 4 new cards, other player also discards hand\n\n");
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    
    //player chooses to discard hand and draw 4 cards
    choice1 = 0;
    choice2 = 1;
    
    cardEffect(minion, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's number of actions should be incremented by 1\n");
    assert(state.numActions + 1, test.numActions);
    
    printf("Player has 4 cards in hand after discard\n");
    assert(4, test.handCount[thisPlayer]);
    
    printf("Player has discarded original hand (5 cards)\n");
    assert(state.discardCount[thisPlayer] + 5, test.discardCount[thisPlayer]);
    
    printf("Other player discards and draws 4 new cards\n");
    assert(4, test.handCount[1]);
    
    printf("Other player has discarded original hand (5 cards)\n");
    assert(state.discardCount[1] + 5, test.discardCount[1]);
    
    
    //Test 3: player chooses to discard hand and gain 4 new cards, other players don't discard (have less than 5 cards)
    printf("\nTest 3: Player chooses to discard hand and gain 4 new cards, other player doesn't discard hand\n\n");
    
    state.hand[thisPlayer][0] = minion;
    state.hand[thisPlayer][1] = state.hand[thisPlayer][2] = state.hand[thisPlayer][3] = state.hand[thisPlayer][4] = copper;
    
    //set other player's cards
    state.handCount[1] = 4;
    state.hand[1][0] = minion;
    state.hand[1][1] = state.hand[1][2] = state.hand[1][3] = copper;
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    
    //player chooses to discard hand and draw 4 cards
    choice1 = 0;
    choice2 = 1;
    
    cardEffect(minion, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's number of actions should be incremented by 1\n");
    assert(state.numActions + 1, test.numActions);
    
    printf("Player has 4 cards in hand after discard\n");
    assert(4, test.handCount[thisPlayer]);
    
    printf("Player has discarded original hand (5 cards)\n");
    assert(state.discardCount[thisPlayer] + 5, test.discardCount[thisPlayer]);
    
    printf("Other player's hand is unchanged\n");
    assert(state.handCount[1], test.handCount[1]);
    
    printf("Other player's discard pile is unchanged\n");
    assert(state.discardCount[1], test.discardCount[1]);
    
    printf("\n----------------- End Testing Card: %s -----------------\n", TESTCARD);
    
    return 0;
}
