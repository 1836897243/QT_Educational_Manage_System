#include "stu_alllessions.h"
#include "ui_stu_alllessions.h"
#include "student_menu.h"
#include <string.h>
#include "Education/student.h"
#include "QStandardItemModel"
#include "Education/course.h"

Stu_allLessions::Stu_allLessions(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Stu_allLessions)
{
    ui->setupUi(this);
}

Stu_allLessions::~Stu_allLessions()
{
    delete ui;
}

void Stu_allLessions::Welcome(const QString &str){
    ui->label_2->setText(str);
    Update();
}

void Stu_allLessions::on_pushButton_clicked()
{
    this->close();
    Student_menu *student_menu=new Student_menu();
    student_menu->Welcome(ui->label_2->text());
    student_menu->show();
}

void Stu_allLessions::Update(){
    std::string studentId=ui->label_2->text().toStdString();
    bool isSuccess;
    std::string info;
    Student S(studentId,"null","null","null","null","null","null");
    std::tie(isSuccess,info,S)=Student::LoadFromDB(studentId);

    // 设置ListView
    QStandardItemModel* model = new QStandardItemModel();

    /* 设置列数 */
    model->setColumnCount(9);
    model->setHeaderData(0, Qt::Horizontal, " 课程学院 ");
    model->setHeaderData(1, Qt::Horizontal, "课程编号");
    model->setHeaderData(2, Qt::Horizontal, "课程名称");
    model->setHeaderData(3, Qt::Horizontal, "课程学分");
    model->setHeaderData(4, Qt::Horizontal, "教师教工号");
    model->setHeaderData(5, Qt::Horizontal, "教师姓名");
    model->setHeaderData(6, Qt::Horizontal, "已选人数");
    model->setHeaderData(7, Qt::Horizontal, "上限人数");
    model->setHeaderData(8, Qt::Horizontal, "学习成绩");

    vector<pair<string, int>>courseInfo= S.getCoursesIdScore();

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
        bool isSuccess1=false;
        std::string info1;
        Course C("null","null","null",0.0,0);
        std::tie(isSuccess1,info1,C)=Course::LoadFromDB(courseInfo[i].first);

        model->setItem(i, 0, new QStandardItem(QString::fromStdString(C.getIName())));
        model->setItem(i, 1, new QStandardItem(QString::fromStdString(courseInfo[i].first)));
        model->setItem(i, 2, new QStandardItem(QString::fromStdString(C.getCName())));
        model->setItem(i, 3, new QStandardItem(QString::number(C.getCredits())));
        model->setItem(i, 4, new QStandardItem(QString::fromStdString(C.getTeacherIdTime().first)));

        Teacher T("null","null","null","null",.0,"null");
        std::tie(isSuccess1,info1,T)=Teacher::LoadFromDB(C.getTeacherIdTime().first);
        model->setItem(i, 5, new QStandardItem(QString::fromStdString(C.getCName())));

        model->setItem(i, 6, new QStandardItem(QString::number(C.getStuNumber())));
        model->setItem(i, 7, new QStandardItem(QString::number(C.getQuota())));
        int Score=C.getScore(S.getSID());
        model->setItem(i, 8, new QStandardItem(Score<0?"null":QString::number(Score)));

    }
    ui->tableView->adjustSize();
    ui->tableView->show();
}


void Stu_allLessions::on_pushButton_2_clicked()
{
    Update();
}
