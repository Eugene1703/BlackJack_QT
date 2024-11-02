#ifndef DECK_H
#define DECK_H
#include <card.h>
#include <QVector>
#include<QRandomGenerator>
class Deck
{
public:
    Deck();
    QVector<Card> deck;
    void generate(QString imageFolderPath);
    void shuffle();
    Card dealCard();
private:
    QRandomGenerator *generator;
};

#endif // DECK_H
