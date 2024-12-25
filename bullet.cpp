#include "bullet.h"
#include <QPainter>
#include <QTimer>
#include <QDebug>

Bullet::Bullet(int x, int y, int dx, int dy, QWidget *parent)
    : QWidget(parent), xPos(x), yPos(y), dx(dx), dy(dy) {
    bulletImage.load(":/images qt/bullet.png");
    setFixedSize(bulletImage.size());
    move(xPos, yPos);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Bullet::moveBullet);
    timer->start(50);
}

void Bullet::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (!bulletImage.isNull()) {
        painter.drawPixmap(0, 0, bulletImage);
    }
}

void Bullet::moveBullet() {
    xPos += dx;
    yPos += dy;
    move(xPos, yPos);
}
