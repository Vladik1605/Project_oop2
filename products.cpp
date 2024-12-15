#include "products.h"
#include "ui_products.h"
#include "classes.h"
#include <QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QCompleter>
#include <KDReportsPreviewDialog.h>
#include <KDReportsReport.h>
#include <KDReportsTextElement.h>
#include <KDReportsHeader.h>
#include <KDReportsTableElement.h>
#include <KDReportsCell.h>
#include <QPrintDialog>
#include <QLineEdit>
#include <QScrollArea>
#include <QVBoxLayout>
#include "Exceptions.h"
#include <QMessageBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QFileDialog>
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <KDReportsReport.h>
#include "Delegate.h"
/**
 * @brief Конструктор класса Products.
 * Инициализация окна, подключение к базе данных и заполнение таблицы данными из базы.
 *
 * @param parent Родительский виджет.
 * @param shop_id Идентификатор магазина.
 */
Products::Products(QWidget *parent, QString shop_id)
    : QDialog(parent)
    , ui(new Ui::Products)
{
    ui->setupUi(this);

    // Отключаем кнопку по умолчанию
    ui->SaveChangeButton->setEnabled(false);

    // Инициализация параметров
    this->shop_id = shop_id;
    this->setAttribute(Qt::WA_DeleteOnClose);

    // Создание таблицы для отображения продуктов
    tableWidget_products = new QTableWidget(this);
    tableWidget_products->setColumnCount(6);
    tableWidget_products->setHorizontalHeaderLabels(QStringList() << "Name" << "Type" << "Size" << "Price" << "In Stock" << "In Window");
    tableWidget_products->horizontalHeader()->setStretchLastSection(true);

    // Размещение таблицы в layout
    QVBoxLayout *dialogLayout = new QVBoxLayout(this);
    dialogLayout->addWidget(tableWidget_products);

    // Кнопки управления
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    buttonLayout->addItem(spacer);
    buttonLayout->addWidget(ui->MakePdfButton);
    buttonLayout->addWidget(ui->DeleteButton);
    buttonLayout->addWidget(ui->RedactButton);
    buttonLayout->addWidget(ui->SaveChangeButton);
    buttonLayout->addWidget(ui->AddProductButton);

    dialogLayout->addLayout(buttonLayout);
    setLayout(dialogLayout);

    // Подключение к базе данных
    db = QSqlDatabase::addDatabase("QMYSQL", "mainConnection1");
    db.setHostName("localhost");
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("0504Vladik");
    db.open();

    // Запрос данных о продуктах для магазина
    QSqlQuery query(db);
    query.exec("SELECT idProduct, in_stock, in_window, price FROM product_shop WHERE idShop='" + shop_id + "'");

    prod = new Product();

    // Обработка полученных данных
    while (query.next()) {
        QString productId = query.value(0).toString();
        id_list.append(productId);
        int inStock = query.value(1).toInt();
        prod->set_stock(inStock);
        int inWindow = query.value(2).toInt();
        prod->set_window(inWindow);
        int price = query.value(3).toInt();
        prod->setPrice(price);

        // Запрос дополнительных данных о продукте
        QSqlQuery query1(db);
        query1.exec("SELECT name, type, size FROM product WHERE idProduct='" + productId + "'");

        // Обработка информации о продукте
        while (query1.next()) {
            QString name = query1.value(0).toString();
            prod->setName(name);

            QString typeId = query1.value(1).toString();
            QString size = query1.value(2).toString();
            prod->setSize(size);

            // Получение типа продукта
            QSqlQuery query2(db);
            query2.exec("SELECT product_type FROM type WHERE idType='" + typeId + "'");
            QString type;
            if (query2.next()) {
                type = query2.value(0).toString();
                prod->setType(type);
            }

            // Добавление данных о продукте в таблицу
            int row = tableWidget_products->rowCount();
            tableWidget_products->insertRow(row);
            tableWidget_products->setItem(row, 0, new QTableWidgetItem(name));
            tableWidget_products->setItem(row, 1, new QTableWidgetItem(type));
            tableWidget_products->setItem(row, 2, new QTableWidgetItem(size));
            tableWidget_products->setItem(row, 3, new QTableWidgetItem(QString::number(price)));
            tableWidget_products->setItem(row, 4, new QTableWidgetItem(QString::number(inStock)));
            tableWidget_products->setItem(row, 5, new QTableWidgetItem(QString::number(inWindow)));

            // Установка флага, чтобы ячейки были не редактируемыми
            for (int col = 0; col < tableWidget_products->columnCount(); ++col) {
                QTableWidgetItem* item = tableWidget_products->item(row, col);
                if (item) {
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                }
            }
            ValidationProductDelegate* delegate = new ValidationProductDelegate(db,tableWidget_products, this);
            tableWidget_products->setItemDelegate(delegate);
            isRowSaved << true;
        }
    }
}

