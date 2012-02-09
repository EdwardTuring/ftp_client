#ifndef QT4_H
#define QT4_H

#include <QtGui>
#include <QtCore>
/*
���ͷ�ļ������˻����ĺ궨��

*/
#define CONNECT(a,b,c,d) connect(a,SIGNAL(b),c,SLOT(d))
QString FromSpecialEncoding(const QString &InputStr)
{
    QString TempResult;
    //1.��ȡ����
    size_t InStrBufSize= InputStr.size()*sizeof(QChar);
    char* InStrBuf= (char*)malloc(InStrBufSize);
    if (InStrBuf==NULL)
    {
        return TempResult;
    }
    memcpy(InStrBuf, InputStr.data(), InStrBufSize);
    //2.�������
    size_t i;
#if Q_BYTE_ORDER==Q_LITTLE_ENDIAN
    //С�˶�����(����Intel��x86�ܹ�)
    //ԭʼ�����±� 0 2 4 6 8 10
    //�޸������±� 0 1 2 3 4 5
    i= 0;
    for (i=0; i<InStrBufSize; i=i+2)
    {
        InStrBuf[i>>1]=InStrBuf[i];
    }
    memset(InStrBuf+ (i>>1), 0, i>>1);
#else
    //��˶�����
    //ԭʼ�����±� 1 3 5 7 9
    //�޸������±� 0 1 2 3 4
    i= 1;
    for (i=1; i<=InStrBufSize; i=i+2)
    {
        InStrBuf[(i-1)>>1]=InStrBuf[i];
    }
    memset(InStrBuf+ ((i-1)>>1), 0, (i-1)>>1);
#endif
    //3.����������װ
    TempResult= TempResult.fromAscii(InStrBuf);
    free(InStrBuf);
    return TempResult;
}
//=============================================================================
QString ToSpecialEncoding(const QString &InputStr)
{
    QString TempResult;
    //1.��ȡ����
    size_t InStrBufSize= InputStr.toAscii().size();
    char* InStrBuf= (char*)malloc(InStrBufSize);//= InputStr.toAscii().data();
    memset(InStrBuf, 0, InStrBufSize);
    if (InStrBuf==NULL)
    {
        return TempResult;
    }
    memcpy(InStrBuf, InputStr.toAscii().constData(), InStrBufSize);
    //2.�����������
    //��������СҪ��Ascii�ֽ�*2��������ֽ� ���ڱ�ʶ����ַ�����β
    size_t OutStrBufSize= (InStrBufSize+1)*sizeof(QChar);
    quint16* OutStrBuf= (quint16*)malloc(OutStrBufSize);
    if (OutStrBuf==NULL)
    {
        return TempResult;
    }
    memset(OutStrBuf, 0, OutStrBufSize);
    //3.���±���
    size_t i= 0;
    for(i= 0; i<InStrBufSize; i++)
    {
        OutStrBuf[i]=(quint8)InStrBuf[i];
    }
    //4.����������װ
    TempResult= QString::fromUtf16(OutStrBuf);
    free(InStrBuf);
    free(OutStrBuf);
    return TempResult;
}


#endif // QT4_H
