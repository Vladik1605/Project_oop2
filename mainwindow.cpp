/*! \file */

#include <QtUiTools>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QObject>
#include <QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QSqlError>
#include <QDomDocument>
#include "shop_information.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addingshop.h"
#include "filesaving.h"
/**
 * @brief Конструктор главного окна.
 * Инициализирует пользовательский интерфейс, подключение к базе данных,
 * а также настройку виджетов и отображение списка магазинов.
 *
 * @param parent родительский элемент окна.
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);  ///< Инициализация UI компонента
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(ui->verticalLayout);

    // Настройка подключения к базе данных
    db = QSqlDatabase::addDatabase("QMYSQL", "main_window_conection");
    db.setHostName("localhost");
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("0504Vladik");
    db.open();

    // Настройка для отображения прокручиваемого списка магазинов
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    scrollArea->setFixedWidth(ui->ChooseButton->width());
    scrollArea->setFixedHeight(175);

    menuContainer = new QWidget();
    menuLayout = new QVBoxLayout(menuContainer);

    scrollArea->setWidget(menuContainer);

    scrollArea->setVisible(false);  ///< Скрываем scrollArea изначально
    firstClick = true;  ///< Устанавливаем состояние для первого клика
    ui->verticalLayout->addWidget(scrollArea);
    ui->verticalLayout->setAlignment(scrollArea, Qt::AlignHCenter);
}

/**
 * @brief Деструктор главного окна.
 * Закрывает соединение с базой данных и освобождает ресурсы.
 */
MainWindow::~MainWindow() {
    if (db.isOpen()) {
        db.close();  ///< Закрытие соединения с базой данных
    }

    QSqlDatabase::removeDatabase("main_window_conection");
    delete ui;  ///< Удаление UI компонента

    if (menuContainer) {
        delete menuContainer;  ///< Освобождение памяти
    }

}

/**
 * @brief Обработчик кнопки для открытия окна добавления магазина.
 * Показывает окно для добавления нового магазина.
 */
void MainWindow::on_AddButton_clicked(bool checked) {
    AddingShop* dialogw = new AddingShop;
    dialogw->show();  ///< Открытие диалогового окна для добавления магазина
}

/**
 * @brief Метод для обработки нажатия кнопки pushButton_2, которая отображает и скрывает выпадающее меню.
 * При первом клике загружается список магазинов, при следующем — скрывается.
 */
void MainWindow::on_ChooseButton_clicked() {
    if (firstClick) {
        // Очистка текущих кнопок в меню
        while (QLayoutItem* item = menuLayout->takeAt(0)) {
            QWidget* widget = item->widget();
            if (widget) {
                widget->deleteLater();  ///< Удаляем старые кнопки
            }
            delete item;  ///< Удаляем layout-элемент
        }

        // Запрос в базу данных для получения списка магазинов
        QSqlQuery query(db);
        if (query.exec("SELECT shop_name FROM shop")) {
            while (query.next()) {
                QString strmenu = query.value(0).toString();  ///< Получаем название магазина
                QPushButton* button = new QPushButton(strmenu, menuContainer);

                // Подключаем обработчик события нажатия кнопки
                connect(button, &QPushButton::clicked, [this, strmenu]() {
                    Shop_Information* info = new Shop_Information(this, strmenu);
                    info->show();  ///< Открываем окно с информацией о магазине

                    connect(info, &Shop_Information::requestRemoveButton, this, &MainWindow::handleRemoveButtonRequest);
                });

                // Добавляем кнопку в layout
                menuLayout->addWidget(button);
            }
        } else {
            qWarning() << "Failed to execute query:" << query.lastError().text();  ///< Логирование ошибок выполнения запроса
        }

        firstClick = false;  ///< Изменяем состояние на второй клик
        scrollArea->setVisible(true);  ///< Показываем прокручиваемую область
    } else {
        // Очистка кнопок и скрытие прокручиваемой области
        while (QLayoutItem* item = menuLayout->takeAt(0)) {
            QWidget* widget = item->widget();
            if (widget) {
                widget->deleteLater();  ///< Удаляем старые кнопки
            }
            delete item;  ///< Удаляем layout-элемент
        }

        firstClick = true;  ///< Переключаем состояние на первый клик
        scrollArea->setVisible(false);  ///< Скрываем прокручиваемую область
    }
}

/**
 * @brief Удаляет кнопку по имени из меню.
 * Используется для удаления кнопок с экрана, когда они больше не нужны.
 *
 * @param buttonName название кнопки, которую нужно удалить.
 */
