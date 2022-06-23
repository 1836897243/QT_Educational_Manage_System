#ifndef TEACHER_SIGN_H
#define TEACHER_SIGN_H

#include <QMainWindow>

namespace Ui {
class Teacher_sign;
}

class Teacher_sign : public QMainWindow
{
    Q_OBJECT

public:
    explicit Teacher_sign(QWidget *parent = nullptr);
    ~Teacher_sign();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Teacher_sign *ui;
};

#endif // TEACHER_SIGN_H
