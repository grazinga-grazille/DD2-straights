#ifndef _HUMANPLAYER_H
#define _HUMANPLAYER_H

#include "player.h"

class HumanPlayer : public Player {
  public:
    HumanPlayer(std::string name, bool type);
    ~HumanPlayer();
    virtual void playCard(Card card, Table &table) override;
    virtual void discardCard(Card card) override;
};

#endif



