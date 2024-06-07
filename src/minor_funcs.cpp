#include "include/funcs.h"

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

bool isValidEmail(const QString& email) {
    /*
     * функция соответствия почты паттерну
    */
    const QRegularExpression pattern(R"((\w+)(\.{1}\w+)*@(\w+)(\.\w{2,})+)");

    return pattern.match(email).hasMatch();
}

bool isValidPassword(const QString& password) {
    /*
     * функция соответствия пароля паттерну
    */
    const QRegularExpression pattern(R"((?=.*[A-Z])(?=.*[a-z])(?=.*\d).{4,})");

    return pattern.match(password).hasMatch();
}
