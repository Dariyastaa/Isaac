#ifndef ENEMY_H
#define ENEMY_H

#include <QWidget>
#include <QPainter>
#include <QString>

class Enemy : public QWidget {
    Q_OBJECT

public:
    explicit Enemy(int x, int y, QWidget *parent = nullptr);
    void moveTowards(int targetX, int targetY);
    int getHealth() const { return health; }
    void takeDamage(int damage);
    bool isDead() const { return health <= 0; }

    virtual ~Enemy() {}

    QTimer* timer;
    int currentFrame;
    QPixmap frames[4];

private slots:
    void updateFrame();

protected:
    void paintEvent(QPaintEvent *event) override;
    int health = 2;
};

#endif // ENEMY_H
