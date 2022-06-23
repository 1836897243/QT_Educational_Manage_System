#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "QMessageBox"

QSqlDatabase initDB()
{
    QSqlDatabase database;
    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("EducationDB.db");
    database.setUserName("root");
    database.setPassword("123456");
    if (!database.open())
    {
        QMessageBox::information(NULL,QString::fromLocal8Bit("提示信息"),QString::fromLocal8Bit("数据库打开失败"));
        exit(-1);
    }
    QSqlQuery query(database);
    query.exec("PRAGMA foreign_keys = ON;");
    return database;
}

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

