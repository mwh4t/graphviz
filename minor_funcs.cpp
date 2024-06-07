#include "funcs.h"

void cngEchoMode(QLineEdit *lineEdit)
{
    /*
     * функция изменения отображения содержимого lineEdit
    */
    QLineEdit::EchoMode currentMode = lineEdit->echoMode();

    if (currentMode == QLineEdit::Normal)
        lineEdit->setEchoMode(QLineEdit::Password);
    else
        lineEdit->setEchoMode(QLineEdit::Normal);
}
