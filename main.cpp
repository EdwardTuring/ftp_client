#include <QtGui/QApplication>
#include "mainwindow.h"

void setCodec()
{
    QTextCodec *codec = QTextCodec::codecForName("System");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
}

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    setCodec();

    QTranslator translator;

     translator.load("ftpclient_zh",".");
     app.installTranslator(&translator);
    MainWindow w;
    w.show();

    return app.exec();
}
