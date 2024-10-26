#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <card.h>
#include <QVector>
#include <QRandomGenerator>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_hitPushButton_clicked();

    void on_standPushButton_clicked();

private:

    Ui::MainWindow *ui;
    QVector<Card> deck;
    QVector<Card> playerCards;
    QVector<Card> dealerCards;
    QRandomGenerator *generator;
    const QString ace = "Ace";
    int playerScore=0, dealerScore=0;
    bool isPlayer=true;
    void dealCard(bool isPlayer);
    void generateDeck(QVector<Card> &deck);
    void shuffleDeck(QVector<Card> &deck);
    void printCards();
    bool isPlayerWin();
    Card getCardFromDeck(QVector<Card> &deck);
    int addScore(Card card, int score);
    void startGame();
    void updatePlayerDealerScore();
    int countScore();

};
#endif // MAINWINDOW_H
