#ifndef UTILS_H
#define UTILS_H

#include "libs/json.hpp"
#include <iostream>
#include <fstream>
#include <QDebug>
#include <QMessageBox>
#include <QLineEdit>
#include <QRegularExpression>
#include <QString>
#include <regex>
#include <QSqlQuery>
#include <QSqlError>

// для удобства
using json = nlohmann::ordered_json;

// методы для работы с json
void jsonSaver(const json& data);
json jsonParser();

// методы для работы с БД
void createUsersTable(QSqlDatabase& db);
bool addUser(QSqlDatabase& db, const QString& email, const QString& password);
bool checkUserCredentials(QSqlDatabase& db, const QString& email, const QString& password);

// методы для авторизации
void cngEchoMode(QLineEdit *lineEdit);
bool isValidEmail(const QString& email);
bool isValidPassword(const QString& password);

#endif // UTILS_H
