#ifndef BULLET_ENEMY_H
#define BULLET_ENEMY_H

#include <QWidget>
#include <QPixmap>
#include <QTimer>

class BulletEnemy : public QWidget {
    Q_OBJECT

public:
    enum Direction { Up, Down, Left, Right };
    BulletEnemy(int x, int y, Direction dir, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

public slots:
    void moveBulletEnemy();

private:
    QPixmap bulletImage;
    int xPos, yPos;
    Direction direction;
    QTimer* timer;
};

#endif // BULLET_ENEMY_H
