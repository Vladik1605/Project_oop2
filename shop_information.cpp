#include "shop_information.h"
#include "ui_shop_information.h"
#include <QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QFile>
#include <QXmlStreamWriter>
#include "Exceptions.h"
#include "products.h"
#include "workers.h"
#include "redact_director.h"
#include "AddDirector.h"
#include "mainwindow.h"

/**
 * @brief Конструктор класса Shop_Information, инициализирует интерфейс и подключение к базе данных.
 * @param parent Родительский виджет.
 * @param str Название магазина для поиска информации.
 */
Shop_Information::Shop_Information(QWidget *parent, QString str)
    : QDialog(parent)
    , ui(new Ui::Shop_Information)
{
    ui->setupUi(this);  // Инициализация UI
    this->setLayout(ui->gridLayout);  // Установка компоновки
    ui->lineEdit_Name->setEnabled(false);  // Отключение редактирования полей
    ui->lineEdit_Address->setEnabled(false);
    ui->lineEdit_Director->setEnabled(false);
    ui->lineEdit_Spec->setEnabled(false);

    // Подключение к базе данных
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("0504Vladik");
    db.open();

    shop_name = str;  // Название магазина
    this->setAttribute(Qt::WA_DeleteOnClose);  // Установка атрибута для автоматического удаления при закрытии

    QSqlQuery query(db);  // Создание запроса для работы с базой данных

    // Загрузка списка специализаций магазина
    QStringList Shop_Spec;
    query.exec("SELECT specialization FROM specialization");
    while (query.next()) {
        Shop_Spec << query.value(0).toString();
    }

    // Настройка автозаполнения для поля специализации
    QCompleter *completer = new QCompleter(Shop_Spec, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setFilterMode(Qt::MatchStartsWith);
    ui->lineEdit_Spec->setCompleter(completer);

    // Обработчик для выбора специализации из автозаполнения
    connect(completer, QOverload<const QString &>::of(&QCompleter::activated), this, [=](const QString &selectedName) {
        ui->lineEdit_Spec->setText(selectedName);
    });

    firstClick = true;  // Инициализация флага для первого клика

    QString str_id;
    shop_inf = new shop;  // Создание объекта для магазина
    query.exec("SELECT shop_name, shop_address, director_name_shop, spec_of_shop, idShop FROM shop WHERE shop_name='" + str + "'");
    while (query.next()) {
        // Заполнение информации о магазине
        ui->lineEdit_Name->setText(query.value(0).toString());
        shop_inf->setName(query.value(0).toString());

        ui->lineEdit_Address->setText(query.value(1).toString());
        shop_inf->setAddress(query.value(1).toString());

        ui->lineEdit_Director->setText(query.value(2).toString());
        shop_inf->setDirector(query.value(2).toString());

        str_id = query.value(3).toString();
        shop_id = query.value(4).toString();
    }

    // Получение специализации магазина
    query.exec("SELECT specialization FROM specialization WHERE Specid='" + str_id + "'");
    while (query.next()) {
        ui->lineEdit_Spec->setText(query.value(0).toString());
        shop_inf->setSpec(query.value(0).toString());
    }
}

/**
 * @brief Деструктор класса Shop_Information.
 */
Shop_Information::~Shop_Information()
{
    delete ui;  // Очистка ресурсов интерфейса
}

/**
 * @brief Обработчик завершения редактирования поля "Название магазина".
 */
void Shop_Information::on_lineEdit_Name_editingFinished()
{
    ui->label_5->setText("");  // Очистка метки ошибки
    shop_inf->setName(ui->lineEdit_Name->text());  // Установка значения в объект магазина
}

/**
 * @brief Обработчик завершения редактирования поля "Адрес магазина".
 */
void Shop_Information::on_lineEdit_Address_editingFinished()
{
    ui->label_6->setText("");  // Очистка метки ошибки
    shop_inf->setAddress(ui->lineEdit_Address->text());  // Установка адреса магазина
}

/**
 * @brief Обработчик завершения редактирования поля "Директор магазина".
 * Проверка на корректность введенных данных для директора.
 */
void Shop_Information::on_lineEdit_Director_editingFinished()
{
    ui->label_7->setText("");  // Очистка метки ошибки

    if (shop_inf) {
        try {
            QString *str = new QString;
            *str = ui->lineEdit_Director->text();
            ValidatorName(str);  // Валидация имени директора
            shop_inf->setDirector(ui->lineEdit_Director->text());  // Установка имени директора
        } catch (ExCorrection& ex) {
            QMessageBox::information(this, "Внимание!", ex.what(), QMessageBox::Ok);  // Показ ошибки
            ui->lineEdit_Director->setText("");  // Очистка поля
        }
    }
}

/**
 * @brief Обработчик завершения редактирования поля "Специализация магазина".
 */
void Shop_Information::on_lineEdit_Spec_editingFinished()
{
    ui->label_8->setText("");  // Очистка метки ошибки
    shop_inf->setSpec(ui->lineEdit_Spec->text());  // Установка специализации магазина
}


/**
 * @brief Обрабатывает нажатие на кнопку "Сохранить" или "Редактировать" в зависимости от состояния.
 *
 * Если это первый клик, то кнопки становятся доступными для редактирования, а сама кнопка меняет текст на "Сохранить".
 * При втором клике выполняется проверка введенных данных и обновление информации в базе данных.
 */
void Shop_Information::on_RedactButton_clicked()
{
    if (firstClick) {
        // Изменение текста кнопки и активация полей ввода
        this->ui->RedactButton->setText("Сохранить");
        ui->lineEdit_Name->setEnabled(true);
        ui->lineEdit_Address->setEnabled(true);
        ui->lineEdit_Director->setEnabled(true);
        ui->lineEdit_Spec->setEnabled(true);
        firstClick = false;
    }
    else {
        int id=-1;
        QSqlQuery query(db);

        // Проверка на наличие магазина с таким же именем
        query.exec("SELECT shop_name FROM shop WHERE shop_name='"+shop_inf->getName()+"' AND  idShop<>'"+shop_id+"' ");
        while(query.next()){
            id=query.value(0).toInt();
        }

        try {
            QMap<QLabel*, QString> errors;

            // Проверка обязательных полей на пустоту
            if(id==-1){
                shop_inf->setName(ui->lineEdit_Name->text());
            }
            else{
                errors.insert(ui->label_5, "Данное название уже занято");
            }
            if(shop_inf->getAddress()==""){
                errors.insert(ui->label_6, "Это обязательное поле");
            }
            if(shop_inf->getName()==""){
                errors.insert(ui->label_5, "Это обязательное поле");
            }
            if(shop_inf->getDirector()==""){
                errors.insert(ui->label_7, "Это обязательное поле");
            }
            if(shop_inf->getSpec()==""){
                errors.insert(ui->label_8, "Это обязательное поле");
            }

            // Вывод ошибок, если они есть
            if(!errors.empty()){
                throw MyEx{errors};
            }

            id=-1;
            query.exec("SELECT Specid FROM specialization WHERE specialization='"+shop_inf->getSpec()+"'");
            while(query.next()){
                id=query.value(0).toInt();
            }

            QString str_id=QString::number(id);
            // Обновление информации о магазине в базе данных
            if(id!=-1){
                query.exec("UPDATE shop SET shop_name='"+shop_inf->getName()+"', shop_address='"+shop_inf->getAddress()+"', spec_of_shop='"+str_id+"', director_name_shop='"+shop_inf->getDirector()+"' WHERE idShop='"+shop_id+"'");
                query.exec("UPDATE director SET FIO='"+shop_inf->getDirector()+"' WHERE work_place='"+shop_id+"'");
            }
            else{
                // Вставка новой специализации, если она не найдена
                query.exec("INSERT INTO specialization (specialization) VALUES ('"+shop_inf->getSpec()+"')");
                query.exec("SELECT Specid FROM specialization WHERE specialization='"+shop_inf->getSpec()+"'");
                while(query.next()){
                    id=query.value(0).toInt();
                }
                str_id=QString::number(id);
                query.exec("UPDATE shop SET shop_name='"+shop_inf->getName()+"', shop_address='"+shop_inf->getAddress()+"', spec_of_shop='"+str_id+"', director_name_shop='"+shop_inf->getDirector()+"' WHERE idShop='"+shop_id+"'");
                query.exec("UPDATE director SET FIO='"+shop_inf->getName()+"' WHERE work_place='"+shop_id+"'");
            }

            // Смена состояния кнопки и деактивация полей ввода
            this->ui->RedactButton->setText("Редактировать");
            ui->lineEdit_Name->setEnabled(false);
            ui->lineEdit_Address->setEnabled(false);
            ui->lineEdit_Director->setEnabled(false);
            ui->lineEdit_Spec->setEnabled(false);
            firstClick = true;

            // Обновление значений в интерфейсе
            ui->lineEdit_Name->setText(shop_inf->getName());
            ui->lineEdit_Address->setText(shop_inf->getAddress());
            ui->lineEdit_Director->setText(shop_inf->getDirector());
            ui->lineEdit_Spec->setText(shop_inf->getSpec());
        }
        catch (MyEx& ex) {
            // Обработка ошибок валидации
            ex.ShowError();
        }
    }
}

/**
 * @brief Открывает окно для добавления новых продуктов в магазин.
 */
void Shop_Information::on_ProductsButton_clicked()
{
    new_products=new Products(nullptr, shop_id);
    new_products->show();
}

/**
 * @brief Открывает окно для управления работниками магазина.
 */
void Shop_Information::on_WorkersButton_clicked()
{
    Workers * worker;
    worker=new Workers(nullptr, shop_id);
    worker->show();
}

/**
 * @brief Открывает окно для редактирования или добавления директора магазина.
 */
void Shop_Information::on_DirectorButton_clicked()
{
    QSqlQuery query(db);
    QString id="";

    // Поиск ID директора, если он есть
    query.exec("SELECT idDirector FROM director WHERE work_place='"+shop_name+"'");
    while(query.next()){
        id=query.value(0).toString();
    }

    // Если директор найден, то редактируем его данные
    if(QString::compare(id,"")!=0){
        Redact_Director* window=new Redact_Director(nullptr, id);
        window->show();
    }
    else{
        // Если директора нет, создаем нового
        AddDirector *window=new AddDirector(nullptr, shop_inf);
        window->show();
    }
}

/**
 * @brief Удаляет магазин из базы данных с подтверждением.
 *
 * Отображается окно подтверждения перед удалением магазина. Если пользователь соглашается, выполняется удаление данных о магазине, директорах и товарах.
 */
void Shop_Information::on_DeleteButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение удаления",
                                  "Вы уверены, что хотите удалить магазин?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply != QMessageBox::Yes) {
        return;
    }

    // Запрос на удаление магазина и связанных данных
    emit requestRemoveButton(shop_name);
    QSqlQuery query(db);
    query.exec("DELETE FROM assistant WHERE work_place='"+shop_id+"'");
    query.exec("DELETE FROM director WHERE work_place='"+shop_id+"'");
    query.exec("DELETE FROM product_shop WHERE idShop='"+shop_id+"'");
    query.exec("DELETE FROM shop WHERE idShop='"+shop_id+"'");
}


