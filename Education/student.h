#ifndef STUDENT_H
#define STUDENT_H
#include<string>
#include<vector>
using namespace std;

class Student
{
public:
    static tuple<bool,string,Student> LoadFromDB(string Sid);//从数据库中读取学号为Sid的学生信息，若读取成功，则返回{ture,学生信息}，否则返回{false,xxx}
    static pair<bool,string> Login(string sid, string passwd);//查看账号密码是否匹配
    static pair<bool,string> Rigister(Student Stu);//将Stu的信息更新到数据库(即注册)
    static vector<Student>getInstitudeStudents(string I_name);
    bool cancelCourse(string CourseId);//取消选课，取消课程ID为CourseId的课


    vector<pair<string, int>> getCoursesIdScore();//得到学生上的课,对应成绩，以数组形式返回
    bool takeCourse(string CourseId);//选课，选择课程ID为CourseId的课
    bool updata2DB();//更新当前学生信息
    bool insert2DB();//插入当前学生信息
    bool deleteFromDB();
public:
    Student(string sid, string s_name, string I_name, string gender, string birthday, string phone, string passwd)
        :SID(sid), SName(s_name), IName(I_name), Gender(gender), Birthday(birthday), PhoneNum(phone), PassWd(passwd)
    {}
    string getSID();
    string getSName();
    string getINmae();
    string getGender();
    string getBirthday();
    string getPhone();
    string getPasswd();

    void setGender(string gender);
    void setInstitute(string I_name);
    void setBirthday(string birthday);
    void setPhoneNum(string num);
    void setPassWd(string passwd);
private:
    string SID;
    string SName;
    string IName;
    string Gender;
    string Birthday;
    string PhoneNum;
    string PassWd;
};

#endif // STUDENT_H
