#ifndef DELEGATE_H
#define DELEGATE_H
#include <QFile>
#include <QException>
#include <QLabel>
#include <QLineEdit>
#include <QPropertyAnimation>
#include <QGraphicsEffect>
#include <QSequentialAnimationGroup>
#include <QMessageBox>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QCompleter>
#include <QSqlError>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QWidget>
#include <QVector>
#include <QDebug>
#include <QBrush>
#include <QColor>
/**
 * @class ValidationDelegate
 * @brief Класс для делегата, выполняющего валидацию и создание редакторов ячеек таблицы
 */
class ValidationDelegate : public QStyledItemDelegate {
public:
    /**
     * @brief Конструктор делегата
     * @param parent Родительский объект
     */
    explicit ValidationDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}

    /**
     * @brief Создание редактора для ввода данных в ячейку таблицы
     * @param parent Родительский виджет
     * @param option Опции отображения элемента
     * @param index Индекс элемента в модели
     * @return QWidget* Редактор для ввода данных
     */
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex& index) const override {
        QLineEdit* editor = new QLineEdit(parent);

        // Устанавливаем маску ввода в зависимости от столбца
        if (index.column() == 1) { // Дата рождения
            editor->setInputMask("00.00.0000"); // Формат: ДД.ММ.ГГГГ
        } else if (index.column() == 2) { // Номер телефона
            editor->setInputMask("+7 (000) 000-00-00");
        } else if (index.column() == 3) { // Паспортные данные
            editor->setInputMask("0000 000000"); // Формат паспортных данных
        }

        return editor;
    }

    /**
     * @brief Рисование элемента в таблице с учетом валидации
     * @param painter Объект рисования
     * @param option Опции отображения элемента
     * @param index Индекс элемента в модели
     */
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override {
        QStyledItemDelegate::paint(painter, option, index);  // Рисуем стандартное содержимое

        QVariant isInvalid = index.data(Qt::UserRole + 1); // Получаем флаг ошибки
        if (isInvalid.isValid() && isInvalid.toBool()) { // Если есть ошибка
            painter->save();
            painter->setPen(Qt::red);  // Устанавливаем красный цвет для текста
            QRect rect = option.rect.adjusted(option.rect.width() - 15, 0, 0, 0);  // Позиция звезды в правом углу
            painter->drawText(rect, Qt::AlignRight | Qt::AlignVCenter, "*");  // Рисуем красную звезду
            painter->restore();
        }
    }

    /**
     * @brief Установка данных в модель и валидация значений
     * @param editor Редактор для ввода данных
     * @param model Модель данных
     * @param index Индекс элемента в модели
     */
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override {
        QLineEdit* lineEdit = qobject_cast<QLineEdit*>(editor);
        if (lineEdit) {
            QString text = lineEdit->text(); // Получаем текст из редактора
            QString al = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzАаБбВвГгДдЕеЁёЖжЗзИиЙйКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщъыьЭэЮюЯя "; // Разрешенные символы
            QString al1 = "0987654321"; // Цифры

            bool isInvalid = false; // Флаг ошибки

            // Валидация в зависимости от столбца
            switch (index.column()) {
            case 0:  // ФИО
                for (int i = 0; i < text.length(); i++) {
                    if (al.indexOf(text.at(i)) == -1) {
                        isInvalid = true;  // Недопустимый символ
                        break;  // Прерываем цикл при нахождении недопустимого символа
                    }
                }
                if (text.isEmpty()) isInvalid = true; // Если поле пустое, ошибка
                break;
            case 1:  // Дата рождения
                isInvalid = !QRegularExpression("\\d{2}.\\d{2}.\\d{4}").match(text).hasMatch(); // Проверка на формат даты
                break;
            case 2:  // Телефон
                isInvalid = !QRegularExpression("\\+7 \\(\\d{3}\\) \\d{3}-\\d{2}-\\d{2}").match(text).hasMatch(); // Проверка на формат телефона
                break;
            case 3:  // Паспорт
                isInvalid = !QRegularExpression("\\d{4} \\d{6}").match(text).hasMatch(); // Проверка на формат паспортных данных
                break;
            case 4:  // Стаж работы
                for (int i = 0; i < text.length(); i++) {
                    if (al1.indexOf(text.at(i)) == -1) {
                        isInvalid = text.toInt() <= 0; // Если значение отрицательное или ноль
                    }
                }
                break;
            case 5:  // Зарплата
                for (int i = 0; i < text.length(); i++) {
                    if (al1.indexOf(text.at(i)) == -1) {
                        isInvalid = text.toInt() <= 0; // Если значение отрицательное или ноль
                    }
                }
                if (text.isEmpty()) isInvalid = true; // Если поле пустое, ошибка
                break;
            case 7:  // Переработка
                for (int i = 0; i < text.length(); i++) {
                    if (al1.indexOf(text.at(i)) == -1) {
                        isInvalid = text.toInt() <= 0; // Если значение отрицательное или ноль
                    }
                }
                break;
            default:
                break;
            }

            // Устанавливаем данные и флаг ошибки в модель
            model->setData(index, text);  // Устанавливаем текст
            model->setData(index, isInvalid, Qt::UserRole + 1);  // Устанавливаем флаг ошибки
        }
    }
};


