#include "myImageLabel.h"
#include <QWidget>

void MyImageLabel::paintEvent(QPaintEvent *event){
	qDebug("fuckint paint!!!!");
	QLabel::paintEvent(event);
	QPainter painter(this);
	painter.setPen(Qt::red);
}