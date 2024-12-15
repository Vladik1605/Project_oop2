#include "redact_director.h"
#include "ui_redact_director.h"
#include "Exceptions.h"

/**
 * @brief Конструктор класса Redact_Director.
 * Инициализирует подключение к базе данных, загружает данные директора по его ID.
 * Устанавливает начальные значения в поля ввода и отключает их для редактирования.
 *
 * @param parent Родительский виджет.
 * @param director_id ID директора.
 */
Redact_Director::Redact_Director(QWidget *parent, QString director_id)
    : QDialog(parent)
    , ui(new Ui::Redact_Director)
{
    ui->setupUi(this);

    // Устанавливаем соединение с базой данных
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("0504Vladik");
    db.open();

    worker = new Director;

    this->setAttribute(Qt::WA_DeleteOnClose);  // Устанавливаем атрибут для удаления окна по закрытию

    this->director_id = director_id;
    firstClick = true;

    // Загружаем данные директора из базы данных
    QSqlQuery query(db);
    query.exec("SELECT number_wards, salary, FIO, Birthday, phone_number, pasport, work_age FROM director WHERE idDirector='" + director_id + "'");
    while(query.next()) {
        ui->lineEdit_FIO->setText(query.value(2).toString());
        worker->setFIO(query.value(2).toString());
        ui->lineEdit_Birth->setText(query.value(3).toString());
        worker->setBirth(query.value(3).toString());
        ui->lineEdit_Phone->setText(query.value(4).toString());
        worker->setPhone(query.value(4).toString());
        ui->lineEdit_Pasport->setText(query.value(5).toString());
        worker->setPassport(query.value(5).toString());
        ui->lineEdit_WA->setText(query.value(6).toString());
        worker->setWork_age(query.value(6).toInt());
        ui->lineEdit_Salary->setText(query.value(1).toString());
        worker->setSalary(query.value(1).toInt());
        ui->lineEdit_Wards->setText(query.value(0).toString());
        worker->setWards(query.value(0).toInt());

        // Отключаем возможность редактирования полей
        ui->lineEdit_FIO->setEnabled(false);
        ui->lineEdit_Birth->setEnabled(false);
        ui->lineEdit_Phone->setEnabled(false);
        ui->lineEdit_Pasport->setEnabled(false);
        ui->lineEdit_Wards->setEnabled(false);
        ui->lineEdit_WA->setEnabled(false);
        ui->lineEdit_Salary->setEnabled(false);
    }

    // Получаем id магазина, связанного с директором
    query.exec("SELECT idShop FROM shop WHERE director_name_shop='" + worker->getFIO() + "'");
    while(query.next()) {
        shop_id = query.value(0).toString();
    }
}

/**
 * @brief Деструктор класса Redact_Director.
 * Освобождает ресурсы.
 */
Redact_Director::~Redact_Director()
{
    delete ui;
}

/**
 * @brief Обработчик завершения редактирования поля ФИО.
 * Проверяет введенные данные на корректность и сохраняет в объект.
 */
void Redact_Director::on_lineEdit_FIO_editingFinished()
{
    ui->label->setText("ФИО");
    ui->label->setStyleSheet("");
    try {
        QString* str = new QString;
        *str = ui->lineEdit_FIO->text();
        ValidatorName(str);  // Проверка корректности ФИО
        worker->setFIO(ui->lineEdit_FIO->text());
    }
    catch (ExCorrection& ex) {
        QMessageBox::information(this, "Внимание!", ex.what(), QMessageBox::Ok);
        ui->lineEdit_FIO->setText("");
    }
}

/**
 * @brief Обработчик завершения редактирования поля Дата рождения.
 * Сохраняет введенную дату рождения в объект.
 */
void Redact_Director::on_lineEdit_Birth_editingFinished()
{
    ui->label_2->setText("Дата рождения");
    ui->label_2->setStyleSheet("");
    worker->setBirth(ui->lineEdit_Birth->text());
}

/**
 * @brief Обработчик завершения редактирования поля Номер телефона.
 * Сохраняет введенный номер телефона в объект.
 */
void Redact_Director::on_lineEdit_Phone_editingFinished()
{
    ui->label_3->setText("Номер телефона");
    ui->label_3->setStyleSheet("");

    QString* str = new QString;
    *str = ui->lineEdit_Phone->text();
    worker->setPhone(*str);
}

/**
 * @brief Обработчик завершения редактирования поля Паспорт.
 * Сохраняет паспортные данные в объект.
 */
void Redact_Director::on_lineEdit_Pasport_editingFinished()
{
    ui->label_4->setText("Паспортные данные(серия и номер)");
    ui->label_4->setStyleSheet("");
    worker->setPassport(ui->lineEdit_Pasport->text());
}

/**
 * @brief Обработчик завершения редактирования поля Стаж работы.
 * Проверяет корректность введенного стажа и сохраняет в объект.
 */
void Redact_Director::on_lineEdit_WA_editingFinished()
{
    try {
        QString* str = new QString;
        *str = ui->lineEdit_WA->text();
        ValidatorWorkAge(str);  // Проверка корректности стажа работы
        worker->setWork_age(ui->lineEdit_WA->text().toInt());
    }
    catch (ExCorrection& e) {
        QMessageBox::information(this, "Внимание!", e.what(), QMessageBox::Ok);
        ui->lineEdit_WA->setText("");
    }
}

/**
 * @brief Обработчик завершения редактирования поля Зарплата.
 * Проверяет корректность введенной зарплаты и сохраняет в объект.
 */
