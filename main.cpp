#include "mainscreen.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainScreen mainScreen;
    mainScreen.showFullScreen();
    return app.exec();
}

