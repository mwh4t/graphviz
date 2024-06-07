#include "include/authorizationwindow.h"
#include "ui_authorizationwindow.h"
#include "include/mainwindow.h"
#include "include/funcs.h"

AuthorizationWindow::AuthorizationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthorizationWindow)
{
    ui->setupUi(this);
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

    if(!isValidEmail(email)) // проверка почты
        QMessageBox::critical(this, "", "Неверный формат почты!");
    else if(!isValidPassword(password)) // проверка пароля
        QMessageBox::critical(this, "", "Неверный формат пароля!");
    else if(email == "123" && password == "123") // проверка соответствия
    {
        MainWindow *mw = new MainWindow();
        mw->show();
        this->close();
    }
    else
        QMessageBox::critical(this, "", "Неверная почта или пароль!");
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
