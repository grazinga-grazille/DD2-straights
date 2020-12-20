#include "player.h"

Player::Player(std::string name, bool type)
    : name{ name },
    type{ type },
    playerHand{},
    playerDiscards{},
    legalCards{}
{}

Player::~Player() {
}

std::string Player::getName() { return name; }

bool Player::getType() { return type; }

std::vector<Card *> Player::getPlayerHand() { return playerHand; }

std::vector<Card *> Player::getPlayerDiscards() { return playerDiscards; }

std::vector<Card *> Player::getLegalCards() { return legalCards; }

void Player::clearDiscards() { playerDiscards.clear(); }

void Player::setType(bool val) { type = val; }

void Player::setLegalCards(std::vector<Card *> vec) {
    legalCards.clear();
    for (unsigned int i = 0; i < vec.size(); ++i) {
        legalCards.push_back(vec.at(i));
    }
}

int Player::recalculateScore() {
    int val = 0;
    for (unsigned int i = 0; i < playerDiscards.size(); ++i) {
        val+=playerDiscards.at(i)->getRankNumber();
    }
    return val;
}

void Player::addCard(Card *card) { playerHand.push_back(card); }

void Player::deleteCardfromHand(Card *card) {
    for (unsigned int i = 0; i < playerHand.size(); ++i) {
        if (*playerHand.at(i) == *card) {
            playerHand.erase(playerHand.begin()+i);
        }
    }
}

std::string Player::printHand() {
    std::string new_str;
    for (unsigned int i = 0; i < playerHand.size(); ++i) {
        new_str+=" ";
        new_str+=playerHand.at(i)->getRankString()+=playerHand.at(i)->getSuitString();
    }
    return new_str;
}

std::string Player::printDiscards() {
    std::string new_str;
    for (unsigned int i = 0; i < playerDiscards.size(); ++i) {
        new_str+=" ";
        new_str+=playerDiscards.at(i)->getRankString()+=playerDiscards.at(i)->getSuitString();
    }
    return new_str;
}

std::string Player::printLegalCards() {
    std::string new_str;
    for (unsigned int i = 0; i < legalCards.size(); ++i) {
        new_str+=" ";
        new_str+=legalCards.at(i)->getRankString()+=legalCards.at(i)->getSuitString();
    }
    return new_str;
}


