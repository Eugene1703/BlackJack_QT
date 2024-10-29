#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateBet();
    updateBalance();
}


MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_hitPushButton_clicked()
{
    game.hit();
    ui->playerListWidget->addItem(game.player.getLastCard().cardToString());
    updatePlayerDealerScore();
    if(game.player.getScore()>game.scoreLimit)
    {

            QMessageBox::StandardButton reply;
            QMessageBox::information(this,"Information" , "You lose. Another one?", QMessageBox::Ok, QMessageBox::Cancel);
            if(reply = QMessageBox::Ok )
            {
                game.start();
                updatePlayerDealerScore();
                qDebug() << "Player cards count:" << game.player.getCards().size();
                qDebug() << "Dealer cards count:" << game.dealer.getCards().size();
                updateUI();
                printCards();
            }
    }

}

void MainWindow::on_standPushButton_clicked()
{
    game.stand();
    ui->dealerListWidget->addItem(game.dealer.getLastCard().cardToString());
    updatePlayerDealerScore();
    bool isPlayerWin = game.checkWinner();
    if(isPlayerWin)
    {
        game.addWinnings();
        QMessageBox::StandardButton reply;
        QMessageBox::information(this,"Information" , "You win. Another one?", QMessageBox::Ok, QMessageBox::Cancel);
        if(reply = QMessageBox::Ok )
        {
            game.start();
            updatePlayerDealerScore();
            qDebug() << "Player cards count:" << game.player.getCards().size();
            qDebug() << "Dealer cards count:" << game.dealer.getCards().size();
            updateUI();
            printCards();
        }

    }
    else
    {
        QMessageBox::StandardButton reply;
        QMessageBox::information(this,"Information" , "You lose. Another one?", QMessageBox::Ok, QMessageBox::Cancel);
        if(reply = QMessageBox::Ok )
        {
            game.start();
        }
    }
}

void MainWindow::printCards()
{
    foreach (const Card &card, game.player.getCards())
    {
        ui->playerListWidget->addItem(card.cardToString());
    }
    foreach (const Card &card, game.dealer.getCards())
    {
        if(card.isFaceUp)
        {
        ui->dealerListWidget->addItem(card.cardToString());
        }
    }
}

void MainWindow::updatePlayerDealerScore()
{
    game.player.updateScore();
    game.dealer.updateScore();
    ui->playerTextEdit->setText(QString::number(game.player.getScore()));
    ui->dealerTextEdit->setText(QString::number(game.dealer.getScore()));
}


void MainWindow::updateBet()
{
    ui->betTextEdit->setText(QString::number(game.bet,'f',1));
}

void MainWindow::updateBalance()
{
    ui->balanceTextEdit->setText(QString::number(game.balance));
}

void MainWindow::updateUI()
{
    updateBet();
    updateBalance();
    ui->dealerListWidget->clear();
    ui->playerListWidget->clear();
}

void MainWindow::on_increasBetPushButton_clicked()
{
    float bet = game.bet;
    if (bet >= game.maxBet)
    {
        bet = game.maxBet;
        QMessageBox::information(this, "Information", "Max bet = " + QString::number(game.maxBet,'f',1), QMessageBox::Ok);
    }
    else
    {
        bet += game.betStep;

        bet = std::round(bet * 10) / 10.0;

        if (bet > game.maxBet)
        {
            bet = game.maxBet;
        }
    }
    game.updateBet(bet);
    updateBet();

}

void MainWindow::on_decreaseBetPushButton_clicked()
{
    float bet=game.bet;
    if (bet <= game.minBet)
    {
        bet = game.minBet;
        QMessageBox::information(this, "Information", "Min bet = " + QString::number(game.minBet,'f',1), QMessageBox::Ok);
    }
    else
    {
        bet -= game.betStep;

        bet = std::round(bet * 10) / 10.0;

        if (bet < game.minBet)
        {
            bet = game.minBet;
        }
    }
    game.updateBet(bet);
    updateBet();
}


void MainWindow::on_betInsertLineEdit_editingFinished()
{
    bool convertResult;
    float bet=ui->betInsertLineEdit->text().toFloat(&convertResult);
    if(!convertResult || bet>10 || bet<0.1)
    {
        QMessageBox::warning(this, "Information", "Enter bet from " + QString::number(game.minBet,'f',1) + " to " + QString::number(game.maxBet,'f',1) , QMessageBox::Ok);
    }
    else
    {
        game.updateBet(bet);
        updateBet();
    }
}


void MainWindow::on_playPushButton_clicked()
{
    game.start();
    updatePlayerDealerScore();
    qDebug() << "Player cards count:" << game.player.getCards().size();
    qDebug() << "Dealer cards count:" << game.dealer.getCards().size();
    updateUI();
    printCards();
}

