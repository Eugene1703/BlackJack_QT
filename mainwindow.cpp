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


}


void MainWindow::on_standPushButton_clicked()
{

}

void MainWindow::dealCard()
{
    Card card = getCardFromDeck(deck);
    score+=card.getMyRank();
    qDebug() << std::to_string(score);
    qDebug() << card.cardToString();
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

Card MainWindow::getCardFromDeck(QVector<Card> &deck)
{
    if(!deck.isEmpty())
    {
        Card card = deck.last();
        deck.removeLast();
        return card;
    }

}

void MainWindow::startGame()
{

    generateDeck(deck);
    shuffleDeck(deck);
    for (int i=0;i<2;i++)
    {
        dealCard();
    }


}
