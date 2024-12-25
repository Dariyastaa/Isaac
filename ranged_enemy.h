#ifndef RANGED_ENEMY_H
#define RANGED_ENEMY_H

#include <QWidget>
#include <QTimer>
#include "bullet_enemy.h"

class RangedEnemy : public QWidget {
    Q_OBJECT

public:
    explicit RangedEnemy(int x, int y, QWidget *parent = nullptr);
    int getHealth() const { return health; }
    void takeDamage(int damage);
    bool isDead() const { return health <= 0; }

    virtual ~RangedEnemy() { delete shootTimer;}

    QTimer* timer;
    int currentFrame;
    QPixmap frames[20];

private slots:
    void updateFrame();

protected:
    void paintEvent(QPaintEvent *event) override;
    QPixmap enemyImage;
    int health = 5;

private:
    void shootBullets();
    int xPos, yPos;
    QTimer* shootTimer;
};

#endif // RANGED_ENEMY_H