void MainWindow::removeButtonByName(const QString& buttonName) {
    // Поиск и удаление кнопки с заданным именем
    for (int i = 0; i < menuLayout->count(); ++i) {
        QLayoutItem* item = menuLayout->itemAt(i);
        if (!item)
            continue;

        QWidget* widget = item->widget();
        if (QPushButton* button = qobject_cast<QPushButton*>(widget)) {
            if (button->text() == buttonName) {
                menuLayout->removeWidget(button);
                button->deleteLater();  ///< Удаляем кнопку
                return;
            }
        }
    }
}



/**
 * @brief Метод для обработки нажатия на кнопку pushButton_3, которая открывает диалоговое окно для сохранения в файл.
 *
 */

void MainWindow::on_SaveButton_clicked()
{
    FileSaving* files;
    files=new FileSaving(this, "XML", nullptr);
    files->show();
}


/**
 * @brief Обработчик нажатия кнопки для загрузки последнего сохранения.
 *
 * Загружает данные из XML-файла и вставляет их в базу данных.
 * Перед этим очищает таблицы, если пользователь подтверждает действие.
 */
void MainWindow::on_UploadButton_clicked()
{
    // Запрос на подтверждение загрузки последнего сохранения
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение загрузки последнего сохранения",
                                  "Вы уверены, что хотите загрузить последнее сохранение?",
                                  QMessageBox::Yes | QMessageBox::No);

    // Если пользователь отменяет, выходим из функции
    if (reply != QMessageBox::Yes) {
        return;
    }

    // Очищаем данные в базе перед загрузкой
    QSqlQuery query(db);
    // query.exec("DELETE FROM assistant");
    // query.exec("DELETE FROM director");
    // query.exec("DELETE FROM product_shop");
    // query.exec("DELETE FROM product");
    // query.exec("DELETE FROM shop");
    // query.exec("DELETE FROM specialization");
    // query.exec("DELETE FROM type");

    // Открытие диалогового окна для выбора XML-файла
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open XML File"), "", tr("XML Files (*.xml)"));
    if (fileName.isEmpty()) {
        return;
    }

    // Открытие файла для чтения
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot open file for reading"));
        return;
    }

    // Парсинг XML-документа
    QDomDocument document;
    if (!document.setContent(&file)) {
        file.close();
        QMessageBox::warning(this, tr("Error"), tr("Failed to parse XML"));
        return;
    }
    file.close();

    /**
     * @brief Загрузка и вставка данных о специализациях из XML.
     *
     * Вставляет каждую специализацию в таблицу specialization.
     */
    QDomNodeList special = document.elementsByTagName("SPECIALIZATION").at(0).childNodes();
    for (int i = 0; i < special.count(); ++i) {
        QSqlQuery query(db);
        QDomElement spec = special.at(i).toElement();
        QString specialization = spec.firstChildElement("specialization").text();
        query.exec("SELECT Specid FROM specialization WHERE specialization='"+specialization+"'");
        int repeated_id=-1;
        while(query.next()){
            repeated_id=query.value(0).toInt();
        }
        if (repeated_id==-1){
        query.prepare("INSERT INTO specialization (specialization) VALUES (:specialization)");
        query.bindValue(":specialization", specialization);
        }
        if (!query.exec()) {
            QMessageBox::warning(this, tr("Error"), tr("Failed to insert shop data: %1").arg(query.lastError().text()));
        }
    }

    /**
     * @brief Загрузка и вставка данных о типах продуктов из XML.
     *
     * Вставляет каждый тип продукта в таблицу type.
     */
    QDomNodeList type = document.elementsByTagName("TYPE").at(0).childNodes();
    for (int i = 0; i < type.count(); ++i) {
        QDomElement tp = type.at(i).toElement();
        QString product_type = tp.firstChildElement("product_type").text();

        QSqlQuery query(db);
        query.exec("SELECT idType FROM type WHERE product_type='"+product_type+"'");
        int repeated_id=-1;
        while(query.next()){
            repeated_id=query.value(0).toInt();
        }
        if (repeated_id==-1){
        query.prepare("INSERT INTO type (product_type) VALUES (:product_type)");
        query.bindValue(":product_type", product_type);
        }
        if (!query.exec()) {
            QMessageBox::warning(this, tr("Error"), tr("Failed to insert shop data: %1").arg(query.lastError().text()));
        }
    }

    /**
     * @brief Загрузка и вставка данных о магазинах из XML.
     *
     * Вставляет каждый магазин в таблицу shop, связывая его с существующей специализацией.
     */
    QDomNodeList shops = document.elementsByTagName("SHOPS").at(0).childNodes();
    for (int i = 0; i < shops.count(); ++i) {
        QDomElement shop = shops.at(i).toElement();
        QString name = shop.firstChildElement("name").text();
        QString address = shop.firstChildElement("address").text();
        QString director = shop.firstChildElement("director").text();
        QString specialization = shop.firstChildElement("specialization").text();
        QSqlQuery query(db);

        query.exec("SELECT idShop FROM shop WHERE shop_name='"+name+"'");
        int repeated_id=-1;
        while(query.next()){
            repeated_id=query.value(0).toInt();
        }
        if (repeated_id==-1){
        // Получение id специализации из базы
        query.exec("SELECT Specid FROM specialization WHERE specialization='"+specialization+"'");
        while(query.next()){
            specialization=query.value(0).toString();
        }

        // Вставка данных о магазине
        query.prepare("INSERT INTO shop (shop_name, shop_address, spec_of_shop, director_name_shop) VALUES (:name, :address, :specialization, :director)");
        query.bindValue(":name", name);
        query.bindValue(":address", address);
        query.bindValue(":specialization", specialization);
        query.bindValue(":director", director);
        }
        if (!query.exec()) {
            QMessageBox::warning(this, tr("Error"), tr("Failed to insert shop data: %1").arg(query.lastError().text()));
        }
    }

    /**
     * @brief Загрузка и вставка данных об ассистентах из XML.
     *
     * Вставляет информацию об ассистентах в таблицу assistant.
     */
    QDomNodeList assistant = document.elementsByTagName("ASSISTANTS").at(0).childNodes();
    for (int i = 0; i < assistant.count(); ++i) {
        QDomElement assis = assistant.at(i).toElement();
        QString sector = assis.firstChildElement("sector").text();
        QString salary = assis.firstChildElement("salary").text();
        QString overtime_hour = assis.firstChildElement("overtime_hour").text();
        QString FIO = assis.firstChildElement("FIO").text();
        QString Birthday = assis.firstChildElement("Birthday").text();
        QString phone_number = assis.firstChildElement("phone_number").text();
        QString pasport = assis.firstChildElement("pasport").text();
        QString work_place = assis.firstChildElement("work_place").text();
        QString work_age = assis.firstChildElement("work_age").text();

        // Получение id магазина из базы
        QSqlQuery query(db);

        query.exec("SELECT idAssistant FROM assistant WHERE pasport='"+pasport+"'");
        int repeated_id=-1;
        while(query.next()){
            repeated_id=query.value(0).toInt();
        }
        if (repeated_id==-1){
        query.exec("SELECT idShop FROM shop WHERE shop_name='"+work_place+"'");
        while(query.next()){
            work_place=query.value(0).toString();
        }

        // Вставка данных об ассистенте
        query.prepare("INSERT INTO assistant (sector, salary, overtime_hour, FIO, Birthday, phone_number, pasport, work_place, work_age) VALUES (:sector, :salary, :overtime_hour, :FIO, :Birthday, :phone_number, :pasport, :work_place, :work_age)");
        query.bindValue(":sector", sector);
        query.bindValue(":salary", salary);
        query.bindValue(":overtime_hour", overtime_hour);
        query.bindValue(":FIO", FIO);
        query.bindValue(":Birthday", Birthday);
        query.bindValue(":phone_number", phone_number);
        query.bindValue(":pasport", pasport);
        query.bindValue(":work_place", work_place);
        query.bindValue(":work_age", work_age);
        }
        if (!query.exec()) {
            QMessageBox::warning(this, tr("Error"), tr("Failed to insert shop data: %1").arg(query.lastError().text()));
        }
    }

    /**
     * @brief Загрузка и вставка данных о директорах из XML.
     *
     * Вставляет информацию о директорах в таблицу director.
     */
    QDomNodeList dirrector = document.elementsByTagName("DIRECTORS").at(0).childNodes();
    for (int i = 0; i < dirrector.count(); ++i) {
        QDomElement dir = dirrector.at(i).toElement();
        QString number_wards = dir.firstChildElement("number_wards").text();
        QString salary = dir.firstChildElement("salary").text();
        QString FIO = dir.firstChildElement("FIO").text();
        QString Birthday = dir.firstChildElement("Birthday").text();
        QString phone_number = dir.firstChildElement("phone_number").text();
        QString pasport = dir.firstChildElement("pasport").text();
        QString work_place = dir.firstChildElement("work_place").text();
        QString work_age = dir.firstChildElement("work_age").text();

        // Вставка данных о директоре
        QSqlQuery query(db);
        query.exec("SELECT idDirector FROM director WHERE pasport='"+pasport+"'");
        int repeated_id=-1;
        while(query.next()){
            repeated_id=query.value(0).toInt();
        }
        if (repeated_id==-1){
        query.prepare("INSERT INTO director (number_wards, salary, FIO, Birthday, phone_number, pasport, work_place, work_age) VALUES (:number_wards, :salary, :FIO, :Birthday, :phone_number, :pasport, :work_place, :work_age)");
        query.bindValue(":number_wards", number_wards);
        query.bindValue(":salary", salary);
        query.bindValue(":FIO", FIO);
        query.bindValue(":Birthday", Birthday);
        query.bindValue(":phone_number", phone_number);
        query.bindValue(":pasport", pasport);
        query.bindValue(":work_place", work_place);
        query.bindValue(":work_age", work_age);
        }
        if (!query.exec()) {
            QMessageBox::warning(this, tr("Error"), tr("Failed to insert shop data: %1").arg(query.lastError().text()));
        }
    }

    /**
     * @brief Загрузка и вставка данных о продуктах из XML.
     *
     * Вставляет каждый продукт в таблицу product.
     */
    QDomNodeList products = document.elementsByTagName("PRODUCTS").at(0).childNodes();
    for (int i = 0; i < products.count(); ++i) {
        QDomElement prod = products.at(i).toElement();
        QString name = prod.firstChildElement("name").text();
        QString type = prod.firstChildElement("type").text();
        QString size = prod.firstChildElement("size").text();

        // Получение id типа продукта из базы
        QSqlQuery query(db);


        query.exec("SELECT idType FROM type WHERE product_type='"+type+"'");
        while(query.next()){
            type=query.value(0).toString();
        }

        query.exec("SELECT idProduct FROM product WHERE name='"+name+"' AND type='"+type+"' AND size='"+size+"'");
        int repeated_id=-1;
        while(query.next()){
            repeated_id=query.value(0).toInt();
        }
        if (repeated_id==-1){
        // Вставка данных о продукте
        query.prepare("INSERT INTO product (name, type, size) VALUES (:name, :type, :size)");
        query.bindValue(":name", name);
        query.bindValue(":type", type);
        query.bindValue(":size", size);
        }
        if (!query.exec()) {
            QMessageBox::warning(this, tr("Error"), tr("Failed to insert shop data: %1").arg(query.lastError().text()));
        }
    }

    /**
     * @brief Загрузка и вставка данных о продуктах в магазинах из XML.
     *
     * Вставляет данные о продукции в магазинах в таблицу product_shop.
     */
    QDomNodeList products_sh = document.elementsByTagName("PRODUCTS_SHOPS").at(0).childNodes();
    for (int i = 0; i < products_sh.count(); ++i) {
        QDomElement pr_sh = products_sh.at(i).toElement();
        QString idProduct = pr_sh.firstChildElement("idProduct").text();
        QString idShop = pr_sh.firstChildElement("idShop").text();
        QString in_stock = pr_sh.firstChildElement("in_stock").text();
        QString in_window = pr_sh.firstChildElement("in_window").text();
        QString price = pr_sh.firstChildElement("price").text();
        QString size = pr_sh.firstChildElement("SizeProduct").text();

        // Получение id продукта и магазина
        QSqlQuery query(db);
        query.exec("SELECT idProduct FROM product WHERE name='"+idProduct+"' AND size='"+size+"'");
        while(query.next()){
            idProduct=query.value(0).toString();
        }

        query.exec("SELECT idShop FROM shop WHERE shop_name='"+idShop+"'");
        while(query.next()){
            idShop=query.value(0).toString();
        }
        query.exec("SELECT idperson_product FROM product_shop WHERE idProduct='"+idProduct+"' AND idShop='"+idShop+"'");
        int repeated_id=-1;
        while(query.next()){
            repeated_id=query.value(0).toInt();
        }
        if (repeated_id==-1){
        // Вставка данных о продукции в магазине
        query.prepare("INSERT INTO product_shop (idProduct, idShop, in_stock, in_window, price) VALUES (:idProduct, :idShop, :in_stock, :in_window, :price)");
        query.bindValue(":idProduct", idProduct);
        query.bindValue(":idShop", idShop);
        query.bindValue(":in_stock", in_stock);
        query.bindValue(":in_window", in_window);
        query.bindValue(":price", price);
        }
        if (!query.exec()) {
            QMessageBox::warning(this, tr("Error"), tr("Failed to insert shop data: %1").arg(query.lastError().text()));
        }
    }
}


