#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/utils.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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

    ui->lineEdit->setFocus();

    // зум и перетаскивание графика
    ui->graph->setInteraction(QCP::iRangeZoom, true);
    ui->graph->setInteraction(QCP::iRangeDrag, true);
}

MainWindow::~MainWindow()
{
    delete ui;
}



/*
 * методы кнопок тулбара
*/
void MainWindow::on_back_triggered()
{
    /*
     * функция кнопки "Back"
    */
    if(ui->stackedWidget->currentIndex() == 3 || // страница регистрации
        ui->stackedWidget->currentIndex() == 1) // страница восстановления
        ui->stackedWidget->setCurrentIndex(2); // страница входа
    else
        ui->stackedWidget->setCurrentIndex(0); // главная страница
    updateBackButtonState(ui->stackedWidget, ui->back);
}

void MainWindow::on_profile_triggered()
{
    /*
     * переход на страницу профиля
    */
    json loadedData = jsonParser();

    if(!loadedData["current account"].empty())
    {
        ui->stackedWidget->setCurrentIndex(4);
        updateBackButtonState(ui->stackedWidget, ui->back);
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(2);
        updateBackButtonState(ui->stackedWidget, ui->back);
    }
}

void MainWindow::on_gh_triggered()
{
    /*
     * функция перехода на мой ГитХаб :)
    */
    QUrl url("https://github.com/mwh4t");
    QDesktopServices::openUrl(url);
}



/*
 * методы кнопок основной страницы
*/
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    /*
     * функция нажатия Enter для вызова слота
    */
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
        on_enter_pushButton_clicked();

    QMainWindow::keyPressEvent(event);
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
    QCustomPlot *customPlot = ui->graph;
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);

    // Изменение цвета графика
    QPen graphPen;
    graphPen.setColor(QColor(Qt::white));
    graphPen.setWidth(2);
    customPlot->graph(0)->setPen(graphPen);
    ui->graph->setBackground(QBrush(Qt::black));

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



/*
 * методы кнопок страницы профиля, входа и регистрации
*/
void MainWindow::on_signin_pushButton_clicked()
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

        ui->email_pf_lineEdit->setText(email);
        ui->pw_pf_lineEdit->setText(password);

        // переход на страницу профиля
        ui->stackedWidget->setCurrentIndex(4);

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

void MainWindow::on_signup_pushButton_clicked()
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

        // переход на страницу профиля
        ui->stackedWidget->setCurrentIndex(4);
    }
    else
        QMessageBox::critical(this, "", "Ошибка регистрации! Возможно, пользователь "
                                        "с такой почтой уже существует.");
}

void MainWindow::on_logout_pushButton_clicked()
{
    json loadedData = jsonParser();

    loadedData["current account"].clear();
    jsonSaver(loadedData);

    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_show_pushButton_clicked()
{
    /*
     * изменение отображения содержимого lineEdit на
     * странице входа в аккаунт
    */
    cngEchoMode(ui->pw_lineEdit);
}

void MainWindow::on_show_pushButton_2_clicked()
{
    /*
     * изменение отображения содержимого lineEdit на
     * странице регистрации аккаунта 1
    */
    cngEchoMode(ui->pw_lineEdit_2);
}

void MainWindow::on_show_pushButton_3_clicked()
{
    /*
     * изменение отображения содержимого lineEdit на
     * странице регистрации аккаунта 1
    */
    cngEchoMode(ui->pw_lineEdit_3);
}

void MainWindow::on_forgotpw_pushButton_clicked()
{
    /*
     * переход на страницу с восстановлением пароля
    */
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_noacc_pushButton_clicked()
{
    /*
     * переход на страницу с регистрацией аккаунта
    */
    ui->stackedWidget->setCurrentIndex(3);
}
