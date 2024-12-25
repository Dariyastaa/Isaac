#include "gamescreen.h"

GameScreen::GameScreen(QWidget *parent) : QWidget(parent), character(nullptr), canShootUp(true), canShootDown(true), canShootLeft(true), canShootRight(true), playerHealth(5){
    setWindowTitle("Игровая комната");
    showFullScreen();

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    addCharacter();

    doorArea = QRect(width()-150, (height()-300)/2, 150, 300);

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &GameScreen::updateGame);
    gameTimer->start(16);

    upShotTimer = new QTimer(this);
    downShotTimer = new QTimer(this);
    leftShotTimer = new QTimer(this);
    rightShotTimer = new QTimer(this);

    connect(upShotTimer, &QTimer::timeout, this, &GameScreen::resetUpShot);
    connect(downShotTimer, &QTimer::timeout, this, &GameScreen::resetDownShot);
    connect(leftShotTimer, &QTimer::timeout, this, &GameScreen::resetLeftShot);
    connect(rightShotTimer, &QTimer::timeout, this, &GameScreen::resetRightShot);

    upShotTimer->setInterval(500);
    downShotTimer->setInterval(500);
    leftShotTimer->setInterval(500);
    rightShotTimer->setInterval(500);

    invincibilityTimer = new QTimer(this);
    invincibilityTimer->setSingleShot(true);
    connect(invincibilityTimer, &QTimer::timeout, this, &GameScreen::resetInvincibility);
}


void GameScreen::addCharacter() {
    character = new Character(160, 500, this);
    character->show();
}

void GameScreen::spawnEnemies(int count) {
    for (int i = 0; i < count; ++i) {
        int x = (std::rand() % (width() - 600)) + 300;
        int y = (std::rand() % (height() - 600)) + 300;

            Enemy* enemy = new Enemy(x, y, this);
            enemies.push_back(enemy);
            enemy->show();
    }
    int renemy = std::rand() % 3;
    if (renemy == 2 || renemy == 1) {
        int x = (std::rand() % (width() - 800)) + 400;
        int y = (std::rand() % (height() - 800)) + 400;
        RangedEnemy* Renemy = new RangedEnemy(x, y, this);
        renemies.push_back(Renemy);
        Renemy->show();
    }
}

void GameScreen::spawnChest() {
    Chest* chest = new Chest(this);
    chest->setChestPosition((width() - 200)/2, (height() - 250)/2);
    chest->show();
    chests.push_back(chest);
}

void GameScreen::transitionToNewRoom() {
    for (auto rock : rocks) {
        rock->hide();
        delete rock;
    }
    rocks.clear();

    for (auto enemy : enemies) {
        enemy->hide();
        delete enemy;
    }
    enemies.clear();

    for (auto bullet : bullets) {
        bullet->hide();
        delete bullet;
    }
    bullets.clear();

    for (auto ebullet : ebullets) {
        ebullet->hide();
        delete ebullet;
    }
    ebullets.clear();

    for (auto renemy : renemies) {
        renemy->hide();
        delete renemy;
    }
    renemies.clear();

    int newX = 160;
    int newY = 500;
    character->move(newX, newY);

    int room = std::rand() % 2;
    if ((room == 0 && playerCoins >= 3) || playerCoins >= 6) {
        spawnChest();
    }
    else {
        int enem = std::rand() % 4;
        while (enem == 0) {
            enem = std::rand() % 4;
        }
        int rock = std::rand() % 6;
        spawnRocks(rock);
        spawnEnemies(enem);
    }
}

bool GameScreen::checkCollisionWalls(int newX, int newY) {
    QRect heroRect(newX, newY, character->width(), character->height());
    QRect roomBounds(150, 50, width()-250, height()-150);
    if (!roomBounds.contains(heroRect)) {
        return true;
    }
}

