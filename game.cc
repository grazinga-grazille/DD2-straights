#include "game.h"
#include <string>
#include <algorithm>
#include <numeric>
#include <chrono>

Game::Game() :
    deck{},
    table{},
    playersList{},
    playersScore{ 0,0,0,0 }
{}

Game::~Game() {
    removePlayers();
}

Deck &Game::getDeck() { return deck; }

Table &Game::getTable() { return table; }

int Game::getStartingPlayer() { return starting_player; }

int Game::getCurrentPlayer() { return current_player; }

int Game::getHighestScore() { return highestScore; }

bool Game::getLegalExists() { return legalExists; }

bool Game::handEmpty() { return (playersList[current_player]->getPlayerHand().size() == 0); }

std::vector<Player *> Game::getPlayersList() { return playersList; }

std::vector<int> Game::getPlayersScore() { return playersScore; }

bool Game::getGameOver() { return gameOver; }

void Game::nextPlayer() { 
    if (current_player == 3) {
        current_player = 0;
    } else {
        current_player+=1;
    }
    std::cout << std::endl;
    if (playersList.at(current_player)->getPlayerHand().size() == 0) return;
    std::cout << "It's " << playersList.at(current_player)->getName() << "'s turn to play." << std::endl;
    table.print();
    addLegal(playersList.at(current_player));
    std::cout << "Your Hand: ";
    for (unsigned int i = 0; i < playersList.at(current_player)->getPlayerHand().size(); ++i) {
        std::cout << *(playersList.at(current_player)->getPlayerHand().at(i)) << " ";
    }
    std::cout << std::endl;
    std::cout << "Legal Plays:" << playersList.at(current_player)->printLegalCards() << std::endl;
    legalExists = false;
}

void Game::deal(unsigned int seed) {
    deck.setSeed(seed);
    deck.shuffle();
    std::vector<Card *> shuffled_deck = this->deck.getMyDeck();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 13; ++j) {
            playersList.at(i)->addCard(shuffled_deck.at(i*13+j));
        }
    }
    // find who has 7S
    Card seven_spades = Card(Suit::SPADES, Rank::SEVEN);
    for (int i = 0; i < 4; ++i) {
        Player *thePlayer = playersList.at(i);
        for (unsigned int j = 0; j < thePlayer->getPlayerHand().size(); ++j) {
            if (*thePlayer->getPlayerHand().at(j) == seven_spades) {
                starting_player = i;
                current_player = i;
                break;
            }
        }       
    }
}

void Game::addLegal(Player *thePlayer) {
    std::vector<Card *> playerCards = thePlayer->getPlayerHand();
    std::vector<Card *> legalCards;
    for (unsigned int i = 0; i < playerCards.size(); ++i) {
        std::vector<Card *> correct_pile;
        if (playerCards.at(i)->getSuit() == Suit::SPADES) {
            correct_pile = table.getSpadesList();
        } else if (playerCards.at(i)->getSuit() == Suit::CLUBS) {
            correct_pile = table.getClubsList();
        } else if (playerCards.at(i)->getSuit() == Suit::DIAMONDS) {
            correct_pile = table.getDiamondsList();
        } else if (playerCards.at(i)->getSuit() == Suit::HEARTS) {
            correct_pile = table.getHeartsList();
        }
        for (unsigned int k = 0; k < correct_pile.size(); ++k) {
            int theRank = correct_pile.at(k)->getRankNumber(); // table card rank
            int comp_rank = playerCards.at(i)->getRankNumber(); // player hand rank
            if ((comp_rank == theRank - 1) || (comp_rank == theRank + 1)) {
                legalCards.push_back(playerCards.at(i));
            }
            if (comp_rank == 7) {
                legalCards.push_back(playerCards.at(i));
            }
        }
        if (table.isEmpty() == true) {
            if (playerCards.at(i)->getRank() == Rank::SEVEN && 
            playerCards.at(i)->getSuit() == Suit::SPADES) {
                legalCards.push_back(playerCards.at(i));
            }
        } else if (correct_pile.size() == 0) {
            if (playerCards.at(i)->getRank() == Rank::SEVEN) {
                legalCards.push_back(playerCards.at(i));
            }
        }   
    }
    thePlayer->setLegalCards(legalCards);
    if (legalCards.size() == 0) {
        legalExists = false;
    } else {
        legalExists = true;
    }
} 

