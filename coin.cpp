#include "coin.h"
#include <QPainter>

Coin::Coin(int x, int y, QWidget *parent)
    : QWidget(parent), xPos(x), yPos(y), coinImage(":/images qt/coin.png") {
    setGeometry(xPos, yPos, coinImage.width(), coinImage.height());
}

void Coin::show() {
    QWidget::show();
}

void Coin::hide() {
    QWidget::hide();
}

QRect Coin::geometry() const {
    return QRect(xPos, yPos, coinImage.width(), coinImage.height());
}

void Coin::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, coinImage);
}
