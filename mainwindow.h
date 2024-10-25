#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <card.h>
#include <QVector>
#include <algorithm>
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
    QRandomGenerator *generator;
    int score=0;

    void dealCard();
    void flipCard();
    void generateDeck(QVector<Card> &deck);
    void shuffleDeck(QVector<Card> &deck);
    Card getCardFromDeck(QVector<Card> &deck);
    void startGame();
};
#endif // MAINWINDOW_H