bool Game::playTurn(Card card, bool h_or_c) {
    Player *player_cur = playersList[current_player];
    addLegal(player_cur);
    bool val;
    if (legalExists == true) {
        if (h_or_c == true) {
            bool val1 = false;
            for (unsigned int i = 0; i < playersList.at(current_player)->getLegalCards().size(); ++i) {
                if (card == *playersList.at(current_player)->getLegalCards().at(i)) {
                    val1 = true;
                    break;
                }
            }
            if (val1 == false) return false;
        }
        playersList[current_player]->playCard(card, table);
        successfulPlay = true;
        successfulDiscard = false;
        val = true;
    } else if (legalExists == false) {
        val = false;
    }
    return val;
}

bool Game::discardTurn(Card card, bool h_or_c) {
    Player *player_cur = playersList[current_player];
    addLegal(player_cur);
    bool val;
    if (legalExists == true) {
        val = false;
    } else if (legalExists == false) {
        if (h_or_c == true) {
            bool val1 = true;
            for (unsigned int i = 0; i < playersList.at(current_player)->getPlayerHand().size(); ++i) {
                if (card == *playersList.at(current_player)->getPlayerHand().at(i)) {
                    val1 = false;
                    break;
                }
            }
            if (val1 == true) throw InvalidDiscardCardException{};
        }
        playersList[current_player]->discardCard(card);
        successfulDiscard = true;
        successfulPlay = false;
        val = true;
    }
    return val;
}

void Game::beginNewRound(unsigned int seed) {
    table.clearTable();
    deal(seed);
    std::cout << "A new round begins. It's " << playersList.at(starting_player)->getName() << "'s turn to play." << std::endl;
    table.print();
    addLegal(playersList.at(starting_player));
    std::cout << "Your Hand: ";
    for (unsigned int i = 0; i < playersList.at(current_player)->getPlayerHand().size(); ++i) {
        std::cout << *(playersList.at(current_player)->getPlayerHand().at(i)) << " ";
    }
    std::cout << std::endl;
    std::cout << "Legal Plays:" << playersList.at(starting_player)->printLegalCards() << std::endl;
}

void Game::recalculateAllScores() {
    for (unsigned int i = 0; i < 4; ++i) {
        int val = playersScore.at(i) + playersList.at(i)->recalculateScore();
        if (val >= 80) {
            gameOver = true;
            return;
        }
        playersScore.at(i)+=playersList.at(i)->recalculateScore();
    }
    auto it = std::max_element(std::begin(playersScore), std::end(playersScore));
    highestScore = *it;
}

void Game::addPlayers(bool playerType, std::string name) {
    assert(playerType == true || playerType == false);
    if (playerType == true) { // human
        Player *new_player = new HumanPlayer(name, true);
        playersList.push_back(new_player);
    } else if (playerType == false) { // computer
        Player *new_player = new ComputerPlayer(name, false);
        playersList.push_back(new_player);
    }
}

void Game::removePlayers() {
    for (unsigned int i = 0; i < playersList.size(); ++i) {
        delete playersList.at(i);
    }
    playersList.clear();
}

void Game::clearAllDiscards() {
    for (unsigned int i = 0; i < 4; ++i) {
        playersList.at(i)->clearDiscards();
    }
}

void Game::ragequit() {
    std::cout << "" << playersList[current_player]->getName() << " ragequits. A computer will take over." << std::endl;
    Player *new_player = new ComputerPlayer(*playersList[current_player]);
    delete playersList.at(current_player);
    playersList.at(current_player) = new_player;
    new_player->setType(false); 
}

void Game::printMessage() {
    if (successfulPlay == true) {
        std::cout << "" << playersList.at(current_player)->getName() << " plays ";
    } else if (successfulDiscard == true) {
        std::cout << "" << playersList.at(current_player)->getName() << " discards ";
    }
}
