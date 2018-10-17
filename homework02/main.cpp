#include <QDebug>
#include <QTextStream>
#include <QFile>
#include<QList>
#include <QCoreApplication>
using namespace std;
#define N 4     //选择想排序的列
namespace SK {
enum SortKind{
    col01    =   0x00000001<<0,         //!< 第1列
    col02    =   0x00000001<<1,         //!< 第2列
    col03    =   0x00000001<<2,         //!< 第3列
    col04    =   0x00000001<<3,         //!< 第4列
    col05    =   0x00000001<<4,         //!< 第5列
    col06    =   0x00000001<<5,         //!< 第6列
    col07    =   0x00000001<<6,         //!< 第7列
    col08    =   0x00000001<<7,         //!< 第8列
    col09    =   0x00000001<<8,         //!< 第9列
    col10    =   0x00000001<<9,         //!< 第10列
    col11    =   0x00000001<<10,        //!< 第11列
    col12    =   0x00000001<<11,        //!< 第12列
    col13    =   0x00000001<<12,        //!< 第13列
    col14    =   0x00000001<<13,        //!< 第14列
    col15    =   0x00000001<<14,        //!< 第15列
    col16    =   0x00000001<<15,        //!< 第16列
    col17    =   0x00000001<<16,        //!< 第17列
    col18    =   0x00000001<<17,        //!< 第18列
    col19    =   0x00000001<<18,        //!< 第19列
    col20    =   0x00000001<<19,        //!< 第20列
    col21    =   0x00000001<<20,        //!< 第21列
    col22    =   0x00000001<<21,        //!< 第22列
    col23    =   0x00000001<<22,        //!< 第23列
    col24    =   0x00000001<<23,        //!< 第24列
    col25    =   0x00000001<<24,        //!< 第25列
    col26    =   0x00000001<<25,        //!< 第26列
    col27    =   0x00000001<<26,        //!< 第27列
    col28    =   0x00000001<<27,        //!< 第28列
    col29    =   0x00000001<<28,        //!< 第29列
    col30    =   0x00000001<<29,        //!< 第30列
    col31    =   0x00000001<<30,        //!< 第31列
    col32    =   0x00000001<<31,        //!< 第32列
};
}

/******************************************** *
 *          定义学生数据类结构体               *
 * ****************************************** */
typedef struct{
     QStringList st;
} studData;

 /******************************************** *
  * 运算符重载函数，使其可以直接输出studData结构 *
  * ****************************************** */
QDebug operator<< (QDebug d, const studData &data) {
    for(int i=0;i<data.st.size();i++)
    {
        d.noquote()<<data.st.at(i)<<"   ";               //构造输出函数，通过在最后加上‘\t’来增大输出的数据间距
    }
    return d;
}


/* ********************************
 * 比较类，用于std::sort第三个参数 *
 * ********************************/
class myCmp {
public:
    myCmp(int selectedColumn) { this->currentColumn = selectedColumn; }
    bool operator() (const studData& d1,const studData& d2);
private:
    int currentColumn;
};



bool myCmp::operator()(const studData &d1, const studData &d2)
{
    bool result = false;
    quint32 sortedColumn = 0x00000001<<currentColumn;
    switch (sortedColumn) {
    default: result=(d1.st.at(currentColumn+1)>=d2.st.at(currentColumn+1));break;
    }
    return result;
}


class ScoreSorter
{
public:
    ScoreSorter(QString dataFile);
    void readFile();
    void doSort();
private:
    QString tempfile;
    QList<studData>   student;
    QStringList    title;
};

ScoreSorter::ScoreSorter(QString dataFile)
{
    tempfile=dataFile;
}

void ScoreSorter::doSort()
{
    myCmp cmp_temp(N-2);
    std::sort(student.begin(),student.end(),cmp_temp);
    title.removeLast();                              //删除最后一个"\n"
    qDebug() << ' '<<title;

    for(int j=0;j<student.size();j++)
    {
        qDebug()<<student.at(j);
    }
}

void ScoreSorter::readFile()
{
    QFile mfile(tempfile);
    if(!mfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug()<<"无法打开该文件!";
       }
    studData tempstu;
    QString Title(mfile.readLine());
        title= Title.split(" ", QString::SkipEmptyParts);
    while(!mfile.atEnd()) {
        QString str(mfile.readLine());
        tempstu.st = str.split(" ", QString::SkipEmptyParts);
        if((tempstu.st).last() == "\n") tempstu.st.removeLast();
        if(tempstu.st.size()==0) continue;
        student.append(tempstu);
    }
    mfile.close();
}

//void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
//{

//}

int main()
{
    QString datafile = "data.txt";
    QFile f("sorted_"+datafile);    // 如果排序后文件已存在，则删除之
    if (f.exists()){
        f.remove();
    }

    ScoreSorter s(datafile);
    s.readFile();
    s.doSort();
    return 0;
}
