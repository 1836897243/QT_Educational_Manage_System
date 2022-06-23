#include "manager.h"
#include<QSqlQuery>
#include<functional>
#include<QMessageBox>
#include<QVariant>
tuple<bool,string,Manager> Manager::LoadFromDB(string MID)
{
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="select M_name,I_name,passwd from Manager where MID="+addQuotation(MID);
    Manager res(MID,"null","null","null");
    string info="操作成功";
    if(!query.exec(QString::fromStdString(sql)))
    {
        info="数据库操作失败";
        return make_tuple(false,info,res);
    }
    if(!query.next())
    {
        info="不存在管理员号为"+MID+"的管理员";
        return make_tuple(false,info,res);
    }
    else
    {
        res.MName=query.value("M_name").toString().toStdString();
        res.IName=query.value("I_name").toString().toStdString();
        res.PassWd=query.value("passwd").toString().toStdString();
    }
    return make_tuple(true,info,res);
}
bool Manager::updata2DB()
{
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="update Manager set M_name="+addQuotation(MName)+",I_name="+addQuotation(IName)
            +",passwd="+addQuotation(PassWd)
            +"where MID="+addQuotation(MID);
     return query.exec(QString::fromStdString(sql));
}
bool Manager::insert2DB()
{
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="insert into Manager values("+addQuotation(MID)+","+addQuotation(MName)+","+addQuotation(IName)+","
            +addQuotation(PassWd)+")";
    return query.exec(QString::fromStdString(sql));
}
pair<bool,string> Manager::Login(string mid, string passwd)
{
    bool isSuccess;
    string info;
    Manager M("null","null","null","null");
    std::tie(isSuccess,info,M)=Manager::LoadFromDB(mid);
    if(isSuccess)
    {
        if(M.PassWd==passwd)
            return make_pair(true,"登陆成功");
        else
            return make_pair(false,"密码错误");
    }
    else
        return make_pair(isSuccess,info);
}
pair<bool,string> Manager::Rigister(Manager manager)
{
    bool isSuccess;
    string info;
    Manager M("null","null","null","null");
    std::tie(isSuccess,info,M)=Manager::LoadFromDB(manager.MID);
    if(!isSuccess)
    {
        bool flag=manager.insert2DB();
        if(flag)
            return make_pair(flag,"注册成功");
         else
            return make_pair(flag,"注册失败");
    }
    return make_pair(false,"已存在此账号");
}
string Manager::getMName()
{
    return MName;
}

void Manager::setMName(string name)
{
    MName = name;
}

string Manager::getIName()
{
    return IName;
}

void Manager::setINmae(string name)
{
    IName = name;
}
void Manager::setPassWd(string passwd)
{
    PassWd = passwd;
}
