#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
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
 * @brief Исключение для отображения ошибок на QLabel с анимацией.
 *
 * Класс используется для отображения сообщений об ошибках, привязанных к QLabel.
 * Включает анимацию дрожания метки.
 */
class MyEx : public QException {
public:

    /**
     * @brief Конструктор принимает карту ошибок.
     * @param errors_h Карта, где ключ - указатель на QLabel, а значение - текст ошибки.
     */
    MyEx(QMap<QLabel*, QString> errors_h) {
        errors = errors_h;
    }

    /**
     * @brief Отображение ошибок и анимация дрожания меток.
     */
    void ShowError() {
        for (auto [key, value] : errors.toStdMap()) {
            // Устанавливаем текст ошибки и красный цвет метке.
            key->setText(value);
            key->setStyleSheet("color: red;");
            key->update();

            // Создаем анимационную группу для дрожания метки.
            auto group = new QSequentialAnimationGroup(key);

            // Добавляем анимации дрожания.
            for (int i = 0; i < 5; ++i) {
                auto animation = new QPropertyAnimation(key, "pos");
                animation->setDuration(100);
                animation->setStartValue(key->pos());
                animation->setEndValue(QPoint(key->pos().x() + (i % 2 == 0 ? 5 : -5), key->pos().y()));
                group->addAnimation(animation);
            }

            // Возвращаем метку в исходное положение.
            auto finalAnimation = new QPropertyAnimation(key, "pos");
            finalAnimation->setDuration(100);
            finalAnimation->setStartValue(key->pos());
            finalAnimation->setEndValue(key->pos());
            group->addAnimation(finalAnimation);

            // Удаляем анимацию после завершения.
            QSequentialAnimationGroup::connect(group, &QSequentialAnimationGroup::finished, group, &QObject::deleteLater);

            // Запуск анимации.
            group->start();
        }
    }

private:
    QMap<QLabel*, QString> errors; ///< Карта ошибок, где ключ - QLabel, а значение - текст ошибки.
};


/**
 * @brief Исключение для коррекции данных с сообщением.
 *
 * Используется для генерации исключения с текстом сообщения.
 */
class ExCorrection : public QException {
public:

    /**
     * @brief Конструктор принимает сообщение об ошибке.
     * @param ms Указатель на строку сообщения об ошибке.
     */
    ExCorrection(char* ms) {
        masage = ms;
    }

    /**
     * @brief Получить текст сообщения об ошибке.
     * @return Указатель на текст сообщения.
     */
    const char* what() const noexcept override {
        return masage;
    }

private:
    char* masage; ///< Сообщение об ошибке.
};


/**
 * @brief Валидатор для проверки корректности имени.
 *
 * Проверяет, чтобы имя содержало только допустимые символы.
 * @param name Указатель на строку имени для проверки.
 * @throws ExCorrection Если имя содержит недопустимые символы.
 */
inline void ValidatorName(QString* name) {
    QString al = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzАаБбВвГгДдЕеЁёЖжЗзИиЙйКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщъыьЭэЮюЯя ";
    for (int i = 0; i < name->length(); i++) {
        if (al.indexOf(name->at(i)) == -1) {
            throw ExCorrection{"ФИО содержит недопустимые символы"};
        }
    }
}


/**
 * @brief Валидатор для проверки корректности стажа работы.
 *
 * Проверяет, чтобы стаж содержал только числа.
 * @param age Указатель на строку стажа для проверки.
 * @throws ExCorrection Если стаж содержит недопустимые символы.
 */
inline void ValidatorWorkAge(QString* age) {
    QString al = "0987654321";
    for (int i = 0; i < age->length(); i++) {
        if (al.indexOf(age->at(i)) == -1) {
            throw ExCorrection{"Стаж работы содержит недопустимые символы"};
        }
    }
}