void Redact_Director::on_lineEdit_Salary_editingFinished()
{
    ui->label_6->setText("Зар. плата");
    ui->label_6->setStyleSheet("");
    try {
        QString* str = new QString;
        *str = ui->lineEdit_Salary->text();
        ValidatorWorkAge(str);  // Проверка корректности зарплаты
        worker->setSalary(ui->lineEdit_Salary->text().toInt());
    }
    catch (ExCorrection& e) {
        QMessageBox::information(this, "Внимание!", e.what(), QMessageBox::Ok);
        ui->lineEdit_Salary->setText("");
    }
}

/**
 * @brief Обработчик завершения редактирования поля Количество палат.
 * Проверяет корректность введенного количества палат и сохраняет в объект.
 */
void Redact_Director::on_lineEdit_Wards_editingFinished()
{
    try {
        QString* str = new QString;
        *str = ui->lineEdit_Wards->text();
        ValidatorWards(str);  // Проверка корректности количества палат
        worker->setWards(ui->lineEdit_Wards->text().toInt());
    }
    catch (ExCorrection& ex) {
        QMessageBox::information(this, "Внимание!", ex.what(), QMessageBox::Ok);
        ui->lineEdit_Wards->setText("");
    }
}


/**
 * @brief Метод для обработки нажатия кнопки "Сохранить" или "Редактировать"
 */
void Redact_Director::on_SaveButton_clicked()
{
    // Блок обработки первого клика
    if (firstClick) {
        // Изменение текста кнопки на "Сохранить"
        this->ui->SaveButton->setText("Сохранить");

        // Разрешаем редактирование всех полей ввода
        ui->lineEdit_FIO->setEnabled(true);
        ui->lineEdit_Birth->setEnabled(true);
        ui->lineEdit_Phone->setEnabled(true);
        ui->lineEdit_Pasport->setEnabled(true);
        ui->lineEdit_WA->setEnabled(true);
        ui->lineEdit_Salary->setEnabled(true);
        ui->lineEdit_Wards->setEnabled(true);

        // Устанавливаем маски ввода для полей
        ui->lineEdit_Birth->setInputMask("99.99.9999");
        ui->lineEdit_Phone->setInputMask("+9(999) 999-99-99");
        ui->lineEdit_Pasport->setInputMask("9999 999999");

        // Флаг первого клика изменяется на false
        firstClick = false;
    }
    else {
        // Блок валидации данных перед сохранением
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
            // Проверяем поля на пустоту и правильность ввода
            if(ui->lineEdit_FIO->text().isEmpty()){
                errors.insert(ui->label,"ФИО не должно быть пустым");
            }
            if(QString::compare(ui->lineEdit_Birth->text(),"..")==0){
                errors.insert(ui->label_2,"Дата рождения не должна быть пустой");
            }
            if(QString::compare(ui->lineEdit_Phone->text(),"+() --")==0){
                errors.insert(ui->label_3,"Номер телефона не должен быть пустым");
            }
            if(QString::compare(ui->lineEdit_Pasport->text()," ")==0){
                errors.insert(ui->label_4,"Паспорт не должен быть пустым");
            }
            if(ui->lineEdit_Salary->text().isEmpty()){
                errors.insert(ui->label_6,"Зар. плата не должна быть пустой");
            }
            if(ui->lineEdit_Phone->text().length()<17){
                errors.insert(ui->label_3,"Номер телефона долже быть полным");
            }
            if(ui->lineEdit_Pasport->text().length()<11){
                errors.insert(ui->label_4,"Серия и номер паспорта должны быть полными");
            }
            if(ui->lineEdit_Birth->text().length()<10){
                errors.insert(ui->label_2,"Дата рождения должна быть полной(ДД-ММ-ГГГГ)");
            }

            // Если есть ошибки, выбрасываем исключение
            if(!errors.empty()){
                throw MyEx{errors};
            }

            // Блок обновления данных в базе данных
            query.exec("UPDATE director SET number_wards='"+QString::number(worker->getWards())+"', salary='"+QString::number(worker->getSalary())+"', FIO='"+worker->getFIO()+"', Birthday='"+worker->getBirth()+"', phone_number='"+worker->getPhone()+"', pasport='"+worker->getPassport()+"', work_age='"+QString::number(worker->getWork_age())+"' WHERE idDirector='"+director_id+"'");
            query.exec("UPDATE shop SET director_name_shop='"+worker->getFIO()+"' WHERE idShop='"+shop_id+"'");

            // Изменение текста кнопки на "Редактировать"
            this->ui->SaveButton->setText("Редактировать");

            // Отключаем редактирование полей
            ui->lineEdit_FIO->setEnabled(false);
            ui->lineEdit_Birth->setEnabled(false);
            ui->lineEdit_Phone->setEnabled(false);
            ui->lineEdit_Pasport->setEnabled(false);
            ui->lineEdit_WA->setEnabled(false);
            ui->lineEdit_Salary->setEnabled(false);
            ui->lineEdit_Wards->setEnabled(false);

            // Флаг первого клика снова ставим в true
            firstClick = true;

            // Обновляем значения в полях после сохранения
            ui->lineEdit_FIO->setText(worker->getFIO());
            ui->lineEdit_Birth->setText(worker->getBirth());
            ui->lineEdit_Phone->setText(worker->getPhone());
            ui->lineEdit_Pasport->setText(worker->getPassport());
            ui->lineEdit_WA->setText(QString::number(worker->getWork_age()));
            ui->lineEdit_Salary->setText(QString::number(worker->getSalary()));
            ui->lineEdit_Wards->setText(QString::number(worker->getWards()));
        }
        // Блок обработки исключений
        catch (MyEx& ex) {
            ex.ShowError();
        }
    }
}



