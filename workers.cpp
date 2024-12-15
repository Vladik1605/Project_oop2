#include "workers.h"
#include "ui_workers.h"
#include "classes.h"
#include <QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "Exceptions.h"
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
 * @brief Конструктор класса Workers.
 *
 * Инициализирует интерфейс, подключается к базе данных и заполняет таблицу данными о работниках.
 *
 * @param parent Указатель на родительский виджет.
 * @param shop_id Идентификатор магазина, для которого запрашиваются данные.
 */
Workers::Workers(QWidget *parent, QString shop_id)
    : QDialog(parent)
    , ui(new Ui::Workers)
{
    ui->setupUi(this);

    // Инициализация кнопок и параметров
    ui->SaveButton->setEnabled(false);
    this->shop_id = shop_id;

    // Инициализация таблицы для отображения данных работников
    row = 0;
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(8);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "FIO" << "Birthday" << "Phone" << "Passport" << "Work exp." << "Salary" << "Sector" << "Overtime");
    tableWidget->horizontalHeader()->setStretchLastSection(true);

    // Размещение таблицы в layout
    QVBoxLayout *dialogLayout = new QVBoxLayout(this);
    dialogLayout->addWidget(tableWidget);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    buttonLayout->addItem(spacer);

    buttonLayout->addWidget(ui->DeleteButton);
    buttonLayout->addWidget(ui->RedactButton);
    buttonLayout->addWidget(ui->SaveButton);
    buttonLayout->addWidget(ui->AddWorkerButton);

    dialogLayout->addLayout(buttonLayout);
    setLayout(dialogLayout);

    // Подключение к базе данных MySQL
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("0504Vladik");
    db.open();
    this->setAttribute(Qt::WA_DeleteOnClose);

    // Запрос данных из базы
    QSqlQuery query(db);
    query.exec("SELECT sector, salary, overtime_hour, FIO, Birthday, phone_number, pasport, work_age, idAssistant FROM assistant WHERE work_place='"+shop_id+"'");

    worker = new Asistant();

    // Обработка результатов запроса и заполнение таблицы
    while(query.next()){
        worker->setSector(query.value(0).toString());
        worker->setSalary(query.value(1).toInt());
        worker->setOvertime(query.value(2).toInt());
        worker->setFIO(query.value(3).toString());
        worker->setBirth(query.value(4).toString());
        worker->setPhone(query.value(5).toString());
        worker->setPassport(query.value(6).toString());
        worker->setWork_age(query.value(7).toInt());

        // Вставка новой строки в таблицу с данными
        tableWidget->insertRow(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(worker->getFIO()));
        tableWidget->setItem(row, 1, new QTableWidgetItem(worker->getBirth()));
        tableWidget->setItem(row, 2, new QTableWidgetItem(worker->getPhone()));
        tableWidget->setItem(row, 3, new QTableWidgetItem(worker->getPassport()));
        tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(worker->getWork_age())));
        tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(worker->getSalary())));
        tableWidget->setItem(row, 6, new QTableWidgetItem(worker->getSector()));
        tableWidget->setItem(row, 7, new QTableWidgetItem(QString::number(worker->getOvertime())));

        // Сделать ячейки не редактируемыми
        for (int col = 0; col < tableWidget->columnCount(); ++col) {
            QTableWidgetItem* item = tableWidget->item(row, col);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }



        ValidationDelegate* delegate = new ValidationDelegate(this);
        tableWidget->setItemDelegate(delegate);


        // Добавляем в список, что строка сохранена
        isRowSaved << true;

        // Сохраняем ID работников
        all_id.append(query.value(8).toString());
        row++;
    }
}

/**
 * @brief Деструктор класса Workers.
 *
 * Освобождает ресурсы и удаляет объект интерфейса.
 */
Workers::~Workers()
{
    qDebug() << 1;
    delete ui;
}

/**
 * @brief Обработчик нажатия на кнопку для добавления нового работника.
 *
 * Создаёт новые поля ввода для ввода данных работника и подключает их к соответствующим слотам для валидации.
 */
