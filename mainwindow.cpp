#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    startGame();
}


MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_hitPushButton_clicked()
{
    dealCard(isPlayer);
    ui->playerListWidget->addItem(playerCards.last().cardToString());
    playerScore=addScore(playerCards.last(),playerScore);
    updatePlayerDealerScore();
}

void MainWindow::on_standPushButton_clicked()
{
    dealerCards.last().flip();
    ui->dealerListWidget->addItem(dealerCards.last().cardToString());
    dealerScore=addScore(dealerCards.last(),dealerScore);
    updatePlayerDealerScore();
    if(isPlayerWin())
    {
        qDebug() << "Player win";
    }
    else qDebug() << "Player lose";
}

void MainWindow::dealCard(bool isPlayer)
{
    Card card = getCardFromDeck(deck);
    if(isPlayer)
    {
        playerCards.push_back(card);
    }
    else
    {
        dealerCards.push_back(card);
    }
}

void MainWindow::generateDeck(QVector<Card> &deck)
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

void MainWindow::shuffleDeck(QVector<Card> &deck)
{
    generator = QRandomGenerator::global();
    std::shuffle(deck.begin(),deck.end(),*generator);
}

void MainWindow::printCards()
{
    foreach (const Card &card, playerCards)
    {
        ui->playerListWidget->addItem(card.cardToString());
    }
    foreach (const Card &card, dealerCards)
    {
        if(card.isFaceUp)
        {
        ui->dealerListWidget->addItem(card.cardToString());
        }
    }
    countScore();
    updatePlayerDealerScore();
}

bool MainWindow::isPlayerWin()
{

    if (playerScore>21) return false;
    else if (playerScore>=dealerScore) return true;
}

Card MainWindow::getCardFromDeck(QVector<Card> &deck)
{
    if(!deck.isEmpty())
    {
        Card card = deck.last();
        deck.removeLast();
        return card;
    }

}

int MainWindow::addScore(Card card, int score)
{
    if(card.isFaceUp)
    {
    if(card.suitToString()==ace)
    {
        if(score <=10)
        {
            score+=11;
        }
        else score+=1;
    }
    else score+=card.getMyRank();
    }
    return score;
}

void MainWindow::startGame()
{

    playerScore=0;
    dealerScore=0;
    updatePlayerDealerScore();
    playerCards.clear();
    dealerCards.clear();
    generateDeck(deck);
    shuffleDeck(deck);
    for (int i=0;i<2;i++)
    {
        dealCard(isPlayer);
        dealCard(!isPlayer);
    }
    dealerCards.last().flip();
    printCards();

}

void MainWindow::updatePlayerDealerScore()
{
    ui->playerTextEdit->setText(QString::number(playerScore));
    ui->dealerTextEdit->setText(QString::number(dealerScore));
}

int MainWindow::countScore()
{
    foreach (const Card &card, playerCards)
    {
        playerScore=addScore(card,playerScore);
    }
    foreach (const Card &card, dealerCards)
    {
        dealerScore=addScore(card,dealerScore);
    }
}

