#ifndef CLASSES_H
#define CLASSES_H

#include <QString>
#include <QList>
#include <QMap>
#include<QDebug>
#include <QSharedPointer>
/**
 * @class Type
 * @brief Класс для представления типа продукта.
 */
class Type {
    QString product_type;

public:
    /**
     * @brief Устанавливает тип продукта.
     * @param type Тип продукта.
     */
    inline void setType(QString type) {
        product_type = type;
    }

    /**
     * @brief Получает тип продукта.
     * @return Тип продукта.
     */
    inline QString getType() const {
        return product_type;
    }
};

/**
 * @class Product
 * @brief Класс для представления товара.
 */
class Product {
    QString name;
    Type type;
    QString size;
    int price;
    int in_stock;
    int in_window;

public:
    /**
     * @brief Конструктор по умолчанию, инициализирует товар с отрицательными значениями.
     */
    Product(): in_stock(-1000), price(-1000), in_window(-1000) {}

    /**
     * @brief Получает название товара.
     * @return Название товара.
     */
    QString getName()  {
        return name;
    }

    /**
     * @brief Устанавливает название товара.
     * @param name Название товара.
     */
    void setName(QString name) {
        this->name = name;
    }

    /**
     * @brief Получает тип товара.
     * @return Тип товара.
     */
    QString getType()  {
        return type.getType();
    }

    /**
     * @brief Устанавливает тип товара.
     * @param prtype Тип товара.
     */
    void setType(QString prtype) {
        type.setType(prtype);
    }

    /**
     * @brief Получает размер товара.
     * @return Размер товара.
     */
    QString getSize()  {
        return size;
    }

    /**
     * @brief Устанавливает размер товара.
     * @param size Размер товара.
     */
    void setSize(QString size) {
        this->size = size;
    }

    /**
     * @brief Получает цену товара.
     * @return Цена товара.
     */
    int getPrice()  {
        return price;
    }

    /**
     * @brief Устанавливает цену товара.
     * @param price Цена товара.
     */
    void setPrice(int price) {
        this->price = price;
    }

    /**
     * @brief Устанавливает количество товара на складе.
     * @param stock Количество товара на складе.
     */
    void set_stock(int stock){
        in_stock = stock;
    }

    /**
     * @brief Получает количество товара на складе.
     * @return Количество товара на складе.
     */
    int get_stock(){
        return in_stock;
    }

    /**
     * @brief Устанавливает количество товара в витрине.
     * @param wind Количество товара в витрине.
     */
    void set_window(int wind){
        in_window = wind;
    }

    /**
     * @brief Получает количество товара в витрине.
     * @return Количество товара в витрине.
     */
    int get_window(){
        return in_window;
    }
};

/**
 * @class Person
 * @brief Класс для представления человека.
 */
class Person {
    QString FIO;
    QString Birth;
    QString phone_number;
    QString pasport;
    int work_place;
    int work_age;

public:
    /**
     * @brief Получает ФИО.
     * @return ФИО.
     */
    QString getFIO() {
        return FIO;
    }

    /**
     * @brief Устанавливает ФИО.
     * @param FIO ФИО.
     */
    void setFIO(QString FIO) {
        this->FIO = FIO;
    }

    /**
     * @brief Получает дату рождения.
     * @return Дата рождения.
     */
    QString getBirth() {
        return this->Birth;
    }

    /**
     * @brief Устанавливает дату рождения.
     * @param birth Дата рождения.
     */
    void setBirth(QString birth) {
        this->Birth = birth;
    }

    /**
     * @brief Получает номер телефона.
     * @return Номер телефона.
     */
    QString getPhone() {
        return this->phone_number;
    }

    /**
     * @brief Устанавливает номер телефона.
     * @param phone Номер телефона.
     */
    void setPhone(QString phone) {
        this->phone_number = phone;
    }

    /**
     * @brief Получает паспорт.
     * @return Паспорт.
     */
    QString getPassport() {
        return this->pasport;
    }

    /**
     * @brief Устанавливает паспорт.
     * @param passport Паспорт.
     */
    void setPassport(QString passport) {
        this->pasport = passport;
    }

    /**
     * @brief Получает место работы.
     * @return Место работы.
     */
    int getWork_place() {
        return this->work_place;
    }

    /**
     * @brief Устанавливает место работы.
     * @param wp Место работы.
     */
    void setWork_place(int wp) {
        this->work_place = wp;
    }

    /**
     * @brief Получает возраст на работе.
     * @return Возраст на работе.
     */
    int getWork_age() {
        return this->work_age;
    }

    /**
     * @brief Устанавливает возраст на работе.
     * @param wa Возраст на работе.
     */
    void setWork_age(int wa) {
        this->work_age = wa;
    }
};

/**
 * @class Director
 * @brief Класс для представления директора, наследуется от Person.
 */
class Director : public Person {
    int number_wards;
    int salary;

public:
    /**
     * @brief Получает количество подчиненных.
     * @return Количество подчиненных.
     */
    int getWards() {
        return this->number_wards;
    }