/**
 * @brief Деструктор класса Products.
 * Освобождение ресурсов.
 */
Products::~Products()
{
    delete ui;
}


/**
 * @brief Обработчик нажатия кнопки для добавления нового продукта в таблицу.
 * Создает новые строки с полями ввода для каждого параметра продукта,
 * подключает автозаполнение для полей и связывает их с базой данных.
 */
void Products::on_AddProductButton_clicked()
{
    // Инициализация полей ввода для новой строки
    ld_Name = new QLineEdit; //Название
    ld_Type = new QLineEdit; //Тип
    ld_Size = new QLineEdit; //Размер
    ld_Price = new QLineEdit; //Цена
    ld_Stock = new QLineEdit; // На складе
    ld_Window = new QLineEdit; //На витрине

    // Добавление новой строки в таблицу
    int row = tableWidget_products->rowCount();
    tableWidget_products->insertRow(row);

    // Установка полей ввода в ячейки таблицы
    tableWidget_products->setCellWidget(row, 0, ld_Name);
    tableWidget_products->setCellWidget(row, 1, ld_Type);
    tableWidget_products->setCellWidget(row, 2, ld_Size);
    tableWidget_products->setCellWidget(row, 3, ld_Price);
    tableWidget_products->setCellWidget(row, 4, ld_Stock);
    tableWidget_products->setCellWidget(row, 5, ld_Window);
    isRowSaved << false;

    // Создание объекта продукта для дальнейшего использования
    prod = new Product;

    // Подключение автозаполнителя для поля типа продукта
    QStringList typeEntries;
    QSqlQuery query1(db);
    query1.exec("SELECT product_type FROM type");
    while(query1.next()){
        typeEntries << query1.value(0).toString();
    }

    QCompleter *completer1 = new QCompleter(typeEntries, this);
    completer1->setCaseSensitivity(Qt::CaseInsensitive);
    completer1->setFilterMode(Qt::MatchStartsWith);
    ld_Type->setCompleter(completer1);

    // Подключение автозаполнителя для поля названия и размера продукта
    QStringList productEntries;
    QSqlQuery query("SELECT name, size FROM product", db);
    while (query.next()) {
        QString name = query.value("name").toString();
        QString size = query.value("size").toString();
        productEntries << name + "\t" + size; // Создаем уникальную строку с названием и размером
    }

    QCompleter *completer = new QCompleter(productEntries, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setFilterMode(Qt::MatchStartsWith);
    ld_Name->setCompleter(completer);

    //Обработчик изменения текста в поле с названием продукта
    connect(ld_Name, &QLineEdit::textChanged, this, [=](const QString &text) {
        QStringList parts = text.split('\t'); // Разделяем строку с разделителем
        if (parts.size() == 2) {
            ld_Name->blockSignals(true);            // Блокируем сигналы, чтобы избежать циклических вызовов
            ld_Name->setText(parts[0]);            // Устанавливаем только название
            ld_Name->blockSignals(false);          // Разблокируем сигналы
        }
    });

    // Обработчик выделения записи в автозаполнителе
    connect(completer, QOverload<const QString &>::of(&QCompleter::highlighted), this, [=](const QString &highlightedEntry) {
        QStringList parts = highlightedEntry.split('\t'); // Разделяем строку на название и размер
        if (parts.size() == 2) {
            QString highlightedName = parts[0];
            QString highlightedSize = parts[1];

            // Получаем данные из базы данных
            QSqlQuery query(db);
            query.prepare("SELECT type FROM product WHERE name = :name AND size = :size");
            query.bindValue(":name", highlightedName);
            query.bindValue(":size", highlightedSize);

            if (query.exec() && query.next()) {
                QString type_id = query.value("type").toString();

                QSqlQuery typeQuery(db);
                typeQuery.prepare("SELECT product_type FROM type WHERE idType = :idType");
                typeQuery.bindValue(":idType", type_id);

                if (typeQuery.exec() && typeQuery.next()) {
                    QString productType = typeQuery.value("product_type").toString();

                    // Обновляем поля в новой строке таблицы
                    ld_Name->setText(highlightedName); // Вставляем только название
                    ld_Type->setText(productType);    // Тип
                    ld_Size->setText(highlightedSize); // Размер
                }
            }
        }
    });

    // Обработчик выбора записи из автозаполнителя
    connect(completer, QOverload<const QString &>::of(&QCompleter::activated), this, [=](const QString &selectedEntry) {
        QStringList parts = selectedEntry.split('\t'); // Разделяем строку на название и размер
        if (parts.size() == 2) {
            QString selectedName = parts[0];
            QString selectedSize = parts[1];

            // Получаем данные из базы данных
            QSqlQuery query(db);
            query.prepare("SELECT type FROM product WHERE name = :name AND size = :size");
            query.bindValue(":name", selectedName);
            query.bindValue(":size", selectedSize);

            if (query.exec() && query.next()) {
                QString type_id = query.value("type").toString();

                QSqlQuery typeQuery(db);
                typeQuery.prepare("SELECT product_type FROM type WHERE idType = :idType");
                typeQuery.bindValue(":idType", type_id);

                if (typeQuery.exec() && typeQuery.next()) {
                    QString productType = typeQuery.value("product_type").toString();

                    // Устанавливаем данные в соответствующих ячейках таблицы
                    int row = tableWidget_products->rowCount() - 1; // Последняя добавленная строка
                    if (row >= 0) {
                        ld_Name->setText(selectedName);  // Вставляем только название
                        ld_Type->setText(productType);  // Тип
                        ld_Size->setText(selectedSize); // Размер
                    }
                }
            }
        }
    });

    // Обработчик изменения текста в поле с названием продукта
    connect(ld_Name, &QLineEdit::textChanged, this, [=]() {
        ld_Name->setStyleSheet("");
        prod->setName(ld_Name->text());
    });

    // Обработчик изменения текста в поле типа продукта
    connect(ld_Type, &QLineEdit::textChanged, this, [=]() {
        ld_Type->setStyleSheet("");
        prod->setType(ld_Type->text());
    });

    // Обработчик изменения текста в поле с размером продукта
    connect(ld_Size, &QLineEdit::textChanged, this, [=]() {
        ld_Size->setStyleSheet("");
        prod->setSize(ld_Size->text());
    });

    // Обработчик завершения редактирования поля цены
    connect(ld_Price, &QLineEdit::editingFinished, this, [=]() {
        ld_Price->setStyleSheet("");
        try {
            QString str = ld_Price->text();
            ValidatorPrice_Stock_Window(&str);
            prod->setPrice(ld_Price->text().toInt());
        } catch (ExCorrection& ex) {
            QMessageBox::warning(this, "Внимание!", ex.what(), QMessageBox::Ok);
            ld_Price->setText("");
        }
    });

    // Обработчик завершения редактирования поля количества на складе
    connect(ld_Stock, &QLineEdit::editingFinished, this, [=]() {
        ld_Stock->setStyleSheet("");
        try {
            QString str = ld_Stock->text();
            ValidatorPrice_Stock_Window(&str);
            prod->set_stock(ld_Stock->text().toInt());
        } catch (ExCorrection& ex) {
            QMessageBox::warning(this, "Внимание!", ex.what(), QMessageBox::Ok);
            ld_Stock->setText("");
        }
    });

    // Обработчик завершения редактирования поля количества в витрине
    connect(ld_Window, &QLineEdit::editingFinished, this, [=]() {
        ld_Window->setStyleSheet("");
        try {
            QString str = ld_Window->text();
            ValidatorPrice_Stock_Window(&str);
            prod->set_window(ld_Window->text().toInt());
        } catch (ExCorrection& ex) {
            QMessageBox::warning(this, "Внимание!", ex.what(), QMessageBox::Ok);
            ld_Window->setText("");
        }
    });

    // Отключаем кнопки после добавления строки
    ui->AddProductButton->setEnabled(false);
    ui->RedactButton->setEnabled(false);
    ui->SaveChangeButton->setEnabled(true);
}


/**
 * @brief Обработчик нажатия кнопки для сохранения изменений в базе данных и добавления в нее новых элментов.
 */

void Products::on_SaveChangeButton_clicked()
{
    row = tableWidget_products->rowCount();  // Получаем количество строк в таблице.

    try {
        // Проверяем, что кнопка для сохранения включена, а другие кнопки отключены.
        if (!ui->AddProductButton->isEnabled() && !ui->RedactButton->isEnabled() && ui->SaveChangeButton->isEnabled()) {
            QVector<QLineEdit*> errors;  // Вектор для хранения полей с ошибками.

            // Проверяем, что все необходимые поля для товара заполнены.
            if (prod->getName() == "") {
                errors.append(ld_Name);
            }
            if (prod->getType() == "") {
                errors.append(ld_Type);
            }
            if (prod->getSize() == "") {
                errors.append(ld_Size);
            }
            if (prod->getPrice() == -1000) {
                errors.append(ld_Price);
            }
            if (prod->get_stock() == -1000) {
                errors.append(ld_Stock);
            }
            if (prod->get_window() == -1000) {
                errors.append(ld_Window);
            }

            // Если есть ошибки, выбрасываем исключение.
            if (errors.length() != 0) {
                throw MyEx_Prod{errors, this};
            }

            // Запрашиваем ID типа товара из базы данных.
            int id = -1;
            QSqlQuery query(db);
            query.exec("SELECT idType FROM type WHERE product_type='" + prod->getType() + "'");
            while (query.next()) {
                id = query.value(0).toInt();
            }

            // Если тип найден в базе, продолжаем обработку товара.
            if (id != -1) {
                QSqlQuery query1(db);
                int id_prod = -1;
                QString type_id;

                // Проверяем, существует ли товар с таким именем, размером и типом.
                query1.exec("SELECT idProduct FROM product WHERE name='" + prod->getName() + "' AND size='" + prod->getSize() + "' AND type='" + QString::number(id) + "'");
                while (query1.next()) {
                    id_prod = query1.value(0).toInt();
                }

                // Проверяем, есть ли товар в текущем магазине.
                query1.exec("SELECT idShop FROM product_shop WHERE idProduct='" + QString::number(id_prod) + "'");
                bool having;
                while (query1.next()) {
                    if (QString::compare(shop_id, query1.value(0).toString()) == 0) {
                        having = true;
                    }
                }
                qDebug() << having;

                // Если товар не существует, добавляем его в базу данных.
                if (id_prod == -1) {
                    query.exec("INSERT INTO product (name, type, size) VALUES ('" + prod->getName() + "', '" + QString::number(id) + "', '" + prod->getSize() + "')");
                    query.exec("SELECT idProduct FROM product WHERE name='" + prod->getName() + "' AND size='" + prod->getSize() + "' AND type='" + QString::number(id) + "'");

                    while (query.next()) {
                        qDebug() << query.value(0).toString();
                        id_list.append(query.value(0).toString());
                        id_prod = query.value(0).toInt();
                    }

                    query.exec("INSERT INTO product_shop (idProduct, idShop, in_stock, in_window, price) VALUES ('" + QString::number(id_prod) + "', '" + shop_id + "', '" + QString::number(prod->get_stock()) + "', '" + QString::number(prod->get_window()) + "', '" + QString::number(prod->getPrice()) + "')");
                }

                // Если товар существует, но не добавлен в текущий магазин, добавляем.
                else if (id_prod != -1 && !having) {
                    query1.exec("SELECT idProduct FROM product WHERE name='" + prod->getName() + "' AND size='" + prod->getSize() + "' AND type='" + type_id + "'");

                    while (query1.next()) {
                        id_list.append(query1.value(0).toString());
                        id_prod = query1.value(0).toInt();
                    }

                    query.exec("INSERT INTO product_shop (idProduct, idShop, in_stock, in_window, price) VALUES ('" + QString::number(id_prod) + "', '" + shop_id + "', '" + QString::number(prod->get_stock()) + "', '" + QString::number(prod->get_window()) + "', '" + QString::number(prod->getPrice()) + "')");
                }
                // Если товар уже есть в базе и магазине, выбрасываем исключение.
                else {
                    throw ExCorrection{"Такой товар уже добавлен"};
                }
            }
            // Если тип не найден, добавляем его в базу данных.
            else {
                QSqlQuery query1(db);
                query1.exec("INSERT INTO type (product_type) VALUES ('" + prod->getType() + "')");
                QSqlQuery query2(db);
                query2.exec("SELECT idType FROM type WHERE product_type='" + prod->getType() + "'");
                while (query2.next()) {
                    id = query2.value(0).toInt();
                }

                QSqlQuery query3(db);
                query3.exec("INSERT INTO product (name, type, size) VALUES ('" + prod->getName() + "', '" + QString::number(id) + "', '" + prod->getSize() + "')");
                query1.exec("SELECT idProduct FROM product WHERE name='" + prod->getName() + "'");
                int id_prod = -1;
                while (query1.next()) {
                    id_prod = query1.value(0).toInt();
                    id_list.append(QString::number(id_prod));
                }

                query.exec("INSERT INTO product_shop (idProduct, idShop, in_stock, in_window, price) VALUES ('" + QString::number(id_prod) + "', '" + shop_id + "', '" + QString::number(prod->get_stock()) + "', '" + QString::number(prod->get_window()) + "', '" + QString::number(prod->getPrice()) + "')");
            }

            // Обновляем таблицу с товаром.
            tableWidget_products->setItem(row - 1, 0, new QTableWidgetItem(ld_Name->text()));
            tableWidget_products->removeCellWidget(row - 1, 0);
            ld_Name->deleteLater();
            ld_Name->setEnabled(false);

            tableWidget_products->setItem(row - 1, 1, new QTableWidgetItem(ld_Type->text()));
            tableWidget_products->removeCellWidget(row - 1, 1);
            ld_Type->deleteLater();
            ld_Type->setEnabled(false);

            tableWidget_products->setItem(row - 1, 2, new QTableWidgetItem(ld_Size->text()));
            tableWidget_products->removeCellWidget(row - 1, 2);
            ld_Size->deleteLater();
            ld_Size->setEnabled(false);

            tableWidget_products->setItem(row - 1, 3, new QTableWidgetItem(ld_Price->text()));
            tableWidget_products->removeCellWidget(row - 1, 3);
            ld_Price->deleteLater();
            ld_Price->setEnabled(false);

            tableWidget_products->setItem(row - 1, 4, new QTableWidgetItem(ld_Stock->text()));
            tableWidget_products->removeCellWidget(row - 1, 4);
            ld_Stock->deleteLater();
            ld_Stock->setEnabled(false);

            tableWidget_products->setItem(row - 1, 5, new QTableWidgetItem(ld_Window->text()));
            tableWidget_products->removeCellWidget(row - 1, 5);
            ld_Window->deleteLater();
            ld_Window->setEnabled(false);

            // Запрещаем редактирование ячеек таблицы.
            for (int col = 0; col < tableWidget_products->columnCount(); ++col) {
                QTableWidgetItem* item = tableWidget_products->item(row - 1, col);
                if (item) {
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                }
            }

            // Обновляем состояние кнопок.
            ui->SaveChangeButton->setEnabled(false);
            ui->AddProductButton->setEnabled(true);
            ui->RedactButton->setEnabled(true);
            isRowSaved[row - 1] = true;
        }



        // Проверка состояния кнопок перед выполнением операции
        if (ui->RedactButton->isEnabled() && ui->SaveChangeButton->isEnabled() && !ui->AddProductButton->isEnabled()) {
            QVector<QTableWidgetItem*> errors;
            int rowCount = tableWidget_products->rowCount();

            // Обработка каждой строки таблицы
            for (int row = 0; row < rowCount; row++) {
                //Product* product = new Product();  // Создаем объект для продукта

                for (int col = 0; col < tableWidget_products->columnCount(); ++col) {
                    QTableWidgetItem* item = tableWidget_products->item(row, col);
                    if (item) {
                        QString text = item->text();

                        // Проверяем, есть ли ошибка для текущей ячейки (флаг ошибки, установленный делегатом)
                        QVariant isInvalid = item->data(Qt::UserRole + 1);  // Флаг ошибки
                        if (isInvalid.isValid() && isInvalid.toBool()) {
                            errors.append(item);  // Добавляем ошибочную ячейку
                        }

                        // Устанавливаем данные в объект product
                        switch (col) {
                        case 0:  // Название продукта
                            prod->setName(text);
                            break;
                        case 1:  // Размер продукта
                            prod->setType(text);
                            break;
                        case 2:  // Тип продукта
                            prod->setSize(text);
                            break;
                        case 3:  // Цена продукта
                            prod->setPrice(text.toInt());
                            break;
                        case 4:  // Количество на складе
                            prod->set_stock(text.toInt());
                            break;
                        case 5:  // Количество на складе
                            prod->set_window(text.toInt());
                            break;
                            // Добавьте другие столбцы по мере необходимости
                        }
                    }
                }

                // Если есть ошибки, выбрасываем исключение
                if (!errors.isEmpty()) {
                    throw MyEx_Table{errors, this};
                }

                // Получаем idType для типа продукта из базы данных
                int id = -1;
                QSqlQuery query(db);
                query.exec("SELECT idType FROM type WHERE product_type='" + prod->getType() + "'");
                while (query.next()) {
                    id = query.value(0).toInt();
                }

                // Если тип найден, ищем или создаем продукт в базе данных
                if (id != -1) {
                    QSqlQuery query1(db);
                    int id_prod = -1;
                    query1.exec("SELECT idProduct FROM product WHERE name='" + prod->getName() + "' AND size='" + prod->getSize() + "' AND type='" + QString::number(id) + "'");
                    while (query1.next()) {
                        id_prod = query1.value(0).toInt();
                    }

                    // Проверка на наличие продукта в магазине
                    query1.exec("SELECT idShop FROM product_shop WHERE idProduct='" + QString::number(id_prod) + "'");
                    bool having = false;
                    while (query1.next()) {
                        if (shop_id == query1.value(0).toString()) {
                            having = true;
                        }
                    }

                    // Логика для добавления или обновления продукта в базе данных
                    if (id_prod == -1) {
                        int anywhere = -1;
                        query1.exec("SELECT idShop FROM product_shop WHERE idProduct='" + id_list[row] + "' AND idShop<>'" + shop_id + "'");
                        while(query1.next()){
                            anywhere = query1.value(0).toInt();
                        }

                        // Логика добавления или обновления записи в product_shop
                        if (anywhere != -1) {
                            query.exec("INSERT INTO product (name, type, size) VALUES ('" + prod->getName() + "', '" + QString::number(id) + "', '" + prod->getSize() + "')");
                            query1.exec("SELECT idProduct FROM product WHERE name='" + prod->getName() + "'");
                            while(query1.next()) {
                                id_list.append(query1.value(0).toString());
                                id_prod = query1.value(0).toInt();
                            }
                            query.exec("INSERT INTO product_shop (idProduct, idShop, in_stock, in_window, price) VALUES ('" + QString::number(id_prod) + "', '" + shop_id + "', '" + QString::number(prod->get_stock()) + "', '" + QString::number(prod->get_window()) + "', '" + QString::number(prod->getPrice()) + "')");
                        } else {
                            // Логика обновления информации о продукте
                            query.exec("UPDATE product SET name='" + prod->getName() + "', type='" + QString::number(id) + "', size='" + prod->getSize() + "' WHERE idProduct='" + id_list[row] + "'");
                            query.exec("UPDATE product_shop SET in_stock='" + QString::number(prod->get_stock()) + "', in_window='" + QString::number(prod->get_window()) + "', price='" + QString::number(prod->getPrice()) + "' WHERE idProduct='" + id_list[row] + "' AND idShop='" + shop_id + "'");
                        }
                    }
                    // Далее идет логика для различных случаев обновления или удаления продукта
                    else if(id_prod != -1 && !having) {
                        int anywhere = -1;
                        query1.exec("SELECT idShop FROM product_shop WHERE idProduct='" + id_list[row] + "' AND idShop<>'" + shop_id + "'");
                        while(query1.next()){
                            anywhere = query1.value(0).toInt();
                        }

                        // Если товар не найден в других магазинах, обновляем или удаляем его
                        if(anywhere == -1) {
                            query.exec("DELETE FROM product_shop WHERE idProduct='" + id_list[row] + "'");
                            query.exec("DELETE FROM product WHERE idProduct='" + id_list[row] + "'");
                            query.exec("INSERT INTO product_shop (idProduct, idShop, in_stock, in_window, price) VALUES ('" + QString::number(id_prod) + "', '" + shop_id + "', '" + QString::number(prod->get_stock()) + "', '" + QString::number(prod->get_window()) + "', '" + QString::number(prod->getPrice()) + "')");
                        } else {
                            query.exec("UPDATE product_shop SET idProduct='" + QString::number(id_prod) + "', in_stock='" + QString::number(prod->get_stock()) + "', in_window='" + QString::number(prod->get_window()) + "', price='" + QString::number(prod->getPrice()) + "' WHERE idProduct='" + id_list[row] + "' AND idShop='" + shop_id + "'");
                        }
                    }
                    // Другие сценарии с id_prod и having
                    else if(id_prod != -1 && having) {
                        query.exec("UPDATE product_shop SET in_stock='" + QString::number(prod->get_stock()) + "', in_window='" + QString::number(prod->get_window()) + "', price='" + QString::number(prod->getPrice()) + "' WHERE idProduct='" + id_list[row] + "' AND idShop='" + shop_id + "'");
                    }
                } else {
                    // Создание нового типа и добавление продукта в базу данных
                    QSqlQuery query1(db);
                    query1.exec("INSERT INTO type (product_type) VALUES ('" + prod->getType() + "')");
                    query1.exec("SELECT idType FROM type WHERE product_type='" + prod->getType() + "'");
                    while(query1.next()) {
                        id = query1.value(0).toInt();
                    }
                    query.exec("UPDATE product SET name='" + prod->getName() + "', type='" + QString::number(id) + "', size='" + prod->getSize() + "' WHERE idProduct='" + id_list[row] + "'");

                    // query.exec("INSERT INTO product (name, type, size) VALUES ('" + prod->getName() + "', '" + QString::number(id) + "', '" + prod->getSize() + "')");
                }

                // Отключение редактирования ячеек после обработки
                for (int col = 0; col < tableWidget_products->columnCount(); ++col) {
                    QTableWidgetItem* item = tableWidget_products->item(row, col);
                    if (item) {
                        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                    }
                }
            }

            // Включаем кнопки после завершения операции
            ui->AddProductButton->setEnabled(true);
            ui->SaveChangeButton->setEnabled(false);
        }

    }
    catch (MyEx_Prod& ex) {
        ex.ShowError();
    }
    catch (MyEx_Table& ex) {
        ex.ShowError();
    } catch(ExCorrection& ex) {
        // Ошибка валидации
        QMessageBox::warning(this,"Внимание!", ex.what(), QMessageBox::Ok);
    }
}


/**
 * @brief Обработчик клика по кнопке "pushButton_3"
 * Включает редактирование ячеек таблицы и изменяет состояние кнопок.
 */
void Products::on_RedactButton_clicked()
{
    ui->AddProductButton->setEnabled(false);
    ui->SaveChangeButton->setEnabled(true);

    // Включаем редактирование для каждой ячейки в таблице
    for (int row = 0; row < tableWidget_products->rowCount(); ++row) {
        for (int column = 0; column < tableWidget_products->columnCount(); ++column) {
            QTableWidgetItem* item = tableWidget_products->item(row, column);
            if (item) {
                item->setFlags(item->flags() | Qt::ItemIsEditable);
            }
        }
    }
}

/**
 * @brief Обработчик клика по кнопке "pushButton_4"
 * Удаляет выбранные строки из таблицы и базы данных.
 */
void Products::on_DeleteButton_clicked()
{
    QItemSelectionModel *selectionModel = tableWidget_products->selectionModel();
    if (selectionModel) {
        QModelIndexList selectedRows = selectionModel->selectedRows();

        // Обрабатываем каждую выбранную строку
        for (int i = selectedRows.size() - 1; i >= 0; --i) {
            int row = selectedRows.at(i).row();

            // Если строка не сохранена, удаляем её из таблицы
            if (!isRowSaved[row]) {
                tableWidget_products->removeRow(row);
                isRowSaved.removeAt(row);
                continue;
            }

            // Запрашиваем подтверждение удаления
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Подтверждение удаления",
                                          "Вы уверены, что хотите удалить выбранные элементы?",
                                          QMessageBox::Yes | QMessageBox::No);

            if (reply != QMessageBox::Yes) {
                return;
            }

            // Удаляем строку из таблицы
            tableWidget_products->removeRow(row);

            int anywhere = -1;
            QSqlQuery query1(db);
            QSqlQuery query(db);
            qDebug() << id_list;

            // Проверяем наличие другого магазина для выбранного продукта
            query1.exec("SELECT idShop FROM product_shop WHERE idProduct='" + id_list[row] + "' AND idShop<>'" + shop_id + "'");
            while (query1.next()) {
                anywhere = query1.value(0).toInt();
            }

            // Если других магазинов нет, удаляем продукт
            if (anywhere == -1) {
                query.exec("DELETE FROM product_shop WHERE idProduct='" + id_list[row] + "'");
                query.exec("DELETE FROM product WHERE idProduct='" + id_list[row] + "'");
                isRowSaved.removeAt(row);
                id_list.removeAt(row);
            }
            else {
                query.exec("DELETE FROM product_shop WHERE idProduct='" + id_list[row] + "' AND idShop='" + shop_id + "'");
                isRowSaved.removeAt(row);
                id_list.removeAt(row);
            }
        }

        // Восстанавливаем состояние кнопок
        ui->RedactButton->setEnabled(true);
        ui->AddProductButton->setEnabled(true);
        ui->SaveChangeButton->setEnabled(false);
    }
}

