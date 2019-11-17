/*******************************
 CS 362 - Assignment 4
 Author: Kendrick Chu
 Date: 11/9/19
 Description: Random unit test for tribute card in dominion game.
 *****************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    srand(time(NULL));
    int i, j;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int thisPlayer = 0;
    int nextPlayer = thisPlayer + 1;
    
    struct gameState state, test;
    int k[10] = {adventurer, ambassador, duchy, gardens, mine, tribute, smithy, village, baron, estate};
    
    for(i = 0; i < 100; ++i) {
        //generate random number of players between 2 and 10
        int numPlayers = (rand() % (10 - 2 + 1)) + 2;
        
        //initialize game state and player cards
        initializeGame(numPlayers, k, seed, &state);
        
        printf("----------------- Testing Card: %s %d/100-----------------\n", TESTCARD, i + 1);
        
        //generate hand size of current player between 1 and 10
        state.handCount[thisPlayer] = (rand() % (10 - 1 + 1) + 1);
        state.hand[thisPlayer][0] = tribute;
        for(j = 1; j < state.handCount[thisPlayer]; ++j) {
            //get a random index of the cards in play in k
            int randomCard = rand() % 10;
            state.hand[thisPlayer][i] = k[randomCard];
        }
        int numTreasure = 0;
        int numAction = 0;
        int numVictory = 0;
        //set next player's deck count to be 0 to 2
        state.deckCount[nextPlayer] = rand() % 3;
        //randomize the careds in the next player's deck
        for(j = 0; j < state.deckCount[nextPlayer]; ++j) {
            int randomCard = rand() % 13;
            if(randomCard == 10) {
                state.deck[nextPlayer][j] = copper;
            }
            else if(randomCard == 11) {
                state.deck[nextPlayer][j] = silver;
            }
            else if(randomCard == 12) {
                state.deck[nextPlayer][j] = gold;
            }
            else {
                state.deck[nextPlayer][j] = k[randomCard];
            }
        }
        //if the next player has no cards in deck, randomize cards in discard between 0 to 2 cards
        //keep track of types of cards in next player's discard
        if(state.deckCount[nextPlayer] == 0) {
            state.discardCount[nextPlayer] = rand() % 3;
            for(j = 0; j < state.discardCount[nextPlayer]; ++j) {
                int randomCard = rand() % 13;
                if(randomCard == 10) {
                    state.discard[nextPlayer][j] = copper;
                    ++numTreasure;
                }
                else if(randomCard == 11) {
                    state.discard[nextPlayer][j] = silver;
                    ++numTreasure;
                }
                else if(randomCard == 12) {
                    state.discard[nextPlayer][j] = gold;
                    ++numTreasure;
                }
                else {
                    state.discard[nextPlayer][j] = k[randomCard];
                    if(state.discard[nextPlayer][j] == estate || state.discard[nextPlayer][j] == duchy) {
                        ++numVictory;
                    }
                    else {
                        ++numAction;
                    }
                }
            }
        }
        //if the next player has 1 card1 in deck, randomize cards in discard between 0 to 1 cards
        //keep track of types of cards in next player's discard and deck
        else if(state.deckCount[nextPlayer] == 1) {
            state.discardCount[nextPlayer] = rand() % 2;
            if(state.deck[nextPlayer][0] == copper || state.deck[nextPlayer][0] == silver || state.deck[nextPlayer][0] == gold) {
                ++numTreasure;
            }
            else if(state.deck[nextPlayer][0] == estate || state.deck[nextPlayer][0] == duchy) {
                ++numVictory;
            }
            else {
                ++numAction;
            }
            for(j = 0; j < state.discardCount[nextPlayer]; ++j) {
                int randomCard = rand() % 13;
                if(randomCard == 10) {
                    state.discard[nextPlayer][j] = copper;
                    ++numTreasure;
                }
                else if(randomCard == 11) {
                    state.discard[nextPlayer][j] = silver;
                    ++numTreasure;
                }
                else if(randomCard == 12) {
                    state.discard[nextPlayer][j] = gold;
                    ++numTreasure;
                }
                else {
                    state.discard[nextPlayer][j] = k[randomCard];
                    if(state.discard[nextPlayer][j] == estate || state.discard[nextPlayer][j] == duchy) {
                        ++numVictory;
                    }
                    else {
                        ++numAction;
                    }
                }
            }
        }
        //else the next player has no cards in discard
        //keep track of types of cards in next player's deck
        else {
            state.discardCount[nextPlayer] = 0;
            for(j = 0; j < state.deckCount[nextPlayer]; ++j) {
                if(state.deck[nextPlayer][j] == copper || state.deck[nextPlayer][j] == silver || state.deck[nextPlayer][j] == gold) {
                    ++numTreasure;
                }
                else if(state.deck[nextPlayer][j] == estate || state.deck[nextPlayer][j] == duchy) {
                    ++numVictory;
                }
                else {
                    ++numAction;
                }
            }
        }
        
        state.coins = rand() % 100;
        
        //copy the current game state to a test case
        memcpy(&test, &state, sizeof(struct gameState));
        
        cardEffect(tribute, choice1, choice2, choice3, &test, handpos, &bonus);
        
        if(state.deckCount[nextPlayer] == 0 && state.discardCount[nextPlayer] == 0) {
            printf("\nTest: Next player had no cards in deck and discard, current player's discarded pile should be unchanged\n");
            assert(state.discardCount[thisPlayer], test.discardCount[thisPlayer]);
        }
        else {
            printf("\nTest: Next player has cards, discard pile should be increased by 1 (tribute)\n");
            assert(state.discardCount[thisPlayer] + 1, test.discardCount[thisPlayer]);
            
            printf("\nTest: Current player's top card in discard should be tribute card\n");
            assert(tribute, test.discard[thisPlayer][test.discardCount[thisPlayer] - 1]);
            
            printf("\nTest: Next player's deck should be empty\n");
            assert(0, test.deckCount[nextPlayer]);
            
            printf("\nTest: Next player's discard pile should have all cards\n");
            assert(state.deckCount[nextPlayer] + state.discardCount[nextPlayer], test.discardCount[nextPlayer]);
            
            printf("\nTest: Current player's number of coins should be increased accordingly\n");
            assert(state.coins + (numTreasure * 2), test.coins);
            
            printf("\nTest: Current player's number of cards should be increased accordingly\n");
            assert(state.handCount[thisPlayer] + (numVictory * 2) - 1, test.handCount[thisPlayer]);
            
            printf("\nTest: Current player's number of actions should be incresaed accordingly\n");
            assert(state.numActions + (numAction * 2), test.numActions);
        }
    }
    
    printf("\n----------------- End Testing Card: %s -----------------\n", TESTCARD);
    
    return 0;
}
