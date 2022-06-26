#ifndef INITDATABASS_H
#define INITDATABASS_H
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
    query.exec("CREATE TABLE if not EXISTS Course ( \
               CID	char(10),                       \
               C_name	varchar(20),                \
               I_name	varchar(20),                \
               credits	float(2, 1),                \
               quota	INT,                        \
               PRIMARY KEY(CID),                    \
               FOREIGN KEY(I_name) REFERENCES Institute \
           )");
    query.exec("CREATE TABLE if not EXISTS Institute (  \
               I_name	varchar(20),    \
               building	varchar(30),    \
               budget	float,  \
               PRIMARY KEY(I_name)  \
           );");
    query.exec("CREATE TABLE if not EXISTS Manager (    \
               MID	char(10),   \
               M_name	varchar(20),    \
               I_name	varchar(20),    \
               passwd	varchar(20),    \
               FOREIGN KEY(I_name) REFERENCES Institute,    \
               PRIMARY KEY(MID) \
           );");
    query.exec("CREATE TABLE if not EXISTS Student (    \
               SID	char(10),   \
               S_name	varchar(20),    \
               I_name	varchar(20),    \
               gender	char(5),    \
               birthday	date,   \
               phone	char(11),   \
               passwd	varchar(20),    \
               FOREIGN KEY(I_name) REFERENCES Institute,    \
               PRIMARY KEY(SID) \
           );");
    query.exec("CREATE TABLE if not EXISTS Teaches (    \
               TID	char(10),   \
               CID	char(10),   \
               TeachTime	int,    \
               FOREIGN KEY(TID) REFERENCES Teacher, \
               FOREIGN KEY(CID) REFERENCES Course,  \
               PRIMARY KEY(TID,CID) \
           );");
    query.exec("CREATE TABLE if not EXISTS takes (  \
               SID	char(10),   \
               CID	char(10),   \
               Grade	int,    \
               FOREIGN KEY(CID) REFERENCES Course,  \
               FOREIGN KEY(SID) REFERENCES Student, \
               PRIMARY KEY(SID,CID) \
           );");
    query.exec("CREATE TABLE if not EXISTS teacher (    \
               TID	char(10),   \
               T_name	varchar(20),    \
               I_name	varchar(20),    \
               phone	char(11),   \
               salary	float,  \
               passwd	varchar(20),    \
               FOREIGN KEY(I_name) REFERENCES Institute,    \
               PRIMARY KEY(TID) \
           );");
    return database;
}


#endif // INITDATABASS_H