/**
 * @brief Обработчик клика по кнопке "pushButton_5"
 * Генерирует и сохраняет отчёт по продуктам в формате PDF.
 */
void Products::on_MakePdfButton_clicked()
{
    KDReports::Report report;

    // Заголовок отчёта
    KDReports::Header& header = report.header(KDReports::FirstPage);
    KDReports::TextElement title("Отчёт по продуктам");
    title.setPointSize(18);
    title.setBold(true);
    header.addElement(title, Qt::AlignCenter);

    // Создаём таблицу отчёта
    KDReports::TableElement table;
    table.setHeaderRowCount(1);
    table.setBorder(1);
    table.setWidth(100, KDReports::Percent);

    // Заголовки таблицы
    QStringList headers = { "Название", "Размер", "Цена", "В наличии"};
    for (int i = 0; i < headers.size(); ++i) {
        KDReports::TextElement headerText(headers[i]);
        headerText.setBold(true);
        table.cell(0, i).addElement(headerText);
    }

    // Заполнение таблицы данными из tableWidget
    for (int row = 0; row < tableWidget_products->rowCount(); ++row) {
        int column = 0;
        for (int col = 0; col < tableWidget_products->columnCount(); ++col) {
            if (col == 0 || col == 2 || col == 3) {
                QString cellText = tableWidget_products->item(row, col)->text();
                KDReports::TextElement cellElement(cellText);
                table.cell(row + 1, column++).addElement(cellElement);
            }
            if (col == 4) {
                int cellText = tableWidget_products->item(row, col)->text().toInt();
                int cellText2 = tableWidget_products->item(row, col + 1)->text().toInt();
                KDReports::TextElement cellElement(QString::number(cellText + cellText2));
                table.cell(row + 1, column++).addElement(cellElement);
            }
        }
    }

    // Добавляем таблицу в отчёт
    report.addElement(table);

    // Запрашиваем путь для сохранения отчёта
    QString filePath = QFileDialog::getSaveFileName(this,
                                                    "Сохранить отчёт как",
                                                    "",
                                                    "PDF Files (*.pdf);;All Files (*)");

    // Если путь не выбран, показываем предупреждение
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Сохранение отчёта", "Путь для сохранения не выбран.");
        return;
    }

    // Добавляем расширение .pdf, если оно не указано
    if (!filePath.endsWith(".pdf", Qt::CaseInsensitive)) {
        filePath += ".pdf";
    }

    // Настроим принтер для сохранения в PDF
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    // Печатаем отчёт в файл
    report.print(&printer);

    // Информируем пользователя о сохранении
    QMessageBox::information(this, "Сохранение отчёта", "Отчёт успешно сохранён в файл:\n" + filePath);
}


