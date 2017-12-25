#include "myscene.h"  

MyScene::MyScene(QObject *parent) :
	QGraphicsScene(parent)
{
	clearFocus();
}

void MyScene::setParentView(MyView &parent) {
	this->parentView = &parent;
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	m_isMousePress = true;
	posX = event->scenePos().x();
	posY = event->scenePos().y();
	if (parentView->mode == 1) {
		if (event->button() == Qt::LeftButton)
		{
			m_beginPoint = event->scenePos();
		}
	}
	if (parentView->mode == 4) {
		if (event->button() == Qt::LeftButton) {
			emit colorClick(posX, posY);
		}
	}
	QGraphicsScene::mousePressEvent(event);
}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
	posX = event->scenePos().x();
	posY = event->scenePos().y();
	if (parentView->mode == 1) { // selection mode
		if (m_isMousePress)
		{
			m_endPoint = event->scenePos();
			update();
			QRect selectedRect = getRect(m_beginPoint.toPoint(), m_endPoint.toPoint());
			QString hStr, wStr;
			hStr.sprintf("%d", selectedRect.height());
			wStr.sprintf("%d", selectedRect.width());
			parentView->parentUI->label_height->setText(hStr);
			parentView->parentUI->label_width->setText(wStr);

		}
	}
	if (parentView->mode == 2) { // pen mode
		if (m_isMousePress) {
			emit penMove(posX, posY);
		}
	}
	if (parentView->mode == 3) { // eraser mode
		if (m_isMousePress) {
			emit eraserMove(posX, posY);
		}
	}
	emit mouseMove(posX, posY);
	QString xStr, yStr;
	xStr.sprintf("%d", posX);
	yStr.sprintf("%d", posY);
	parentView->parentUI->label_posX->setText(xStr);
	parentView->parentUI->label_posY->setText(yStr);
	QGraphicsScene::mouseMoveEvent(event);  //��仰�����޾����˸��ؼ��ܷ�׽�����ؼ��������������¼�
	//Ҳ�������ӿؼ���׽�����¼��ܷ񴫵�����
}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
	//if (parentView->mode == 1) {
		m_endPoint = event->scenePos();
		m_isMousePress = false;
	//}
	QGraphicsScene::mouseReleaseEvent(event);
}

void MyScene::wheelRollEvent(QGraphicsSceneWheelEvent *event) {
	QGraphicsScene::wheelEvent(event);
}

QRect MyScene::getRect(const QPoint &beginPoint, const QPoint &endPoint) {
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
