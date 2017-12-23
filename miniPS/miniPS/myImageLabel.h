#pragma once
#include <QWidget>
#include <QLabel>
#include <QtWidgets/QMainWindow>
#include <QGraphicsView>  
#include <QPaintEvent>
#include "ui_miniPS.h"

class MyImageLabel : public QLabel {

	Q_OBJECT
public:
	MyImageLabel(QWidget *parent = 0) : QLabel(parent) {};
	~MyImageLabel() {};
	int A = 127, B = 127, C = 127, D = 127;

protected:
	void paintEvent(QPaintEvent *event);
};
