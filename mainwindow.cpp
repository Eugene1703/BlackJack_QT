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

    Card card = getCardFromDeck(deck);

    qDebug() << card.cardToString();
}


void MainWindow::on_standPushButton_clicked()
{

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
    std::random_shuffle(deck.begin(),deck.end());
}

Card MainWindow::getCardFromDeck(QVector<Card> &deck)
{
    Card card = deck.last();
    deck.removeLast();
    return card;
}

void MainWindow::startGame()
{
    generateDeck(deck);
    shuffleDeck(deck);
}
