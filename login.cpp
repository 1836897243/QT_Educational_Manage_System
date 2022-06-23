#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "student_sign.h"
#include "teacher_sign.h"
#include "manager_sign.h"
#include "student_menu.h"
#include "tea_menu.h"
#include "manager_menu.h"
#include "Education/student.h"
#include "Education/teacher.h"
#include "Education/manager.h"
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    this->close();
    MainWindow * mainwindow=new MainWindow();
    mainwindow->show();
}

void Login::on_pushButton_3_clicked()
{
    if(ui->comboBox_3->currentText()=="Student"){
        this->close();
        Student_sign * student_sign=new Student_sign();
        student_sign->show();
    }

    if(ui->comboBox_3->currentText()=="Teacher"){
        this->close();
        Teacher_sign * teacher_sign=new Teacher_sign();
        teacher_sign->show();
    }

    if(ui->comboBox_3->currentText()=="Manager"){
        this->close();
        Manager_sign * manager_sign=new Manager_sign();
        manager_sign->show();
    }
}

void Login::on_pushButton_2_clicked()
{
    if(ui->comboBox_2->currentText()=="Student"){
        string Account=ui->lineEdit_4->text().toStdString();
        string Password=ui->lineEdit_3->text().toStdString();
        if(Student::Login(Account,Password).first==true){
            this->close();
            Student_menu * student_menu=new Student_menu();
            student_menu->Welcome(ui->lineEdit_4->text());
            student_menu->show();
        }
        else{
            QMessageBox::warning(this,"警告",QString::fromStdString(Student::Login(Account,Password).second));
        }
    }

    if(ui->comboBox_2->currentText()=="Teacher"){
        string Account=ui->lineEdit_4->text().toStdString();
        string Password=ui->lineEdit_3->text().toStdString();
        if(Teacher::Login(Account,Password).first==true){
            this->close();
            Tea_menu * tea_menu=new Tea_menu();
            tea_menu->Welcome(ui->lineEdit_4->text());
            tea_menu->show();
        }
        else{
            QMessageBox::warning(this,"警告",QString::fromStdString(Teacher::Login(Account,Password).second));
        }
    }

    if(ui->comboBox_2->currentText()=="Manager"){
        string Account=ui->lineEdit_4->text().toStdString();
        string Password=ui->lineEdit_3->text().toStdString();
        if(Manager::Login(Account,Password).first==true){
            this->close();
            Manager_menu * manager_menu=new Manager_menu();
            manager_menu->Welcome(ui->lineEdit_4->text());
            manager_menu->show();
        }
        else{
            QMessageBox::warning(this,"警告",QString::fromStdString(Manager::Login(Account,Password).second));
        }
    }
}