    /**
     * @brief Устанавливает количество подчиненных.
     * @param wa Количество подчиненных.
     */
    void setWards(int wa) {
        this->number_wards = wa;
    }

    /**
     * @brief Получает зарплату.
     * @return Зарплата.
     */
    int getSalary() {
        return this->salary;
    }

    /**
     * @brief Устанавливает зарплату.
     * @param salary Зарплата.
     */
    void setSalary(int salary) {
        this->salary = salary;
    }
};

/**
 * @class Asistant
 * @brief Класс для представления ассистента, наследуется от Person.
 */
class Asistant : public Person {
    int overtime;
    int salary;
    QString sector;

public:
    /**
     * @brief Получает количество переработанных часов.
     * @return Количество переработанных часов.
     */
    int getOvertime() {
        return this->overtime;
    }

    /**
     * @brief Устанавливает количество переработанных часов.
     * @param over Количество переработанных часов.
     */
    void setOvertime(int over) {
        this->overtime = over;
    }

    /**
     * @brief Получает зарплату.
     * @return Зарплата.
     */
    int getSalary() {
        return this->salary;
    }

    /**
     * @brief Устанавливает зарплату.
     * @param salary Зарплата.
     */
    void setSalary(int salary) {
        this->salary = salary;
    }

    /**
     * @brief Получает сектор.
     * @return Сектор.
     */
    QString getSector() {
        return this->sector;
    }

    /**
     * @brief Устанавливает сектор.
     * @param sector Сектор.
     */
    void setSector(QString sector) {
        this->sector = sector;
    }
};

/**
 * @class Specialization
 * @brief Класс для представления специализации.
 */
class Specialization {
    QString spec;

public:
    /**
     * @brief Устанавливает специализацию.
     * @param spec Специализация.
     */
    void setSpec(QString spec) {
        this->spec = spec;
    }

    /**
     * @brief Получает специализацию.
     * @return Специализация.
     */
    QString getSpec() {
        return spec;
    }
};

/**
 * @class Lists
 * @brief Абстрактный класс для списков.
 */
class Lists {
public:
    virtual void output() const {
        // Вывод информации о списке
    }
};

/**
 * @class Assistant_list
 * @brief Класс для списка ассистентов, наследуется от Lists.
 */
class Assistant_list : public Lists {
    QList <Asistant> assistant;

public:
    /**
     * @brief Выводит информацию о списке ассистентов.
     */
    void output() const override {
        // Реализация вывода списка ассистентов
    }
};

/**
 * @class product_list
 * @brief Класс для списка продуктов, наследуется от Lists.
 */
class product_list : public Lists {
    QList <Product> product;

public:
    /**
     * @brief Добавляет товар в список.
     * @param prod Товар для добавления.
     */
    void append(Product prod){
        product.append(prod);
    }

    /**
     * @brief Удаляет товар из списка.
     * @param i Индекс товара для удаления.
     */
    void erase(int i){
        QList<Product>::Iterator st=product.begin();
        product.erase(st+i);
    }

    /**
     * @brief Вставляет товар в список по указанному индексу.
     * @param i Индекс для вставки товара.
     * @param prod Товар для вставки.
     */
    void insert(int i, Product prod){
        QList<Product>::Iterator st=product.begin();
        product.insert(st+i, prod);
    }
};

/**
 * @class shop
 * @brief Класс для представления магазина.
 */
class shop {
    QString name;
    QString address;
    Director* director;
    Specialization spec;
    Lists list;
    QMap<QString, int> in_stock;
    QMap<QString, int> in_window;

public:
    /**
     * @brief Конструктор магазина.
     */
    shop() {
        director = new Director();
    }

    /**
     * @brief Получает название магазина.
     * @return Название магазина.
     */
    QString getName() {
        return this->name;
    }

    /**
     * @brief Устанавливает название магазина.
     * @param name Название магазина.
     */
    void setName(QString name) {
        this->name = name;
    }

    /**
     * @brief Получает адрес магазина.
     * @return Адрес магазина.
     */
    QString getAddress() {
        return this->address;
    }

    /**
     * @brief Устанавливает адрес магазина.
     * @param address Адрес магазина.
     */
    void setAddress(QString address) {
        this->address = address;
    }

    /**
     * @brief Получает ФИО директора магазина.
     * @return ФИО директора.
     */
    QString getDirector() {
        if (director) {
            QString fio = director->getFIO();
            return fio;
        }
    }

    /**
     * @brief Устанавливает ФИО директора магазина.
     * @param fio ФИО директора.
     */
    void setDirector(QString fio) {
        if (director) {
            director->setFIO(fio);
        }
    }

    /**
     * @brief Получает специализацию магазина.
     * @return Специализация магазина.
     */
    QString getSpec() {
        return spec.getSpec();
    }

    /**
     * @brief Устанавливает специализацию магазина.
     * @param sp Специализация магазина.
     */
    void setSpec(QString sp) {
        spec.setSpec(sp);
    }


};


#endif // CLASSES_H
