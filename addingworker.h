#ifndef ADDINGWORKER_H
#define ADDINGWORKER_H

#include <QDialog>
#include <QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTimer>
#include "classes.h"
#include <QLineEdit>

/**
 * @brief Класс, реализующий кастомное поведение для QLineEdit
 *
 * CustomLineEdit обеспечивает обработку первого клика,
 * устанавливая курсор в начало строки.
 */
class CustomLineEdit : public QLineEdit {
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса CustomLineEdit
     * @param parent Указатель на родительский виджет
     */
    CustomLineEdit(QWidget *parent = nullptr)
        : QLineEdit(parent), firstClick(true) {}

protected:
    /**
     * @brief Переопределенный метод для обработки нажатий мыши
     * @param event Указатель на событие нажатия мыши
     */
    void mousePressEvent(QMouseEvent *event) override {
        if (firstClick) {
            setCursorPosition(0);  ///< Устанавливаем курсор в начало строки
            firstClick = false;
        } else {
            QLineEdit::mousePressEvent(event);
        }
    }

private:
    bool firstClick; ///< Флаг, указывающий на первое нажатие
};

namespace Ui {
class AddingWorker;
}

/**
 * @brief Класс для диалога добавления нового работника
 */
class AddingWorker : public QDialog {
    Q_OBJECT

public:

    explicit AddingWorker(QWidget *parent = nullptr, shop* shop = nullptr);

    ~AddingWorker();

private slots:

    void on_lineEdit_FIO_editingFinished();

    void on_lineEdit_Birth_editingFinished();

    void on_lineEdit_Phone_editingFinished();

    void on_lineEdit_Pasport_editingFinished();

    void on_lineEdit_WA_editingFinished();

    void on_lineEdit_Salary_editingFinished();

    void on_lineEdit_Sector_editingFinished();

    void on_SaveButton_clicked();

    void on_SkipButton_clicked();

    void fadeOut();

    void enableButton();

private:
    Ui::AddingWorker *ui; ///< Указатель на интерфейс пользователя
    QSqlDatabase db; ///< Подключение к базе данных
    shop* shop1; ///< Указатель на объект магазина
    Asistant* worker; ///< Указатель на объект работника
    QTimer *timer; ///< Таймер для управления событиями
    QTimer *buttonTimer; ///< Таймер для активации кнопки
};

#endif // ADDINGWORKER_H