/**
 * @brief Валидатор для проверки корректности зарплаты.
 *
 * Проверяет, чтобы зарплата содержала только целые числа.
 * @param sal Указатель на строку зарплаты для проверки.
 * @throws ExCorrection Если зарплата содержит недопустимые символы.
 */
inline void ValidatorSalary(QString* sal) {
    QString al = "0987654321";
    for (int i = 0; i < sal->length(); i++) {
        if (al.indexOf(sal->at(i)) == -1) {
            throw ExCorrection{"Зар.плата может быть только целым числом"};
        }
    }
}


/**
 * @brief Валидатор для проверки корректности дополнительных числовых данных.
 *
 * Проверяет, чтобы строка содержала только числа.
 * @param sal Указатель на строку для проверки.
 * @throws ExCorrection Если строка содержит недопустимые символы.
 */
inline void ValidatorPrice_Stock_Window(QString* sal) {
    QString al = "0987654321";
    for (int i = 0; i < sal->length(); i++) {
        if (al.indexOf(sal->at(i)) == -1) {
            throw ExCorrection{"Может быть только целым числом!"};
        }
    }
}


/**
 * @brief Валидатор для проверки пути к файлу.
 *
 * Проверяет, чтобы путь был не пустым и существовал.
 * @param file Путь к файлу.
 * @throws ExCorrection Если путь пуст или не существует.
 */
inline void ValidatorFile(QString file) {
    if (file == "") {
        throw ExCorrection{"Выберите папку!"};
    }
    if (!QFile::exists(file)) {
        throw ExCorrection{"Такого пути нет!"};
    }
}


/**
 * @brief Валидатор для проверки корректности числа (например, количество).
 * @param num Указатель на строку, содержащую проверяемое число.
 * @throws ExCorrection Если строка содержит недопустимые символы.
 */
inline void ValidatorWards(QString* num) {
    QString al = "0987654321";

    // Проверка, чтобы строка содержала только цифры
    for (int i = 0; i < num->length(); i++) {
        if (al.indexOf(num->at(i)) == -1) {
            throw ExCorrection{"Количество может быть только целым числом"};
        }
    }
}


/**
 * @brief Исключение, содержащее обработку ошибок с QLineEdit.
 * Позволяет визуально выделить некорректно заполненные поля и анимировать их.
 */
class MyEx_Prod : public QException {
public:

    /**
     * @brief Конструктор исключения.
     * @param errors_h Вектор с указателями на QLineEdit, содержащие ошибки.
     * @param wind Указатель на виджет, в котором происходит ошибка.
     */
    MyEx_Prod(QVector<QLineEdit*> errors_h, QWidget* wind) {
        errors = errors_h;
        this->wind = wind;
    }

    /**
     * @brief Отображает ошибки.
     * Выделяет красным некорректно заполненные поля и запускает анимацию "дрожания".
     */
    void ShowError() {
        for (int i = 0; i < errors.length(); i++) {
            // Изменение внешнего вида некорректного поля
            errors[i]->setStyleSheet("QLineEdit { border: 1px solid red; color: red; }");
            errors[i]->update();

            // Создание группы анимаций
            auto group = new QSequentialAnimationGroup(errors[i]);

            // Анимация "дрожания" для выделения ошибки
            for (int j = 0; j < 5; ++j) {
                auto animation = new QPropertyAnimation(errors[i], "pos");
                animation->setDuration(100); // Длительность одного дрожания
                animation->setStartValue(errors[i]->pos());
                animation->setEndValue(QPoint(errors[i]->pos().x() + (j % 2 == 0 ? 5 : -5), errors[i]->pos().y())); // Сдвиг влево и вправо
                group->addAnimation(animation);
            }

            // Финальная анимация для возврата поля в исходное положение
            auto finalAnimation = new QPropertyAnimation(errors[i], "pos");
            finalAnimation->setDuration(0);
            finalAnimation->setStartValue(errors[i]->pos());
            finalAnimation->setEndValue(errors[i]->pos());
            group->addAnimation(finalAnimation);

            // Удаление группы анимаций после завершения
            QSequentialAnimationGroup::connect(group, &QSequentialAnimationGroup::finished, group, &QObject::deleteLater);

            // Запуск анимации
            group->start();
        }

        // Отображение сообщения об ошибке пользователю
        QMessageBox::warning(wind, "Внимание!", "Заполните обяательные поля", QMessageBox::Ok);
    }

private:
    QVector<QLineEdit*> errors; ///< Вектор с указателями на QLineEdit с ошибками.
    QWidget* wind;             ///< Указатель на родительский виджет.
};













