#ifndef MANAGER_H
#define MANAGER_H

#include<tuple>
#include<string>
#include<vector>
using namespace std;

class Manager
{
public:
    static tuple<bool,string,Manager>LoadFromDB(string MID);//从数据库中读取ID号为MID的管理员信息，若读取成功，则返回{ture,管理员信息}，否则返回{false,xxx}
    static pair<bool,string> Login(string mid, string passwd);//查看账号密码是否匹配
    static pair<bool,string> Rigister(Manager manager);//将manager的信息更新到数据库(即注册)

    bool updata2DB();//将课程信息更新到数据库
    bool insert2DB();//将课程信息插入到数据库
public:
    Manager(string mid, string m_name, string i_name, string passwd)
        :MID(mid), MName(m_name), IName(i_name), PassWd(passwd)
    {}
    string getMName();
    string getIName();
    void setMName(string name);
    void setINmae(string name);
    void setPassWd(string passwd);
private:
    string MID;
    string MName;
    string IName;
    string PassWd;

};

#endif // MANAGER_H