void Workers::on_AddWorkerButton_clicked()
{
    // Инициализация полей ввода
    ld_Pasport = new CustomLineEdit(this);
    ld_WA = new CustomLineEdit(this);
    ld_Salary = new CustomLineEdit(this);
    ld_Sector = new CustomLineEdit(this);
    ld_Birth = new CustomLineEdit(this);
    ld_Phone = new CustomLineEdit(this);
    ld_FIO = new CustomLineEdit(this);
    ld_Over = new CustomLineEdit(this);

    // Установка масок ввода для полей
    ld_Birth->setInputMask("99.99.9999");
    ld_Phone->setInputMask("+9(999) 999-99-99");
    ld_Pasport->setInputMask("9999 999999");

    // Вставка новой строки в таблицу
    int row = tableWidget->rowCount();
    tableWidget->insertRow(row);

    // Установка полей ввода в ячейки таблицы
    tableWidget->setCellWidget(row, 0, ld_FIO);
    tableWidget->setCellWidget(row, 1, ld_Birth);
    tableWidget->setCellWidget(row, 2, ld_Phone);
    tableWidget->setCellWidget(row, 3, ld_Pasport);
    tableWidget->setCellWidget(row, 4, ld_WA);
    tableWidget->setCellWidget(row, 5, ld_Salary);
    tableWidget->setCellWidget(row, 6, ld_Sector);
    tableWidget->setCellWidget(row, 7, ld_Over);
    isRowSaved << false;

    // Создание нового объекта работника
    worker = new Asistant();

    // Подключение слотов для валидации и сохранения данных
    connect(ld_FIO, &QLineEdit::editingFinished, this, [=]() {
        ld_FIO->setStyleSheet("");
        try {
            QString str = ld_FIO->text();
            ValidatorName(&str);
            worker->setFIO(ld_FIO->text());
        } catch (ExCorrection& ex) {
            QMessageBox::warning(this, "Внимание!", ex.what(), QMessageBox::Ok);
            ld_FIO->setText("");
        }
    });

    connect(ld_Birth, &QLineEdit::editingFinished, this, [=]() {
        ld_Birth->setStyleSheet("");
        worker->setBirth(ld_Birth->text());
    });

    connect(ld_Phone, &QLineEdit::editingFinished, this, [=]() {
        ld_Phone->setStyleSheet("");
        worker->setPhone(ld_Phone->text());
    });

    connect(ld_Pasport, &QLineEdit::editingFinished, this, [=]() {
        ld_Phone->setStyleSheet("");
        worker->setPassport(ld_Pasport->text());
    });

    connect(ld_WA, &QLineEdit::editingFinished, this, [=]() {
        ld_WA->setStyleSheet("");
        try {
            QString str = ld_WA->text();
            ValidatorWorkAge(&str);
            worker->setWork_age(ld_WA->text().toInt());
        } catch (ExCorrection& ex) {
            QMessageBox::warning(this, "Внимание!", ex.what(), QMessageBox::Ok);
            ld_WA->setText("");
        }
    });

    connect(ld_Salary, &QLineEdit::editingFinished, this, [=]() {
        ld_Salary->setStyleSheet("");
        try {
            QString str = ld_Salary->text();
            ValidatorSalary(&str);
            worker->setSalary(ld_Salary->text().toInt());
        } catch (ExCorrection& ex) {
            QMessageBox::warning(this, "Внимание!", ex.what(), QMessageBox::Ok);
            ld_Salary->setText("");
        }
    });

    connect(ld_Sector, &QLineEdit::editingFinished, this, [=]() {
        ld_Sector->setStyleSheet("");
        worker->setSector(ld_Sector->text());
    });

    connect(ld_Over, &QLineEdit::editingFinished, this, [=]() {
        ld_Over->setStyleSheet("");
        try {
            QString str = ld_Over->text();
            ValidatorPrice_Stock_Window(&str);
            worker->setOvertime(ld_Over->text().toInt());
        } catch (ExCorrection& ex) {
            QMessageBox::warning(this, "Внимание!", ex.what(), QMessageBox::Ok);
            ld_Over->setText("");
        }
    });

    // Отключение кнопки добавления нового работника и активация кнопки сохранения
    ui->AddWorkerButton->setEnabled(false);
    ui->RedactButton->setEnabled(false);
    ui->SaveButton->setEnabled(true);
}



