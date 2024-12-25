#ifndef CHEST_H
#define CHEST_H

#include <QWidget>
#include <QPainter>
#include <QString>

class Chest : public QWidget {
    Q_OBJECT

public:
    explicit Chest(QWidget* parent = nullptr);

    void setChestPosition(int x, int y);
    QString openChest(int& playerCoins);

protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    void updateFrame();

public:
    const int chestWidth = 200;
    const int chestHeight = 250;
    int chestX;
    int chestY;
    QTimer* timer;

    int currentFrame;
    QPixmap frames[12];
};

#endif // CHEST_H
