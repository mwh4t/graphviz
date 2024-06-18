#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/utils.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    json loadedData = jsonParser();

    // инициализация и подключение к БД
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./users.db");
    if(!db.open())
        qDebug() << "ошибка запуска БД: " << db.lastError();
    else
        createUsersTable(db);

    // установка темы
    loadedData["isDarkTheme"];
    jsonSaver(loadedData);

    if(loadedData["isDarkTheme"].is_null() ||
        loadedData["isDarkTheme"].get<bool>())
    {
        darkThemeChanging(ui->back, ui->profile, ui->theme,
                          ui->gh, ui->graph, this);

        loadedData["isDarkTheme"] = true;
        jsonSaver(loadedData);
    }
    else
    {
        lightThemeChanging(ui->back, ui->profile, ui->theme,
                           ui->gh, ui->graph, this);
    }

    // проверка состояния флага для checkbox
    if(!loadedData.empty() && loadedData.contains("checkbox state"))
    {
        bool isChecked = loadedData["checkbox state"].get<bool>();
        ui->checkBox->setChecked(isChecked);

        // подстановка данных юзера из json если флаг установлен
        if(isChecked && loadedData.contains("current account"))
        {
            if (loadedData["current account"].contains("email") &&
                !loadedData["current account"]["email"].is_null()) {
                QString email = QString::fromStdString(
                    loadedData["current account"]["email"]);
                ui->email_lineEdit->setText(email);
            }

            if (loadedData["current account"].contains("password") &&
                !loadedData["current account"]["password"].is_null()) {
                QString password = QString::fromStdString(
                    loadedData["current account"]["password"]);
                ui->pw_lineEdit->setText(password);
            }
        }
    }

    // подстановка данных юзера из json в профиль
    if (loadedData.contains("current account"))
    {
        if (loadedData["current account"].contains("email") &&
            !loadedData["current account"]["email"].is_null()) {
            QString email = QString::fromStdString(
                loadedData["current account"]["email"]);
            ui->email_pf_lineEdit->setText(email);
        }

        if (loadedData["current account"].contains("password") &&
            !loadedData["current account"]["password"].is_null()) {
            QString password = QString::fromStdString(
                loadedData["current account"]["password"]);
            ui->pw_pf_lineEdit->setText(password);
        }
    }

    // зум и перетаскивание графика
    ui->graph->setInteraction(QCP::iRangeZoom, true);
    ui->graph->setInteraction(QCP::iRangeDrag, true);

    // ui->lineEdit->setFocus();
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
     * функция кнопки Back
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
     * функция перехода на страницу профиля
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

void MainWindow::on_theme_triggered()
{
    /*
     * функция изменения темы
    */
    json loadedData = jsonParser();

    if(loadedData["isDarkTheme"].get<bool>())
    {
        lightThemeChanging(ui->back, ui->profile, ui->theme,
                           ui->gh, ui->graph, this);
        loadedData["isDarkTheme"] = false;
        jsonSaver(loadedData);
    }
    else
    {
        darkThemeChanging(ui->back, ui->profile, ui->theme,
                          ui->gh, ui->graph, this);
        loadedData["isDarkTheme"] = true;
        jsonSaver(loadedData);
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
void MainWindow::on_enter_pushButton_clicked()
{
    /*
     * функция кнопки ввода
    */
    QString qExpression = ui->lineEdit->text();
    std::string expression = qExpression.toStdString();

    // подготовка данных
    int numPoints = 100; // количество точек
    QVector<double> x(numPoints), y(numPoints);
    for (int i = 0; i < numPoints; i++)
    {
        x[i] = i / 10.0; // значения x
        y[i] = evaluateExpression(expression, x[i]); // значения y
    }

    // добавление графика
    QCustomPlot* customPlot = ui->graph;
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);

    customPlot->xAxis->setRange(0, 10);
    customPlot->yAxis->setRange(*std::min_element(y.begin(), y.end()),
                                *std::max_element(y.begin(), y.end()));

    customPlot->replot();
}

void MainWindow::on_abc_pushButton_clicked()
{
    /*
     * функция выбора буквы для ввода в lineEdit
    */
    QMessageBox::critical(this, "", "temporarily unavailable!");
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
    // updateLineEdit(ui->lineEdit, "y");
    QMessageBox::critical(this, "", "temporarily unavailable!");
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
    // updateLineEdit(ui->lineEdit, "||");
    // updateCursorPos(ui->lineEdit, -1);
    QMessageBox::critical(this, "", "temporarily unavailable!");
}

void MainWindow::on_comma_pushButton_clicked()
{
    /*
     * функция ввода , в lineEdit
    */
    // updateLineEdit(ui->lineEdit, ",");
    QMessageBox::critical(this, "", "temporarily unavailable!");
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
    updateLineEdit(ui->lineEdit, "3.14");
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
    // if()
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
        QMessageBox::critical(this, "", "invalid e-mail format!");
        return;
    }

    // проверка формата пароля
    if(!isValidPassword(password))
    {
        QMessageBox::critical(this, "", "invalid password format!");
        return;
    }

    // проверка наличия юзера в БД
    if(checkUserCredentials(db, email, password))
    {
        QMessageBox::information(this, "", "the sign in went through!");

        ui->email_pf_lineEdit->setText(email);
        ui->pw_pf_lineEdit->setText(password);

        // переход на страницу профиля
        ui->stackedWidget->setCurrentIndex(4);

        // сохранение данных юзера в json
        if(ui->checkBox->isChecked())
        {
            json loadedData = jsonParser();
            loadedData["checkbox state"] = true;
            loadedData["current account"]["email"] = email.toStdString();
            loadedData["current account"]["password"] = password.toStdString();

            jsonSaver(loadedData);
        }
        else
        {
            json loadedData = jsonParser();
            loadedData["checkbox state"] = false;
            loadedData["current account"]["email"] = email.toStdString();
            loadedData["current account"]["password"] = password.toStdString();

            jsonSaver(loadedData);
        }

        // очистка строк
        ui->email_lineEdit->setText("");
        ui->pw_lineEdit->setText("");
    }
    else
        QMessageBox::critical(this, "", "invalid e-mail or password!");
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
        QMessageBox::critical(this, "", "invalid e-mail format!");
        return;
    }

    // проверка формата пароля
    if(!isValidPassword(password))
    {
        QMessageBox::critical(this, "", "invalid password format!");
        return;
    }

    // проверка совпадения паролей
    if(password != confirmPassword)
    {
        QMessageBox::critical(this, "", "passwords don't match!");
        return;
    }

    // добавление нового юзера в БД
    if(addUser(db, email, password))
    {
        QMessageBox::information(this, "", "the sign up went through!");

        // переход на страницу профиля
        ui->stackedWidget->setCurrentIndex(4);

        // очистка строк
        ui->email_lineEdit_2->setText("");
        ui->pw_lineEdit_2->setText("");
        ui->pw_lineEdit_3->setText("");
    }
    else
        QMessageBox::critical(this, "", "the sign up error!");
}

void MainWindow::on_logout_pushButton_clicked()
{
    /*
     * функция выхода из аккаунта
    */
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

void MainWindow::on_show_pushButton_4_clicked()
{
    /*
     * изменение отображения содержимого lineEdit на
     * странице профиля
    */
    cngEchoMode(ui->pw_pf_lineEdit);
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
