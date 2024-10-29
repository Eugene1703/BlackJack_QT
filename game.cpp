#include "game.h"
#include "qdebug.h"

Game::Game() {}

void Game::start()
{
    player.reset();
    dealer.reset();
    deck.generate();
    deck.shuffle();
    takeBet();

    dealCard(player);
    dealCard(player);

    dealCard(dealer);
    qDebug() << dealer.getLastCard().cardToString();
    dealCard(dealer);
    qDebug() << dealer.getLastCard().cardToString();
    dealer.getLastCard().flip();
    qDebug() << dealer.getLastCard().cardToString();
    if(dealer.getLastCard().isFaceUp)
    {
        qDebug() << dealer.getLastCard().cardToString();
        qDebug() << "IsFaceUp";
    }


}

void Game::hit()
{
    dealCard(this->player);
    this->player.updateScore();
}

void Game::stand()
{
    dealer.getLastCard().flip();
    dealer.updateScore();
}

bool Game::checkWinner()
{
    int playerScore= player.getScore();
    int dealerScore = dealer.getScore();
    if (playerScore>scoreLimit) return false;
    else if (playerScore>=dealerScore) return true;
    else if(playerScore<dealerScore) return false;
}

void Game::updateBet(float _bet)
{
    bet=_bet;
}


void Game::dealCard(Player &_player)
{
    _player.addCard(deck.dealCard());
}

void Game::addWinnings()
{
    balance+=2*bet;
}

void Game::takeBet()
{
    balance-=bet;
}
