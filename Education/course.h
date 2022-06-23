#ifndef COURSE_H
#define COURSE_H
#include<string>
#include<vector>
#include"Education/teacher.h"
using namespace std;


class Course
{
public:
     static tuple<bool,string,Course>LoadFromDB(string CID);//从数据库中读取课程号为CID的课程信息，若读取成功，则返回{ture,课程信息}，否则返回{false,xxx}

    vector<pair<string, int>> getStudentsIdScore();//以数组形式返回此门课程的学生学号以及对应分数
    static vector<Course> getInstituteCourses(string I_name="");
    pair<string,teachTime> getTeacherIdTime();//返回教授此门课的老师Id以及上课时间，若没有老师教授此门课，返回{"null",-1};
    bool updataScore(string sid,int score);
    bool updata2DB();//将课程信息更新到数据库
    bool insert2DB();//将课程信息插入到数据库
    bool deleteFromDB();//从数据库删除这门课的信息
    int getStuNumber();//从数据库中查询选择这门课的人数
    int getScore(string sid);
public:
    Course(string cid, string cName, string iName, float credits, int quota)
        :CId(cid), CName(cName), IName(iName), Credits(credits), Quota(quota)
    {}
    string getCID();
    string getCName();
    string getIName();
    float getCredits();
    int getQuota();

    void setCName(string name);
    void setCredits(float credits);
    void setQuota(int quota);
private:
    string CId;
    string CName;
    string IName;
    float Credits;
    int Quota;
};

#endif // COURSE_H
