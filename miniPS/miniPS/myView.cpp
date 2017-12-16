#include "myView.h"  
#include "myScene.h"
#include <QKeyEvent>  

MyView::MyView(QWidget *parent) :
	QGraphicsView(parent)
{
	scaleVal = 1.00;
	setMouseTracking(true);
}

void MyView::setParentUI(Ui::miniPSClass  &parent) {
	this->parentUI = &parent;
}


//MyScene MyView::getChild() {
//	return child_scene;
//}
//
//void MyView::setChild(const MyScene &scene) {
//	child_scene = scene;
//}

void MyView::zoomInOut(float scale)
{
	if (scaleVal <= 0.2 && scale < 1) {
		return;
	}
	else if (scaleVal >= 10 && scale > 1) {
		return;
	}
	this->scale(scale, scale);
	scaleVal *= scale;
}

//to make sure when you load a new image in proper size after zooming on the previous image.
void MyView::resetSize() {
	this->scale(1 / scaleVal, 1 / scaleVal);
	scaleVal = 1.00;
}

void MyView::freshView() {
	this->scale(2, 2);
	this->scale(0.5, 0.5);
}

double MyView::getScaleVal() {
	return scaleVal;
}

void MyView::keyPressEvent(QKeyEvent *event)
{
	qDebug("*********MyView::keyPressEvent***************");
	switch (event->key())
	{
	case Qt::Key_Left:
		scale(1.2, 1.2);
		break;
	case Qt::Key_Right:
		scale(1 / 1.2, 1 / 1.2);
		break;
	case Qt::Key_Up:
		rotate(30);
		break;
	}
	QGraphicsView::keyPressEvent(event);
}

void MyView::mousePressEvent(QMouseEvent *event)
{
	/*if (mode == 1) {
		if (event->button() == Qt::LeftButton)
		{
			m_isMousePress = true;
			m_beginPoint = event->pos();
		}
	}*/
	QGraphicsView::mousePressEvent(event);
}

void MyView::mouseMoveEvent(QMouseEvent *event)
{
	//if (mode == 1) {
	//	if (m_isMousePress)
	//	{
	//		m_endPoint = event->pos();
	//		update();
	//		m_painter.setPen(Qt::red);
	//		QRect selectedRect = getRect(m_beginPoint, m_endPoint);
	//		m_painter.drawRect(selectedRect);
	//	}
	//}
	//posX = event->pos().x();
	//posY = event->pos().y();
	//QString xStr, yStr;
	//xStr.sprintf("%d", posX);                 //用这种方法得到的view窗口的坐标，与里面的scene无关了
	//yStr.sprintf("%d", posY);
	//parentUI->label_posX->setText(xStr);
	//parentUI->label_posY->setText(yStr);
	QGraphicsView::mouseMoveEvent(event);
}

void MyView::mouseReleaseEvent(QMouseEvent *event)
{
	/*if (mode == 1) {
		m_endPoint = event->pos();
		m_isMousePress = false;
	}*/
	QGraphicsView::mouseReleaseEvent(event);
}

void MyView::paintEvent(QPaintEvent *event)
{
	if (mode == 1) {
		/*MyScene *child = (MyScene *)this->scene();
		child->m_painter.begin(m_pixmap);
		child->m_painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::FlatCap));
		qDebug("fucking paint !!!!");
		child->m_painter.drawRect(child->getRect(child->m_beginPoint.toPoint(),child->m_endPoint.toPoint()));
		child->m_painter.end();*/

		//TODO: make painted rectangle above the picture !
		m_painter.begin(this->viewport());
		QPoint beginPoint, endPoint;
		MyScene *child = (MyScene *)this->scene();
		beginPoint = mapFromScene(child->m_beginPoint);
		endPoint = mapFromScene(child->m_endPoint);
		m_painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::FlatCap));
		QRect tmpRect = getRect(beginPoint, endPoint);
		m_painter.drawRect(tmpRect);
		qDebug("do paint !!!!");
		m_painter.end();
	}
	QGraphicsView::paintEvent(event);
}

QRect MyView::getRect(const QPoint &beginPoint, const QPoint &endPoint) {
	int x, y, width, height;
	width = qAbs(beginPoint.x() - endPoint.x());
	height = qAbs(beginPoint.y() - endPoint.y());
	x = beginPoint.x() < endPoint.x() ? beginPoint.x() : endPoint.x();
	y = beginPoint.y() < endPoint.y() ? beginPoint.y() : endPoint.y();

	QRect selectedRect = QRect(x, y, width, height);
	if (selectedRect.width() == 0)
	{
		selectedRect.setWidth(2);
	}
	if (selectedRect.height() == 0)
	{
		selectedRect.setHeight(2);
	}

	return selectedRect;
}

