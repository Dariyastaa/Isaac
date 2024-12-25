#include "enemy.h"
#include "coin.h"
#include "mainscreen.h"
#include <QPainter>

Enemy::Enemy(int x, int y, QWidget *parent) : QWidget(parent), health(3), currentFrame(0) {
    setGeometry(x, y, 60, 45);
    frames[0].load(":/images qt/mux1.png");
    frames[1].load(":/images qt/mux2.png");
    frames[2].load(":/images qt/mux3.png");
    frames[3].load(":/images qt/mux2.png");

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Enemy::updateFrame);
    timer->start(80);
}

void Enemy::updateFrame() {
        currentFrame = (currentFrame + 1) % 4;
        update();
}

void Enemy::takeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        health = 0;
    }
}

void Enemy::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, frames[currentFrame]);
}

void Enemy::moveTowards(int targetX, int targetY) {
    int step = 5;

    if (x() < targetX) {
        move(x() + step, y());
    } else if (x() > targetX) {
        move(x() - step, y());
    }

    if (y() < targetY) {
        move(x(), y() + step);
    } else if (y() > targetY) {
        move(x(), y() - step);
    }
}
