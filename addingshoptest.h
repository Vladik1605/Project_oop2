#ifndef ADDINGSHOPTEST_H
#define ADDINGSHOPTEST_H

#include <QtTest>
#include "addingshop.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>


/**
* @brief Класс для реализации unit-тестов
*/
class AddingShopTest : public QObject {
    Q_OBJECT

private slots:

    /**
     * @brief Инициализация теста: подключение к базе данных.
     */
    void initTestCase() {
        db= new QSqlDatabase();
        *db = QSqlDatabase::addDatabase("QMYSQL", "test_connection");
        db->setHostName("localhost");
        db->setDatabaseName("test_db");
        db->setUserName("root");
        db->setPassword("0504Vladik");
    }

    /**
     * @brief Очистка после теста: удаление тестовых данных из базы и закрытие подключения.
     */
    void cleanupTestCase() {
        const auto connectionNames = QSqlDatabase::connectionNames();

        // Перебираем все подключения
        QSqlQuery query(*db);

        query.exec("DELETE FROM shop");
        query.exec("DELETE FROM specialization");

        db->close();
        delete db;
    }

    /**
     * @brief Тест успешного добавления магазина в базу данных.
     */
    void testAddShopSuccess() {
        AddingShop addingShop(db, nullptr);

        // Устанавливаем данные для магазина
        addingShop.shop1->setName("Test Shop");
        addingShop.shop1->setAddress("123 Test Street");
        addingShop.shop1->setDirector("John Doe");
        addingShop.shop1->setSpec("Electronics");

        // Кликаем на кнопку для добавления магазина
        addingShop.on_SaveButton_clicked(true);
        db->open();

        // Проверка, что магазин был добавлен в базу данных
        QSqlQuery query(*db);
        query.exec("SELECT COUNT(*) FROM shop WHERE shop_name = 'Test Shop'");
        QVERIFY(query.next());

        QCOMPARE(query.value(0).toInt(), 1);
    }

    /**
     * @brief Тест добавления магазина с пустыми обязательными полями.
     */
    void testAddShopWithEmptyFields() {
        AddingShop addingShop(db, nullptr);

        // Устанавливаем данные для магазина с пустым адресом
        addingShop.shop1->setName("Shop Without Address");
        addingShop.shop1->setAddress("");
        addingShop.shop1->setDirector("John Doe");
        addingShop.shop1->setSpec("Electronics");

        // Кликаем на кнопку для добавления магазина
        addingShop.on_SaveButton_clicked(true);

        // Проверка на наличие ошибок
        QVERIFY(addingShop.errors.size() > 0);
    }

    /**
     * @brief Тест добавления магазина с дублирующимся названием.
     */
    void testAddShopDuplicateName() {
        AddingShop* addingShop = new AddingShop(db, nullptr);

        // Устанавливаем данные для первого магазина
        addingShop->shop1->setName("Unique Shop");
        addingShop->shop1->setAddress("123 Unique Street");
        addingShop->shop1->setDirector("Jane Doe");
        addingShop->shop1->setSpec("Books");

        // Кликаем на кнопку для добавления магазина
        addingShop->on_SaveButton_clicked(true);

        delete addingShop;

        AddingShop* addingShop2 = new AddingShop(db, nullptr);

        // Устанавливаем данные для второго магазина с дублирующимся названием
        addingShop2->shop1->setName("Unique Shop");
        addingShop2->shop1->setAddress("456 Unique Street");
        addingShop2->shop1->setDirector("John Smith");
        addingShop2->shop1->setSpec("Electronics");

        // Кликаем на кнопку для добавления магазина
        addingShop2->on_SaveButton_clicked(true);

        // Проверка на наличие ошибок
        QVERIFY(addingShop2->errors.size() > 0);

        delete addingShop2;
    }

private:
    QSqlDatabase * db;
};





#endif // ADDINGSHOPTEST_H
