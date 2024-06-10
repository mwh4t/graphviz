#include "include/authorizationwindow.h"
#include "ui_authorizationwindow.h"
#include "include/mainwindow.h"
#include "include/utils.h"

AuthorizationWindow::AuthorizationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthorizationWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./users.db");
    if(!db.open())
        qDebug() << "Ошибка запуска БД: " << db.lastError();
    else
        createUsersTable(db);

    json loadedData = jsonParser();

    // проверка состояние флага для checkbox
    if(!loadedData.empty() && loadedData.contains("checkbox state"))
    {
        bool isChecked = loadedData["checkbox state"].get<bool>();
        ui->checkBox->setChecked(isChecked);

        // подстановка данных юзера из json
        if(isChecked && !loadedData.empty() && loadedData.contains("current account"))
        {
            QString email = QString::fromStdString(loadedData["current account"]["email"]);
            QString password = QString::fromStdString(loadedData["current account"]["password"]);

            ui->email_lineEdit->setText(email);
            ui->pw_lineEdit->setText(password);
        }
    }
}

AuthorizationWindow::~AuthorizationWindow()
{
    delete ui;
}

void AuthorizationWindow::on_signin_pushButton_clicked()
{
    /*
     * функция входа в аккаунт
    */
    QString email = ui->email_lineEdit->text();
    QString password = ui->pw_lineEdit->text();

    // проверка формата почты
    if(!isValidEmail(email))
    {
        QMessageBox::critical(this, "", "Неверный формат почты!");
        return;
    }

    // проверка формата пароля
    if(!isValidPassword(password))
    {
        QMessageBox::critical(this, "", "Неверный формат пароля!");
        return;
    }

    // проверка наличия юзера в БД
    if(checkUserCredentials(db, email, password))
    {
        QMessageBox::information(this, "", "Вход выполнен успешно!");

        // переход в главное окно
        MainWindow *mw = new MainWindow();
        mw->show();
        this->close();

        // сохранение данных юзера в json
        if(ui->checkBox->isChecked())
        {
            json j;
            j["checkbox state"] = true;
            j["current account"]["email"] = email.toStdString();
            j["current account"]["password"] = password.toStdString();

            jsonSaver(j);
        }
        else
        {
            json j;
            j["checkbox state"] = false;
            j["current account"]["email"] = email.toStdString();
            j["current account"]["password"] = password.toStdString();

            jsonSaver(j);
        }
    }
    else
        QMessageBox::critical(this, "", "Неверная почта или пароль!");
}

void AuthorizationWindow::on_signup_pushButton_clicked()
{
    /*
     * функция регистрации аккаунта
    */
    QString email = ui->email_lineEdit_2->text();
    QString password = ui->pw_lineEdit_2->text();
    QString confirmPassword = ui->pw_lineEdit_3->text();

    // проверка формата почты
    if(!isValidEmail(email))
    {
        QMessageBox::critical(this, "", "Неверный формат почты!");
        return;
    }

    // проверка формата пароля
    if(!isValidPassword(password))
    {
        QMessageBox::critical(this, "", "Неверный формат пароля!");
        return;
    }

    // проверка совпадения паролей
    if(password != confirmPassword)
    {
        QMessageBox::critical(this, "", "Пароли не совпадают!");
        return;
    }

    // добавление нового юзера в БД
    if(addUser(db, email, password))
    {
        QMessageBox::information(this, "", "Регистрация прошла успешно!");

        // переход в главное окно
        MainWindow *mw = new MainWindow();
        mw->show();
        this->close();
    }
    else
        QMessageBox::critical(this, "", "Ошибка регистрации! Возможно, пользователь "
                                        "с такой почтой уже существует.");
}

void AuthorizationWindow::on_show_pushButton_clicked()
{
    /*
     * изменение отображения содержимого lineEdit на
     * странице входа в аккаунт
    */
    cngEchoMode(ui->pw_lineEdit);
}

void AuthorizationWindow::on_show_pushButton_2_clicked()
{
    /*
     * изменение отображения содержимого lineEdit на
     * странице регистрации аккаунта 1
    */
    cngEchoMode(ui->pw_lineEdit_2);
}

void AuthorizationWindow::on_show_pushButton_3_clicked()
{
    /*
     * изменение отображения содержимого lineEdit на
     * странице регистрации аккаунта 1
    */
    cngEchoMode(ui->pw_lineEdit_3);
}

void AuthorizationWindow::on_forgotpw_pushButton_clicked()
{
    /*
     * переход на страницу с восстановлением пароля
    */
    ui->stackedWidget->setCurrentIndex(2);
}

void AuthorizationWindow::on_noacc_pushButton_clicked()
{
    /*
     * переход на страницу с регистрацией аккаунта
    */
    ui->stackedWidget->setCurrentIndex(1);
}

void AuthorizationWindow::on_back_pushButton_clicked()
{
    /*
     * переход на страницу входа в аккаунт
    */
    ui->stackedWidget->setCurrentIndex(0);
}

void AuthorizationWindow::on_back_pushButton_2_clicked()
{
    /*
     * переход на страницу входа в аккаунт
    */
    ui->stackedWidget->setCurrentIndex(0);
}
