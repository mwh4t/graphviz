#include "include/authorizationwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AuthorizationWindow aw;
    // aw.setWindowFlags(Qt::FramelessWindowHint);
    aw.setFixedSize(450, 600);
    aw.show();

    return a.exec();
}
