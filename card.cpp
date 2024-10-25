#include "card.h"

// Card::Card(Rank rank, Suit suit) {}
Card::Card(){}
QString Card::cardToString()
{
    return suitToString()+ "_" + rankToString();
}

QString Card::rankToString()
{
    switch (myRank)
    {
    case Two: return "2";
    case Three: return "3";
    case Four: return "4";
    case Five: return "5";
    case Six: return "6";
    case Seven : return "7";
    case Eight : return "8";
    case Nine : return "9";
    case Ten : return "10";
    case Jack : return "j";
    case Queen : return "q";
    case King : return "k";
    case Ace : return "a";
    default: return "Something went wrong";
    }
}

QString Card::suitToString()
{
    switch (mySuit)
    {
    case Hearts : return "Hearts";
    case Diamonds : return "Diamonds";
    case Clubs : return "Clubs";
    case Spades : return "Spades";
    default: return "Something went wrong";
    }
}
