#include "AddDirector.h"
#include "ui_AddDirector.h"
#include "classes.h"
#include <QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QTimer>
#include <QChar>
#include <QDebug>
#include "AddDirector.h"
#include "classes.h"
#include "Exceptions.h"

/**
 * @brief Конструктор диалогового окна для добавления директора.
 * @param parent Родительский виджет.
 * @param shop12 Указатель на объект магазина, с которым связан директор.
 */
AddDirector::AddDirector(QWidget *parent, shop* shop12)
    : QDialog(parent)
    , ui(new Ui::AddDirector)
{
    ui->setupUi(this);

    // Установка маски ввода для полей
    ui->lineEdit_Birth->setInputMask("99.99.9999");
    ui->lineEdit_Phone->setInputMask("+9(999) 999-99-99");
    ui->lineEdit_Pasport->setInputMask("9999 999999");

    // Таймер для включения кнопки
    buttonTimer = new QTimer(this);
    connect(buttonTimer, &QTimer::timeout, this, &AddDirector::enableButton);

    // Установка макета для диалогового окна
    this->setLayout(ui->gridLayout);

    // Подключение к базе данных
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("0504Vladik");
    db.open();

    // Инициализация объекта работника и магазина
    worker = new Director;
    shop1 = new shop();

    // Устанавливаем атрибут для автоматического удаления окна при закрытии
    this->setAttribute(Qt::WA_DeleteOnClose);

    // Получение магазина и директора
    this->shop1 = shop12;
    ui->lineEdit_FIO->setText(shop1->getDirector());
    ui->lineEdit_FIO->setEnabled(false);

    // Запрос для получения ID магазина
    QSqlQuery query(db);
    query.exec("SELECT idShop FROM shop WHERE shop_name='" + shop1->getName() + "'");
    while (query.next()) {
        worker->setWork_place(query.value(0).toInt());
    }

    worker->setFIO(shop12->getDirector());
}

/**
 * @brief Деструктор для освобождения ресурсов.
 */
AddDirector::~AddDirector()
{
    delete ui;
}

/**
 * @brief Включение кнопки после задержки.
 */
void AddDirector::enableButton() {
    ui->SaveButton->setEnabled(true);
}

/**
 * @brief Обработчик изменения текста в поле ФИО.
 */
void AddDirector::on_lineEdit_FIO_editingFinished()
{
    ui->label->setText("ФИО");
    ui->label->setStyleSheet("");
    try {
        QString* str = new QString;
        *str = ui->lineEdit_FIO->text();
        qDebug() << *str;

        // Валидация имени
        ValidatorName(str);
        worker->setFIO(ui->lineEdit_FIO->text());
    }
    catch (ExCorrection& ex) {
        QMessageBox::information(this, "Внимание!", ex.what(), QMessageBox::Ok);
        ui->lineEdit_FIO->setText("");
    }
}

/**
 * @brief Обработчик изменения текста в поле Дата рождения.
 */
void AddDirector::on_lineEdit_Birth_editingFinished()
{
    ui->label_2->setText("Дата рождения");
    ui->label_2->setStyleSheet("");
    worker->setBirth(ui->lineEdit_Birth->text());
}

/**
 * @brief Обработчик изменения текста в поле Номер телефона.
 */
void AddDirector::on_lineEdit_Phone_editingFinished()
{
    ui->label_3->setText("Номер телефона");
    ui->label_3->setStyleSheet("");

    QString* str = new QString;
    *str = ui->lineEdit_Phone->text();
    worker->setPhone(*str);
}

/**
 * @brief Обработчик изменения текста в поле Паспортные данные.
 */
void AddDirector::on_lineEdit_Pasport_editingFinished()
{
    ui->label_4->setText("Паспортные данные(серия и номер)");
    ui->label_4->setStyleSheet("");
    worker->setPassport(ui->lineEdit_Pasport->text());
}

/**
 * @brief Обработчик изменения текста в поле Стаж работы.
 */
void AddDirector::on_lineEdit_WA_editingFinished()
{
    try {
        QString* str = new QString;
        *str = ui->lineEdit_WA->text();
        ValidatorWorkAge(str);
        worker->setWork_age(ui->lineEdit_WA->text().toInt());
    }
    catch (ExCorrection& e) {
        QMessageBox::information(this, "Внимание!", e.what(), QMessageBox::Ok);
        ui->lineEdit_WA->setText("");
    }
}

/**
 * @brief Обработчик изменения текста в поле Зарплата.
 */
void AddDirector::on_lineEdit_Salary_editingFinished()
{
    ui->label_6->setText("Зар. плата");
    ui->label_6->setStyleSheet("");
    try {
        QString* str = new QString;
        *str = ui->lineEdit_Salary->text();
        ValidatorWorkAge(str);
        worker->setSalary(ui->lineEdit_Salary->text().toInt());
    }
    catch (ExCorrection& e) {
        QMessageBox::information(this, "Внимание!", e.what(), QMessageBox::Ok);
        ui->lineEdit_Salary->setText("");
    }
}

/**
 * @brief Обработчик изменения текста в поле Количество подчиненных.
 */
