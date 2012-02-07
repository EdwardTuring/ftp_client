#include "connectdialog.h"

ConnectDialog::ConnectDialog(QWidget *parent)
: QDialog(parent),ui(new Ui::ui_ConnectDialog)
{
	ui->setupUi(this);
	setWindowTitle("…Ë÷√");
	 

}

ConnectDialog::~ConnectDialog()
{
	delete ui;

}
