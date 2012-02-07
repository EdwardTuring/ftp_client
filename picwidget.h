
#include <QtCore>
#include <QtGui>
#include <QWidget>
class PicWidget:public QWidget
{
	Q_OBJECT
public:
	PicWidget(QWidget * parent = 0, Qt::WindowFlags f = 0);
	~PicWidget();
protected:
	void paintEvent(QPaintEvent *);
private:
	QPixmap *background_;


};


