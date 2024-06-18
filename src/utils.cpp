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

double evaluateExpression(const std::string &expr, double x)
{
    /*
     * функция для вычисления значений выражения
    */
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;

    symbol_table_t symbol_table;
    symbol_table.add_variable("x", x);
    symbol_table.add_constants();

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;
    if (!parser.compile(expr, expression))
    {
        std::cerr << "Error: " << parser.error() << std::endl;
        return 0.0;
    }

    return expression.value();
}

void updateBackButtonState(QStackedWidget* stackedWidget, QAction* back)
{
    /*
     * функция обновления состояния кнопки "back"
    */
    if (stackedWidget->currentIndex() > 0)
        back->setEnabled(true);
    else
        back->setEnabled(false);
}

void setGraphColor(QCustomPlot* customPlot, QString background,
                   QString captions, QString line)
{
    /*
     * функция изменения цвета графика
    */
    QColor backgroundColor = QColor(background); // цвет фона
    QColor labelColor = QColor(captions); // цвет подписей
    QColor lineColor = QColor(line); // цвет линии

    // установка цвета фона
    customPlot->setBackground(QBrush(backgroundColor));

    // настройка цветов осей
    customPlot->xAxis->setBasePen(QPen(labelColor)); // цвет осей
    customPlot->yAxis->setBasePen(QPen(labelColor));
    customPlot->xAxis->setTickPen(QPen(labelColor)); // цвет тиков
    customPlot->yAxis->setTickPen(QPen(labelColor));
    customPlot->xAxis->setSubTickPen(QPen(labelColor));
    customPlot->yAxis->setSubTickPen(QPen(labelColor));
    customPlot->xAxis->setTickLabelColor(labelColor); // цвет подписей тиков
    customPlot->yAxis->setTickLabelColor(labelColor);
    customPlot->xAxis->setLabelColor(labelColor); // цвет подписей осей
    customPlot->yAxis->setLabelColor(labelColor);

    // изменение цвета графика
    customPlot->addGraph();
    QPen graphPen;
    graphPen.setColor(lineColor); // установка цвета линии
    graphPen.setWidth(2);
    customPlot->graph(0)->setPen(graphPen);

    customPlot->replot();
}

void lightThemeChanging(QAction* back, QAction* profile, QAction* theme, QAction* gh,
                        QCustomPlot* graph, QMainWindow* MainWindow)
{
    /*
     * функция изменения темы на светлую
    */
    // применение стилей
    QString styleSheet = R"(
            QWidget {
                background-color: #f0f0f0;
                color: #2e2e2e;
                font-family: "American Typewriter";
            }

            /* QPushButton styling */
            QPushButton {
                background-color: #e0e0e0;
                color: #2e2e2e;
                border: 2px solid #b0b0b0;
                border-radius: 5px;
                padding: 5px 10px;
                font-family: "American Typewriter";
            }

            QPushButton:hover {
                background-color: #d0d0d0;
            }

            QPushButton:pressed {
                background-color: #c0c0c0;
            }

            /* QCheckBox styling */
            QCheckBox {
                color: #2e2e2e;
                font-family: "American Typewriter";
            }

            QCheckBox::indicator {
                width: 16px;
                height: 16px;
                border: 2px solid #b0b0b0;
                border-radius: 3px;
                background-color: #f0f0f0;
            }

            QCheckBox::indicator:checked {
                background-color: #2e2e2e;
            }

            QCheckBox::indicator:unchecked {
                background-color: #f0f0f0;
            }

            QCheckBox::indicator:hover {
                background-color: #c0c0c0;
            }

            QCheckBox::indicator:pressed {
                background-color: #f0f0f0;
            }

            /* QLabel styling */
            QLabel {
                color: #2e2e2e;
                font-family: "American Typewriter";
            }

            /* QLineEdit styling */
            QLineEdit {
                background-color: #e0e0e0;
                color: #2e2e2e;
                border: 2px solid #b0b0b0;
                border-radius: 5px;
                padding: 5px;
                font-family: "American Typewriter";
            }

            /* QToolBar styling */
            QToolBar {
                background-color: #f5f5f5;
                border-bottom: 2px solid #b0b0b0;
            }

            QToolBar QToolButton {
                background-color: none;
                color: #2e2e2e;
                border: none;
                padding: 5px;
                margin: 2px;
                font-family: "American Typewriter";
            }

            QToolBar QToolButton:hover {
                background-color: #e0e0e0;
            }

            QToolBar QToolButton:pressed {
                background-color: none;
            }

            /* QMenuBar styling */
            QMenuBar {
                background-color: #f0f0f0;
                color: #2e2e2e;
                border-bottom: 2px solid #b0b0b0;
            }

            QMenuBar::item {
                background-color: #f0f0f0;
                color: #2e2e2e;
                padding: 5px 10px;
            }

            QMenuBar::item:selected {
                background-color: #d0d0d0;
            }

            QMenu {
                background-color: #e0e0e0;
                color: #2e2e2e;
                border: 2px solid #b0b0b0;
            }

            QMenu::item {
                background-color: #e0e0e0;
                color: #2e2e2e;
                padding: 5px 10px;
            }

            QMenu::item:selected {
                background-color: #d0d0d0;
            }

            /* QStatusBar styling */
            QStatusBar {
                background-color: #f0f0f0;
                color: #2e2e2e;
            }

            QStatusBar::item {
                border: none;
            }
        )";
    MainWindow->setStyleSheet(styleSheet);

    // изменение иконок в тулбаре
    back->setIcon(QIcon(":/pics/back_dark.png"));
    profile->setIcon(QIcon(":/pics/profile_dark.png"));
    theme->setIcon(QIcon(":/pics/sun.png"));
    gh->setIcon(QIcon(":/pics/gh_dark.png"));

    // установка цвета графика
    setGraphColor(graph, "#f0f0f0", "#000000", "#000000");
}

