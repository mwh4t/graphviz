#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/utils.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setFocus();

    // зум и перетаскивание графика
    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    /*
     * функция нажатия Enter для вызова слота
    */
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
        on_enter_pushButton_clicked();

    QMainWindow::keyPressEvent(event);
}



void MainWindow::enterEvent(QEnterEvent *event) {
    if (event->type() == QEvent::Enter) {
        QWidget *widget = QApplication::widgetAt(QCursor::pos());
        if (widget == ui->line) {
            // Adjust QSizePolicy for ui->stackedWidget_2
            ui->stackedWidget_2->setSizePolicy(QSizePolicy::Preferred, ui->stackedWidget_2->sizePolicy().verticalPolicy());
            ui->stackedWidget_2->updateGeometry();
        }
    }
    QMainWindow::enterEvent(event);
}



void MainWindow::on_enter_pushButton_clicked()
{
    /*
     * функция кнопки ввода
    */
    // json loadedData = jsonParser();
    QString qExpression = ui->lineEdit->text();
    std::string expression = qExpression.toStdString();

    // подготовка данных
    int numPoints = 100; // количество точек
    QVector<double> x(numPoints), y(numPoints);
    for (int i = 0; i < numPoints; i++)
    {
        x[i] = i / 10.0;  // значения x
        y[i] = evaluateExpression(expression, x[i]);  // значения y
    }

    // добавление графика
    QCustomPlot *customPlot = ui->widget;
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);

    // Изменение цвета графика
    QPen graphPen;
    graphPen.setColor(QColor(Qt::black)); // Установите нужный цвет
    graphPen.setWidth(2);
    customPlot->graph(0)->setPen(graphPen);

    customPlot->xAxis->setRange(0, 10);
    customPlot->yAxis->setRange(*std::min_element(y.begin(), y.end()), *std::max_element(y.begin(), y.end()));

    customPlot->replot();
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
    /*
     * функция ввода ( в lineEdit
    */
    updateLineEdit(ui->lineEdit, "(");
}

void MainWindow::on_bracket2_pushButton_clicked()
{
    /*
     * функция ввода ) в lineEdit
    */
    updateLineEdit(ui->lineEdit, ")");
}

void MainWindow::on_less_pushButton_clicked()
{
    /*
     * функция ввода < в lineEdit
    */
    updateLineEdit(ui->lineEdit, "<");
}

void MainWindow::on_more_pushButton_clicked()
{    /*
     * функция ввода > в lineEdit
    */
    updateLineEdit(ui->lineEdit, ">");
}

void MainWindow::on_module_pushButton_clicked()
{
    /*
     * функция ввода || в lineEdit
    */
    updateLineEdit(ui->lineEdit, "||");
    updateCursorPos(ui->lineEdit, -1);
}

void MainWindow::on_comma_pushButton_clicked()
{
    /*
     * функция ввода , в lineEdit
    */
    updateLineEdit(ui->lineEdit, ",");
}

void MainWindow::on_less_or_equal_pushButton_clicked()
{
    /*
     * функция ввода <= в lineEdit
    */
    updateLineEdit(ui->lineEdit, "<=");
}

void MainWindow::on_more_or_equal_pushButton_clicked()
{
    /*
     * функция ввода >= в lineEdit
    */
    updateLineEdit(ui->lineEdit, ">=");
}

void MainWindow::on_sqrt_pushButton_clicked()
{
    /*
     * функция ввода sqrt() в lineEdit
    */
    updateLineEdit(ui->lineEdit, "sqrt()");
    updateCursorPos(ui->lineEdit, -1);
}

void MainWindow::on_pi_pushButton_clicked()
{
    /*
     * функция ввода Pi в lineEdit
    */
    updateLineEdit(ui->lineEdit, "Pi");
}

void MainWindow::on_zero_pushButton_clicked()
{
    /*
     * функция ввода 0 в lineEdit
    */
    updateLineEdit(ui->lineEdit, "0");
}

void MainWindow::on_one_pushButton_clicked()
{
    /*
     * функция ввода 1 в lineEdit
    */
    updateLineEdit(ui->lineEdit, "1");
}

void MainWindow::on_two_pushButton_clicked()
{
    /*
     * функция ввода 2 в lineEdit
    */
    updateLineEdit(ui->lineEdit, "2");
}

void MainWindow::on_three_pushButton_clicked()
{
    /*
     * функция ввода 3 в lineEdit
    */
    updateLineEdit(ui->lineEdit, "3");
}

void MainWindow::on_four_pushButton_clicked()
{
    /*
     * функция ввода 4 в lineEdit
    */
    updateLineEdit(ui->lineEdit, "4");
}

void MainWindow::on_five_pushButton_clicked()
{
    /*
     * функция ввода 5 в lineEdit
    */
    updateLineEdit(ui->lineEdit, "5");
}

void MainWindow::on_six_pushButton_clicked()
{
    /*
     * функция ввода 6 в lineEdit
    */
    updateLineEdit(ui->lineEdit, "6");
}

void MainWindow::on_seven_pushButton_clicked()
{
    /*
     * функция ввода 7 в lineEdit
    */
    updateLineEdit(ui->lineEdit, "7");
}

void MainWindow::on_eight_pushButton_clicked()
{
    /*
     * функция ввода 8 в lineEdit
    */
    updateLineEdit(ui->lineEdit, "8");
}

void MainWindow::on_nine_pushButton_clicked()
{
    /*
     * функция ввода 9 в lineEdit
    */
    updateLineEdit(ui->lineEdit, "9");
}

void MainWindow::on_div_pushButton_clicked()
{
    /*
     * функция ввода / в lineEdit
    */
    updateLineEdit(ui->lineEdit, "/");
}

void MainWindow::on_increase_pushButton_clicked()
{
    /*
     * функция ввода * в lineEdit
    */
    updateLineEdit(ui->lineEdit, "*");
}

void MainWindow::on_minus_pushButton_clicked()
{
    /*
     * функция ввода - в lineEdit
    */
    updateLineEdit(ui->lineEdit, "-");
}

void MainWindow::on_plus_pushButton_clicked()
{
    /*
     * функция ввода + в lineEdit
    */
    updateLineEdit(ui->lineEdit, "+");
}

void MainWindow::on_equal_pushButton_clicked()
{
    /*
     * функция ввода = в lineEdit
    */
    updateLineEdit(ui->lineEdit, "=");
}

void MainWindow::on_point_pushButton_clicked()
{
    /*
     * функция ввода . в lineEdit
    */
    updateLineEdit(ui->lineEdit, ".");
}

void MainWindow::on_back_pushButton_clicked()
{
    /*
     * функция перемещения курсора назад
    */
    updateCursorPos(ui->lineEdit, -1);
}

void MainWindow::on_forth_pushButton_clicked()
{
    /*
     * функция перемещения курсора вперёд
    */
    updateCursorPos(ui->lineEdit, 1);
}

void MainWindow::on_backspace_pushButton_clicked()
{
    /*
     * функция стирания последнего символа
    */
    ui->lineEdit->backspace();
}
