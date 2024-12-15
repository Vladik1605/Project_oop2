#include "filesaving.h"
#include "ui_filesaving.h"
#include <QFileDialog>
#include <QMessageBox>
#include "Exceptions.h"
#include <QXmlStreamWriter>
#include <QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QTimer>
#include <QPrinter>
#include <QPainter>
#include "mainwindow.h"

/**
 * @brief Конструктор класса FileSaving.
 * Инициализирует пользовательский интерфейс и подключение к базе данных.
 *
 * @param parent родительский элемент окна.
 * @param str строка, которая указывает тип файла.
 * @param table таблица, передаваемая в качестве параметра.
 */
FileSaving::FileSaving(QWidget *parent, QString str, QTableWidget* table)
    : QDialog(parent)
    , ui(new Ui::FileSaving)
{
    ui->setupUi(this);
    this->parent=str;
    this->table=table;
    this->setAttribute(Qt::WA_DeleteOnClose);

    this->setLayout(ui->gridLayout);
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("0504Vladik");
    db.open();

}

/**
 * @brief Деструктор класса FileSaving.
 * Закрывает соединение с базой данных и освобождает ресурсы.
 */
FileSaving::~FileSaving()
{
    delete ui;
    db.close();
}


/**
 * @brief Обработчик нажатия на кнопку выбора папки.
 * Открывает диалог выбора папки и устанавливает выбранный путь в поле ввода.
 */
void FileSaving::ChooseButton()
{
        QString folder = QFileDialog::getExistingDirectory(nullptr,"Выберите папку",QDir::homePath());
        ui->lineEdit->setText(folder);
}



/**
 * @brief Функция плавного исчезновения текста.
 * Создает анимацию исчезновения и применяет её к метке.
 */
