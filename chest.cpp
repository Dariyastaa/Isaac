#include "chest.h"
#include <QRandomGenerator>
#include <QTimer>
#include <QDebug>

Chest::Chest(QWidget* parent)
    : QWidget(parent), chestX(0), chestY(0), currentFrame(0) {

    frames[0].load(":/images qt/chest_1.png");
    frames[1].load(":/images qt/chest_2.png");
    frames[2].load(":/images qt/chest_3.png");
    frames[3].load(":/images qt/chest_4.png");
    frames[4].load(":/images qt/chest_5.png");
    frames[5].load(":/images qt/chest_6.png");
    frames[6].load(":/images qt/chest_6.png");
    frames[7].load(":/images qt/chest_5.png");
    frames[8].load(":/images qt/chest_4.png");
    frames[9].load(":/images qt/chest_3.png");
    frames[10].load(":/images qt/chest_2.png");
    frames[11].load(":/images qt/chest_1.png");

    setFixedSize(200, 250);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Chest::updateFrame);
    timer->start(80);

}

void Chest::updateFrame() {
        currentFrame = (currentFrame + 1) % 12;
        update();
}

void Chest::setChestPosition(int x, int y) {
    chestX = x;
    chestY = y;
    move(x, y);
    update();
}

QString Chest::openChest(int& playerCoins) {
    int chestCost = 3;
    playerCoins -= chestCost;
    update();

    int bonusType = QRandomGenerator::global()->bounded(4);
    switch (bonusType) {
        case 0:
            return "heart";
        case 1:
            return "attack";
        case 2:
            return "speed";
        case 3:
            return "shield";
        default:
            return "";
    }
}

void Chest::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, frames[currentFrame]);
}
