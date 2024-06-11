#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/utils.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_x_pushButton_clicked()
{
    /*
     * функция ввода x в lineEdit
    */
    updateLineEdit(ui->lineEdit, "x");
}

void MainWindow::on_y_pushButton_clicked()
{
    /*
     * функция ввода y в lineEdit
    */
    updateLineEdit(ui->lineEdit, "y");
}

void MainWindow::on_a2_pushButton_clicked()
{
    /*
     * функция ввода ()^2 в lineEdit
    */
    updateLineEdit(ui->lineEdit, "()^2");
    updateCursorPos(ui->lineEdit, -3);
}

void MainWindow::on_ab_pushButton_clicked()
{
    /*
     * функция ввода ()^() в lineEdit
    */
    updateLineEdit(ui->lineEdit, "()^()");
    updateCursorPos(ui->lineEdit, -4);
}

void MainWindow::on_bracket1_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, "(");
}

void MainWindow::on_bracket2_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, ")");
}

void MainWindow::on_less_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, "<");
}

void MainWindow::on_more_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, ">");
}

void MainWindow::on_module_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, "||");
    updateCursorPos(ui->lineEdit, -1);
}

void MainWindow::on_comma_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, ",");
}

void MainWindow::on_less_or_equal_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, "<=");
}

void MainWindow::on_more_or_equal_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, ">=");
}

void MainWindow::on_sqrt_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, "sqrt()");
    updateCursorPos(ui->lineEdit, -1);
}

void MainWindow::on_pi_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, "Pi");
}

void MainWindow::on_zero_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, "0");
}

void MainWindow::on_one_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, "1");
}

void MainWindow::on_two_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, "2");
}

void MainWindow::on_three_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, "3");
}

void MainWindow::on_four_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, "4");
}

void MainWindow::on_five_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, "5");
}

void MainWindow::on_six_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, "6");
}

void MainWindow::on_seven_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, "7");
}

void MainWindow::on_eight_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, "8");
}

void MainWindow::on_nine_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, "9");
}

void MainWindow::on_div_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, "/");
}

void MainWindow::on_increase_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, "*");
}

void MainWindow::on_minus_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, "-");
}

void MainWindow::on_plus_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, "+");
}

void MainWindow::on_equal_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, "=");
}

void MainWindow::on_point_pushButton_clicked()
{
    updateLineEdit(ui->lineEdit, ".");
}

void MainWindow::on_back_pushButton_clicked()
{
    updateCursorPos(ui->lineEdit, -1);
}

void MainWindow::on_forth_pushButton_clicked()
{
    updateCursorPos(ui->lineEdit, 1);
}

void MainWindow::on_backspace_pushButton_clicked()
{
    ui->lineEdit->backspace();
}
