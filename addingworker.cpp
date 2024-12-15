#include "addingworker.h"
#include "ui_addingworker.h"
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
 * @brief Конструктор класса AddingWorker.
 *
 * Этот конструктор инициализирует пользовательский интерфейс и подключает базу данных.
 * Также настраивает маски для ввода и связывает действия с кнопками.
 *
 * @param parent Родительский виджет для диалогового окна.
 * @param shop Указатель на объект магазина, с которым связан этот работник.
 */
AddingWorker::AddingWorker(QWidget *parent, shop* shop)
    : QDialog(parent)
    , ui(new Ui::AddingWorker)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    // Устанавливаем маски для ввода данных
    ui->lineEdit_Birth->setInputMask("99.99.9999");
    ui->lineEdit_Phone->setInputMask("+9(999) 999-99-99");
    ui->lineEdit_Pasport->setInputMask("9999 999999");

    // Настройка таймера для активации кнопки
    buttonTimer = new QTimer(this);
    connect(buttonTimer, &QTimer::timeout, this, &AddingWorker::enableButton);

    this->setLayout(ui->gridLayout);

    // Устанавливаем подключение к базе данных
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("0504Vladik");
    db.open();

    worker = new Asistant;
    this->shop1 = shop;

    // Получаем id магазина для дальнейшего использования
    QSqlQuery query(db);
    query.exec("SELECT idShop FROM shop WHERE shop_name='"+shop1->getName()+"'");
    while(query.next()){
        worker->setWork_place(query.value(0).toInt());
    }
}

/**
 * @brief Деструктор для класса AddingWorker.
 *
 * Освобождает ресурсы, связанные с интерфейсом.
 */
AddingWorker::~AddingWorker()
{
    delete ui;
}

/**
 * @brief Включает кнопку после задержки.
 *
 * Этот метод вызывается таймером после заданного времени и включает кнопку.
 */
void AddingWorker::enableButton() {
    ui->SaveButton->setEnabled(true);
}

/**
 * @brief Обработчик завершения редактирования поля "ФИО".
 *
 * После завершения редактирования поля "ФИО" происходит валидация данных и установка значения в объект worker.
 */
void AddingWorker::on_lineEdit_FIO_editingFinished()
{
    ui->label->setText("ФИО");
    ui->label->setStyleSheet("");
    try {
        QString *str = new QString;
        *str = ui->lineEdit_FIO->text();
        ValidatorName(str);  // Валидация ФИО
        worker->setFIO(ui->lineEdit_FIO->text());
    }
    catch (ExCorrection& ex) {
        QMessageBox::information(this, "Внимание!", ex.what(), QMessageBox::Ok);
        ui->lineEdit_FIO->setText("");
    }
}

/**
 * @brief Обработчик завершения редактирования поля "Дата рождения".
 *
 * Устанавливает дату рождения работника.
 */
void AddingWorker::on_lineEdit_Birth_editingFinished()
{
    ui->label_2->setText("Дата рождения");
    ui->label_2->setStyleSheet("");
    worker->setBirth(ui->lineEdit_Birth->text());
}

/**
 * @brief Обработчик завершения редактирования поля "Номер телефона".
 *
 * Проверяет, существует ли уже работник с таким номером телефона, и устанавливает его в объект worker.
 */
void AddingWorker::on_lineEdit_Phone_editingFinished()
{
    ui->label_3->setText("Номер телефона");
    ui->label_3->setStyleSheet("");

    int id = -1;
    QSqlQuery query(db);
    query.exec("SELECT idAssistant FROM assistant WHERE phone_number='"+ui->lineEdit_Phone->text()+"' AND work_place='"+QString::number(worker->getWork_place())+"'");
    while(query.next()){
        id = query.value(0).toInt();
    }
    try {
        if(id == -1){
            QString *str = new QString;
            *str = ui->lineEdit_Phone->text();
            //ValidatorPhoneNumbe(str); // (включить проверку номера)
            worker->setPhone(*str);
        }
        else{
            throw new ExCorrection{"Работник с таким телефонным номером уже добавлен"};
        }
    } catch (ExCorrection ex) {
        QMessageBox::information(this, "Внимание!", ex.what(), QMessageBox::Ok);
        ui->lineEdit_Phone->setText("");
    }
}

