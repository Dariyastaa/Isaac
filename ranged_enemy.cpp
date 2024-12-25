#include "ranged_enemy.h"
#include "coin.h"
#include "mainscreen.h"
#include <QPainter>
#include <QTimerEvent>

RangedEnemy::RangedEnemy(int x, int y, QWidget *parent) : QWidget(parent), health(5), xPos(x), yPos(y), currentFrame(0) {
    setGeometry(x, y, 100, 100);

    frames[0].load(":/images qt/fly2.png");
    frames[1].load(":/images qt/fly1.png");
    frames[2].load(":/images qt/fly2.png");
    frames[3].load(":/images qt/fly3r.png");
    frames[4].load(":/images qt/fly4r.png");
    frames[5].load(":/images qt/fly5r.png");
    frames[6].load(":/images qt/fly6r.png");
    frames[7].load(":/images qt/fly5r.png");
    frames[8].load(":/images qt/fly4r.png");
    frames[9].load(":/images qt/fly3r.png");
    frames[10].load(":/images qt/fly2.png");
    frames[11].load(":/images qt/fly1.png");
    frames[12].load(":/images qt/fly2.png");
    frames[13].load(":/images qt/fly3l.png");
    frames[14].load(":/images qt/fly4l.png");
    frames[15].load(":/images qt/fly5l.png");
    frames[16].load(":/images qt/fly6l.png");
    frames[17].load(":/images qt/fly5l.png");
    frames[18].load(":/images qt/fly4l.png");
    frames[19].load(":/images qt/fly3l.png");

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &RangedEnemy::updateFrame);
    timer->start(80);

    shootTimer = new QTimer(this);
    connect(shootTimer, &QTimer::timeout, this, &RangedEnemy::shootBullets);
    shootTimer->start(3500);
}

void RangedEnemy::updateFrame() {
        currentFrame = (currentFrame + 1) % 20;
        update();
}

void RangedEnemy::takeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        health = 0;
        shootTimer->stop();
    }
}

// Отрисовка врага
void RangedEnemy::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, frames[currentFrame]);
}

void RangedEnemy::shootBullets() {
    if (isDead()) return;

    BulletEnemy* bulletUp = new BulletEnemy(xPos + 25, yPos, BulletEnemy::Up, parentWidget());
    BulletEnemy* bulletDown = new BulletEnemy(xPos + 25, yPos, BulletEnemy::Down, parentWidget());
    BulletEnemy* bulletLeft = new BulletEnemy(xPos, yPos + 25, BulletEnemy::Left, parentWidget());
    BulletEnemy* bulletRight = new BulletEnemy(xPos + 50, yPos + 25, BulletEnemy::Right, parentWidget());

    dynamic_cast<GameScreen*>(parentWidget())->addBullet(bulletUp);
    dynamic_cast<GameScreen*>(parentWidget())->addBullet(bulletDown);
    dynamic_cast<GameScreen*>(parentWidget())->addBullet(bulletLeft);
    dynamic_cast<GameScreen*>(parentWidget())->addBullet(bulletRight);

    shootTimer->start(2000);
}
