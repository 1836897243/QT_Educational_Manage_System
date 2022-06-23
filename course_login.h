#ifndef COURSE_LOGIN_H
#define COURSE_LOGIN_H

#include <QMainWindow>
#include"Global.h"
namespace Ui {
class Course_login;
}

class Course_login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Course_login(QWidget *parent = nullptr);
    void Welcome(const QString &str);
    ~Course_login();
private:
    void updateCourseTable();
    void saveCoursTable();
private slots:
    void on_pushButton_clicked();

    void on_addCourse_clicked();

    void on_pushButton_3_clicked();

    void on_save_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Course_login *ui;
};

#endif // COURSE_LOGIN_H
