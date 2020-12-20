#ifndef _PLAYER_H
#define _PLAYER_H

#include <vector>
#include "card.h"
#include "table.h"

class Player {
  protected:
    std::string name;
    bool type; // true for human and false for computer
    std::vector<Card *> playerHand;
    std::vector<Card *> playerDiscards;
    std::vector<Card *> legalCards;
    bool handEmpty;
  public:
    Player(std::string name, bool type);
    ~Player();
    std::string getName();
    bool getType();
    std::vector<Card *> getPlayerHand();
    std::vector<Card *> getPlayerDiscards();
    std::vector<Card *> getLegalCards();
    void setType(bool val);
    void setLegalCards(std::vector<Card *> vec);
    int recalculateScore();
    void addCard(Card *card);
    void deleteCardfromHand(Card *card);
    void clearDiscards();
    std::string printHand();
    std::string printDiscards();
    std::string printLegalCards();
    virtual void playCard(Card card, Table &table) = 0; 
    virtual void discardCard(Card card) = 0; 
};

#endif

