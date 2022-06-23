#ifndef STU_ALLLESSIONS_H
#define STU_ALLLESSIONS_H

#include <QMainWindow>

namespace Ui {
class Stu_allLessions;
}

class Stu_allLessions : public QMainWindow
{
    Q_OBJECT

public:
    explicit Stu_allLessions(QWidget *parent = nullptr);
    void Welcome(const QString &str);
    void Update();
    ~Stu_allLessions();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Stu_allLessions *ui;
};

#endif // STU_ALLLESSIONS_H
