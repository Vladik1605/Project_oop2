#include <QDebug>
#include <QString>
#include <QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QCompleter>
#include <QMessageBox>
#include "addingshop.h"
#include "ui_addingshop.h"
#include "classes.h"
#include "addingworker.h"
#include "Exceptions.h"
#include "AddDirector.h"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(addShopLog, "add.shop")

/**
 * @brief Обработчик сообщений логирования.
 *
 * Эта функция записывает сообщения различных типов (Debug, Info, Warning, Critical, Fatal) в файл "add_shop_log.txt".
 *
 * @param type Тип сообщения (Debug, Info, Warning, Critical, Fatal).
 * @param context Контекст, в котором было вызвано сообщение.
 * @param msg Сообщение для записи в лог.
 */
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    QFile logFile("add_shop_log.txt");
    if (logFile.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&logFile);
        switch (type) {
        case QtDebugMsg:
            out << "Debug: " << msg << "\n";
            break;
        case QtInfoMsg:
            out << "Info: " << msg << "\n";
            break;
        case QtWarningMsg:
            out << "Warning: " << msg << "\n";
            break;
        case QtCriticalMsg:
            out << "Critical: " << msg << "\n";
            break;
        case QtFatalMsg:
            out << "Fatal: " << msg << "\n";
            abort();
        }
    }
}

/**
 * @brief Настройка логирования для приложения.
 *
 * Устанавливает обработчик сообщений логирования для записи сообщений
 * о событиях приложения в файл.
 */
void setupLogging() {
    qInstallMessageHandler(messageHandler);
}

/**
 * @brief Конструктор класса AddingShop.
 *
 * Этот конструктор инициализирует пользовательский интерфейс, подключается
 * к базе данных и настраивает автозаполнение для поля специализации магазина.
 *
 * @param db Указатель на объект базы данных. Если nullptr, создается новое соединение.
 * @param parent Родительский виджет для диалогового окна.
 */
AddingShop::AddingShop(QSqlDatabase *db, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddingShop)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);

    // Подключение к базе данных, если она не передана
    if(db==nullptr){
        this->db = QSqlDatabase::addDatabase("QMYSQL", "main_connection");
        this->db.setHostName("localhost");
        this->db.setDatabaseName("test");
        this->db.setUserName("root");
        this->db.setPassword("0504Vladik");
        this->db.open();
    }
    else {
        this->db = *db;
        this->db.open();
    }

    this->setLayout(ui->formLayout);
    shop1 = new shop();

    // Получение списка специализаций для автозаполнения
    QStringList Shop_Spec;
    QSqlQuery query("SELECT specialization FROM specialization", this->db);
    while (query.next()) {
        Shop_Spec << query.value(0).toString();
    }

    // Настройка автозаполнителя для поля специализации
    QCompleter *completer = new QCompleter(Shop_Spec, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setFilterMode(Qt::MatchStartsWith);
    ui->lineEdit_Spec->setCompleter(completer);

    // Обработчик для автозаполнителя
    connect(completer, QOverload<const QString &>::of(&QCompleter::activated), this, [=](const QString &selectedName) {
        ui->lineEdit_Spec->setText(selectedName);
    });
}

/**
 * @brief Деструктор для класса AddingShop.
 *
 * Этот метод удаляет интерфейс пользователя, освобождая ресурсы.
 */
AddingShop::~AddingShop()
{
    delete ui;
}

/**
 * @brief Обработчик завершения редактирования поля "Название магазина".
 *
 * Устанавливает имя магазина в объект `shop1` после завершения редактирования.
 */
void AddingShop::on_lineEdit_Name_editingFinished()
{
    ui->label_3->setText("");
    shop1->setName(ui->lineEdit_Name->text());
}

/**
 * @brief Обработчик завершения редактирования поля "Адрес магазина".
 *
 * Устанавливает адрес магазина в объект `shop1` после завершения редактирования.
 */
void AddingShop::on_lineEdit_Address_editingFinished()
{
    ui->label_6->setText("");
    shop1->setAddress(ui->lineEdit_Address->text());
}

/**
 * @brief Обработчик завершения редактирования поля "Директор магазина".
 *
 * Устанавливает имя директора магазина в объект `shop1` после завершения редактирования.
 */