bool GameScreen::checkCollisionDoor(int newX, int newY) {
    QRect heroRect(newX, newY, character->width(), character->height());
        if (heroRect.intersects(doorArea) && enemies.empty() && renemies.empty()) {
            transitionToNewRoom();
            return true;
        }
}

void GameScreen::checkCollisionChest() {
    for (auto& chest : chests) {
        QRect chestRect(chest->chestX, chest->chestY, chest->chestWidth, chest->chestHeight);
        if (character->geometry().intersects(chestRect)) {
            QString bonus = chest->openChest(playerCoins);
            chests.removeOne(chest);
            chest->hide();
            delete chest;
            update();
            if (bonus == "heart") {
                playerHealth++;
            }
            else if (bonus == "attack" && playerAttackPower != 5) {
                playerAttackPower++;
            }
            else if (bonus == "speed" && playerSpeed != 25) {
                playerSpeed += 5;
            }
            else if (bonus == "shield") {
                shieldCount += 2;
            }
            else {
                shieldCount += 1;
                playerHealth += 1;
            }
        }
    }
    update();
}

bool GameScreen::checkCollisionIsaac(int newX, int newY) {
    QRect heroRect(newX, newY, character->width(), character->height());
    for (auto& rock : rocks) {
        QRect rockRect(rock->x(), rock->y(), rock->width(), rock->height());
        if (heroRect.intersects(rockRect)) {
            return true;
        }
            for (auto& enemy : enemies) {
                QRect enemyRect(enemy->x(), enemy->y(), enemy->width(), enemy->height());
                if (heroRect.intersects(enemyRect) && !isInvincible) {
                    if (shieldCount == 0) {
                        handlePlayerDamage();
                        return true;
                    }
                    else if (!isInvincible){
                        shieldDamage();
                        return true;
                    }
                }
            }
            for (auto& renemy : renemies) {
                QRect enemyRect(renemy->x(), renemy->y(), renemy->width(), renemy->height());
                if (heroRect.intersects(enemyRect) && !isInvincible) {
                    if (shieldCount == 0) {
                        handlePlayerDamage();
                        return true;
                    }
                    else if (!isInvincible){
                        shieldDamage();
                        return true;
                    }
                }
            }
    }
    return false;
}

void GameScreen::shieldDamage() {
    shieldCount -= 1;
    isInvincible = true;
    invincibilityTimer->start(invincibilityDuration);
}

void GameScreen::checkBulletCollisions() {
    for (int i = 0; i < bullets.size(); ++i) {
        Bullet* bullet = bullets[i];
        QScreen *screen = QGuiApplication::primaryScreen();
        QRect screenGeometry = screen->geometry();
        int width = screenGeometry.width();
        int height = screenGeometry.height();
                if (bullet->x() < 50 || bullet->x() > (width - 150) || bullet->y() < 50 || bullet->y() > (height - 150)) {
                    bullets.erase(bullets.begin() + i);
                    delete bullet;
                    --i;
                    continue;
                }
        for (size_t j = 0; j < enemies.size(); ++j) {
            Enemy* enemy = enemies[j];
            if (bullet->geometry().intersects(enemy->geometry())) {
                enemy->takeDamage(playerAttackPower);
                if (enemy->isDead()) {
                    Coin* coin = new Coin(enemy->x(), enemy->y(), this);
                    coin->show();
                    coins.push_back(coin);
                }
                bullets.erase(bullets.begin() + i);
                delete bullet;
                --i;
                break;
            }
        }
        for (size_t j = 0; j < renemies.size(); ++j) {
            RangedEnemy* renemy = renemies[j];
            if (bullet->geometry().intersects(renemy->geometry())) {
                renemy->takeDamage(playerAttackPower);
                if (renemy->isDead()) {
                    Coin* coin = new Coin(renemy->x(), renemy->y(), this);
                    coin->show();
                    coins.push_back(coin);
                }
                bullets.erase(bullets.begin() + i);
                delete bullet;
                --i;
                break;
            }
        }
    }
    for (size_t j = 0; j < enemies.size(); ) {
        if (enemies[j]->isDead()) {
            delete enemies[j];
            enemies.erase(enemies.begin() + j);
        } else {
            ++j;
        }
    }
    for (size_t j = 0; j < renemies.size(); ) {
        if (renemies[j]->isDead()) {
            delete renemies[j];
            renemies.erase(renemies.begin() + j);
        } else {
            ++j;
        }
    }
}

