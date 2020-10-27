#include "UI.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UI w;
    w.resize(1920, 1080);
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    return a.exec();
}
