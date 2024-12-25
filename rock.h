#ifndef ROCK_H
#define ROCK_H

#include <QWidget>
#include <QPixmap>

class Rock : public QWidget {
    Q_OBJECT

public:
    int xPos;
    int yPos;

    Rock(int x, int y, QWidget *parent = nullptr);
    ~Rock() = default;

    int getX() const;
    int getY() const;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap rockImage;

};

#endif // ROCK_H
