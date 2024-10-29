#include "player.h"

Player::Player() {}

void Player::addCard(const Card &card)
{
    cards.push_back(card);
    updateScore();
}

int Player::getScore() const
{
    return score;
}

void Player::reset()
{
    cards.clear();
    score=0;
    startPos = QPoint(-100,0);

}

QVector<QString> Player::getCardsAsString() const
{
    QVector<QString> result;
    foreach(const Card &card, cards)
    {
        result.push_back(card.cardToString());
    }
    return result;
}

void Player::updateScore()
{
    score=0;
    foreach (const Card &card, cards)
    {
        if(card.isFaceUp)
        {
            if(card.rankToString()==ace)
            {
                if(score <=10)
                {
                    score+=11;
                }
                else score+=1;
            }
            else score+=card.getMyRank();
        }
    }
}

Card& Player::getLastCard()
{
    return cards.last();
}

QVector<Card> Player::getCards() const
{
    return cards;
}


const QPoint &Player::getStartPos() const
{
    return startPos;
}
