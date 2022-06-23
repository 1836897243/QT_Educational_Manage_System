#include "manager_menu.h"
#include "ui_manager_menu.h"
#include "login.h"
#include "course_login.h"
#include "manager_stu.h"
#include "manager_tea.h"

Manager_menu::Manager_menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Manager_menu)
{
    ui->setupUi(this);
}

Manager_menu::~Manager_menu()
{
    delete ui;
}

void Manager_menu::Welcome(const QString &str){
    ui->label_5->setText(str);
}

void Manager_menu::on_pushButton_8_clicked()
{
    this->close();
    Login *login=new Login();
    login->show();
}

void Manager_menu::on_pushButton_4_clicked()
{
    this->close();
    Course_login * course_login=new Course_login();
    course_login->Welcome(ui->label_5->text());
    course_login->show();
}

void Manager_menu::on_pushButton_6_clicked()
{
    this->close();
    Manager_stu * manager_stu=new Manager_stu();
    manager_stu->Welcome(ui->label_5->text());
    manager_stu->show();
}

void Manager_menu::on_pushButton_7_clicked()
{
    this->close();
    Manager_tea * manager_tea=new Manager_tea();
    manager_tea->Welcome(ui->label_5->text());
    manager_tea->show();
}
