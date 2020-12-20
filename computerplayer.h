#ifndef _COMPUTERPLAYER_H
#define _COMPUTERPLAYER_H

#include "player.h"

class ComputerPlayer : public Player {
  public:
    ComputerPlayer(std::string name, bool type);
    ComputerPlayer(const Player &other);
    ~ComputerPlayer();
    virtual void playCard(Card card, Table &table) override;
    virtual void discardCard(Card card) override;
};

#endif
