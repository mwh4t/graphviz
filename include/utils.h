#ifndef UTILS_H
#define UTILS_H

#include "libs/json/json.hpp"
#include "libs/qcustomplot/qcustomplot.h"
#include "libs/exprtk/exprtk.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>
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

// методы для основного функционала
void updateLineEdit(QLineEdit* lineEdit, const QString& text);
void updateCursorPos(QLineEdit* lineEdit, const qint32 num);
double evaluateExpression(const std::string &expr, double x);
void updateBackButtonState(QStackedWidget* stackedWidget, QAction* back);
void setGraphColor(QCustomPlot* customPlot, QString background,
                   QString captions, QString line);
void lightThemeChanging(QAction* back, QAction* profile, QAction* theme, QAction* gh,
                        QCustomPlot* graph, QMainWindow* MainWindow);
void darkThemeChanging(QAction* back, QAction* profile, QAction* theme, QAction* gh,
                        QCustomPlot* graph, QMainWindow* MainWindow);
#endif // UTILS_H
