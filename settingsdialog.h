#ifndef SETTINSDIALOG_H
#define SETTINSDIALOG_H
#include "ui_SettingsDialog.h"
#include <QtGui>
#include <QtCore>

class SettingsDialog : public QDialog
{
	Q_OBJECT

public:
	SettingsDialog(QWidget *parent);
	~SettingsDialog();
	protected slots:
	void addToList();
private:
	Ui::ui_SettingsDialog *ui;
};

#endif // SETTINSDIALOG_H
