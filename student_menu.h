#ifndef STUDENT_MENU_H
#define STUDENT_MENU_H

#include <QMainWindow>

namespace Ui {
class Student_menu;
}

class Student_menu : public QMainWindow
{
    Q_OBJECT

public:
    void Welcome(const QString &str);
    explicit Student_menu(QWidget *parent = nullptr);
    ~Student_menu();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Student_menu *ui;
};

#endif // STUDENT_MENU_H
