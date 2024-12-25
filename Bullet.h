#ifndef BULLET_H
#define BULLET_H

#include <QWidget>
#include <QPixmap>
#include <QTimer>

class Bullet : public QWidget {
    Q_OBJECT

public:
    Bullet(int x, int y, int dx, int dy, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void moveBullet();

private:
    QPixmap bulletImage;
    int xPos, yPos;
    int dx, dy;
    QTimer* timer;
};

#endif // BULLET_H
