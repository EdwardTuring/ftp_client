#include "mainwindow.h"
#include "ui_connectDialog.h"
#include "ui_SettingsDialog.h"
#include "qt4.h"
//244 244 244






MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);
	ui->progress_bar_->hide();
    this->handleConfig();
	this->connectdialog_=new ConnectDialog(this);
	this->settingdialog_=new SettingsDialog(this);
	
    connect(ui->file_tree_, SIGNAL(itemActivated(QTreeWidgetItem*,int)),
               this, SLOT(processItem(QTreeWidgetItem*,int)));
	CONNECT(ui->file_tree_,	itemClicked ( QTreeWidgetItem *, int  ),this,itemChoosed(QTreeWidgetItem *, int));
    CONNECT(ui->btn_cd_to_parent_,clicked(),this,cdToParent());
	CONNECT(ui->btn_download_,clicked(),this,downloadFile());
	CONNECT(ui->btn_settings_,clicked(),this,showConnectDialog());
	CONNECT(ui->act_connect_to_,triggered(),this,showSettingDialog());
	this->setWindowTitle("����������ý����Ƶ���ݹ���ƽ̨");   
	connectToFtpServer();


}
void MainWindow::showConnectDialog()
	{

		this->connectdialog_->show();
	}
void MainWindow::showSettingDialog()
{

	this->settingdialog_->show();
}
void MainWindow::test(const QUrlInfo &info)
{
    QMessageBox::about(NULL,"",QString::number(info.size()));
}

MainWindow::~MainWindow()
{
    delete ui;
	
}

void MainWindow::connectToFtpServer()
{

    ftp_=new QFtp(this);



  connect(ftp_, SIGNAL(listInfo(QUrlInfo)),
                  this, SLOT(addList(QUrlInfo)));
  connect(ftp_, SIGNAL(commandFinished(int,bool)),
              this, SLOT(ftpCommandFinished(int,bool)));
  connect(ftp_, SIGNAL(dataTransferProgress(qint64,qint64)),
	  this, SLOT(updateDataTransferProgress(qint64,qint64)));

  ftp_->connectToHost(this->hostname_);
  ftp_->login();
    ui->file_tree_->setEnabled(true);

}
void MainWindow::loginToFtpServer()
{
    ftp_->login(this->usrname_,this->pwd_);

}

void MainWindow::ftpCommandFinished(int, bool error)
{
    if (ftp_->currentCommand() == QFtp::ConnectToHost) {
        if (error) {
            QMessageBox::information(this, tr("FTP"),
                                     "�޷����ӵ�FTP������ ");

            return;
        }
        ui->status_->setText("�����ӵ� "+this->hostname_);
        ui->file_tree_->setFocus();


        return;
    }

    if (ftp_->currentCommand() == QFtp::Login){
        ftp_->list();


}
    if (ftp_->currentCommand() == QFtp::Get)
    {
		if (error) {
			ui->status_->setText("�޷����� "+(file_->fileName()));
			file_->close();
			file_->remove();
		} else {
			ui->status_->setText("�������� "+(file_->fileName())+" ����ǰĿ¼...");
			file_->close();
		}
		delete file_;
		ui->btn_download_->setEnabled(false);
		ui->progress_bar_->hide();

    }
    else if (ftp_->currentCommand() == QFtp::List)
    {
        if (isDirectory.isEmpty())
        {
            ui->file_tree_->addTopLevelItem(new QTreeWidgetItem(QStringList() << "(��)"));
           ui->file_tree_->setEnabled(false);
        }
    }
}
void MainWindow::handleConfig()
{
    bool config_exist_=QFile::exists("config.ini");

    if(config_exist_)
    {
         QSettings config("config.ini",QSettings::IniFormat);
          config.setIniCodec(QTextCodec::codecForName("System"));

        //��ȡ�����ļ������ݣ�
        readConfig(config);
    }
    else
    {
         QSettings config("config.ini",QSettings::IniFormat);
          config.setIniCodec(QTextCodec::codecForName("System"));
         //д��Ĭ�ϵ����ã�
         writeDefualtConfig(config);
         readConfig(config);
    }
}