void GameScreen::checkEBulletCollisions(int newX, int newY) {
    for (int i = 0; i < ebullets.size(); ++i) {
        BulletEnemy* ebullet = ebullets[i];
        QScreen *screen = QGuiApplication::primaryScreen();
        QRect screenGeometry = screen->geometry();
        int width = screenGeometry.width();
        int height = screenGeometry.height();
        if (ebullet->x() < 50 || ebullet->x() > (width - 150) || ebullet->y() < 50 || ebullet->y() > (height - 150)) {
            ebullets.erase(ebullets.begin() + i);
            delete ebullet;
            --i;
            continue;
        }
                QRect heroRect(newX, newY, character->width(), character->height());
                QRect ebulletRect(ebullet->x(), ebullet->y(), ebullet->width(), ebullet->height());
                if (heroRect.intersects(ebulletRect)) {
                    if (shieldCount == 0) {
                        handlePlayerDamage();
                    }
                    else {
                        shieldCount -= 1;
                    }
                    ebullets.erase(ebullets.begin() + i);
                    delete ebullet;
                    --i;
                    break;
                }
     }
}

void GameScreen::checkCoinPickup() {
    for (size_t i = 0; i < coins.size(); ++i) {
        Coin* coin = coins[i];
        if (coin->geometry().intersects(character->geometry())) {
            coins.erase(coins.begin() + i);
            delete coin;
            playerCoins++;
            qDebug() << "Coins collected: " << playerCoins;
            break;
        }
    }
    update();
}

void GameScreen::shootBullet(int dx, int dy) {
    int bulletX = character->x() + 35;
    int bulletY = character->y() + 70;
    Bullet* bullet = new Bullet(bulletX, bulletY, dx, dy, this);
    bullets.push_back(bullet);
    bullet->show();
}

void GameScreen::keyPressEvent(QKeyEvent *event) {
    pressedKeys.insert(event->key());
}

void GameScreen::keyReleaseEvent(QKeyEvent *event) {
    pressedKeys.remove(event->key());
}

void GameScreen::updateGame() {
    int step = playerSpeed;
    int newX = character->x();
    int newY = character->y();

        if  (pressedKeys.contains(Qt::Key_Escape)){
            QApplication::quit();
        }
        if (pressedKeys.contains(Qt::Key_W)) {
            newY -= step;
            character->setDirection(Character::Up);
        }
        if (pressedKeys.contains(Qt::Key_S)) {
            newY += step;
            character->setDirection(Character::Down);
        }
        if (pressedKeys.contains(Qt::Key_A)) {
            newX -= step;
            character->setDirection(Character::Left);
        }
        if (pressedKeys.contains(Qt::Key_D)) {
            newX += step;
            character->setDirection(Character::Right);
        }
        if (!checkCollisionIsaac(newX, newY) && !checkCollisionWalls(newX, newY) && !checkCollisionDoor(newX, newY)) {
            character->move(newX, newY);
        }
        if (pressedKeys.contains(Qt::Key_Up) && canShootUp) {
            shootBullet(0, -15);
            canShootUp = false;
            upShotTimer->start();
        }
        if (pressedKeys.contains(Qt::Key_Down) && canShootDown) {
            shootBullet(0, 15);
            canShootDown = false;
            downShotTimer->start();
        }
        if (pressedKeys.contains(Qt::Key_Left) && canShootLeft) {
            shootBullet(-15, 0);
            canShootLeft = false;
            leftShotTimer->start();
        }
        if (pressedKeys.contains(Qt::Key_Right) && canShootRight) {
            shootBullet(15, 0);
            canShootRight = false;
            rightShotTimer->start();
        }

        for (auto& enemy : enemies) {
            enemy->moveTowards(character->x(), character->y());
        }
        checkBulletCollisions();
        checkCoinPickup();
        checkCollisionChest();
        checkEBulletCollisions(newX, newY);
        for (BulletEnemy* ebullet : ebullets) {
            ebullet->moveBulletEnemy();
        }
}