/**
 * @class MyEx_Table
 * @brief Класс для обработки ошибок в таблице и отображения анимации.
 *
 * Этот класс предназначен для обработки ошибок в таблице, отображения анимации при ошибках и отображения предупреждения для пользователя.
 */
class MyEx_Table : public QException {
public:

    /**
     * @brief Конструктор класса.
     * @param errors_h Список ячеек таблицы с ошибками.
     * @param wind Указатель на окно для отображения сообщений.
     */
    MyEx_Table(QVector<QTableWidgetItem*> errors_h, QWidget* wind) {
        errors = errors_h;
        this->wind = wind;
    }

    /**
     * @brief Отображает ошибку и анимацию для ошибок в таблице.
     *
     * Для каждой ячейки с ошибкой устанавливается видимость символа ошибки, затем для каждой ячейки
     * создается анимация тряски, и после завершения анимации удаляется временный виджет.
     */
    void ShowError() {
        // Проходим по всем ячейкам с ошибками
        for (int i = 0; i < errors.length(); i++) {

            // Устанавливаем символ ошибки как видимый
            errors[i]->setData(Qt::UserRole + 1, true); // Делает символ видимым

            // Получаем таблицу, к которой принадлежит ячейка с ошибкой
            QTableWidget* table = errors[i]->tableWidget();
            if (!table) continue; // Убедимся, что таблица существует

            // Получаем прямоугольник ячейки для анимации
            QRect cellRect = table->visualItemRect(errors[i]);

            // Создаем виджет-заглушку для анимации
            QWidget* shakeWidget = new QWidget(table);
            shakeWidget->setGeometry(cellRect); // Устанавливаем геометрию виджета на основе ячейки
            shakeWidget->show(); // Отображаем виджет

            // Настройка анимации для тряски
            auto group = new QSequentialAnimationGroup(shakeWidget);
            for (int j = 0; j < 5; ++j) { // Количество дрожаний
                auto animation = new QPropertyAnimation(shakeWidget, "pos");
                animation->setDuration(50); // Длительность одного дрожания
                animation->setStartValue(shakeWidget->pos());
                animation->setEndValue(QPoint(
                    shakeWidget->pos().x() + (j % 2 == 0 ? 5 : -5),
                    shakeWidget->pos().y())); // Сдвиг влево и вправо
                group->addAnimation(animation);
            }

            // Финальная анимация возврата в исходную позицию
            auto finalAnimation = new QPropertyAnimation(shakeWidget, "pos");
            finalAnimation->setDuration(0); // Без задержки
            finalAnimation->setStartValue(shakeWidget->pos());
            finalAnimation->setEndValue(shakeWidget->pos());
            group->addAnimation(finalAnimation);

            // После завершения анимации удаляем временный виджет
            QObject::connect(group, &QSequentialAnimationGroup::finished, shakeWidget, &QWidget::deleteLater);
            QObject::connect(group, &QSequentialAnimationGroup::finished, group, &QObject::deleteLater);

            // Запуск анимации
            group->start();
        }

        // Отображаем предупреждающее сообщение
        QMessageBox::warning(wind, "Внимание!", "Заполните обязательные поля корректными данными", QMessageBox::Ok);
    }

private:
    QVector<QTableWidgetItem*> errors; ///< Список ячеек с ошибками.
    QWidget* wind; ///< Указатель на окно для отображения сообщений.
};





#endif // EXCEPTIONS_H
