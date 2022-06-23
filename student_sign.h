#ifndef STUDENT_SIGN_H
#define STUDENT_SIGN_H

#include <QMainWindow>

namespace Ui {
class Student_sign;
}

class Student_sign : public QMainWindow
{
    Q_OBJECT

public:
    explicit Student_sign(QWidget *parent = nullptr);
    ~Student_sign();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Student_sign *ui;
};

#endif // STUDENT_SIGN_H
