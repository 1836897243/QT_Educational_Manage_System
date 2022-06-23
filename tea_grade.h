#ifndef TEA_GRADE_H
#define TEA_GRADE_H

#include <QMainWindow>
#include"Education/course.h"
namespace Ui {
class Tea_grade;
}

class Tea_grade : public QMainWindow
{
    Q_OBJECT

public:
    explicit Tea_grade(QWidget *parent = nullptr);
    void Welcome(const QString &str);
    ~Tea_grade();
private:
    void updateStuTable(Course c);
    void saveStuTable();
private slots:
    void on_pushButton_clicked();

    void on_comboBoxCourse_currentIndexChanged(const QString &arg1);

    void on_save_clicked();


private:
    Ui::Tea_grade *ui;
};

#endif // TEA_GRADE_H