void darkThemeChanging(QAction* back, QAction* profile, QAction* theme, QAction* gh,
                        QCustomPlot* graph, QMainWindow* MainWindow)
{
    /*
     * функция изменения темы на тёмную
    */
    // применение стилей
    QString styleSheet = R"(
            QWidget {
                background-color: #2e2e2e;
                color: white;
                font-family: "American Typewriter";
            }

            /* QPushButton styling */
            QPushButton {
                background-color: #4d4d4d;
                color: white;
                border: 2px solid #646464;
                border-radius: 5px;
                padding: 5px 10px;
                font-family: "American Typewriter";
            }

            QPushButton:hover {
                background-color: #5a5a5a;
            }

            QPushButton:pressed {
                background-color: #3a3a3a;
            }

            /* QCheckBox styling */
            QCheckBox {
                color: #ffffff;
                font-family: "American Typewriter";
            }

            QCheckBox::indicator {
                width: 16px;
                height: 16px;
                border: 2px solid #646464;
                border-radius: 3px;
                background-color: #2e2e2e;
            }

            QCheckBox::indicator:checked {
                background-color: white;
            }

            QCheckBox::indicator:unchecked {
                background-color: #2e2e2e;
            }

            QCheckBox::indicator:hover {
                background-color: #454545;
            }

            QCheckBox::indicator:pressed {
                background-color: #2e2e2e;
            }

            /* QLabel styling */
            QLabel {
                color: #ffffff;
                font-family: "American Typewriter";
            }

            /* QLineEdit styling */
            QLineEdit {
                background-color: #3e3e3e;
                color: #ffffff;
                border: 2px solid #646464;
                border-radius: 5px;
                padding: 5px;
                font-family: "American Typewriter";
            }

            /* QToolBar styling */
            QToolBar {
                background-color: #1f1f1f;
                border-bottom: 2px solid #646464;
            }

            QToolBar QToolButton {
                background-color: none;
                color: #ffffff;
                border: none;
                padding: 5px;
                margin: 2px;
                font-family: "American Typewriter";
            }

            QToolBar QToolButton:hover {
                background-color: #262626;
            }

            QToolBar QToolButton:pressed {
                background-color: none;
            }

            /* QMenuBar styling */
            QMenuBar {
                background-color: #2e2e2e;
                color: #ffffff;
                border-bottom: 2px solid #646464;
            }

            QMenuBar::item {
                background-color: #2e2e2e;
                color: #ffffff;
                padding: 5px 10px;
            }

            QMenuBar::item:selected {
                background-color: #5a5a5a;
            }

            QMenu {
                background-color: #3e3e3e;
                color: #ffffff;
                border: 2px solid #646464;
            }

            QMenu::item {
                background-color: #3e3e3e;
                color: #ffffff;
                padding: 5px 10px;
            }

            QMenu::item:selected {
                background-color: #5a5a5a;
            }

            /* QStatusBar styling */
            QStatusBar {
                background-color: #2e2e2e;
                color: #ffffff;
            }

            QStatusBar::item {
                border: none;
            }
        )";
    MainWindow->setStyleSheet(styleSheet);

    // изменение иконок в тулбаре
    back->setIcon(QIcon(":/pics/back_light.png"));
    profile->setIcon(QIcon(":/pics/profile_light.png"));
    theme->setIcon(QIcon(":/pics/moon.png"));
    gh->setIcon(QIcon(":/pics/gh_light.png"));

    // установка цвета графика
    setGraphColor(graph, "#2e2e2e", "#ffffff", "#ffffff");
}
