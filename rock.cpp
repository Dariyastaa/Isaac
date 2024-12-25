#include "rock.h"
#include <QPainter>
#include <QDebug>

Rock::Rock(int x, int y, QWidget *parent) : QWidget(parent), xPos(x), yPos(y) {
    rockImage.load(":/images qt/rock.png");
    setFixedSize(rockImage.size());
}

void Rock::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (!rockImage.isNull()) {
        painter.drawPixmap(0, 0, rockImage);
    } else {
        qDebug() << "Rock image is not loaded";
    }
}

int Rock::getX() const {
    return xPos;
}

int Rock::getY() const {
    return yPos;
}
