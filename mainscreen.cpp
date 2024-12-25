#include "mainscreen.h"
#include <QMessageBox>
#include <QApplication>
#include <QPainter>

MainScreen::MainScreen(QWidget *parent) : QWidget(parent) {
    stackedWidget = new QStackedWidget(this);

    gameScreen = new GameScreen();

    QWidget *mainMenu = new QWidget(this);
    QPushButton *playButton = new QPushButton(mainMenu);
    QPushButton *exitButton = new QPushButton(mainMenu);
    soundButton = new QPushButton(mainMenu);

    QPixmap playPixmap(":/images qt/newrun.png");
    QIcon playIcon(playPixmap);
    playButton->setIcon(playIcon);
    playButton->setIconSize(playPixmap.rect().size());
    playButton->setFixedSize(playPixmap.rect().size());

    QPixmap exitPixmap(":/images qt/exit.png");
    QIcon exitIcon(exitPixmap);
    exitButton->setIcon(exitIcon);
    exitButton->setIconSize(exitPixmap.rect().size());
    exitButton->setFixedSize(exitPixmap.rect().size());

    QPixmap soundPixmap(":/images qt/soundon.png");
    QIcon soundIcon(soundPixmap);
    soundButton->setIcon(soundIcon);
    soundButton->setIconSize(soundPixmap.rect().size());
    soundButton->setFixedSize(soundPixmap.rect().size());

    playButton->resize(playButton->iconSize());
    exitButton->resize(exitButton->iconSize());
    soundButton->resize(soundButton->iconSize());

    QVBoxLayout *layout = new QVBoxLayout(mainMenu);
    layout->addWidget(playButton);
    layout->addWidget(exitButton);
    layout->addWidget(soundButton);

    layout->setAlignment(playButton, Qt::AlignHCenter);
    layout->setAlignment(exitButton, Qt::AlignHCenter);
    layout->setAlignment(soundButton, Qt::AlignHCenter);

    stackedWidget->addWidget(mainMenu);
    stackedWidget->addWidget(gameScreen);

    connect(playButton, &QPushButton::clicked, this, &MainScreen::startGame);
    connect(exitButton, &QPushButton::clicked, this, &MainScreen::exitGame);
    connect(soundButton, &QPushButton::clicked, this, &MainScreen::soundGame);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stackedWidget);
    setLayout(mainLayout);

    setWindowTitle("Isaac Game");

    player = new QMediaPlayer(this);
    player->setMedia(QUrl("qrc:/sounds/music.mp3"));
    player->setVolume(100);
    player->play();
    connect(player, &QMediaPlayer::mediaStatusChanged, [=](QMediaPlayer::MediaStatus stat) {
        if (stat == QMediaPlayer::EndOfMedia) {
            player -> play();
        }
    });
}

void MainScreen::startGame() {
    stackedWidget->setCurrentWidget(gameScreen);
}

void MainScreen::exitGame() {
    QApplication::quit();
}

void MainScreen::soundGame() {
    if (sound == true) {

        sound = false;
        player->pause();
        QPixmap soundPixmap(":/images qt/soundoff.png");
        QIcon soundIcon(soundPixmap);
        soundButton->setIcon(soundIcon);
        soundButton->setIconSize(soundPixmap.rect().size());
        soundButton->setFixedSize(soundPixmap.rect().size());
        soundButton->repaint();

    } else {

        sound = true;
        player->play();
        QPixmap soundPixmap(":/images qt/soundon.png");
        QIcon soundIcon(soundPixmap);
        soundButton->setIcon(soundIcon);
        soundButton->setIconSize(soundPixmap.rect().size());
        soundButton->setFixedSize(soundPixmap.rect().size());
        soundButton->repaint();
    }
}

void MainScreen::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    QPixmap background(":/images qt/mainscreen.PNG");

    painter.drawPixmap(0, 0, width(), height(), background);
}
