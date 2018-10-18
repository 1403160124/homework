#include <QCoreApplication>
#include <QDebug>
#include <QVector>
#include<QList>
#include <QTextStream>
#include <QFile>
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


typedef struct{
    QStringList st_da;
} studData;//创建studData结构体；

QDebug operator<< (QDebug d, const studData &data) {   //运算符重载函数，使其可以直接输出studData结构
    for(int i=0;i<data.st_da.size();i++){
        d.noquote().nospace()<<QString(data.st_da.at(i))<<"\t";
    }
    return d;
}
class myCmp {                                                                                           // 比较每一列的两个数的大小
public:
    myCmp(int selectedColumn) { this->currentColumn = selectedColumn; }
    bool operator()(const studData & d1,const studData & d2) ;
private:
    int currentColumn;
};
bool myCmp::operator()(const studData &d1, const studData &d2)
{
    if(d1.st_da.at (currentColumn+1)>d2.st_da.at(currentColumn+1))     //判断d1是否大于d2
        return 0 ;
    else
        return 1;
}



class ScoreSorter                                                               //排序类
{
public:
    ScoreSorter(QString dataFile);
    void readFile();
    void doSort();
private:
    QString tempFile;
    QList<studData> s_data;
    studData List;
    void creat_txt(quint8 n);
};


 ScoreSorter::ScoreSorter(QString dataFile)
{
     this->tempFile=dataFile;
}
 void ScoreSorter::doSort()
 {
     for(int i=1;i<this->List.st_da.size();i++)
     {
         myCmp cmp(i-1);
         std::sort(this->s_data.begin() , this->s_data.end() ,cmp );
         qDebug()<<"根据第"<<i+1<<"列排序：";
         qDebug() <<"\t"<< (this->List)<<"\t";                                                                      //输出表头
         for(int i=0;i<this->s_data.size();i++)  qDebug() <<" "<< this->s_data.at(i)<<"\t\t";   //输出学生信息
         qDebug()<<"************************************************\n";
         this->creat_txt(i+1);                              //生成TXT文件
     }
 }
 void ScoreSorter::readFile()
 {
     QFile file(this->tempFile);
     if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
         qDebug()<<"Can't open the file!"<<endl;
     }
     QString title(file.readLine());
     this->List.st_da = title.split(" ", QString::SkipEmptyParts);
     if((this->List.st_da).last() == "\n") this->List.st_da.removeLast();
     studData lastdata;
     while(!file.atEnd()) {
         QByteArray line = file.readLine();
         QString str(line);
         lastdata.st_da = str.split(" ", QString::SkipEmptyParts);
         if((lastdata.st_da).last() == "\n") lastdata.st_da.removeLast();
         if(lastdata.st_da.size()==0) continue;
         this->s_data.append(lastdata);
     }
     file.close();
 }
 void ScoreSorter::creat_txt(quint8 n)
 {
     QFile file("resort_"+this->tempFile);
     file.open(QIODevice::ReadWrite | QIODevice::Append);
     QTextStream stream(&file);
     stream.setCodec("UTF-8");//用UTF-8编码输入
     stream<<QString("根据第 ")<<n <<QString(" 列排序")<<"\r\n";
     stream<<"\t";
     for(int j=0;j<this->List.st_da.size();j++)
         stream<<this->List.st_da.at(j)<<"\t";
     stream<<"\r\n";
     for(int k=0;k<this->s_data.size();k++)
     {
         for(int m=0;m<this->List.st_da.size();m++)
             stream<<this->s_data.at(k).st_da.at(m)<<"\t";
         stream<<"\r\n";
     }
     stream<<"****************************************************"<<"\r\n\r\n";
     file.close();
 }


void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
        switch (type) {
        case QtDebugMsg:
            fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtInfoMsg:
            fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtWarningMsg:
            fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtCriticalMsg:
            fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtFatalMsg:
            fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            abort();
        }
}

int main ()
{

    QString datafile = "data.txt";
    QFile f("resort_"+datafile);
    if (f.exists())
    {
        f.remove();
    }                       // 如果排序后文件已存在，则删除之

    ScoreSorter s(datafile);
    s.readFile();
    s.doSort();

    return 0;
}
