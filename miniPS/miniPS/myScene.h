#pragma once
#include <QGraphicsScene>  
#include <QGraphicsSceneMouseEvent>  
#include <QGraphicsSceneWheelEvent>
#include <QPaintEvent>  
#include <QKeyEvent>
#include "myView.h"

class MyScene : public QGraphicsScene {

	Q_OBJECT
public:
	explicit MyScene(QObject *parent = 0);
	void setParentView(MyView &parent);
	QPointF m_beginPoint, m_endPoint;
	QPainter m_painter;
	QRect getRect(const QPoint &beginPoint, const QPoint &endPoint);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void wheelRollEvent(QGraphicsSceneWheelEvent *event);

private:
	int posX;
	int posY;
	MyView *parentView; //scene hold ptr to a view and view hold ptr to UIclass so that scene can manipulate UIclass directly
	bool m_isMousePress;
	
signals:
	void mouseMove(int x, int y); // self-defined signal, triggered when view mouseMoveEven happen.
	void penMove(int x, int y);
	void eraserMove(int x, int y);
	void colorClick(int x, int y); // will be emit when in the color pick mode(4) and there is a click on the canvas
	
};