/**
 * @brief Обработчик завершения редактирования поля "Паспортные данные".
 *
 * Проверяет, существует ли уже работник с такими паспортными данными, и устанавливает их в объект worker.
 */
void AddingWorker::on_lineEdit_Pasport_editingFinished()
{
    ui->label_4->setText("Паспортные данные(серия и номер)");
    ui->label_4->setStyleSheet("");

    int id = -1;
    QSqlQuery query(db);
    query.exec("SELECT idAssistant FROM assistant WHERE pasport='"+ui->lineEdit_Pasport->text()+"' AND work_place='"+QString::number(worker->getWork_place())+"'");
    while(query.next()){
        id = query.value(0).toInt();
    }
    if(id != -1){
        ui->lineEdit_Pasport->setText("");
        QMessageBox::information(this, "Внимание!", "Работник с таким паспортом уже добавлен", QMessageBox::Ok);
    }
    else{
        worker->setPassport(ui->lineEdit_Pasport->text());
    }
}

/**
 * @brief Обработчик завершения редактирования поля "Стаж работы".
 *
 * Валидация стажа работы и установка значения в объект worker.
 */
void AddingWorker::on_lineEdit_WA_editingFinished()
{
    try {
        QString *str = new QString;
        *str = ui->lineEdit_WA->text();
        ValidatorWorkAge(str);
        worker->setWork_age(ui->lineEdit_WA->text().toInt());
    }
    catch(ExCorrection& e){
        QMessageBox::information(this, "Внимание!", e.what(), QMessageBox::Ok);
        ui->lineEdit_WA->setText("");
    }
}

/**
 * @brief Обработчик завершения редактирования поля "Зарплата".
 *
 * Валидация значения зарплаты и установка его в объект worker.
 */
void AddingWorker::on_lineEdit_Salary_editingFinished()
{
    ui->label_6->setText("Зар. плата");
    ui->label_6->setStyleSheet("");
    try {
        QString *str = new QString;
        *str = ui->lineEdit_Salary->text();
        ValidatorSalary(str);
        worker->setSalary(ui->lineEdit_Salary->text().toInt());
    }
    catch(ExCorrection& e){
        QMessageBox::information(this, "Внимание!", e.what(), QMessageBox::Ok);
        ui->lineEdit_Salary->setText("");
    }
}

/**
 * @brief Обработчик завершения редактирования поля "Сектор".
 *
 * Устанавливает значение сектора в объект worker.
 */
void AddingWorker::on_lineEdit_Sector_editingFinished()
{
    worker->setSector(ui->lineEdit_Sector->text());
}

/**
 * @brief Скрытие метки с анимацией исчезновения.
 *
 * Эта функция применяется для плавного исчезновения метки с уведомлением.
 */
