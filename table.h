#ifndef _TABLE_H
#define _TABLE_H

#include "card.h"
#include <vector>
#include <iostream>

class Table {
    std::vector<Card *> tableCardsSpades;
    std::vector<Card *> tableCardsClubs;
    std::vector<Card *> tableCardsDiamonds;
    std::vector<Card *> tableCardsHearts;
  public:
    Table();
    ~Table();
    std::vector<Card *> getSpadesList();
    std::vector<Card *> getClubsList();
    std::vector<Card *> getDiamondsList();
    std::vector<Card *> getHeartsList();
    bool isEmpty();
    void placeCardSpades(Card *card);
    void placeCardClubs(Card *card);
    void placeCardDiamonds(Card *card);
    void placeCardHearts(Card *card);
    void clearTable();
    void print();
  private:
    std::string getCardsString(std::vector<Card *> card_vec);
    static bool myfunction (Card *card1, Card *card2);
    std::vector<Card *> sortList(std::vector<Card *>myVector);
};

#endif