/**
 * @brief Делегат для валидации данных в таблице продуктов.
 *
 * Этот делегат используется для редактирования и валидации данных о продуктах в таблице.
 * Он поддерживает автозаполнение для полей "Название продукта" и "Тип продукта",
 * а также проверку введенных данных в соответствии с типами данных и их форматами.
 */
class ValidationProductDelegate : public QStyledItemDelegate {
public:

    /**
     * @brief Конструктор делегата.
     *
     * Инициализирует делегат с подключением к базе данных и таблицей.
     * @param db Ссылка на подключение к базе данных.
     * @param tableWidget Указатель на таблицу, где применяется делегат.
     * @param parent Родительский объект для делегата.
     */
    explicit ValidationProductDelegate(const QSqlDatabase& db, QTableWidget* tableWidget = nullptr, QObject* parent = nullptr)
        : QStyledItemDelegate(parent), m_db(db), tableWidget(tableWidget) {
        if (!m_db.isValid() || !m_db.isOpen()) {
            qDebug() << "Database connection is invalid or not open!";
        }
    }

    /**
     * @brief Создание редактора для ячейки.
     *
     * Создает редактор (QLineEdit) для редактирования ячейки в зависимости от ее столбца.
     * Для столбца с названием продукта используется автозаполнение с предложениями из базы данных.
     * @param parent Родительский виджет для редактора.
     * @param option Опции отображения ячейки.
     * @param index Индекс ячейки.
     * @return QWidget* Указатель на созданный редактор.
     */
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex& index) const override {
        QLineEdit* editor = new QLineEdit(parent);

        // Автозаполнение для "Название продукта"
        if (index.column() == 0) {
            QStringList productEntries;
            QSqlQuery query(m_db);

            // Запрос к базе данных для получения списка продуктов
            if (query.exec("SELECT name, size FROM product")) {
                while (query.next()) {
                    QString name = query.value("name").toString();
                    QString size = query.value("size").toString();
                    productEntries << name + "\t" + size; // Формируем запись "название   размер"
                }
            } else {
                qWarning() << "Failed to execute query for product names:" << query.lastError().text();
            }

            // Настраиваем QCompleter для автозаполнения
            QCompleter* completer = new QCompleter(productEntries, editor);
            completer->setCaseSensitivity(Qt::CaseInsensitive);
            completer->setFilterMode(Qt::MatchStartsWith);
            editor->setCompleter(completer);

            // Обработчик изменения ячейки
            connect(tableWidget, &QTableWidget::itemChanged, this, [this](QTableWidgetItem* item) {
                if (item->column() == 0) { // Если редактируется ячейка с названием (столбец 0)
                    QString text = item->text();
                    QStringList parts = text.split('\t'); // Разделяем строку по табуляции

                    // Если строка разделена корректно (два элемента: название и размер)
                    if (parts.size() == 2) {
                        QString newName = parts[0];
                        QString size = parts[1];

                        // Получаем индекс строки
                        int row = item->row();

                        // Получаем ячейку для размера (столбец 2)
                        QTableWidgetItem* sizeItem = tableWidget->item(row, 2); // Столбец 2 - размер
                        if (!sizeItem) {
                            sizeItem = new QTableWidgetItem();
                            tableWidget->setItem(row, 2, sizeItem);
                        }

                        // Устанавливаем новый размер, если он был изменен
                        sizeItem->setText(size);

                        // Устанавливаем только название в ячейку с названием
                        item->setText(newName);
                    }
                }
            });

            // Обработчик выделения записи из автозаполнителя
            connect(completer, QOverload<const QString &>::of(&QCompleter::highlighted), this, [this, editor, index](const QString &highlightedEntry) {
                // Разделяем строку, полученную из выпадающего списка, на название и размер
                QStringList parts = highlightedEntry.split('\t');
                if (parts.size() == 2) {
                    QString highlightedName = parts[0];
                    QString highlightedSize = parts[1];

                    // Получаем данные из базы данных
                    QSqlQuery query(m_db);
                    query.prepare("SELECT type FROM product WHERE name = :name AND size = :size");
                    query.bindValue(":name", highlightedName);
                    query.bindValue(":size", highlightedSize);

                    if (query.exec() && query.next()) {
                        QString type_id = query.value("type").toString();

                        QSqlQuery typeQuery(m_db);
                        typeQuery.prepare("SELECT product_type FROM type WHERE idType = :idType");
                        typeQuery.bindValue(":idType", type_id);

                        if (typeQuery.exec() && typeQuery.next()) {
                            QString productType = typeQuery.value("product_type").toString();

                            // Обновляем ячейки с данными
                            int row = index.row();
                            QTableWidgetItem* nameItem = tableWidget->item(row, 0);
                            QTableWidgetItem* typeItem = tableWidget->item(row, 1);
                            QTableWidgetItem* sizeItem = tableWidget->item(row, 2);

                            if (!nameItem) {
                                nameItem = new QTableWidgetItem();
                                tableWidget->setItem(row, 0, nameItem);
                            }
                            if (!typeItem) {
                                typeItem = new QTableWidgetItem();
                                tableWidget->setItem(row, 1, typeItem);
                            }
                            if (!sizeItem) {
                                sizeItem = new QTableWidgetItem();
                                tableWidget->setItem(row, 2, sizeItem);
                            }

                            nameItem->setText(highlightedName);   // Название
                            typeItem->setText(productType);        // Тип
                            sizeItem->setText(highlightedSize);    // Размер
                        }
                    }
                }
            });

            // Обработчик активации записи из автозаполнителя
            connect(completer, QOverload<const QString&>::of(&QCompleter::activated), this, [this, editor, index](const QString& selectedEntry) {
                QStringList parts = selectedEntry.split('\t'); // Разделяем строку на название и размер
                if (parts.size() == 2) {
                    QString selectedName = parts[0];
                    QString selectedSize = parts[1];

                    // Устанавливаем только название в поле редактора
                    editor->setText(selectedName);  // Название продукта

                    // Получаем данные из базы данных для типа продукта
                    QSqlQuery query(m_db);
                    query.prepare("SELECT type FROM product WHERE name = :name AND size = :size");
                    query.bindValue(":name", selectedName);
                    query.bindValue(":size", selectedSize);

                    if (query.exec() && query.next()) {
                        QString type_id = query.value("type").toString();

                        QSqlQuery typeQuery(m_db);
                        typeQuery.prepare("SELECT product_type FROM type WHERE idType = :idType");
                        typeQuery.bindValue(":idType", type_id);

                        if (typeQuery.exec() && typeQuery.next()) {
                            QString productType = typeQuery.value("product_type").toString();

                            // Устанавливаем тип и размер в соответствующие ячейки таблицы
                            int row = index.row();
                            QTableWidgetItem* nameItem = tableWidget->item(row, 0);
                            QTableWidgetItem* typeItem = tableWidget->item(row, 1);
                            QTableWidgetItem* sizeItem = tableWidget->item(row, 2);

                            if (!nameItem) {
                                nameItem = new QTableWidgetItem();
                                tableWidget->setItem(row, 0, nameItem);
                            }
                            if (!typeItem) {
                                typeItem = new QTableWidgetItem();
                                tableWidget->setItem(row, 1, typeItem);
                            }
                            if (!sizeItem) {
                                sizeItem = new QTableWidgetItem();
                                tableWidget->setItem(row, 2, sizeItem);
                            }

                            nameItem->setText(selectedName);   // Название
                            typeItem->setText(productType);    // Тип
                            sizeItem->setText(selectedSize);   // Размер
                        }
                    }
                }
            });

        } else if (index.column() == 1) { // Тип продукта
            QStringList typeEntries;
            QSqlQuery query(m_db);

            // Запрос к базе данных для получения списка типов продуктов
            if (query.exec("SELECT product_type FROM type")) {
                while (query.next()) {
                    typeEntries << query.value(0).toString();
                }
            } else {
                qWarning() << "Failed to execute query for product types:" << query.lastError().text();
            }

            // Настроим автозаполнение для типа продукта
            QCompleter* completer = new QCompleter(typeEntries, editor);
            completer->setCaseSensitivity(Qt::CaseInsensitive);
            completer->setFilterMode(Qt::MatchStartsWith);
            editor->setCompleter(completer);
        }

        return editor;
    }


    /**
     * @brief Рисование ячейки с данными.
     *
     * Этот метод используется для рисования ячеек в таблице, включая отображение красной звезды
     * в случае ошибки валидации данных.
     * @param painter Рисующий объект.
     * @param option Опции отображения ячейки.
     * @param index Индекс ячейки.
     */
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override {
        QStyledItemDelegate::paint(painter, option, index);  // Рисуем стандартное содержимое

        QVariant isInvalid = index.data(Qt::UserRole + 1);
        if (isInvalid.isValid() && isInvalid.toBool()) {
            painter->save();
            painter->setPen(Qt::red);  // Устанавливаем красный цвет для текста
            QRect rect = option.rect.adjusted(option.rect.width() - 15, 0, 0, 0);  // Расположение звезды в правом углу
            painter->drawText(rect, Qt::AlignRight | Qt::AlignVCenter, "*");  // Рисуем красную звезду
            painter->restore();
        }
    }


    /**
     * @brief Установка данных в модель из редактора.
     *
     * Этот метод используется для обновления данных в модели после редактирования ячейки.
     * Он также проверяет данные на валидность и отображает ошибку в случае необходимости.
     * @param editor Редактор данных.
     * @param model Модель данных.
     * @param index Индекс ячейки.
     */
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override {
        QLineEdit* lineEdit = qobject_cast<QLineEdit*>(editor);
        if (lineEdit) {
            QString text = lineEdit->text();
            QString al = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzАаБбВвГгДдЕеЁёЖжЗзИиЙйКкЛлМмНнОоПпСсТтУуФфХхЦцЧчШшЩщъыьЭэЮюЯя ";
            QString al1="0987654321";

            // Проверка на пустоту и валидация для других столбцов
            bool isInvalid = false;

            switch (index.column()) {
            case 0:  // Название

                if(text.isEmpty()) isInvalid=true;
                break;
            case 1:  // Тип
                if(text.isEmpty()) isInvalid=true;
                break;
            case 2:  // Размер
                if(text.isEmpty()) isInvalid=true;
                break;
            case 3:  // Цена
                for(int i=0;i<text.length();i++){
                    if(al1.indexOf(text.at(i))==-1){
                        isInvalid = text.toInt() <= 0;
                    }
                }
                if(text.isEmpty()) isInvalid=true;
                break;
            case 4:  // Стаж работы
                for(int i=0;i<text.length();i++){
                    if(al1.indexOf(text.at(i))==-1){
                        isInvalid = text.toInt() <= 0;
                    }
                }
                if(text.isEmpty()) isInvalid=true;
                break;
            case 5:  // Зарплата
                for(int i=0;i<text.length();i++){
                    if(al1.indexOf(text.at(i))==-1){
                        isInvalid = text.toInt() <= 0;
                    }
                }
                if(text.isEmpty()) isInvalid=true;
                break;

            default:
                break;
            }

            // Устанавливаем данные и флаг ошибки
            model->setData(index, text);  // Устанавливаем текст
            model->setData(index, isInvalid, Qt::UserRole + 1);  // Устанавливаем флаг ошибки
        }
    }
private:
    QSqlDatabase m_db;  ///< Ссылка на базу данных.
    QTableWidget* tableWidget;  ///< Указатель на таблицу.
};
#endif // DELEGATE_H
