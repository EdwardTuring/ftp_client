#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
: QDialog(parent),ui(new Ui::ui_SettingsDialog)
{
	ui->setupUi(this);
	setWindowTitle("连接");
	addToList();
}
void SettingsDialog::addToList()
{
	QTreeWidgetItem *item0 = new QTreeWidgetItem;
	QTreeWidgetItem *item1 = new QTreeWidgetItem;
	QTreeWidgetItem *item2 = new QTreeWidgetItem;
	item0->setText(0,"服务器1");
	item0->setText(1,"222.31.88.7");
	
	QPixmap pixmap0(":/res/images/server.png");
	item0->setIcon(0, pixmap0);
	item1->setText(0,"服务器2");
	item1->setText(1,"222.31.88.45");
	
	QPixmap pixmap1(":/res/images/server.png");
	item2->setText(0,"服务器3");
	item2->setText(1,"222.31.88.31");

	QPixmap pixmap2(":/res/images/server.png");
	item2->setIcon(0, pixmap1);
	item1->setIcon(0,pixmap2);
	ui->server_list_->addTopLevelItem(item0);
	ui->server_list_->addTopLevelItem(item1);
	ui->server_list_->addTopLevelItem(item2);

}
SettingsDialog::~SettingsDialog()
{
	delete ui;
}
