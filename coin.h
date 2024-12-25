#ifndef COIN_H
#define COIN_H

#include <QWidget>
#include <QPixmap>

class Coin : public QWidget {
    Q_OBJECT

public:
    Coin(int x, int y, QWidget *parent = nullptr);
    void show();
    void hide();
    QRect geometry() const;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int xPos;
    int yPos;
    QPixmap coinImage;
};

#endif // COIN_H
