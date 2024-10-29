#ifndef CARD_H
#define CARD_H

#include <QString>
enum Suit
{
    Hearts,
    Diamonds,
    Clubs,
    Spades
};

enum Rank
{
    Two = 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten,
    Ace, Jack, Queen,King
};

class Card
{
public:
    Rank myRank;
    Suit mySuit;
    bool isFaceUp=true;
    Card(Rank rank, Suit suit) : myRank(rank), mySuit(suit) {}
    Card();
    QString cardToString() const;
    QString suitToString() const;
    QString rankToString() const;
    int getMyRank() const;
    void flip();
};

#endif // CARD_H
