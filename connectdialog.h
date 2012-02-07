#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QtGui>
#include <QtCore>
#include "ui_connectDialog.h"
class ConnectDialog : public QDialog
{
	Q_OBJECT

public:
	ConnectDialog(QWidget *parent);
	~ConnectDialog();
	
	
private:
	Ui::ui_ConnectDialog *ui;
	
};

#endif // CONNECTDIALOG_H
