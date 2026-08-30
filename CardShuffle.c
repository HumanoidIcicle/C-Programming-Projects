#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DECK_SIZE 52
#define CARDS 13
#define SUITS 4

// Struct to represent a card
typedef struct {
    unsigned short int rank: 4, // 0-12 (2-10, J, Q, K, A)
                        suit:4 ; // 0-3 (Hearts, Diamonds, Clubs, Spades)
} Card;

// Function to get rank name
const char* get_rank_name(unsigned short int rank) {
    static const char *ranks[] = {"A", "2","3","4","5","6","7","8","9",
        "10","J","Q","K"};
    return ranks[rank];
}

// Function to get suit name
const char* get_suit_name(unsigned short int suit) {
    static const char* suits[] = {"Hearts","Diamonds","Clubs","Spades"};
    return suits[suit];
}

// Function to fill the deck
void fill_deck(Card deck[]) {
    int card = 0; // index into the deck
    for (int rank = 0; rank < CARDS; rank++) {
        for (int suit = 0; suit < SUITS; suit++) {
            Card tcard;
            tcard.rank = rank;
            tcard.suit = suit;
            deck[card++] = tcard; // move to next card
        }
    }
}

// Function to shuffle the deck
void shuffle_deck(Card deck[]) {
    for (int i = DECK_SIZE-1; i > 0; i--) {
        int j = rand() %(i+1);
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

// Function to print the deck
void print_deck(Card deck[]) {
    for (int i = 0; i<DECK_SIZE-1;i++) {
        printf("%s of %s\n", get_rank_name(deck[i].rank),
            get_suit_name(deck[i].suit));
    }
}

int main() {
    Card deck[DECK_SIZE]; // Declare an array of 52 cards
    srand(time(NULL));

    // Fill the deck
    fill_deck(deck);
    printf("Original Deck:\n");
    print_deck(deck);

    // Shuffle the deck
    shuffle_deck(deck);
    printf("\nShuffled Deck:\n");
    print_deck(deck);

    return 0;
}

