#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPainter>
#include <QPixmap>
#include <QStackedWidget>
#include <QMediaPlayer>
#include <memory>
#include "gamescreen.h"

class MainScreen : public QWidget {
    Q_OBJECT

public:
    MainScreen(QWidget *parent = nullptr);
    bool sound = true;

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void startGame();
    void exitGame();
    void soundGame();

private:
    QStackedWidget *stackedWidget;
    GameScreen *gameScreen;
    QMediaPlayer *player;
    QPushButton *soundButton;
};

#endif // MAINSCREEN_H
