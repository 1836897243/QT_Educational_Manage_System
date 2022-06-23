#ifndef TEACHER_H
#define TEACHER_H
#include<string>
#include<vector>
using namespace std;
typedef int teachTime;

class Teacher
{
public:

    static tuple<bool,string,Teacher>LoadFromDB(string TID);//利用老师ID从数据库加载老师信息
    static pair<bool,string> Login(string tid, string passwd);//登录
    static pair<bool,string> Rigister(Teacher teacher);//注册
    static vector<Teacher> getInstitudeTeacher(string I_name);
     bool cancelCourse(string CourseID);

    vector<pair<string,teachTime>> getCoursesId();//得到老师教授的课程及对应的上课时间，以数组形式返回
    bool updata2DB();//更新当前老师信息
    bool insert2DB();//插入当前老师信息
    bool teachCourse(string CourseID,teachTime time=0);//老师选择课程号为CourseID的课，并设定上课时间为time
    bool deleteFromDB();
public:
    Teacher(string tid, string t_name, string i_name, string phone_num, float salary, string passwd)
        :TID(tid), TName(t_name), IName(i_name), PhoneNum(phone_num), Salary(salary), PassWd(passwd)
    {}
    string getTID();
    string getTName();
    string getIName();
    string getPhoneNum();
    float getSalary();
    string getPasswd();

    void setInstitute(string I_name);
    void setPhoneNum(string num);
    void setSalary(float salary);
    void setPassWd(string passwd);
private:
    string TID;
    string TName;
    string IName;
    string PhoneNum;
    float Salary;
    string PassWd;
};

#endif // TEACHER_H
