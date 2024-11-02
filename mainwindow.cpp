#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    ui->hitPushButton->setVisible(false);
    ui->standPushButton->setVisible(false);
    ui->playerTextEdit->setVisible(false);
    ui->dealerTextEdit->setVisible(false);
    game.setImageFolderPath(defaultFolderPath);
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
    printCards();
    updatePlayerDealerScore();
    if(game.player.getScore()>game.scoreLimit)
    {

            QMessageBox::information(this,"Information" , "You lose.");
            setUiVisible();
            updateUI();

    }

}

void MainWindow::on_standPushButton_clicked()
{
    game.stand();
    Card card = game.dealer.getLastCard();
    card.flip();
    printCards();
    updatePlayerDealerScore();
    bool isPlayerWin = game.checkWinner();
    if(isPlayerWin)
    {
        game.addWinnings();
        QMessageBox::information(this,"Information" , "You win.");
    }
    else
    {
        QMessageBox::information(this,"Information" , "You lose.");
    }
    setUiVisible();
    updateUI();
}

void MainWindow::printCards()
{
    clearLayout(ui->playerCardsLayout);
    clearLayout(ui->dealerCardsLayout);
    QPoint startPos = game.player.getStartPos();
    QPoint endPos = startPos + QPoint(140,0);
    QParallelAnimationGroup* group = new QParallelAnimationGroup(this);
    foreach (const Card &card, game.player.getCards())
    {

        group->addAnimation(addCardToLayout(ui->playerCardsLayout,card,startPos, endPos));
        endPos+= QPoint(40,0);
    }
    endPos = startPos + QPoint(140,0);
    foreach (const Card &card, game.dealer.getCards())
    {
        group->addAnimation(addCardToLayout(ui->dealerCardsLayout, card,startPos, endPos));
        endPos+= QPoint(40,0);
    }
    group->start(QAbstractAnimation::DeleteWhenStopped);
}

QPropertyAnimation* MainWindow::addCardToLayout(QLayout *layout, Card card, QPoint &startPos, QPoint &endPos)
{
    QLabel *cardLabel = new QLabel(this);
    QString imagePath;

    if(card.isFaceUp)
    {
    imagePath = card.imageFolderPath + card.cardToString() + ".png";
    }
    else
    {
        flipCardLabel = cardLabel;
        imagePath = card.imageFolderPath + card.backName + ".png";
    }
    qDebug() << imagePath;
    QPixmap pixmap(imagePath);
    if (!pixmap.isNull())
    {
        cardLabel->setPixmap(pixmap);
    } else
    {
        cardLabel->setText("Image not found");
    }
    cardLabel->setPixmap(pixmap);
    cardLabel->setFixedSize(80, 120);
    cardLabel->setScaledContents(true);
    layout->addWidget(cardLabel);
    return createCardAnim(cardLabel,startPos,endPos);
}

QPropertyAnimation* MainWindow::createCardAnim(QLabel *cardLabel, QPoint startPos, QPoint &endPos)
{
    QPropertyAnimation *animation = new QPropertyAnimation(cardLabel, "pos");
    animation->setDuration(500);
    animation->setStartValue(startPos);
    animation->setEndValue(endPos);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    return animation;
}

void MainWindow::setUiVisible()
{

    QVector<QWidget*> uiElements =
        {
            ui->hitPushButton,
            ui->standPushButton,
            ui->betInsertLineEdit,
            ui->increasBetPushButton,
            ui->decreaseBetPushButton,
            ui->label,
            ui->playerTextEdit,
            ui->dealerTextEdit,
            ui->playPushButton

        };
    foreach(QWidget* element, uiElements)
    {
        element->setVisible(!element->isVisible());
    }

}

void MainWindow::clearLayout(QLayout *layout)
{
    if (layout == NULL)
        return;
    QLayoutItem *item;
    while((item = layout->takeAt(0)))
    {
        if (item->layout())
        {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
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
    clearLayout(ui->playerCardsLayout);
    clearLayout(ui->dealerCardsLayout);
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
    if(game.balance>=game.bet)
    {
        game.start();
        setUiVisible();
        updatePlayerDealerScore();
        updateUI();
        printCards();
    }
    else
    {
        QMessageBox::warning(this,"Information","Not enough balance");
    }

}


void MainWindow::on_actionChange_skins_triggered()
{
    QString folderPath = QFileDialog::getExistingDirectory(nullptr,"Select the skins folder");
    if(folderPath.isEmpty())
    {
        QMessageBox::information(this,"Information","The folder doesn't exist");
        return;
    }
    folderPath+="/";
    game.setImageFolderPath(folderPath);
}

