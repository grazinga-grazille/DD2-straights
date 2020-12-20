#ifndef _CARD_H
#define _CARD_H
#include <string>
#include <istream>
#include <ostream>

// State of the card
enum class Suit { CLUBS, SPADES, HEARTS, DIAMONDS };
enum class Rank { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };


class Card {
    Suit suit;
    Rank rank;
  public:
    Card();
    Card(Suit suit, Rank rank);
    Suit getSuit() const;
    std::string getSuitString() const;
    Rank getRank() const;
    std::string getRankString() const;
    int getRankNumber() const;
    friend std::ostream &operator<<(std::ostream &out, const Card &card);
    friend bool operator==(const Card &card1, const Card &card2);
    friend std::istream &operator>>(std::istream &in, Card &card);
};

std::ostream &operator<<(std::ostream &out, const Card &card);
bool operator==(const Card &card1, const Card &card2);
std::istream &operator>>(std::istream &in, Card &card);

class InvalidValueException{};

#endif
