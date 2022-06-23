#include "tea_menu.h"
#include "ui_tea_menu.h"
#include "login.h"
#include "tea_changeinfo.h"
#include "tea_teachlessions.h"
#include "tea_grade.h"

Tea_menu::Tea_menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Tea_menu)
{
    ui->setupUi(this);
}

Tea_menu::~Tea_menu()
{
    delete ui;
}

void Tea_menu::Welcome(const QString &str){
    ui->label_5->setText(str);
}

void Tea_menu::on_pushButton_8_clicked()
{
    this->close();
    Login *login=new Login();
    login->show();
}

void Tea_menu::on_pushButton_7_clicked()
{
    this->close();
    Tea_changeInfo * tea_changeInfo=new Tea_changeInfo();
    tea_changeInfo->Welcome(ui->label_5->text());
    tea_changeInfo->show();
}

void Tea_menu::on_pushButton_4_clicked()
{
    this->close();
    Tea_teachLessions * tea_teachLessions=new Tea_teachLessions();
    tea_teachLessions->Welcome(ui->label_5->text());
    tea_teachLessions->show();
}

void Tea_menu::on_pushButton_6_clicked()
{
    this->close();
    Tea_grade * tea_grade=new Tea_grade();
    tea_grade->Welcome(ui->label_5->text());
    tea_grade->show();
}
