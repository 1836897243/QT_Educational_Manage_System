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
#include "Education/institute.h"
#include <QMessageBox>
#include<QDialogButtonBox>
#include<QSpinBox>
#include<QDoubleSpinBox>
#include<QFormLayout>
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

void Login::on_btnAddInstitute_clicked()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("User input:"));
    // 学院名称
    QString IName = QString("学院名称: ");
    QLineEdit LEIName(&dialog);
    form.addRow(IName, &LEIName);

    // 学院楼
    QString IBuilding = QString("学院楼: ");
    QLineEdit LEIBuilding(&dialog);
    form.addRow(IBuilding, &LEIBuilding);

    // 学院预算
    QString IBudget = QString("学院预算(万): ");
    QDoubleSpinBox SPIBudget(&dialog);
    SPIBudget.setMaximum(1000000000);
    form.addRow(IBudget, &SPIBudget);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    if (dialog.exec() == QDialog::Accepted) {
        Institute I(LEIName.text().toStdString(),LEIBuilding.text().toStdString(),SPIBudget.value());
        if(I.insert2DB())
        {
            QMessageBox::information(this,"通知","添加成功");
        }
        else
            QMessageBox::warning(this,"警告","添加失败");
    }
}
