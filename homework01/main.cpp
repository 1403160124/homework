#include<QDebug>
#include<QCoreApplication>
#include<QList>
typedef quint8 byte;
typedef quint32 word;
#define N 0x12345678
#define HHI(X) ((byte) ((word)(X)>>24)&0xFF)
#define LHI(X) ((byte) ((word)(X)>>16)&0xFF)
#define HLO(X) ((byte) ((word)(X)>>8)&0xFF)
#define LLO(X) ((byte) ((word)(X))&0xFF)
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
int main()
{
    int rebuiltN;
    QList<quint8> values;
    values.append(HHI(N));
    values.append(LHI(N));
    values.append(HLO(N));
    values.append(LLO(N));
    qDebug("原数据为：0x%x==%d",N,N);
   qDebug("0x%x==%d  0x%x==%d  0x%x==%d  0x%x==%d ",HHI(N),HHI(N),LHI(N),LHI(N),HLO(N),HLO(N),LLO(N),LLO(N));//分别取出最高8位，次高8位，次低8位，最低8位
    qDebug("最高8位和次高8位的最大值:0x%x<%d>",MAX(values.at(0),values.at(1)),MAX(values.at(0),values.at(1)));//返回最高8位和次高8位的最大值
    qDebug("次低8位和最低8位的最小值:0x%x<%d>",MIN(values.at(2),values.at(3)),MIN(values.at(2),values.at(3)));//次低8位和最低8位的最小值
    rebuiltN = (values.at(2)<<24)+(values.at(0)<<16)+(values.at(3)<<8)+(values.at(1));//新的值为原次低8位，最高8位，最低8位，次高8位
    qDebug("重新组合后的数值：0x%x<%d>",rebuiltN,rebuiltN);
    qDebug()<<"排序前："<<values;
    std::sort(values.begin(),values.end(),std::greater<quint8>());
    qDebug()<<"排序后：" <<values;
    return 0;
}
