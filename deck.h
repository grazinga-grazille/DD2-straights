#ifndef _DECK_H
#define _DECK_H

#include "deck.h"
#include <vector>
#include "card.h"
#include <iostream>


class Deck {
    std::vector<Card *> theDeck;
    unsigned int new_seed;
  public:
    Deck();
    ~Deck();
    void setSeed(unsigned int seed);
    std::vector<Card *> getMyDeck();
    void shuffle();
    void print();
};

#endif
