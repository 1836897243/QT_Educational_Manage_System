#include "tea_teachlessions.h"
#include "ui_tea_teachlessions.h"
#include "tea_menu.h"
#include "QStandardItemModel"
#include "Education/course.h"
#include <vector>
#include <QMessageBox>

using namespace std;

Tea_teachLessions::Tea_teachLessions(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Tea_teachLessions)
{
    ui->setupUi(this);
}

Tea_teachLessions::~Tea_teachLessions()
{
    delete ui;
}

void Tea_teachLessions::Welcome(const QString &str){
    ui->label_2->setText(str);
    this->Update();
}

void Tea_teachLessions::on_pushButton_clicked()
{
    this->close();
    Tea_menu *tea_menu=new Tea_menu();
    tea_menu->Welcome(ui->label_2->text());
    tea_menu->show();
}
void Tea_teachLessions::Update(){
    // 设置ListView
    QStandardItemModel* model = new QStandardItemModel();

    /* 设置列数 */
    model->setColumnCount(7);

    model->setHeaderData(0, Qt::Horizontal, "课程编号");
    model->setHeaderData(1, Qt::Horizontal, "课程名称");
    model->setHeaderData(2, Qt::Horizontal, "学院名称");
    model->setHeaderData(3, Qt::Horizontal, "课程学分");
    model->setHeaderData(4, Qt::Horizontal, "授课教师");
    model->setHeaderData(5, Qt::Horizontal, "已选人数");
    model->setHeaderData(6, Qt::Horizontal, "上限人数");

    vector<Course>courseInfo= Course::getInstituteCourses();
    //得到学生上的课,对应成绩，以数组形式返回

    /* 设置行数 */
    model->setRowCount(courseInfo.size());
    //        model->setHeaderData(0, Qt::Vertical, "");

    ui->tableView->setModel(model);
    /* 行颜色交替显示 */
    ui->tableView->setAlternatingRowColors(true);
    /* 不允许在图形界面修改内容 */
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 遍历结果集，并添加记录到ListView
    for(unsigned i=0;i<courseInfo.size();i++)
    {
        model->setItem(i, 0, new QStandardItem(QString::fromStdString(courseInfo[i].getCID())));
        model->setItem(i, 1, new QStandardItem(QString::fromStdString(courseInfo[i].getCName())));
        model->setItem(i, 2, new QStandardItem(QString::fromStdString(courseInfo[i].getIName())));
        model->setItem(i, 3, new QStandardItem(QString::number(courseInfo[i].getCredits())));
        model->setItem(i, 4, new QStandardItem(QString::fromStdString(courseInfo[i].getTeacherIdTime().first)));
        model->setItem(i, 5, new QStandardItem(QString::number(courseInfo[i].getStuNumber())));
        model->setItem(i, 6, new QStandardItem(QString::number(courseInfo[i].getQuota())));

    }
    ui->tableView->adjustSize();
    ui->tableView->show();
}

void Tea_teachLessions::on_pushButton_4_clicked()
{
    this->Update();
}

void Tea_teachLessions::on_pushButton_2_clicked()
{
    std::string teacherId=ui->label_2->text().toStdString();
    bool isSuccess;
    std::string info;
    Teacher T(teacherId,"null","null","null",0.0,"null");
    std::tie(isSuccess,info,T)=Teacher::LoadFromDB(teacherId);
    if(T.teachCourse(ui->courseid0->text().toStdString())==false){
        QMessageBox::warning(this,"警告","添加失败");
    }
    else{
         QMessageBox::warning(this,"通知","添加成功");
    }
}

void Tea_teachLessions::on_pushButton_3_clicked()
{
    std::string teacherId=ui->label_2->text().toStdString();
    bool isSuccess;
    std::string info;
    Teacher T(teacherId,"null","null","null",0.0,"null");
    std::tie(isSuccess,info,T)=Teacher::LoadFromDB(teacherId);
    if(T.cancelCourse(ui->courseid0->text().toStdString())==false){
        QMessageBox::warning(this,"警告","删除失败");
    }
    else{
         QMessageBox::warning(this,"通知","删除成功");
    }
}
