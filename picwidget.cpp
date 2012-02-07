#include "picwidget.h"
#include <QWidget>
PicWidget::PicWidget(QWidget *parent,Qt::WindowFlags f):QWidget(parent,f)
{
	this->background_=new QPixmap(":res/images/background.jpg");
	
	
	

}
PicWidget::~PicWidget()
{
	delete background_;

}
void PicWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	
	painter.drawPixmap(0,0,700,120,*(this->background_));
	
}