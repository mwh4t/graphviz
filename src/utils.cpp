#include "include/utils.h"
#include "include/mainwindow.h"

void jsonSaver(const json& data)
{
    /*
     * функция, позволяющая сохранить данные в json-файл
    */
    std::ofstream file("data.json");
    file << std::setw(4) << data << std::endl;
    file.close();
}

json jsonParser()
{
    /*
     * функция, позволяющая выгрузить данные из json-файла
    */
    std::ifstream readFile("data.json");
    json loadedData;
    readFile >> loadedData;
    readFile.close();

    return loadedData;
}

void createUsersTable(QSqlDatabase& db)
{
    /*
     * функция создания таблицы
    */
    QSqlQuery query(db);
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS users ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                               "email TEXT NOT NULL UNIQUE, "
                               "password TEXT NOT NULL)";
    if(!query.exec(createTableQuery))
        qDebug() << "Failed to create table: " << query.lastError();
}

bool addUser(QSqlDatabase& db, const QString& email, const QString& password)
{
    /*
     * функция для вставки новых пользователей
    */
    QSqlQuery query(db);
    query.prepare("INSERT INTO users (email, password) VALUES (:email, :password)");
    query.bindValue(":email", email);
    query.bindValue(":password", password);

    if(!query.exec()) {
        qDebug() << "Failed to add user: " << query.lastError();
        return false;
    }
    return true;
}

bool checkUserCredentials(QSqlDatabase& db, const QString& email, const QString& password)
{
    /*
     * функция проверки учетных данных пользователя
    */
    QSqlQuery query(db);
    query.prepare("SELECT * FROM users WHERE email = :email AND password = :password");
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    query.exec();

    return query.next();
}

void cngEchoMode(QLineEdit *lineEdit)
{
    /*
     * функция изменения отображения содержимого lineEdit
    */
    QLineEdit::EchoMode currentMode = lineEdit->echoMode();

    if(currentMode == QLineEdit::Normal)
        lineEdit->setEchoMode(QLineEdit::Password);
    else
        lineEdit->setEchoMode(QLineEdit::Normal);
}

bool isValidEmail(const QString& email)
{
    /*
     * функция соответствия почты паттерну
    */
    const QRegularExpression pattern(R"((\w+)(\.{1}\w+)*@(\w+)(\.\w{2,})+)");

    return pattern.match(email).hasMatch();
}

bool isValidPassword(const QString& password)
{
    /*
     * функция соответствия пароля паттерну
    */
    const QRegularExpression pattern(R"((?=.*[A-Z])(?=.*[a-z])(?=.*\d).{4,})");

    return pattern.match(password).hasMatch();
}

void updateLineEdit(QLineEdit* lineEdit, const QString& text)
{
    /*
     * функция обновления текста в lineEdit
    */
    // QString currentText = lineEdit->text();
    lineEdit->insert(text);
}

void updateCursorPos(QLineEdit* lineEdit, const qint32 num)
{
    /*
     * функция изменения позиции курсора в lineEdit
    */
    lineEdit->setCursorPosition(lineEdit->cursorPosition() + num);
}
