#ifndef CHARACTER_H
#define CHARACTER_H

#include <QWidget>
#include <QPixmap>

class Character : public QWidget {
    Q_OBJECT

public:
    enum Direction { Up, Down, Left, Right, None };
    Character(int x, int y, QWidget *parent = nullptr);
    void moveCharacter(int dx, int dy);
    void setDirection(Direction dir);
    void updateAnimation();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap characterImage;
    int xPos, yPos;

    QPixmap currentFrame;
    QVector<QPixmap> framesUp;
    QVector<QPixmap> framesDown;
    QVector<QPixmap> framesLeft;
    QVector<QPixmap> framesRight;
    int frameIndex;
    Direction currentDirection;
    QTimer *animationTimer;
};

#endif // CHARACTER_H
