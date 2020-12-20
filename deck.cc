#include "deck.h"
#include <algorithm>
#include <random>

Deck::Deck() : theDeck{} 
{
    for (int i = 0; i < 4; ++i) {
        for (int k = 0; k < 13; ++k) {
            theDeck.emplace_back(new Card{ (Suit) i, (Rank) k});
        }
    }
}

Deck::~Deck() {
    for (unsigned int i = 0; i < theDeck.size(); ++i) {
        delete theDeck.at(i);
    }
    theDeck.clear();
}

std::vector<Card *> Deck::getMyDeck() {
    return theDeck;
}

void Deck::setSeed(unsigned int seed) { new_seed = seed; }

void Deck::shuffle() {
    std::default_random_engine rng{ new_seed };
	for ( int i = 0; i < 1000; i++ ) {
		std::shuffle( theDeck.begin(), theDeck.end(), rng );		
	}
}

void Deck::print() {
    for (unsigned int i = 0; i < theDeck.size(); ++i) {
        if (i == 12) {
            std::cout << *theDeck.at(i) << std::endl;
        } else if (i == 25) {
            std::cout << *theDeck.at(i) << std::endl;
        } else if (i == 38) {
            std::cout << *theDeck.at(i) << std::endl;
        } else if (i == 51) {
            std::cout << *theDeck.at(i) << std::endl;
        } else {
            std::cout << *theDeck.at(i) << " ";
        }
    }
}

