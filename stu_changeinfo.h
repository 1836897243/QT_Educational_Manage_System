#ifndef STU_CHANGEINFO_H
#define STU_CHANGEINFO_H

#include <QMainWindow>

namespace Ui {
class Stu_changeInfo;
}

class Stu_changeInfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit Stu_changeInfo(QWidget *parent = nullptr);
    void Welcome(const QString &str);
    ~Stu_changeInfo();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Stu_changeInfo *ui;
};

#endif // STU_CHANGEINFO_H
