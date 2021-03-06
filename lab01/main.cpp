#include <QCoreApplication>
#include<QDebug>
#include<iostream>
//定义学生信息类；(姓名：name，学号：number，课程1：course1，课程2：course2)
class st_inf
 {
 public:
     int number;
     QString name;
     int course1;
     int course2;
 };
void output(QVector<st_inf> *s)
{
    qDebug()<<"  学号\t"<<"\t   姓名\t"<<"\t课程1"<<"\t课程2";
    QVector<st_inf> ::iterator n=s->begin();
    while(n!=s->end())
    {
        qDebug()<<n->number<<"\t"<<n->name<<"\t"<<n->course1<<"\t"<<n->course2;
        n++;
    }
}
//姓名排序函数；
bool sort_name(st_inf s1,st_inf s2)
{
    if (s1.name>s2.name)
        return 1;
    else
        return 0;
}

//课程1排序函数；
bool sort_course1(st_inf s1,st_inf s2)
{
    if (s1.course1>s2.course1)
        return 1;
    else
        return 0;
}
//课程2排序函数；
bool sort_course2(st_inf s1,st_inf s2)
{
    if (s1.course2>s2.course2)
        return 1;
    else
        return 0;
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//
    st_inf std1,std2,std3,std4;
    //以下为赋值过程：
    std1.name="鲁智深";
    std1.number=1403130209;
    std1.course1=80;
    std1.course2=72;
    std2.name="林冲";
    std2.number=1403140101;
    std2.course1=82;
    std2.course2=76;
    std3.name="宋江";
    std3.number=1403140102;
    std3.course1=76;
    std3.course2=85;
    std4.name="武松";
    std4.number=1403140103;
    std4.course1=88;
    std4.course2=80;
    //定义学生信息列表；
    QVector<st_inf> list;
    list.push_back(std1);
    list.push_back(std2);
    list.push_back(std3);
    list.push_back(std4);

    //数据输出：
    qDebug("原始信息为：");
    output(&list);
    qDebug("---------");

    std::sort(list.begin(),list.end(),sort_name);
    qDebug("按姓名排序输出");
    output(&list);
    qDebug("---------");

    std::sort(list.begin(),list.end(),sort_course1);
    qDebug("按课程1降序输出");
    output(&list);
    qDebug("---------");

    std::sort(list.begin(),list.end(),sort_course2);
    qDebug("按课程2降序输出");
    output(&list);
    return a.exec();
}
