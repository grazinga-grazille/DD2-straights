#include "table.h"
#include <algorithm>

Table::Table() 
    : tableCardsSpades{},
    tableCardsClubs{},
    tableCardsDiamonds{},
    tableCardsHearts{}
{}

Table::~Table() {
}

std::vector<Card *> Table::getSpadesList() { return tableCardsSpades; }

std::vector<Card *> Table::getClubsList() { return tableCardsClubs; }

std::vector<Card *> Table::getDiamondsList() { return tableCardsDiamonds; }

std::vector<Card *> Table::getHeartsList() { return tableCardsHearts; }

bool Table::myfunction (Card* card1, Card* card2) { return (card1->getRankNumber() < card2->getRankNumber()); }

std::vector<Card *> Table::sortList(std::vector<Card *>myVector) {
    std::sort(myVector.begin(), myVector.end(), myfunction);
    return myVector;
}

bool Table::isEmpty() { 
    return (tableCardsClubs.size() == 0 && tableCardsDiamonds.size() == 0 && 
            tableCardsHearts.size() == 0 && tableCardsSpades.size() == 0);
}
void Table::placeCardSpades(Card *card) {
    tableCardsSpades.push_back(card);
}

void Table::placeCardClubs(Card *card) {
    tableCardsClubs.push_back(card);
}

void Table::placeCardDiamonds(Card *card) {
    tableCardsDiamonds.push_back(card);
}

void Table::placeCardHearts(Card *card) {
    tableCardsHearts.push_back(card);
}

void Table::clearTable() {
    tableCardsSpades.clear();
    tableCardsClubs.clear();
    tableCardsDiamonds.clear();
    tableCardsHearts.clear();
}

std::string Table::getCardsString(std::vector<Card *> card_vec) {
    std::string new_str;
    for (unsigned int i = 0; i < card_vec.size(); ++i) {
        new_str+=card_vec.at(i)->getRankString()+= " ";
    }
    return new_str;
}

void Table::print() {
    std::cout << "Cards on table:" << std::endl;
    std::cout << "Clubs: " << getCardsString(sortList(tableCardsClubs)) << std::endl;
    std::cout << "Diamonds: " << getCardsString(sortList(tableCardsDiamonds)) << std::endl;
    std::cout << "Hearts: " << getCardsString(sortList(tableCardsHearts)) << std::endl;
    std::cout << "Spades: " << getCardsString(sortList(tableCardsSpades)) << std::endl;
}


