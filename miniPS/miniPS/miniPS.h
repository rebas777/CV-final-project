#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_miniPS.h"
#include "myView.h"
#include "myScene.h"
#include "QFileDialog"
#include "QMessageBox"
#include "imageProcessor.h"

#define NLAYERS 5
#define ZOOM_IN_RATE 1.2
#define ZOOM_OUT_RATE 0.8
#define ZOOM_MAX 1000 //1000% by origin
#define ZOOM_MIN 20   //20% by origin
#define ZOOM_STEP 20  //zoom step used by slider

class miniPS : public QMainWindow
{
	Q_OBJECT
			
public:
	miniPS(QWidget *parent = Q_NULLPTR);
	~miniPS();

private:
	Ui::miniPSClass ui;

	// Which layer are the user looking at
	int focusedLayer;
	// List of images
	//QImage *images[NLAYERS];
	// List of containers to hold images
	MyView *myViews[NLAYERS];
	// List to record whether a layer is modified and unsaved
	int imagesDirtyFlag[NLAYERS];
	// Image processor to process all image operations
	ImageProcessor myProcessor;

	void refreshImg();


private slots:
void on_slotTabChang_trigged(int cur);
void on_slotLoadImage_trigged();
void on_slotExit_trigged();
void on_slotWinModeFull_trigged();
void on_slotWinModeWined_trigged();
void on_slotZoomIn_trigged();
void on_slotZoomOut_trigged();
void on_slotMin_trigged();
void on_slotSave_trigged();
void on_slotZoomSlid(int cur);
void on_slotFreshScalVal();
void on_slotSlctMode_trigged();
void on_slotNormMode_trigged();
void on_slotCutBtn_trigged();
void on_slotClean_trigged();
void on_viewMouseMove_trigged(int x, int y);  // Self-defined slot
};