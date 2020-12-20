#ifndef _GAME_H
#define _GAME_H

#include "deck.h"
#include "player.h"
#include <cassert>
#include "card.h"
#include "table.h"
#include <vector>
#include <iostream>
#include "humanplayer.h"
#include "computerplayer.h"


class Game {
    Deck deck;
    Table table;
    std::vector<Player *> playersList;
    std::vector<int> playersScore;
  public:
    Game();
    ~Game();
    void deal(unsigned int seed);
    Table &getTable();
    Deck &getDeck();
    std::vector<Player *> getPlayersList();
    std::vector<int> getPlayersScore();
    int getStartingPlayer();
    int getHighestScore();
    int getCurrentPlayer();
    bool getLegalExists();
    bool handEmpty();
    void nextPlayer();
    void addPlayers(bool playerType, std::string name); // true for Human and false for Computer
    void removePlayers();
    void ragequit();
    void addLegal(Player *thePlayer);
    bool playTurn(Card card, bool h_or_c); // returns true if play was successful
    bool discardTurn(Card card, bool h_or_c); // returns true if discard was successful
    void clearAllDiscards();
    void recalculateAllScores();
    void printMessage();
    void beginNewRound(unsigned int seed); // reset everything
    bool getGameOver();
  private:
    int starting_player; // player that starts the game with 7S
    int current_player;
    bool legalExists;
    int highestScore = 0; 
    bool successfulPlay = false; // determines what message needs to be printed after a card is played
    bool successfulDiscard = false; // determines what message needs to be printed after a card is played
    bool gameOver = false;
};

class InvalidDiscardCardException{};

#endif
