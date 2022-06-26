#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "QMessageBox"
#include "Education/initDataBass.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    DB=initDB();
    ui->setupUi(this);
}



MainWindow::~MainWindow()
{
    //DB.close();
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    this->close();
    Login *login=new Login();
    login->show();
}