void MainWindow::readConfig(const QSettings &config)
{


  this->hostname_=config.value("FTP/hostname").toString();
   this->usrname_=config.value("FTP/usrname").toString();
     this->pwd_=config.value("FTP/pwd").toString();
    this->port_=config.value("FTP/port").toUInt();
}

void MainWindow::writeDefualtConfig(QSettings &config)
{
    QString keys[]={"hostname","port","usrname","pwd"};
    QMap<QString,QString> attribute;
    attribute["hostname"]="127.0.0.1";
    attribute["port"]="21";
    attribute["usrname"]="";
    attribute["pwd"]="";

    for(int i=0;i<attribute.size();i++)
    {
        config.setValue("FTP/"+keys[i], attribute.value(keys[i]));

    }
}
void MainWindow::addList(const QUrlInfo &urlInfo)
{

    QTreeWidgetItem *item = new QTreeWidgetItem;

    item->setText(0, QString::fromUtf8(urlInfo.name().toLatin1()));
    qint64 thesize=urlInfo.size();
	QString sizestr;
	//�ж��ļ��Ĵ�С����ȷ���䵥λ
	//{
	if(urlInfo.isDir () )
	{

		sizestr=" ";
	}
	else{
	if(thesize>=1024)
		sizestr=QString::number(thesize/1024)+" KB";
	else if(thesize>=1024*1024)
		sizestr=QString::number(thesize/(1024*1024))+" MB";
	else if(thesize>=1024*1024*1024)
			sizestr=QString::number(thesize/(1024*1024))+" GB";
	else 
	{
		sizestr=QString::number(thesize)+" �ֽ�";

	}
	}
		//}
	item->setText(1, sizestr);

	item->setText(2, urlInfo.lastModified().toString("yyyy��M��dd�� hh:mm:ss"));

    QPixmap pixmap(urlInfo.isDir() ? ":res/images/filefolder.png" : ":res/images/file.png");
    item->setIcon(0, pixmap);

    isDirectory[urlInfo.name()] = urlInfo.isDir();
    ui->file_tree_->addTopLevelItem(item);
    if (!ui->file_tree_->currentItem()) {
        ui->file_tree_->setCurrentItem(ui->file_tree_->topLevelItem(0));
        ui->file_tree_->setEnabled(true);
    }

}
void MainWindow::processItem(QTreeWidgetItem *item, int /*column*/)
{
    QString name = item->text(0);
    if (isDirectory.value(name)) {
        ui->file_tree_->clear();
        isDirectory.clear();
        currentPath += '/';
        currentPath += name;
        ftp_->cd(name);
        ftp_->list();

        return;
    }
}
void MainWindow::cdToParent()
{
    ui->file_tree_->clear();
    isDirectory.clear();
    currentPath = currentPath.left(currentPath.lastIndexOf('/'));
    if (currentPath.isEmpty())
    {
       // ui->btn_cd_to_parent_->setEnabled(false);
        ftp_->cd("/");
    }
    else
        ftp_->cd(currentPath);

    ftp_->list();
}
void MainWindow::itemChoosed( QTreeWidgetItem * item, int column )
{

	ui->file_tree_->setCurrentItem(item);
	
}
void MainWindow::downloadFile()
{
	QString fileName = ui->file_tree_->currentItem()->text(0);
	
		file_ = new QFile(fileName);
	if (!file_->open(QIODevice::WriteOnly)) {
		QMessageBox::information(this, tr("FTP"),"�޷������ļ��� "+(fileName+file_->errorString()));
		delete file_;
		return;
	}

	ftp_->get(ui->file_tree_->currentItem()->text(0), file_);


		ui->progress_bar_->show();
	
	
}
void MainWindow::updateDataTransferProgress(qint64 readBytes,
										   qint64 totalBytes)
{
	ui->progress_bar_->setMaximum(totalBytes);
	ui->progress_bar_->setValue(readBytes);
}