void AddDirector::on_lineEdit_Wards_editingFinished()
{
    try {
        QString* str = new QString;
        *str = ui->lineEdit_Wards->text();
        ValidatorWards(str);
        worker->setWards(ui->lineEdit_Wards->text().toInt());
    } catch (ExCorrection& ex) {
        QMessageBox::information(this, "Внимание!", ex.what(), QMessageBox::Ok);
        ui->lineEdit_Wards->setText("");
    }
}

/**
 * @brief Эффект исчезновения для сообщения.
 */
void AddDirector::fadeOut()
{
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect();
    ui->label_8->setGraphicsEffect(effect);
    QPropertyAnimation* a = new QPropertyAnimation(effect, "opacity");
    a->setDuration(1000);
    a->setStartValue(1);
    a->setEndValue(0);
    a->setEasingCurve(QEasingCurve::OutBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
    connect(a, SIGNAL(finished()), ui->label_8, SLOT(hide()));
}

/**
 * @brief Обработчик нажатия кнопки "Добавить директора".
 */
void AddDirector::on_SaveButton_clicked()
{
    if (!ui->SaveButton->isEnabled()) {
        return;
    }

    ui->SaveButton->setEnabled(false);
    buttonTimer->start(500);

    QSqlQuery query(db);
    try {
        QMap<QLabel*, QString> errors;
        QSqlQuery query(db);
        query.exec("SELECT idDirector FROM director WHERE pasport='"+worker->getPassport()+"'");
        int repeated_id=-1;
        while(query.next()){
            repeated_id=query.value(0).toInt();
        }
        if(repeated_id!=-1){
            errors.insert(ui->label_4, "Человек с таким паспортом уже являтся директором");
        }
        // Проверка всех полей на пустоту
        if (ui->lineEdit_FIO->text().isEmpty()) {
            errors.insert(ui->label, "ФИО не должно быть пустым");
        }
        if (QString::compare(ui->lineEdit_Birth->text(), "..") == 0) {
            errors.insert(ui->label_2, "Дата рождения не должна быть пустой");
        }
        if (QString::compare(ui->lineEdit_Phone->text(), "+() --") == 0) {
            errors.insert(ui->label_3, "Номер телефона не должен быть пустым");
        }
        if (QString::compare(ui->lineEdit_Pasport->text(), " ") == 0) {
            errors.insert(ui->label_4, "Паспорт не должен быть пустым");
        }
        if (ui->lineEdit_Salary->text().isEmpty()) {
            errors.insert(ui->label_6, "Зар. плата не должна быть пустой");
        }
        if (ui->lineEdit_Phone->text().length() < 17) {
            errors.insert(ui->label_3, "Номер телефона должен быть полным");
        }
        if (ui->lineEdit_Pasport->text().length() < 11) {
            errors.insert(ui->label_4, "Серия и номер паспорта должны быть полными");
        }
        if (ui->lineEdit_Birth->text().length() < 10) {
            errors.insert(ui->label_2, "Дата рождения должна быть полной (ДД-ММ-ГГГГ)");
        }

        // Если есть ошибки, выбрасываем исключение
        if (!errors.empty()) {
            throw MyEx{errors};
        }

        // Запрос на получение имени магазина по ID
        QString wp;
        query.exec("SELECT shop_name FROM shop WHERE idShop='" + QString::number(worker->getWork_place()) + "'");
        while (query.next()) {
            wp = query.value(0).toString();
        }

        // Добавление данных о директоре в базу данных
        query.exec("INSERT INTO director (number_wards, salary, FIO, Birthday, phone_number, pasport, work_place, work_age) VALUES('"
                   + QString::number(worker->getWards()) + "', '" + QString::number(worker->getSalary()) + "', '"
                   + worker->getFIO() + "', '" + worker->getBirth() + "', '" + worker->getPhone() + "', '"
                   + worker->getPassport() + "', '" + wp + "', '" + QString::number(worker->getWork_age()) + "')");

        // Очистка полей
        ui->lineEdit_FIO->setText("");
        ui->lineEdit_Birth->setText("");
        ui->lineEdit_Phone->setText("");
        ui->lineEdit_Pasport->setText("");
        ui->lineEdit_WA->setText("");
        ui->lineEdit_Salary->setText("");
        ui->lineEdit_Wards->setText("");

        // Сброс значений в объекте worker
        worker->setSalary(NULL);
        worker->setWards(NULL);
        worker->setWork_age(NULL);
        worker->setBirth(NULL);
        worker->setFIO(NULL);
        worker->setPassport(NULL);
        worker->setPhone(NULL);

        // Показ сообщения об успешном добавлении
        QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect();
        ui->label_8->setGraphicsEffect(effect);
        ui->label_8->setStyleSheet("border: 3px solid gray; border-radius: 20px; background-color: #ffffff; color: gray");
        ui->label_8->setAlignment(Qt::AlignCenter);
        ui->label_8->setText("Вы добавили директора");

        QPropertyAnimation* a = new QPropertyAnimation(effect, "opacity");
        a->setDuration(1000);
        a->setStartValue(0);
        a->setEndValue(1);
        a->setEasingCurve(QEasingCurve::InBack);
        a->start(QPropertyAnimation::DeleteWhenStopped);
        ui->label_8->show();

        // Запуск таймера для скрытия сообщения
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &AddDirector::fadeOut);
        timer->start(2000);

        // Закрытие окна
        close();
    }
    catch (MyEx& ex) {
        ex.ShowError();
    }
}

void AddDirector::on_SkipButton_clicked()
{
    close();
}

