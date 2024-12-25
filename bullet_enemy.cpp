#include "bullet_enemy.h"
#include <QPainter>
#include <QTimer>
#include <QDebug>

BulletEnemy::BulletEnemy(int x, int y, Direction dir, QWidget *parent)
    : QWidget(parent), xPos(x), yPos(y), direction(dir) {
    bulletImage.load(":/images qt/bulletenemy.png");
    setFixedSize(bulletImage.size());
    move(xPos, yPos);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &BulletEnemy::moveBulletEnemy);
    timer->start(20);
}

void BulletEnemy::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (!bulletImage.isNull()) {
        painter.drawPixmap(0, 0, bulletImage);
    }
}

void BulletEnemy::moveBulletEnemy() {
    const int speed = 7;
    switch (direction) {
        case Up:
            yPos -= speed;
            break;
        case Down:
            yPos += speed;
            break;
        case Left:
            xPos -= speed;
            break;
        case Right:
            xPos += speed;
            break;
    }
    move(xPos, yPos);
}
