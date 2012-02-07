#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtGui>
#include <QFtp>
#include "ui_mainwindow.h"
#include "connectdialog.h"
#include "settingsdialog.h"
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected slots:
    void connectToFtpServer();
    void loginToFtpServer();
    void ftpCommandFinished(int, bool error);

    void addList(const QUrlInfo &urlInfo);
    void processItem(QTreeWidgetItem *item, int /*column*/);

    void test(const QUrlInfo &info);
    void cdToParent();
	void 	itemChoosed ( QTreeWidgetItem * item, int column );
	void downloadFile();
	void updateDataTransferProgress(qint64 readBytes,qint64 totalBytes);


	//œ‘ æ∂‘ª∞øÚ£∫
	void showConnectDialog();
	void showSettingDialog();

private:
    void handleConfig();
    void readConfig(const QSettings &config);
    void writeDefualtConfig(QSettings &config);
	
 private:

    Ui::MainWindow *ui;
	ConnectDialog *connectdialog_;
	SettingsDialog *settingdialog_;
    QHash<QString, bool> isDirectory;
    QString currentPath;
    QFtp *ftp_;

    QString hostname_;
    QString usrname_;
    QString pwd_;
    uint port_;
	QFile *file_;

};

#endif // MAINWINDOW_H
