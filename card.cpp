#include "card.h"

int Card::getMyRank() const
{
    if(isFaceUp)
    {
    if (myRank == Jack || myRank == Queen || myRank == King)
    {
        return 10;
    }
    else
    {
        return myRank;
    }
    }
    else return 0;
}

void Card::flip()
{
    isFaceUp=!isFaceUp;
}

void Card::setImageFolderPath(const QString &newImageFolderPath)
{
    imageFolderPath = newImageFolderPath;
}

Card::Card(){}
QString Card::cardToString() const
{
    return suitToString()+ "_" + rankToString();
}

QString Card::rankToString() const
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


QString Card::suitToString() const
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
