#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <game.h>
#include <QRandomGenerator>
#include <QMessageBox>
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

    void on_increasBetPushButton_clicked();

    void on_decreaseBetPushButton_clicked();

    void on_betInsertLineEdit_editingFinished();

    void on_playPushButton_clicked();

private:

    Ui::MainWindow *ui;
    Game game;

    void updateUI();
    void resetGame();
    void updatePlayerDealerScore();
    void printCards();
    void updateBet();
    void updateBalance();




};
#endif // MAINWINDOW_H