void AddingWorker::fadeOut(){
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect();
    ui->label_8->setGraphicsEffect(effect);
    QPropertyAnimation *a = new QPropertyAnimation(effect,"opacity");
    a->setDuration(1000); // время анимации
    a->setStartValue(1);
    a->setEndValue(0);
    a->setEasingCurve(QEasingCurve::OutBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
    connect(a, SIGNAL(finished()), ui->label_8, SLOT(hide()));
}

/**
 * @brief Обработчик нажатия кнопки "Добавить работника".
 *
 * Проводит валидацию данных и добавляет работника в базу данных.
 */
void AddingWorker::on_SaveButton_clicked()
{
    if (!ui->SaveButton->isEnabled()) {
        return;
    }

    ui->SaveButton->setEnabled(false);
    buttonTimer->start(500);

    QSqlQuery query(db);
    try {
        QMap<QLabel*, QString> errors;

        // Проверка на пустые поля
        if(ui->lineEdit_FIO->text().isEmpty()){
            errors.insert(ui->label, "ФИО не должно быть пустым");
        }
        if(QString::compare(ui->lineEdit_Birth->text(), "..") == 0){
            errors.insert(ui->label_2, "Дата рождения не должна быть пустой");
        }
        if(QString::compare(ui->lineEdit_Phone->text(), "+() --") == 0){
            errors.insert(ui->label_3, "Номер телефона не должен быть пустым");
        }
        if(QString::compare(ui->lineEdit_Pasport->text(), " ") == 0){
            errors.insert(ui->label_4, "Паспорт не должен быть пустым");
        }
        if(ui->lineEdit_Salary->text().isEmpty()){
            errors.insert(ui->label_6, "Зар. плата не должна быть пустой");
        }
        if(ui->lineEdit_Phone->text().length() < 17){
            errors.insert(ui->label_3, "Номер телефона должен быть полным");
        }
        if(ui->lineEdit_Pasport->text().length() < 11){
            errors.insert(ui->label_4, "Серия и номер паспорта должны быть полными");
        }
        if(ui->lineEdit_Birth->text().length() < 10){
            errors.insert(ui->label_2, "Дата рождения должна быть полной(ДД-ММ-ГГГГ)");
        }
        if(!errors.empty()){
            throw MyEx{errors};
        }

        // Добавление работника в базу данных
        query.exec("INSERT INTO assistant (sector, salary, FIO, Birthday, phone_number, pasport, work_place, work_age) VALUES('"+worker->getSector()+"', '"+QString::number(worker->getSalary())+"', '"+worker->getFIO()+"', '"+worker->getBirth()+"', '"+worker->getPhone()+"', '"+worker->getPassport()+"', '"+QString::number(worker->getWork_place())+"', '"+QString::number(worker->getWork_age())+"')");

        // Очистка полей формы после успешного добавления
        ui->lineEdit_FIO->setText("");
        ui->lineEdit_Birth->setText("");
        ui->lineEdit_Phone->setText("");
        ui->lineEdit_Pasport->setText("");
        ui->lineEdit_WA->setText("");
        ui->lineEdit_Salary->setText("");
        ui->lineEdit_Sector->setText("");

        // Сброс данных в объекте worker
        worker->setSalary(NULL);
        worker->setSector(NULL);
        worker->setWork_age(NULL);
        worker->setBirth(NULL);
        worker->setFIO(NULL);
        worker->setPassport(NULL);
        worker->setPhone(NULL);

        // Показ уведомления об успешном добавлении
        QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect();
        ui->label_8->setGraphicsEffect(effect);
        ui->label_8->setStyleSheet("border: 3px solid gray;border-radius:20px;background-color:#ffffff;color:gray");
        ui->label_8->setAlignment(Qt::AlignCenter);
        ui->label_8->setText("Вы добавили работника");

        // Анимация уведомления
        QPropertyAnimation* a = new QPropertyAnimation(effect,"opacity");
        a->setDuration(1000);
        a->setStartValue(0);
        a->setEndValue(1);
        a->setEasingCurve(QEasingCurve::InBack);
        a->start(QPropertyAnimation::DeleteWhenStopped);
        ui->label_8->show();

        // Таймер для скрытия уведомления через 2 секунды
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &AddingWorker::fadeOut);
        timer->start(2000);

        ui->SkipButton->setText("Перейти к директору");
    }
    catch (MyEx& ex) {
        ex.ShowError();
    }
}

/**
 * @brief Обработчик нажатия кнопки "Перейти к директору".
 *
 * Открывает окно для добавления директора и закрывает текущее окно.
 */
void AddingWorker::on_SkipButton_clicked()
{
    AddDirector *Dir_window = new AddDirector(nullptr, shop1);
    Dir_window->show();
    db.close();
    close();
}
