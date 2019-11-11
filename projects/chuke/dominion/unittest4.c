/*******************************
 CS 362 - Assignment 3
 Author: Kendrick Chu
 Date: 11/9/19
 Description: Unit test for tribute card in dominion game.
 *****************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define TESTCARD "tribute"

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
    int nextPlayer = thisPlayer + 1;
    
    struct gameState state, test;
    int k[10] = {adventurer, ambassador, duchy, gardens, mine, tribute, smithy, village, baron, estate};
    
    //initialize game state and player cards
    initializeGame(numPlayers, k, seed, &state);
    state.hand[thisPlayer][0] = tribute;
    state.hand[thisPlayer][1] = state.hand[thisPlayer][2] = state.hand[thisPlayer][3] = state.hand[thisPlayer][4] = smithy;
    
    handpos = 0;
    //set coins to better detect bugs
    state.coins = 1;
    printf("----------------- Testing Card: %s -----------------\n", TESTCARD);
    
    //Test 1: next player has no cards in deck and discard
    printf("\nTest 1: Next player has no cards in deck and discard piles\n\n");
    
    state.discardCount[nextPlayer] = 0;
    state.deckCount[nextPlayer] = 0;
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    
    cardEffect(tribute, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's hand should be unchanged\n");
    assert(state.handCount[thisPlayer], test.handCount[thisPlayer]);
    
    printf("Player's discard pile should be unchanged\n");
    assert(state.discardCount[thisPlayer], test.discardCount[thisPlayer]);
    
    printf("Player should have unchanged number of actions\n");
    assert(state.numActions, test.numActions);
    
    printf("Player's coins should be unchanged\n");
    assert(state.coins, test.coins);
    
    printf("Other player's discard count should be unchanged\n");
    assert(state.discardCount[nextPlayer], test.discardCount[nextPlayer]);
    
    printf("Other player's deck count should be unchanged\n");
    assert(state.deckCount[nextPlayer], test.deckCount[nextPlayer]);
    
    
    //Test 2: next player only has 1 card in discard pile
    printf("\nTest 2: Next player has 1 card in discard pile only (copper)\n");
    
    state.deckCount[nextPlayer] = 0;
    state.discardCount[nextPlayer] = 1;
    state.discard[nextPlayer][0] = copper;
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    
    cardEffect(tribute, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's hand should be decremented by 1\n");
    assert(state.handCount[thisPlayer] - 1, test.handCount[thisPlayer]);
    
    printf("Player's discard pile should be incremented by 1\n");
    assert(state.discardCount[thisPlayer] + 1, test.discardCount[thisPlayer]);
    
    printf("Player's top card in discard pile should be Tribute card\n");
    assert(tribute, test.discard[thisPlayer][test.discardCount[thisPlayer] - 1]);
    
    printf("Player should have unchanged number of actions\n");
    assert(state.numActions, test.numActions);
    
    printf("Player's coins should be incremented by 2\n");
    assert(state.coins + 2, test.coins);
    
    printf("Other player's discard count should be unchanged\n");
    assert(state.discardCount[nextPlayer], test.discardCount[nextPlayer]);
    
    printf("Other player's deck count should be unchanged\n");
    assert(state.deckCount[nextPlayer], test.deckCount[nextPlayer]);
    
    
    //Test 3: next player only has 1 card in deck
    printf("\nTest 3: Next player has 1 card in deck only (copper)\n");
    
    state.deckCount[nextPlayer] = 1;
    state.discardCount[nextPlayer] = 0;
    state.deck[nextPlayer][0] = copper;
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    
    cardEffect(tribute, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's hand should be decremented by 1\n");
    assert(state.handCount[thisPlayer] - 1, test.handCount[thisPlayer]);
    
    printf("Player's discard pile should be incremented by 1\n");
    assert(state.discardCount[thisPlayer] + 1, test.discardCount[thisPlayer]);
    
    printf("Player's top card in discard pile should be Tribute card\n");
    assert(tribute, test.discard[thisPlayer][test.discardCount[thisPlayer] - 1]);
    
    printf("Player should have unchanged number of actions\n");
    assert(state.numActions, test.numActions);
    
    printf("Player's coins should be incremented by 2\n");
    assert(state.coins + 2, test.coins);
    
    printf("Other player's discard count should be incremented by 1\n");
    assert(state.discardCount[nextPlayer] + 1, test.discardCount[nextPlayer]);
    
    printf("Other player's deck count should be decremented by 1\n");
    assert(state.deckCount[nextPlayer] - 1, test.deckCount[nextPlayer]);
    
    
    //Test 4: next player only has 1 card in deck and 1 card in discard
    printf("\nTest 4: Next player has 1 card in deck and 1 card in discard (copper and silver)\n");
    
    state.deckCount[nextPlayer] = 1;
    state.discardCount[nextPlayer] = 1;
    state.deck[nextPlayer][0] = copper;
    state.discard[nextPlayer][0] = silver;
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    
    cardEffect(tribute, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's hand should be decremented by 1\n");
    assert(state.handCount[thisPlayer] - 1, test.handCount[thisPlayer]);
    
    printf("Player's discard pile should be incremented by 1\n");
    assert(state.discardCount[thisPlayer] + 1, test.discardCount[thisPlayer]);
    
    printf("Player's top card in discard pile should be Tribute card\n");
    assert(tribute, test.discard[thisPlayer][test.discardCount[thisPlayer] - 1]);
    
    printf("Player should have unchanged number of actions\n");
    assert(state.numActions, test.numActions);
    
    printf("Player's coins should be incremented by 2\n");
    assert(state.coins + 4, test.coins);
    
    printf("Other player's discard count should be incremented by 1\n");
    assert(state.discardCount[nextPlayer] + 1, test.discardCount[nextPlayer]);
    
    printf("Other player's deck count should be decremented by 1\n");
    assert(state.deckCount[nextPlayer] - 1, test.deckCount[nextPlayer]);
    
    
    //Test 5: next player has 2 same treasure cards in deck
    printf("\nTest 5: Next player has 2 of the same treasure cards in deck\n");
    
    state.deckCount[nextPlayer] = 2;
    state.discardCount[nextPlayer] = 0;
    state.deck[nextPlayer][0] = copper;
    state.deck[nextPlayer][1] = copper;
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    
    cardEffect(tribute, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's hand should be decremented by 1\n");
    assert(state.handCount[thisPlayer] - 1, test.handCount[thisPlayer]);
    
    printf("Player's discard pile should be incremented by 1\n");
    assert(state.discardCount[thisPlayer] + 1, test.discardCount[thisPlayer]);
    
    printf("Player's top card in discard pile should be Tribute card\n");
    assert(tribute, test.discard[thisPlayer][test.discardCount[thisPlayer] - 1]);
    
    printf("Player should have unchanged number of actions\n");
    assert(state.numActions, test.numActions);
    
    printf("Player's coins should be incremented by 2\n");
    assert(state.coins + 2, test.coins);
    
    printf("Other player's discard count should be incremented by 2\n");
    assert(state.discardCount[nextPlayer] + 2, test.discardCount[nextPlayer]);
    
    printf("Other player's deck count should be decremented by 2\n");
    assert(state.deckCount[nextPlayer] - 2, test.deckCount[nextPlayer]);
    
    
    //Test 6: next player has 2 different treasure cards in deck
    printf("\nTest 6: Next player has 2 different treasure cards in deck\n");
    
    state.deckCount[nextPlayer] = 2;
    state.discardCount[nextPlayer] = 0;
    state.deck[nextPlayer][0] = copper;
    state.deck[nextPlayer][1] = silver;
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    
    cardEffect(tribute, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's hand should be decremented by 1\n");
    assert(state.handCount[thisPlayer] - 1, test.handCount[thisPlayer]);
    
    printf("Player's discard pile should be incremented by 1\n");
    assert(state.discardCount[thisPlayer] + 1, test.discardCount[thisPlayer]);
    
    printf("Player's top card in discard pile should be Tribute card\n");
    assert(tribute, test.discard[thisPlayer][test.discardCount[thisPlayer] - 1]);
    
    printf("Player should have unchanged number of actions\n");
    assert(state.numActions, test.numActions);
    
    printf("Player's coins should be incremented by 4\n");
    assert(state.coins + 4, test.coins);
    
    printf("Other player's discard count should be incremented by 2\n");
    assert(state.discardCount[nextPlayer] + 2, test.discardCount[nextPlayer]);
    
    printf("Other player's deck count should be decremented by 2\n");
    assert(state.deckCount[nextPlayer] - 2, test.deckCount[nextPlayer]);
    
    
    //Test 7: next player has 2 same victory cards in deck
    printf("\nTest 7: Next player has 2 of the same victory cards in deck\n");
    
    state.deckCount[nextPlayer] = 2;
    state.discardCount[nextPlayer] = 0;
    state.deck[nextPlayer][0] = estate;
    state.deck[nextPlayer][1] = estate;
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    
    cardEffect(tribute, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's hand should be incremented by 1 (played tribute, gained 2 cards)\n");
    assert(state.handCount[thisPlayer] + 1, test.handCount[thisPlayer]);
    
    printf("Player's discard pile should be incremented by 1\n");
    assert(state.discardCount[thisPlayer] + 1, test.discardCount[thisPlayer]);
    
    printf("Player's top card in discard pile should be Tribute card\n");
    assert(tribute, test.discard[thisPlayer][test.discardCount[thisPlayer] - 1]);
    
    printf("Player should have unchanged number of actions\n");
    assert(state.numActions, test.numActions);
    
    printf("Player's coins should be unchanged\n");
    assert(state.coins, test.coins);
    
    printf("Other player's discard count should be incremented by 2\n");
    assert(state.discardCount[nextPlayer] + 2, test.discardCount[nextPlayer]);
    
    printf("Other player's deck count should be decremented by 2\n");
    assert(state.deckCount[nextPlayer] - 2, test.deckCount[nextPlayer]);
    
    
    //Test 8: next player has 2 different victory cards in deck
    printf("\nTest 8: Next player has 2 different victory cards in deck\n");
    
    state.deckCount[nextPlayer] = 2;
    state.discardCount[nextPlayer] = 0;
    state.deck[nextPlayer][0] = estate;
    state.deck[nextPlayer][1] = duchy;
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    
    cardEffect(tribute, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's hand should be incremented by 3 (played tribute, gained 4 cards)\n");
    assert(state.handCount[thisPlayer] + 3, test.handCount[thisPlayer]);
    
    printf("Player's discard pile should be incremented by 1\n");
    assert(state.discardCount[thisPlayer] + 1, test.discardCount[thisPlayer]);
    
    printf("Player's top card in discard pile should be Tribute card\n");
    assert(tribute, test.discard[thisPlayer][test.discardCount[thisPlayer] - 1]);
    
    printf("Player should have unchanged number of actions\n");
    assert(state.numActions, test.numActions);
    
    printf("Player's coins should be unchanged\n");
    assert(state.coins, test.coins);
    
    printf("Other player's discard count should be incremented by 2\n");
    assert(state.discardCount[nextPlayer] + 2, test.discardCount[nextPlayer]);
    
    printf("Other player's deck count should be decremented by 2\n");
    assert(state.deckCount[nextPlayer] - 2, test.deckCount[nextPlayer]);
    
    
    //Test 9: next player has 2 same action cards in deck
    printf("\nTest 9: Next player has 2 of the same action cards in deck\n");
    
    state.deckCount[nextPlayer] = 2;
    state.discardCount[nextPlayer] = 0;
    state.deck[nextPlayer][0] = tribute;
    state.deck[nextPlayer][1] = tribute;
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    
    cardEffect(tribute, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's hand should be decremented by 1\n");
    assert(state.handCount[thisPlayer] - 1, test.handCount[thisPlayer]);
    
    printf("Player's discard pile should be incremented by 1\n");
    assert(state.discardCount[thisPlayer] + 1, test.discardCount[thisPlayer]);
    
    printf("Player's top card in discard pile should be Tribute card\n");
    assert(tribute, test.discard[thisPlayer][test.discardCount[thisPlayer] - 1]);
    
    printf("Player should have 2 more actions\n");
    assert(state.numActions + 2, test.numActions);
    
    printf("Player's coins should be unchanged\n");
    assert(state.coins, test.coins);
    
    printf("Other player's discard count should be incremented by 2\n");
    assert(state.discardCount[nextPlayer] + 2, test.discardCount[nextPlayer]);
    
    printf("Other player's deck count should be decremented by 2\n");
    assert(state.deckCount[nextPlayer] - 2, test.deckCount[nextPlayer]);
    
    
    //Test 9: next player has 2 same action cards in deck
    printf("\nTest 10: Next player has 2 different action cards in deck\n");
    
    state.deckCount[nextPlayer] = 2;
    state.discardCount[nextPlayer] = 0;
    state.deck[nextPlayer][0] = baron;
    state.deck[nextPlayer][1] = tribute;
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    
    cardEffect(tribute, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's hand should be decremented by 1\n");
    assert(state.handCount[thisPlayer] - 1, test.handCount[thisPlayer]);
    
    printf("Player's discard pile should be incremented by 1\n");
    assert(state.discardCount[thisPlayer] + 1, test.discardCount[thisPlayer]);
    
    printf("Player's top card in discard pile should be Tribute card\n");
    assert(tribute, test.discard[thisPlayer][test.discardCount[thisPlayer] - 1]);
    
    printf("Player should have 4 more action\n");
    assert(state.numActions + 4, test.numActions);
    
    printf("Player's coins should be unchanged\n");
    assert(state.coins, test.coins);
    
    printf("Other player's discard count should be incremented by 2\n");
    assert(state.discardCount[nextPlayer] + 2, test.discardCount[nextPlayer]);
    
    printf("Other player's deck count should be decremented by 2\n");
    assert(state.deckCount[nextPlayer] - 2, test.deckCount[nextPlayer]);
    
    
    //Test 11: next player has 2 different types of cards in deck
    printf("\nTest 11: Next player has 2 different types of cards in deck (treasure and action)\n");
    
    state.deckCount[nextPlayer] = 2;
    state.discardCount[nextPlayer] = 0;
    state.deck[nextPlayer][0] = copper;
    state.deck[nextPlayer][1] = tribute;
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    
    cardEffect(tribute, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's hand should be decremented by 1\n");
    assert(state.handCount[thisPlayer] - 1, test.handCount[thisPlayer]);
    
    printf("Player's discard pile should be incremented by 1\n");
    assert(state.discardCount[thisPlayer] + 1, test.discardCount[thisPlayer]);
    
    printf("Player's top card in discard pile should be Tribute card\n");
    assert(tribute, test.discard[thisPlayer][test.discardCount[thisPlayer] - 1]);
    
    printf("Player should have 2 more actions\n");
    assert(state.numActions + 2, test.numActions);
    
    printf("Player's coins should be incremented by 2\n");
    assert(state.coins + 2, test.coins);
    
    printf("Other player's discard count should be incremented by 2\n");
    assert(state.discardCount[nextPlayer] + 2, test.discardCount[nextPlayer]);
    
    printf("Other player's deck count should be decremented by 2\n");
    assert(state.deckCount[nextPlayer] - 2, test.deckCount[nextPlayer]);
    
    printf("\n----------------- End Testing Card: %s -----------------\n", TESTCARD);
    
    return 0;
}
