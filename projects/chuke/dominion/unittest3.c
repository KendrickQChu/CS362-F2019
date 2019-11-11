/*******************************
 CS 362 - Assignment 3
 Author: Kendrick Chu
 Date: 11/9/19
 Description: Unit test for ambassador card in dominion game.
 *****************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define TESTCARD "ambassador"

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
    int k[10] = {adventurer, ambassador, feast, gardens, mine, remodel, smithy, village, baron, estate};
    
    //initialize game state and player cards
    initializeGame(numPlayers, k, seed, &state);
    state.hand[thisPlayer][0] = ambassador;
    state.hand[thisPlayer][1] = state.hand[thisPlayer][2] = state.hand[thisPlayer][3] = copper;
    state.hand[thisPlayer][4] = silver;
    
    handpos = 0;
    printf("----------------- Testing Card: %s -----------------\n", TESTCARD);
    
    //Test 1: try to return played ambassador card to supply
    printf("\nTest 1: Player tries to return played ambassador card to supply\n\n");
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    
    //player chooses to return played ambassador card
    choice1 = handpos;
    choice2 = 1;
    int chosenCard = test.hand[thisPlayer][choice1];
    
    cardEffect(ambassador, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's hand should be unchanged\n");
    assert(state.handCount[thisPlayer], test.handCount[thisPlayer]);
    
    printf("Player's discard pile should be unchanged\n");
    assert(state.discardCount[thisPlayer], test.discardCount[thisPlayer]);
    
    printf("Other player's hand should be unchanged\n");
    assert(state.handCount[1], test.handCount[1]);
    
    printf("Other player's discard pile should be unchanged\n");
    assert(state.discardCount[1], test.discardCount[1]);
    
    printf("Ambassador count in supply should be unchanged\n");
    assert(state.supplyCount[chosenCard], test.supplyCount[chosenCard]);
    
    
    //Test 2: try to return more than 2 cards to supply
    printf("\nTest 2: Player tries to return more than 2 cards to supply\n\n");
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    
    //player chooses to return copper card
    choice1 = 1;
    choice2 = 3;
    chosenCard = test.hand[thisPlayer][choice1];
    
    cardEffect(ambassador, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's hand should be unchanged\n");
    assert(state.handCount[thisPlayer], test.handCount[thisPlayer]);
    
    printf("Player's discard pile should be unchanged\n");
    assert(state.discardCount[thisPlayer], test.discardCount[thisPlayer]);
    
    printf("Other player's hand should be unchanged\n");
    assert(state.handCount[1], test.handCount[1]);
    
    printf("Other player's discard pile should be unchanged\n");
    assert(state.discardCount[1], test.discardCount[1]);
    
    printf("Chosen card's count in supply should be unchanged\n");
    assert(state.supplyCount[chosenCard], test.supplyCount[chosenCard]);
    
    
    //Test 3: try to return more copies than player has in hand
    printf("\nTest 3: Player tries to return more copies than available in hand\n\n");
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    
    //player chooses to return silver card
    choice1 = 4;
    choice2 = 2;
    chosenCard = test.hand[thisPlayer][choice1];
    
    cardEffect(ambassador, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's hand should be unchanged\n");
    assert(state.handCount[thisPlayer], test.handCount[thisPlayer]);
    
    printf("Player's discard pile should be unchanged\n");
    assert(state.discardCount[thisPlayer], test.discardCount[thisPlayer]);
    
    printf("Other player's hand should be unchanged\n");
    assert(state.handCount[1], test.handCount[1]);
    
    printf("Other player's discard pile should be unchanged\n");
    assert(state.discardCount[1], test.discardCount[1]);
    
    printf("Chosen card's count in supply should be unchanged\n");
    assert(state.supplyCount[chosenCard], test.supplyCount[chosenCard]);
    
    
    //Test 4: return 0 copies of card and other player's gain card
//    printf("\nTest 4: Player returns 0 copies of revealed card, other players gain revealed card to hand\n\n");
//
//    //copy the current game state to a test case
//    memcpy(&test, &state, sizeof(struct gameState));
//
//    //player chooses to return played ambassador card
//    choice1 = 1;
//    choice2 = 0;
//    int chosenCard = test->hand[thisPlayer][choice1];
//
//    cardEffect(ambassador, choice1, choice2, choice3, &test, handpos, &bonus);
//
//    printf("Player's hand should be unchanged\n");
//    assert(state.handCount[thisPlayer], test.handCount[thisPlayer]);
//
//    printf("Player's discard pile should be incremented by 1\n");
//    assert(state.discardCount[thisPlayer] + 1, test.discardCount[thisPlayer]);
//
//    printf("Player's top card in discard pile should be Ambassador card\n");
//    assert(ambassador, test.discard[thisPlayer][test.discardCount[thisPlayer] - 1]);
//
//    printf("Other player's hand should be incremented by 1\n");
//    assert(state.handCount[1] + 1, test.handCount[1]);
//
//    printf("Other player's last card in hand should be chosen card\n");
//    assert(chosenCard, test.hand[1][test.handCount[1] - 1]);
//
//    printf("Other player's discard pile should be unchanged\n");
//    assert(state.discardCount[1], test.discardCount[1]);
//
//    printf("Chosen card's count in supply should be unchanged\n");
//    assert(state.supplyCount[chosenCard], test.supplyCount[chosenCard]);
    
    
    //Test 4: return 1 copy of card and other player's gain card
    printf("\nTest 4: Player returns 1 copy of revealed card, other players gain revealed card to hand\n\n");
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
       
    //player chooses to return copper card
    choice1 = 1;
    choice2 = 1;
    chosenCard = test.hand[thisPlayer][choice1];
       
    cardEffect(ambassador, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's hand should be decremented by 2\n");
    assert(state.handCount[thisPlayer] - 2, test.handCount[thisPlayer]);
    
    printf("Player's discard pile should be incremented by 1\n");
    assert(state.discardCount[thisPlayer] + 1, test.discardCount[thisPlayer]);
    
    printf("Player's top card in discard pile should be Ambassador card\n");
    assert(ambassador, test.discard[thisPlayer][test.discardCount[thisPlayer] - 1]);
    
    printf("Other player's hand should be unchanged\n");
    assert(state.handCount[1], test.handCount[1]);
    
    printf("Other player's discard pile should be incremented by 1\n");
    assert(state.discardCount[1] + 1, test.discardCount[1]);
    
    printf("Chosen card's count in supply should be unchanged(1 returned, 1 gained)\n");
    assert(state.supplyCount[chosenCard], test.supplyCount[chosenCard]);
    
    
    //Test 5: return 2 copies of card and other player's gain card
    printf("\nTest 5: Player returns 2 copies of revealed card, other players gain revealed card to hand\n\n");
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
       
    //player chooses to return copper card
    choice1 = 1;
    choice2 = 2;
    chosenCard = test.hand[thisPlayer][choice1];
       
    cardEffect(ambassador, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's hand should be decremented by 3\n");
    assert(state.handCount[thisPlayer] - 3, test.handCount[thisPlayer]);
    
    printf("Player's discard pile should be incremented by 1\n");
    assert(state.discardCount[thisPlayer] + 1, test.discardCount[thisPlayer]);
    
    printf("Player's top card in discard pile should be Ambassador card\n");
    assert(ambassador, test.discard[thisPlayer][test.discardCount[thisPlayer] - 1]);
    
    printf("Other player's hand should be unchanged\n");
    assert(state.handCount[1], test.handCount[1]);
    
    printf("Other player's discard pile should be incremented by 1\n");
    assert(state.discardCount[1] + 1, test.discardCount[1]);
    
    printf("Chosen card's count in supply should be incremented by 1 (2 returned, 1 gained)\n");
    assert(state.supplyCount[chosenCard] + 1, test.supplyCount[chosenCard]);
    
    
    //Test 6: return all copies of card and other player's gain card
    printf("\nTest 6: Player returns all copies of revealed card (including revealed card), other players gain revealed card to hand\n\n");
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
       
    //player chooses to return silver card
    choice1 = 4;
    choice2 = 1;
    chosenCard = test.hand[thisPlayer][choice1];
       
    cardEffect(ambassador, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's hand should be decremented by 2\n");
    assert(state.handCount[thisPlayer] - 2, test.handCount[thisPlayer]);
    
    printf("Player's discard pile should be incremented by 1\n");
    assert(state.discardCount[thisPlayer] + 1, test.discardCount[thisPlayer]);
    
    printf("Player's top card in discard pile should be Ambassador card\n");
    assert(ambassador, test.discard[thisPlayer][test.discardCount[thisPlayer] - 1]);
    
    printf("Other player's hand should be unchanged\n");
    assert(state.handCount[1], test.handCount[1]);
    
    printf("Other player's discard pile should be incremented by 1\n");
    assert(state.discardCount[1] + 1, test.discardCount[1]);
    
    printf("Chosen card's count in supply should be unchanged (1 returned, 1 gained)\n");
    assert(state.supplyCount[chosenCard], test.supplyCount[chosenCard]);
    
    printf("\n----------------- End Testing Card: %s -----------------\n", TESTCARD);
    
    return 0;
}
