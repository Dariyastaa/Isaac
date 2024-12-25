#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QWidget>
#include <QLabel>
#include <QSet>
#include <QVBoxLayout>
#include <QPainter>
#include <QPixmap>
#include <QScreen>
#include <QDebug>
#include <cstdlib>
#include <ctime>
#include <QKeyEvent>
#include <QApplication>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <vector>
#include "rock.h"
#include "character.h"
#include "bullet.h"
#include "enemy.h"
#include "coin.h"
#include "chest.h"
#include "ranged_enemy.h"
#include "bullet_enemy.h"

class GameScreen : public QWidget {
    Q_OBJECT

public:
    GameScreen(QWidget *parent = nullptr);
    void spawnRocks(int count);
    void addCharacter();
    void spawnEnemies(int count);
    void resetInvincibility();
    void transitionToNewRoom();
    void checkCoinPickup();
    void spawnChest();
    void checkCollisionChest();
    void addBullet(BulletEnemy* bullet);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void updateGame();

    void resetUpShot();
    void resetDownShot();
    void resetLeftShot();
    void resetRightShot();

private:
    std::vector<Rock*> rocks;
    bool checkCollision(int x, int y, int rockWidth, int rockHeight);
    bool checkCollisionIsaac(int newX, int newY);
    bool checkCollisionWalls(int newX, int newY);
    bool checkCollisionDoor(int newX, int newY);
    Character* character;
    void shootBullet(int dx, int dy);

    QSet<int> pressedKeys;
    QTimer* gameTimer;

    QTimer* upShotTimer;
    QTimer* downShotTimer;
    QTimer* leftShotTimer;
    QTimer* rightShotTimer;

    bool canShootUp;
    bool canShootDown;
    bool canShootLeft;
    bool canShootRight;

    std::vector<Enemy*> enemies;
    std::vector<RangedEnemy*> renemies;
    int playerHealth;
    void handlePlayerDamage();
    void drawHearts(QPainter& painter);

    bool isInvincible = false;
    QTimer* invincibilityTimer;
    int invincibilityDuration = 2000;

    QRect doorArea;
    void checkBulletCollisions();
    void checkEBulletCollisions(int newX, int newY);
    QVector<Bullet*> bullets;
    QVector<BulletEnemy*> ebullets;
    QVector<Coin*> coins;
    int playerCoins = 0;
    void drawCoins(QPainter& painter);
    QVector<Chest*> chests;

    int playerAttackPower = 1;
    int playerSpeed = 10;
    int shieldCount = 0;

    void shieldDamage();

    void drawDoor(QPainter& painter);
    QPixmap doorImage;

    void drawShield(QPainter& painter);
    QPixmap shieldImage;
};

#endif // GAMESCENE_H
