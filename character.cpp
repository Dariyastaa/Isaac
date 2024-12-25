#include "character.h"
#include <QPainter>
#include <QDebug>
#include <QTimer>

Character::Character(int x, int y, QWidget *parent) : QWidget(parent), xPos(x), yPos(y), frameIndex(0), currentDirection(None) {
    characterImage.load(":/images qt/down1.png");
    setGeometry(x, y, 120, 150);
    move(xPos, yPos);

    framesUp = {
        QPixmap(":/images qt/up1.png"),
        QPixmap(":/images qt/up2.png"),
        QPixmap(":/images qt/up3.png"),
        QPixmap(":/images qt/up4.png"),
        QPixmap(":/images qt/up5.png")
    };
    framesDown = {
        QPixmap(":/images qt/down1.png"),
        QPixmap(":/images qt/down2.png"),
        QPixmap(":/images qt/down3.png"),
        QPixmap(":/images qt/down4.png"),
        QPixmap(":/images qt/down5.png")
    };
    framesLeft = {
        QPixmap(":/images qt/left1.png"),
        QPixmap(":/images qt/left2.png"),
        QPixmap(":/images qt/left3.png"),
        QPixmap(":/images qt/left4.png"),
        QPixmap(":/images qt/left5.png")
    };
    framesRight = {
        QPixmap(":/images qt/right1.png"),
        QPixmap(":/images qt/right2.png"),
        QPixmap(":/images qt/right3.png"),
        QPixmap(":/images qt/right4.png"),
        QPixmap(":/images qt/right5.png")
    };

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &Character::updateAnimation);
    animationTimer->start(100);
}

void Character::moveCharacter(int dx, int dy) {
    xPos += dx;
    yPos += dy;
    move(xPos, yPos);
    update();
}

void Character::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (currentDirection == None) {
        painter.drawPixmap(0, 0, characterImage);
    }
    else {
        painter.drawPixmap(0, 0, currentFrame);
    }
}

void Character::setDirection(Direction dir) {
    if (currentDirection != dir) {
        currentDirection = dir;
        frameIndex = 0;

        if (dir == None) {
            animationTimer->stop();
        } else {
            if (!animationTimer->isActive()) {
                animationTimer->start(100);
            }
        }
    }
}

void Character::updateAnimation() {
    QVector<QPixmap> *currentFrames = &framesDown;

    switch (currentDirection) {
        case Up:
            currentFrames = &framesUp;
            break;
        case Down:
            currentFrames = &framesDown;
            break;
        case Left:
            currentFrames = &framesLeft;
            break;
        case Right:
            currentFrames = &framesRight;
            break;
        case None:
        default:
            return;
    }

    if (currentFrames && !currentFrames->isEmpty()) {
        frameIndex = (frameIndex + 1) % 5;
        currentFrame = (*currentFrames)[frameIndex];
        update();
    }
}
