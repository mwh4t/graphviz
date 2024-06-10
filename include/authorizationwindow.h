#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

namespace Ui {
class AuthorizationWindow;
}

class AuthorizationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AuthorizationWindow(QWidget *parent = nullptr);
    ~AuthorizationWindow();

private slots:
    void on_signin_pushButton_clicked();

    void on_noacc_pushButton_clicked();

    void on_back_pushButton_clicked();

    void on_show_pushButton_clicked();

    void on_show_pushButton_2_clicked();

    void on_show_pushButton_3_clicked();

    void on_forgotpw_pushButton_clicked();

    void on_back_pushButton_2_clicked();

    void on_signup_pushButton_clicked();

private:
    Ui::AuthorizationWindow *ui;

    QSqlDatabase db;
    QSqlQuery *query;
};

#endif // AUTHORIZATIONWINDOW_H
