#include "card.h"
#include <cassert>

Card::Card():
    suit{ Suit::CLUBS },
    rank{ Rank::ACE }
{}

Card::Card(Suit suit, Rank rank) 
    : suit{ suit },
    rank{ rank }
{}

Suit Card::getSuit() const {
    return suit;
}

std::string Card::getSuitString() const {
    std::string str;
    if (suit == Suit::CLUBS) {
        str = "C";
    } else if (suit == Suit::DIAMONDS) {
        str = "D";
    } else if (suit == Suit::SPADES) {
        str = "S";
    } else {
        str = "H";
    }
    return str;
}

Rank Card::getRank() const {
    return rank;
}

std::string Card::getRankString() const {
    std::string str;
    if (rank == Rank::ACE) {
        str = "A";
    } else if (rank == Rank::TWO) {
        str = "2";
    } else if (rank == Rank::THREE) {
        str = "3";
    } else if (rank == Rank::FOUR) {
        str = "4";
    } else if (rank == Rank::FIVE) {
        str = "5";
    } else if (rank == Rank::SIX) {
        str = "6";
    } else if (rank == Rank::SEVEN) {
        str = "7";
    } else if (rank == Rank::EIGHT) {
        str = "8";
    } else if (rank == Rank::NINE) {
        str = "9";
    } else if (rank == Rank::TEN) {
        str = "T";
    } else if (rank == Rank::JACK) {
        str = "J";
    } else if (rank == Rank::QUEEN) {
        str = "Q";
    } else if (rank == Rank::KING) {
        str = "K";
    }
    return str;
}

int Card::getRankNumber() const {
    int num;
    if (rank == Rank::ACE) {
        num = 1;
    } else if (rank == Rank::TWO) {
        num = 2;
    } else if (rank == Rank::THREE) {
        num = 3;
    } else if (rank == Rank::FOUR) {
        num = 4;
    } else if (rank == Rank::FIVE) {
        num = 5;
    } else if (rank == Rank::SIX) {
        num = 6;
    } else if (rank == Rank::SEVEN) {
        num = 7;
    } else if (rank == Rank::EIGHT) {
        num = 8;
    } else if (rank == Rank::NINE) {
        num = 9;
    } else if (rank == Rank::TEN) {
        num = 10;
    } else if (rank == Rank::JACK) {
        num = 11;
    } else if (rank == Rank::QUEEN) {
        num = 12;
    } else if (rank == Rank::KING) {
        num = 13;
    }
    return num;
}

std::ostream &operator<<(std::ostream &out, const Card &card) {
    out << card.getRankString() << card.getSuitString();
    return out;
}

bool operator==(const Card &card1, const Card &card2) {
    return ((card1.getSuitString().compare(card2.getSuitString()) == 0) && 
    (card1.getRankString().compare(card2.getRankString()) == 0));
}

std::istream &operator>>(std::istream &in, Card &card) {
    std::string ranks = "A23456789TJQK";
    std::string suits = "CSHD";
    std::string str;
	in >> str;
	assert ( !in.fail() );
	
	// Ensuring rank is valid
    if (ranks.find( str.at(0) ) == std::string::npos) throw InvalidValueException{};
	card.rank = (Rank)ranks.find( str.at(0) );
	
	// Ensuring suit is valid
    if (suits.find( str.at(1) ) == std::string::npos) throw InvalidValueException{};
	card.suit = (Suit)suits.find( str.at(1) );
	return in;
}