/**
 * @brief Обработчик нажатия кнопки "Добавить / Изменить" в интерфейсе.
 *
 * Выполняет проверку введённых данных и обновление информации о работниках.
 * Включает в себя валидацию полей, вставку данных в базу данных и обновление отображения в таблице.
 */
void Workers::on_SaveButton_clicked()
{
    row = tableWidget->rowCount();  ///< Получение текущего количества строк в таблице.

    try {
        // Проверка активных кнопок для определения режима (добавление/редактирование)
        if (!ui->AddWorkerButton->isEnabled() && !ui->RedactButton->isEnabled() && ui->SaveButton->isEnabled()) {

            QVector<QLineEdit*> errors;  ///< Массив для сбора ошибок ввода.

            // Проверка полей на валидность
            if (worker->getFIO().isEmpty()) {
                errors.append(ld_FIO);
            }
            if (QString::compare(ld_Birth->text(), "..") == 0) {
                errors.append(ld_Birth);
            }
            if (QString::compare(ld_Phone->text(), "+() --") == 0) {
                errors.append(ld_Phone);
            }
            if (QString::compare(ld_Pasport->text(), " ") == 0) {
                errors.append(ld_Pasport);
            }
            if (ld_Salary->text().isEmpty()) {
                errors.append(ld_Salary);
            }
            if (ld_Phone->text().length() < 16) {
                errors.append(ld_Phone);
            }
            if (ld_Pasport->text().length() < 10) {
                errors.append(ld_Pasport);
            }
            if (ld_Birth->text().length() < 10) {
                errors.append(ld_Birth);
            }

            // Если есть ошибки, выбрасываем исключение
            if (errors.length() != 0) {
                throw MyEx_Prod{errors, this};
            }

            int id = -1;
            QSqlQuery query(db);

            // Проверка существующего работника в базе
            query.exec("SELECT idAssistant FROM assistant WHERE work_place='" + shop_id + "' AND pasport='" + worker->getPassport() + "'");
            while (query.next()) {
                id = query.value(0).toInt();
            }

            // Если работник не найден, добавляем его в базу данных
            if (id == -1) {
                query.exec("INSERT INTO assistant (sector, salary, overtime_hour, FIO, Birthday, phone_number, pasport, work_age, work_place) VALUES ('" + worker->getSector() + "', '" + QString::number(worker->getSalary()) + "', '" + QString::number(worker->getOvertime()) + "', '" + worker->getFIO() + "', '" + worker->getBirth() + "', '" + worker->getPhone() + "', '" + worker->getPassport() + "', '" + QString::number(worker->getWork_age()) + "', '" + shop_id + "')");
                query.exec("SELECT LAST_INSERT_ID()");
                while (query.next()) {
                    all_id.append(query.value(0).toString());
                }
            }
            else {
                throw ExCorrection{"Такой работник уже добавлен в этот магазин"};
            }

            // Обновление отображения данных в таблице
            tableWidget->setItem(row - 1, 0, new QTableWidgetItem(ld_FIO->text()));
            tableWidget->removeCellWidget(row - 1, 0);
            disconnect(ld_FIO, &QLineEdit::editingFinished, this, nullptr);
            ld_FIO->deleteLater();

            tableWidget->setItem(row - 1, 1, new QTableWidgetItem(ld_Birth->text()));
            tableWidget->removeCellWidget(row - 1, 1);
            disconnect(ld_Birth, &QLineEdit::editingFinished, this, nullptr);
            ld_Birth->deleteLater();

            tableWidget->setItem(row - 1, 2, new QTableWidgetItem(ld_Phone->text()));
            tableWidget->removeCellWidget(row - 1, 2);
            disconnect(ld_Phone, &QLineEdit::editingFinished, this, nullptr);
            ld_Phone->deleteLater();

            tableWidget->setItem(row - 1, 3, new QTableWidgetItem(ld_Pasport->text()));
            tableWidget->removeCellWidget(row - 1, 3);
            disconnect(ld_Pasport, &QLineEdit::editingFinished, this, nullptr);
            ld_Pasport->deleteLater();

            tableWidget->setItem(row - 1, 4, new QTableWidgetItem(ld_WA->text()));
            tableWidget->removeCellWidget(row - 1, 4);
            disconnect(ld_WA, &QLineEdit::editingFinished, this, nullptr);
            ld_WA->deleteLater();

            tableWidget->setItem(row - 1, 5, new QTableWidgetItem(ld_Salary->text()));
            tableWidget->removeCellWidget(row - 1, 5);
            disconnect(ld_Salary, &QLineEdit::editingFinished, this, nullptr);
            ld_Salary->deleteLater();

            tableWidget->setItem(row - 1, 6, new QTableWidgetItem(ld_Sector->text()));
            tableWidget->removeCellWidget(row - 1, 6);
            disconnect(ld_Sector, &QLineEdit::editingFinished, this, nullptr);
            ld_Sector->deleteLater();

            tableWidget->setItem(row - 1, 7, new QTableWidgetItem(ld_Over->text()));
            tableWidget->removeCellWidget(row - 1, 7);
            disconnect(ld_Over, &QLineEdit::editingFinished, this, nullptr);
            ld_Over->deleteLater();

            // Запрещаем редактирование ячеек
            for (int col = 0; col < tableWidget->columnCount(); ++col) {
                QTableWidgetItem* item = tableWidget->item(row - 1, col);
                if (item) {
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                }
            }

            // Отключение кнопки и активация других
            ui->SaveButton->setEnabled(false);
            ui->AddWorkerButton->setEnabled(true);
            ui->RedactButton->setEnabled(true);

            // Обновление состояния строки
            isRowSaved[row - 1] = true;
        }

        // Обработка редактирования уже добавленных работников
        if (ui->RedactButton->isEnabled() && ui->SaveButton->isEnabled() && !ui->AddWorkerButton->isEnabled()) {
            QVector<QTableWidgetItem*> errors;
            int rowCount = tableWidget->rowCount();

            // Обработка каждой строки таблицы
            for (int row = 0; row < rowCount; row++) {
                worker = new Asistant();

                for (int col = 0; col < tableWidget->columnCount(); ++col) {
                    QTableWidgetItem* item = tableWidget->item(row, col);
                    if (item) {
                        QString text = item->text();

                        // Проверяем, есть ли ошибка для текущей ячейки (установлен флаг ошибки в делегате)
                        QVariant isInvalid = item->data(Qt::UserRole + 1);  // Флаг ошибки, установленных делегатом
                        if (isInvalid.isValid() && isInvalid.toBool()) {
                            //item->setText("");
                            errors.append(item); // Добавляем ошибочную ячейку
                        }

                        // Устанавливаем данные в объект worker
                        switch (col) {
                        case 0:  // FIO
                            worker->setFIO(text);
                            break;
                        case 1:  // Дата рождения
                            worker->setBirth(text);
                            break;
                        case 2:  // Телефон
                            worker->setPhone(text);
                            break;
                        case 3:  // Паспорт
                            worker->setPassport(text);
                            break;
                        case 4:  // Стаж работы
                            worker->setWork_age(text.toInt());
                            break;
                        case 5:  // Зарплата
                            worker->setSalary(text.toInt());
                            break;
                        case 6:  // Сектор
                            worker->setSector(text);
                            break;
                        case 7:  // Переработки
                            worker->setOvertime(text.toInt());
                            break;
                        }
                    }
                }

                // Если есть ошибки, выбрасываем исключение
                if (!errors.isEmpty()) {
                    throw MyEx_Table{errors, this};
                }

                // Проверка уникальности работника
                int id = -1;
                QSqlQuery query(db);
                query.exec("SELECT idAssistant FROM assistant WHERE work_place='" + shop_id + "' AND pasport='" + worker->getPassport() + "' AND idAssistant<>'" + all_id[row] + "'");
                while (query.next()) {
                    id = query.value(0).toInt();
                }

                // Если работник уникален, обновляем информацию в базе
                if (id == -1) {
                    query.exec("UPDATE assistant SET sector='" + worker->getSector() + "', salary='" + QString::number(worker->getSalary()) + "', overtime_hour='" + QString::number(worker->getOvertime()) + "', FIO='" + worker->getFIO() + "', Birthday='" + worker->getBirth() + "', phone_number='" + worker->getPhone() + "', pasport='" + worker->getPassport() + "', work_age='" + QString::number(worker->getWork_age()) + "' WHERE idAssistant='" + all_id[row] + "'");
                } else {
                    throw ExCorrection{"Такой работник уже добавлен в этот магазин"};
                }
                for (int col = 0; col < tableWidget->columnCount(); ++col) {
                    QTableWidgetItem* item = tableWidget->item(row, col);
                    if (item) {
                        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                    }
                }
            }

            // Включаем кнопки и изменяем состояние
            ui->AddWorkerButton->setEnabled(true);
            ui->SaveButton->setEnabled(false);
        }
    }
    // Обработка исключений
    catch (MyEx_Table& ex) {
        ex.ShowError();
    }
    catch (ExCorrection& ex) {
        QMessageBox::warning(this, "Внимание!", ex.what(), QMessageBox::Ok);
    }
}


