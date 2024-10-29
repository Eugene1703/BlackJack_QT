#ifndef GAME_H
#define GAME_H
#include <deck.h>
#include <player.h>
#include <QMessageBox>
class Game
{
public:
    Game();
    void start();
    void hit();
    void stand();
    bool checkWinner();
    void updateBet(float bet);
    void updateBalance();
    void dealCard(Player &_player);
    void addWinnings();
    void takeBet();
    Deck deck;
    Player player, dealer;
    float balance=100.0, bet=0.1, minBet=0.1, maxBet=10, betStep=0.1;
    bool isPlayer = true;
    int scoreLimit = 21;
};

#endif // GAME_H