void FileSaving:: fadeOut(){
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect();
    ui->label_2->setGraphicsEffect(effect);
    QPropertyAnimation *a = new QPropertyAnimation(effect,"opacity");
    a->setDuration(1000);
    a->setStartValue(1);
    a->setEndValue(0);
    a->setEasingCurve(QEasingCurve::OutBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
    connect(a,SIGNAL(finished()),ui->label_2,SLOT(hide()));
}


/**
 * @brief Обработчик нажатия кнопки сохранения файла.
 * Производит валидацию пути, сохраняет данные из базы данных в XML файл.
 *
 * @throws ExCorrection исключение, если произошла ошибка при обработке данных.
 */
void FileSaving::AcceptButton()
{

    try {
        if(parent=="XML"){

        ValidatorFile(ui->lineEdit->text());
        QFile file(ui->lineEdit->text()+"/shop_info.xml");
        file.open(QIODevice::WriteOnly);
        QXmlStreamWriter Writer(&file);
        Writer.setAutoFormatting(true);
        Writer.writeStartDocument();
        QSqlQuery query(db);
        Writer.writeStartElement("DATA");

        Writer.writeStartElement("SHOPS");
        query.exec("SELECT idShop, shop_name, shop_address, director_name_shop, spec_of_shop FROM shop");
        int i=0;
        while (query.next()) {
            Writer.writeStartElement("shop" + QString::number(i));
            Writer.writeTextElement("id", query.value(0).toString());
            Writer.writeTextElement("name", query.value(1).toString());
            Writer.writeTextElement("address", query.value(2).toString());
            Writer.writeTextElement("director", query.value(3).toString());

            QSqlQuery query1(db);
            query1.exec("SELECT specialization FROM specialization WHERE Specid='"+query.value(4).toString()+"'");
            while(query1.next()){
                Writer.writeTextElement("specialization", query1.value(0).toString());
            }
            Writer.writeEndElement(); // Закрыть "shopX"
            i++;
        }
        Writer.writeEndElement(); // Закрыть "SHOPS"
        i=0;
        Writer.writeStartElement("ASSISTANTS");
        query.exec("SELECT idAssistant, sector, salary, overtime_hour, FIO, Birthday, phone_number, pasport, work_place, work_age FROM assistant");
        while(query.next()){
            Writer.writeStartElement("assistant" + QString::number(i));
            Writer.writeStartElement("id");
            Writer.writeCharacters(query.value(0).toString());
            Writer.writeEndElement();
            Writer.writeStartElement("sector");
            Writer.writeCharacters(query.value(1).toString());
            Writer.writeEndElement();
            Writer.writeStartElement("salary");
            Writer.writeCharacters(query.value(2).toString());
            Writer.writeEndElement();
            Writer.writeStartElement("overtime_hour");
            Writer.writeCharacters(query.value(3).toString());
            Writer.writeEndElement();
            Writer.writeStartElement("FIO");
            Writer.writeCharacters(query.value(4).toString());
            Writer.writeEndElement();
            Writer.writeStartElement("Birthday");
            Writer.writeCharacters(query.value(5).toString());
            Writer.writeEndElement();
            Writer.writeStartElement("phone_number");
            Writer.writeCharacters(query.value(6).toString());
            Writer.writeEndElement();
            Writer.writeStartElement("pasport");
            Writer.writeCharacters(query.value(7).toString());
            Writer.writeEndElement();


            QSqlQuery query1(db);
            query1.exec("SELECT shop_name FROM shop WHERE idShop='"+query.value(8).toString()+"'");
            while(query1.next()){
                Writer.writeStartElement("work_place");
                Writer.writeCharacters(query1.value(0).toString());
                Writer.writeEndElement();
            }

            Writer.writeStartElement("work_age");
            Writer.writeCharacters(query.value(9).toString());
            Writer.writeEndElement();
            Writer.writeEndElement(); // Закрываем элемент assistant
            i++;
        }
        Writer.writeEndElement(); // Закрываем элемент ASSISTANTS

        i=0;

        Writer.writeStartElement("DIRECTORS");
        query.exec("SELECT idDirector, number_wards, salary, FIO, Birthday, phone_number, pasport, work_place, work_age FROM director");
        while(query.next()){
            Writer.writeStartElement("director"+QString::number(i));
            Writer.writeStartElement("id");
            Writer.writeCharacters(query.value(0).toString());
            Writer.writeEndElement();
            Writer.writeStartElement("number_wards");
            Writer.writeCharacters(query.value(1).toString());
            Writer.writeEndElement();
            Writer.writeStartElement("salary");
            Writer.writeCharacters(query.value(2).toString());
            Writer.writeEndElement();
            Writer.writeStartElement("FIO");
            Writer.writeCharacters(query.value(3).toString());
            Writer.writeEndElement();
            Writer.writeStartElement("Birthday");
            Writer.writeCharacters(query.value(4).toString());
            Writer.writeEndElement();
            Writer.writeStartElement("phone_number");
            Writer.writeCharacters(query.value(5).toString());
            Writer.writeEndElement();
            Writer.writeStartElement("pasport");
            Writer.writeCharacters(query.value(6).toString());
            Writer.writeEndElement();


            Writer.writeStartElement("work_place");
            Writer.writeCharacters(query.value(7).toString());
            Writer.writeEndElement();




            Writer.writeStartElement("work_age");
            Writer.writeCharacters(query.value(8).toString());
            Writer.writeEndElement();

            Writer.writeEndElement();
            i++;

        }





        i=0;
        Writer.writeEndElement();
        Writer.writeStartElement("PRODUCTS");
        query.exec("SELECT idProduct, name, type, size FROM product");
        while(query.next()){
            Writer.writeStartElement("product"+QString::number(i));
            Writer.writeStartElement("id");
            Writer.writeCharacters(query.value(0).toString());
            Writer.writeEndElement();
            Writer.writeStartElement("name");
            Writer.writeCharacters(query.value(1).toString());
            Writer.writeEndElement();


            QSqlQuery query1(db);
            query1.exec("SELECT product_type FROM type WHERE idType='"+query.value(2).toString()+"'");
            while(query1.next()){
                Writer.writeStartElement("type");
                Writer.writeCharacters(query1.value(0).toString());
                Writer.writeEndElement();
            }

            Writer.writeStartElement("size");
            Writer.writeCharacters(query.value(3).toString());
            Writer.writeEndElement();

            Writer.writeEndElement();
            i++;

        }



        i=0;
        Writer.writeEndElement();
        Writer.writeStartElement("PRODUCTS_SHOPS");
        query.exec("SELECT idperson_product, idProduct, idShop, in_stock, in_window, price FROM product_shop");
        while(query.next()){
            Writer.writeStartElement("product_shop"+QString::number(i));



            Writer.writeStartElement("idperson_product");
            Writer.writeCharacters(query.value(0).toString());
            Writer.writeEndElement();

            QSqlQuery query1(db);
            query1.exec("SELECT name, size FROM product WHERE idProduct='"+query.value(1).toString()+"'");
            while(query1.next()){
                Writer.writeStartElement("idProduct");
                Writer.writeCharacters(query1.value(0).toString());
                Writer.writeEndElement();
                Writer.writeStartElement("SizeProduct");
                Writer.writeCharacters(query1.value(1).toString());
                Writer.writeEndElement();
            }


            query1.exec("SELECT shop_name FROM shop WHERE idShop='"+query.value(2).toString()+"'");
            while(query1.next()){
                Writer.writeStartElement("idShop");
                Writer.writeCharacters(query1.value(0).toString());
                Writer.writeEndElement();
            }

            Writer.writeStartElement("in_stock");
            Writer.writeCharacters(query.value(3).toString());
            Writer.writeEndElement();
            Writer.writeStartElement("in_window");
            Writer.writeCharacters(query.value(4).toString());
            Writer.writeEndElement();
            Writer.writeStartElement("price");
            Writer.writeCharacters(query.value(5).toString());
            Writer.writeEndElement();
            Writer.writeEndElement();
            i++;

        }





        i=0;
        Writer.writeEndElement();
        Writer.writeStartElement("SPECIALIZATION");
        query.exec("SELECT Specid, specialization FROM specialization");
        while(query.next()){
            Writer.writeStartElement("specilization"+QString::number(i));
            Writer.writeStartElement("Specid");
            Writer.writeCharacters(query.value(0).toString());
            Writer.writeEndElement();
            Writer.writeStartElement("specialization");
            Writer.writeCharacters(query.value(1).toString());
            Writer.writeEndElement();

            Writer.writeEndElement();
            i++;

        }





        i=0;
        Writer.writeEndElement();
        Writer.writeStartElement("TYPE");
        query.exec("SELECT idType, product_type FROM type");
        while(query.next()){
            Writer.writeStartElement("type"+QString::number(i));
            Writer.writeStartElement("idType");
            Writer.writeCharacters(query.value(0).toString());
            Writer.writeEndElement();
            Writer.writeStartElement("product_type");
            Writer.writeCharacters(query.value(1).toString());
            Writer.writeEndElement();

            Writer.writeEndElement();
            i++;

        }
        Writer.writeEndElement();
        Writer.writeEndElement();




        QGraphicsOpacityEffect* effect=new QGraphicsOpacityEffect();
        ui->label_2->setGraphicsEffect(effect);
        ui->label_2->setStyleSheet("border: 3px solid gray;border-radius:20px;background-color:#ffffff;color:gray");
        ui->label_2->setAlignment(Qt::AlignCenter);
        ui->label_2->setText("Сохранение успешно");
        QPropertyAnimation* a=new QPropertyAnimation(effect,"opacity");
        a->setDuration(1000);
        a->setStartValue(0);
        a->setEndValue(1);
        a->setEasingCurve(QEasingCurve::InBack);
        a->start(QPropertyAnimation::DeleteWhenStopped);
        ui->label_2->show();
        timer = new QTimer(this);
        connect(timer,&QTimer::timeout,this,&FileSaving::fadeOut);
        timer->start(2000);


        Writer.writeEndDocument();
        file.close();
        ui->lineEdit->setText("");
        }

    } catch (ExCorrection& ex) {
        QMessageBox::warning(this,"Внимание!", ex.what(), QMessageBox::Ok);
        ui->lineEdit->setText("");
    }

}

