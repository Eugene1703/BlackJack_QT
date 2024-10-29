#include "deck.h"

Deck::Deck() {}

void Deck::generate()
{
    deck.clear();
    for(int suit=Hearts;suit<=Spades;suit++)
    {
        for(int rank=Two;rank<=King;rank++)
        {
            Card card(static_cast<Rank>(rank), static_cast<Suit>(suit));
            deck.push_back(card);
        }
    }
}

void Deck::shuffle()
{
    generator = QRandomGenerator::global();
    std::shuffle(deck.begin(),deck.end(),*generator);
}

Card Deck::dealCard()
{
    if(!deck.isEmpty())
    {
        Card card = deck.last();
        deck.removeLast();
        return card;
    }
}
