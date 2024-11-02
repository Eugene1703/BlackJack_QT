#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qlabel.h"
#include <QMainWindow>
#include <game.h>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QFileDialog>
#include <QStyle>
#include <QMediaPlayer>
#include <QAudioOutput>

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

    void on_actionChange_skins_triggered();

    void on_horizontalSlider_valueChanged(int value);

    void on_MutePushButton_clicked();

    void on_mutePushButton_clicked();

private:

    Ui::MainWindow *ui;
    QString defaultFolderPath = "C:/Users/Eugene/Documents/QT Projects/DCTTest/Resources/Skins/DefaultSkins/";
    QString backgroundMusicPath = "C:/Users/Eugene/Documents/QT Projects/DCTTest/Resources/Sounds/backgroundMusic.mp3";
    Game game;
    QLabel *flipCardLabel;
    QMediaPlayer *mediaPlayer = new QMediaPlayer();
    QAudioOutput *audioOutput = new QAudioOutput();

    void updateUI();
    void resetGame();
    void updatePlayerDealerScore();
    void printCards();
    void updateBet();
    void updateBalance();
    QPropertyAnimation* addCardToLayout(QLayout *layout, Card card, QPoint &startPos,QPoint &endPos);
    void clearLayout(QLayout *layout);
    void removeFlipCardFromLayout();
    QPropertyAnimation* createCardAnim(QLabel *cardLabel, QPoint startPos, QPoint &endPos);
    void setUiVisible();
    void setBackgroundMusic();






};
#endif // MAINWINDOW_H
