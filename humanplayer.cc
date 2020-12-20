#include "humanplayer.h"

HumanPlayer::HumanPlayer(std::string name, bool type) 
    : Player(name, type)
{}

HumanPlayer::~HumanPlayer() {
}

void HumanPlayer::playCard(Card card, Table &table) {
    for (unsigned int i = 0; i < playerHand.size(); ++i) {
        if (*playerHand.at(i) == card) {
            if (card.getSuit() == Suit::SPADES) {
                table.placeCardSpades(playerHand.at(i));
                deleteCardfromHand(playerHand.at(i));
            } else if (card.getSuit() == Suit::DIAMONDS) {
                table.placeCardDiamonds(playerHand.at(i));
                deleteCardfromHand(playerHand.at(i));
            } else if (card.getSuit() == Suit::CLUBS) {
                table.placeCardClubs(playerHand.at(i));
                deleteCardfromHand(playerHand.at(i));
            } else if (card.getSuit() == Suit::HEARTS) {
                table.placeCardHearts(playerHand.at(i));
                deleteCardfromHand(playerHand.at(i));
            }
        }
    }
}

void HumanPlayer::discardCard(Card card) {
    for (unsigned int i = 0; i < playerHand.size(); ++i) {
        if (*playerHand.at(i) == card) {
            playerDiscards.push_back(playerHand.at(i));
            deleteCardfromHand(playerHand.at(i));
        }
    }
}
