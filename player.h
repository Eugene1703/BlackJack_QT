#ifndef PLAYER_H
#define PLAYER_H
#include <card.h>
#include <QVector>
#include<QPoint>
class Player
{
public:
    Player();
    void addCard(const Card &card);
    int getScore() const;
    void reset();
    QVector<QString> getCardsAsString() const;
    void updateScore();
    Card& getLastCard();
    QVector<Card> getCards() const;
    const QString ace = "a";
    QPoint startPos;
    const QPoint &getStartPos() const;

private:
    QVector<Card> cards;
    int score;
};

#endif // PLAYER_H