void AddingShop::on_lineEdit_Director_editingFinished()
{
    ui->label_7->setText("");
    if (shop1) {
        shop1->setDirector(ui->lineEdit_Director->text());
    }
}

/**
 * @brief Обработчик завершения редактирования поля "Специализация магазина".
 *
 * Устанавливает специализацию магазина в объект `shop1` после завершения редактирования.
 */
void AddingShop::on_lineEdit_Spec_editingFinished()
{
    ui->label_8->setText("");
    shop1->setSpec(ui->lineEdit_Spec->text());
}

/**
 * @brief Обработчик нажатия на кнопку "Добавить магазин".
 *
 * Проверяет введенные данные, добавляет магазин в базу данных и очищает поля формы.
 * Если произошла ошибка, генерируется исключение.
 *
 * @param checked Статус кнопки (не используется).
 */
void AddingShop::on_SaveButton_clicked(bool checked)
{
    int id = -1;
    QString test_str = shop1->getName();
    qDebug(addShopLog) << "Проверка существования магазина с именем:" << test_str;

    QSqlQuery query(db);
    query.exec("SELECT shop_name FROM shop WHERE shop_name='"+test_str+"'");
    while(query.next()){
        id = query.value(0).toInt();
    }

    try {
        // Проверка на пустые поля и ошибки
        if(id != -1){
            errors.insert(ui->label_3, "Данное название уже занято");
            qWarning(addShopLog) << "Ошибка: Данное название уже занято";
        }

        if(shop1->getAddress() == ""){
            errors.insert(ui->label_6, "Это обязательное поле");
            qWarning(addShopLog) << "Ошибка: адрес не может быть пустым";
        }

        if(shop1->getName() == ""){
            errors.insert(ui->label_3, "Это обязательное поле");
            qWarning(addShopLog) << "Ошибка: имя магазина не может быть пустым";
        }

        if(shop1->getDirector() == ""){
            errors.insert(ui->label_7, "Это обязательное поле");
            qWarning(addShopLog) << "Ошибка: директор не может быть пустым";
        }

        if(shop1->getSpec() == ""){
            errors.insert(ui->label_8, "Это обязательное поле");
            qWarning(addShopLog) << "Ошибка: специальность не может быть пустой";
        }

        // Если есть ошибки, выбрасываем исключение
        if(!errors.empty()){
            throw MyEx{errors};
        }

        // Добавление магазина и специализации в базу данных
        query.exec("SELECT Specid FROM specialization WHERE specialization='"+shop1->getSpec()+"'");
        while(query.next()){
            id = query.value(0).toInt();
        }

        QString str_id = QString::number(id);
        if(id != -1){
            query.exec("INSERT INTO shop (shop_name, shop_address, spec_of_shop, director_name_shop) VALUES ('"+shop1->getName()+"', '"+shop1->getAddress()+"', '"+str_id+"' , '"+shop1->getDirector()+"')");
            qDebug(addShopLog) << "Добавление в базу данных магазина с именем:" << shop1->getName();
        } else {
            query.exec("INSERT INTO specialization (specialization) VALUES ('"+shop1->getSpec()+"')");
            qDebug(addShopLog) << "Добавление в базу данных специализации с именем:" << shop1->getSpec();

            query.exec("SELECT Specid FROM specialization WHERE specialization='"+shop1->getSpec()+"'");
            while(query.next()){
                id = query.value(0).toInt();
            }

            str_id = QString::number(id);
            query.exec("INSERT INTO shop (shop_name, shop_address, spec_of_shop, director_name_shop) VALUES ('"+shop1->getName()+"', '"+shop1->getAddress()+"', '"+str_id+"' , '"+shop1->getDirector()+"')");
            qDebug(addShopLog) << "Добавление в базу данных магазина с именем:" << shop1->getName();
        }

        db.close();

        // Открытие окна добавления работника
        if(!QSqlDatabase::database("test_connection").isOpen()){
            AddingWorker *worker = new AddingWorker(nullptr, shop1);
            worker->show();
        }
        close();

        // Очистка полей формы
        ui->lineEdit_Name->setText("");
        ui->lineEdit_Address->setText("");
        ui->lineEdit_Director->setText("");
        ui->lineEdit_Spec->setText("");

    }
    catch (MyEx& ex) {
        ex.ShowError();
        errors.clear();
    }
}