/**
 * @brief Обработчик события нажатия кнопки "Редактировать" (pushButton_3).
 *
 * Разблокирует возможность редактирования всех ячеек в таблице.
 */
void Workers::on_RedactButton_clicked()
{
    ui->AddWorkerButton->setEnabled(false);
    ui->SaveButton->setEnabled(true);

    // Разрешение редактирования всех ячеек таблицы
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        for (int column = 0; column < tableWidget->columnCount(); ++column) {
            QTableWidgetItem* item = tableWidget->item(row, column);
            if (item) {
                item->setFlags(item->flags() | Qt::ItemIsEditable);
            }
        }
    }
}

/**
 * @brief Обработчик события нажатия кнопки "Удалить" (pushButton_4).
 *
 * Удаляет выбранные строки из таблицы, а также из базы данных, если данные сохранены.
 */
void Workers::on_DeleteButton_clicked()
{
    QItemSelectionModel* selectionModel = tableWidget->selectionModel();

    if (selectionModel) {
        QModelIndexList selectedRows = selectionModel->selectedRows();

        // Перебор выбранных строк для удаления
        for (int i = selectedRows.size() - 1; i >= 0; --i) {
            int row = selectedRows.at(i).row();

            // Если строка не сохранена, просто удаляем из таблицы
            if (!isRowSaved[row]) {
                tableWidget->removeRow(row);
                isRowSaved.removeAt(row);
                continue;
            }

            // Подтверждение удаления сохраненной строки
            QMessageBox::StandardButton reply = QMessageBox::question(
                this, "Подтверждение удаления",
                "Вы уверены, что хотите удалить выбранные элементы?",
                QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes) {
                // Удаление строки из таблицы
                tableWidget->removeRow(row);
                isRowSaved.removeAt(row);

                // Удаление строки из базы данных
                QSqlQuery query(db);
                query.exec("DELETE FROM assistant WHERE idAssistant='" + all_id[row] + "'");
                all_id.removeAt(row);
            }
        }

        // Активация кнопок после изменений
        ui->RedactButton->setEnabled(true);
        ui->AddWorkerButton->setEnabled(true);
        ui->SaveButton->setEnabled(false);
    }
}


