#include "student_menu.h"
#include "ui_student_menu.h"
#include "login.h"
#include "stu_takelession.h"
#include "stu_changeinfo.h"
#include "stu_alllessions.h"

Student_menu::Student_menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Student_menu)
{
    ui->setupUi(this);
}

Student_menu::~Student_menu()
{
    delete ui;
}

void Student_menu::Welcome(const QString &str){
    ui->label_2->setText(str);
}

void Student_menu::on_pushButton_clicked()
{
    this->close();
    Login *login=new Login();
    login->show();
}

void Student_menu::on_pushButton_3_clicked()
{
    this->close();
    Stu_takeLession * stu_takeLession=new Stu_takeLession();
    stu_takeLession->Welcome(ui->label_2->text());
    stu_takeLession->show();
}

void Student_menu::on_pushButton_5_clicked()
{
    this->close();
    Stu_changeInfo * stu_changeInfo=new Stu_changeInfo();
    stu_changeInfo->Welcome(ui->label_2->text());
    stu_changeInfo->show();
}

void Student_menu::on_pushButton_2_clicked()
{
    this->close();
    Stu_allLessions * stu_allLessions=new Stu_allLessions();
    stu_allLessions->Welcome(ui->label_2->text());
    stu_allLessions->show();
}
