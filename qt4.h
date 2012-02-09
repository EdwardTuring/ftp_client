#ifndef QT4_H
#define QT4_H

#include <QtGui>
#include <QtCore>
/*
这个头文件定义了基本的宏定义

*/
#define CONNECT(a,b,c,d) connect(a,SIGNAL(b),c,SLOT(d))
QString FromSpecialEncoding(const QString &InputStr)
{
    QString TempResult;
    //1.提取数据
    size_t InStrBufSize= InputStr.size()*sizeof(QChar);
    char* InStrBuf= (char*)malloc(InStrBufSize);
    if (InStrBuf==NULL)
    {
        return TempResult;
    }
    memcpy(InStrBuf, InputStr.data(), InStrBufSize);
    //2.拆分数据
    size_t i;
#if Q_BYTE_ORDER==Q_LITTLE_ENDIAN
    //小端对齐下(基于Intel的x86架构)
    //原始数据下标 0 2 4 6 8 10
    //修复数据下标 0 1 2 3 4 5
    i= 0;
    for (i=0; i<InStrBufSize; i=i+2)
    {
        InStrBuf[i>>1]=InStrBuf[i];
    }
    memset(InStrBuf+ (i>>1), 0, i>>1);
#else
    //大端对齐下
    //原始数据下标 1 3 5 7 9
    //修复数据下标 0 1 2 3 4
    i= 1;
    for (i=1; i<=InStrBufSize; i=i+2)
    {
        InStrBuf[(i-1)>>1]=InStrBuf[i];
    }
    memset(InStrBuf+ ((i-1)>>1), 0, (i-1)>>1);
#endif
    //3.数据重新组装
    TempResult= TempResult.fromAscii(InStrBuf);
    free(InStrBuf);
    return TempResult;
}
//=============================================================================
QString ToSpecialEncoding(const QString &InputStr)
{
    QString TempResult;
    //1.提取数据
    size_t InStrBufSize= InputStr.toAscii().size();
    char* InStrBuf= (char*)malloc(InStrBufSize);//= InputStr.toAscii().data();
    memset(InStrBuf, 0, InStrBufSize);
    if (InStrBuf==NULL)
    {
        return TempResult;
    }
    memcpy(InStrBuf, InputStr.toAscii().constData(), InStrBufSize);
    //2.建立输出缓冲
    //输出缓冲大小要比Ascii字节*2后多两个字节 用于标识输出字符串结尾
    size_t OutStrBufSize= (InStrBufSize+1)*sizeof(QChar);
    quint16* OutStrBuf= (quint16*)malloc(OutStrBufSize);
    if (OutStrBuf==NULL)
    {
        return TempResult;
    }
    memset(OutStrBuf, 0, OutStrBufSize);
    //3.重新编码
    size_t i= 0;
    for(i= 0; i<InStrBufSize; i++)
    {
        OutStrBuf[i]=(quint8)InStrBuf[i];
    }
    //4.数据重新组装
    TempResult= QString::fromUtf16(OutStrBuf);
    free(InStrBuf);
    free(OutStrBuf);
    return TempResult;
}


#endif // QT4_H