void GameScreen::addBullet(BulletEnemy* ebullet) {
    ebullets.append(ebullet);
    ebullet->show();
}

void GameScreen::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap background(":/images qt/room2.png");
    painter.drawPixmap(0, 0, width(), height(), background);
    drawHearts(painter);
    drawCoins(painter);
    drawShield(painter);
    drawDoor(painter);
}

bool GameScreen::checkCollision(int x, int y, int rockWidth, int rockHeight) {
    for (const Rock* rock : rocks) {
        QRect rockRect(rock->x(), rock->y(), rockWidth, rockHeight);
        QRect newRockRect(x, y, rockWidth, rockHeight);
        if (rockRect.intersects(newRockRect)) {
            return true;
        }
    }
    return false;
}

void GameScreen::spawnRocks(int count) {
    int rockWidth = 100;
    int rockHeight = 100;
    int padding = 400;
    for (int i = 0; i < count; ++i) {
        int x, y;
        bool positionValid;
        do {
            x = padding + std::rand() % (width() - rockWidth - 2 * padding);
            y = padding + std::rand() % (height() - rockHeight - 2 * padding);
            positionValid = !checkCollision(x, y, rockWidth, rockHeight);
            } while (!positionValid);
        Rock* rock = new Rock(x, y, this);
        rock->move(x, y);
        rocks.push_back(rock);
        rock->show();
    }
}

void GameScreen::handlePlayerDamage() {
    if (playerHealth > 0) {
        playerHealth -= 1;
        if (playerHealth <= 0) {
            QMessageBox::information(this, "Игра окончена", "Вы проиграли. Попробуйте снова!");
            QApplication::quit();
        }
        isInvincible = true;
        invincibilityTimer->start(invincibilityDuration);
        update();
    }
}

void GameScreen::drawHearts(QPainter& painter) {
    QPixmap heartImage(":/images qt/heart.png");
    int heartWidth = heartImage.width();
    for (int i = 0; i < playerHealth; ++i) {
        painter.drawPixmap(i * (heartWidth + 5), 0, heartImage);
    }
}

void GameScreen::drawDoor(QPainter& painter) {
    QPixmap doorImage(":/images qt/door.png");
    if (enemies.empty() && renemies.empty()) {
        painter.drawPixmap(width()-150, (height()-300)/2, doorImage);
    }
}

void GameScreen::drawCoins(QPainter& painter) {
    QPixmap coinImage(":/images qt/coin.png");
    int coinWidth = coinImage.width();
    for (int i = 0; i < playerCoins; ++i) {
        painter.drawPixmap(i * (coinWidth + 5), 55, coinImage);
    }
}

void GameScreen::drawShield(QPainter &painter) {
    QPixmap shieldImage(":/images qt/shield.png");
    int shieldWidth = shieldImage.width();
    for (int i = 0; i < shieldCount; ++i) {
        painter.drawPixmap(i * (shieldWidth + 5), 110, shieldImage);
    }
}

void GameScreen::resetUpShot() {
    canShootUp = true;
    upShotTimer->stop();
}

void GameScreen::resetDownShot() {
    canShootDown = true;
    downShotTimer->stop();
}

void GameScreen::resetLeftShot() {
    canShootLeft = true;
    leftShotTimer->stop();
}

void GameScreen::resetRightShot() {
    canShootRight = true;
    rightShotTimer->stop();
}

void GameScreen::resetInvincibility() {
    isInvincible = false;
}
