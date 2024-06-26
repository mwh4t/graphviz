#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVector>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_x_pushButton_clicked();

    void on_y_pushButton_clicked();

    void on_a2_pushButton_clicked();

    void on_ab_pushButton_clicked();

    void on_bracket1_pushButton_clicked();

    void on_bracket2_pushButton_clicked();

    void on_less_pushButton_clicked();

    void on_more_pushButton_clicked();

    void on_module_pushButton_clicked();

    void on_comma_pushButton_clicked();

    void on_less_or_equal_pushButton_clicked();

    void on_more_or_equal_pushButton_clicked();

    void on_sqrt_pushButton_clicked();

    void on_pi_pushButton_clicked();

    void on_zero_pushButton_clicked();

    void on_one_pushButton_clicked();

    void on_two_pushButton_clicked();

    void on_three_pushButton_clicked();

    void on_four_pushButton_clicked();

    void on_five_pushButton_clicked();

    void on_six_pushButton_clicked();

    void on_seven_pushButton_clicked();

    void on_eight_pushButton_clicked();

    void on_nine_pushButton_clicked();

    void on_div_pushButton_clicked();

    void on_increase_pushButton_clicked();

    void on_minus_pushButton_clicked();

    void on_plus_pushButton_clicked();

    void on_equal_pushButton_clicked();

    void on_point_pushButton_clicked();

    void on_back_pushButton_clicked();

    void on_forth_pushButton_clicked();

    void on_backspace_pushButton_clicked();

    void on_enter_pushButton_clicked();

    void on_profile_triggered();

    void on_signin_pushButton_clicked();

    void on_signup_pushButton_clicked();

    void on_show_pushButton_clicked();

    void on_show_pushButton_2_clicked();

    void on_show_pushButton_3_clicked();

    void on_forgotpw_pushButton_clicked();

    void on_noacc_pushButton_clicked();

    void on_back_triggered();

    void on_gh_triggered();

    void on_logout_pushButton_clicked();

    void on_show_pushButton_4_clicked();

    void on_abc_pushButton_clicked();

    void on_theme_triggered();

private:
    Ui::MainWindow *ui;

    QSqlDatabase db;
    QSqlQuery *query;
};
#endif // MAINWINDOW_H
