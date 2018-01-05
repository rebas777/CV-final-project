#pragma once
#include <QGraphicsView>  
#include <QtWidgets/QMainWindow>
#include "ui_miniPS.h"

class MyView : public QGraphicsView
{
	Q_OBJECT
public:
	// mode: normal = 0, selection = 1, pen = 2, eraser = 3, color pick = 4, mosaic = 5
	int mode;
	int posX;
	int posY;

	explicit MyView(QWidget *parent = 0);
	void zoomInOut(float scale);
	void resetSize();
	void freshView();
	double getScaleVal();
	void setParentUI(Ui::miniPSClass  &parent);
	Ui::miniPSClass *parentUI;   // a view hold ptr to UIclass so that it can change UI properties without being called by UIclass

protected:
	
	double scaleVal;
	

	void keyPressEvent(QKeyEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent * event);

signals:

	public slots :

private:
	//bool m_isMousePress;
	//int m_screenwidth;
	//int m_screenheight;
	//QPoint m_beginPoint, m_endPoint;
	QPainter m_painter;
	

	QRect getRect(const QPoint &beginPoint, const QPoint &endPoint);

};