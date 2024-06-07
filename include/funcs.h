#ifndef FUNCS_H
#define FUNCS_H

#include <QMessageBox>
#include <QLineEdit>
#include <QRegularExpression>
#include <QString>
#include <regex>

void cngEchoMode(QLineEdit *lineEdit);
bool isValidEmail(const QString& email);
bool isValidPassword(const QString& password);

#endif // FUNCS_H
