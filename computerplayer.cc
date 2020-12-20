#include "computerplayer.h"
#include <algorithm>

ComputerPlayer::ComputerPlayer(std::string name, bool type) 
    : Player(name, type)
{}

ComputerPlayer::~ComputerPlayer() { 
}

ComputerPlayer::ComputerPlayer(const Player &other) : Player(other)
{}

void ComputerPlayer::playCard(Card card, Table &table) {
    for (unsigned int i = 0; i < playerHand.size(); ++i) {
        if (*playerHand.at(i) == *legalCards.at(0)) {
            if (playerHand.at(i)->getSuit() == Suit::SPADES) {
                table.placeCardSpades(playerHand.at(i));
            } else if (playerHand.at(i)->getSuit() == Suit::DIAMONDS) {
                table.placeCardDiamonds(playerHand.at(i));
            } else if (playerHand.at(i)->getSuit() == Suit::CLUBS) {
                table.placeCardClubs(playerHand.at(i));
            } else if (playerHand.at(i)->getSuit() == Suit::HEARTS) {
                table.placeCardHearts(playerHand.at(i));
            }
            deleteCardfromHand(playerHand.at(i));
            break;
        }
    }
}

void ComputerPlayer::discardCard(Card card) {
    playerDiscards.insert(playerDiscards.begin(), playerHand.at(0));
    deleteCardfromHand(playerHand.at(0));
}












