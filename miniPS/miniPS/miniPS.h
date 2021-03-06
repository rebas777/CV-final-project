#pragma once

#include <QtWidgets/QMainWindow>
#include <QDesktopServices>
#include "ui_miniPS.h"
#include "myView.h"
#include "myScene.h"
#include "QFileDialog"
#include "QMessageBox"
#include "imageProcessor.h"
#include "myImageLabel.h"

#define NLAYERS 5
#define ZOOM_IN_RATE 1.2
#define ZOOM_OUT_RATE 0.8
#define ZOOM_MAX 1000 //1000% by origin
#define ZOOM_MIN 20   //20% by origin
#define ZOOM_STEP 20  //zoom step used by slider
#define HSV_H_MAX 359
#define HSV_H_MIN 0
#define HSV_S_MAX 255
#define HSV_S_MIN -255
#define HSV_V_MAX 255
#define HSV_V_MIN -255
#define HSV_STEP 20

class miniPS : public QMainWindow
{
	Q_OBJECT
			
public:
	miniPS(QWidget *parent = Q_NULLPTR);
	~miniPS();

private:
	Ui::miniPSClass ui;
	double **sobelX;
	double **sobelY;
	double **laplace;

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
	// Picked colors
	std::vector<int> color1, color2;

	int mophoCurTab;

	void refreshImg();

	Mat parseInputKernel();


private slots:
void on_slotUndo_trigged();
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
void on_slotPenMode_trigged();
void on_slotMosaicMode_trigged();
void on_slotEraserMode_trigged();
void on_slotPickMode_trigged();
void on_slotNormMode_trigged();
void on_slotCutBtn_trigged();
void on_slotClean_trigged();
void on_viewMouseMove_trigged(int x, int y);  // Self-defined slot
void on_viewPenMove_trigged(int x, int y); // Self-defined slot
void on_viewEraserMove_trigged(int x, int y); // Self-defined slot
void on_viewColorClick_trigged(int x, int y); // Self-defined slot
void on_viewMosaicMove_trigged(int x, int y); // Self-defined slot
void on_channelSplitR_trigged();
void on_channelSplitG_trigged();
void on_channelSplitB_trigged();
void on_rgb2gry_trigged();
void on_slotHSV_trigged();
void on_slotHSVok_trigged();
void on_slotHSVslidH_trigged(int cur);
void on_slotHSVslidS_trigged(int cur);
void on_slotHSVslidV_trigged(int cur);
void on_slotDbTh_trigged();
void on_slotDbThok_trigged();
void on_slotOtsu_trigged();
void on_slotBinEx();
void on_slotAdd_trigged();
void on_slotSubtraction_trigged();
void on_slotMultiplication_trigged();
void on_slotDivision_trigged();
void on_addOk_trigged();
void on_subOk_trigged();
void on_multiOk_trigged();
void on_dvdOk_trigged();
void on_slotResize_trigged();
void on_resizeOk_trigged();
void on_slotSpin_trigged();
void on_slotRHist_trigged();
void on_slotGHist_trigged();
void on_slotBHist_trigged();
void on_slotHistEqualization();
void on_slotFilter_trigged();
void on_filterOk_trigged();
void on_selfFilter_trigged();
void on_selfFilterOk_trigged();
void on_slotRotate_trigged();
void on_rotateOk_trigged();
void on_slotGSALinear_trigged();
void on_slotGSAExpLog_trigged();
void on_GSALinearSlid(int cur);
void on_GSAOk_trigged();
void on_UGSAOk_trigged();
void on_slotSobelX_trigged();
void on_slotSobelY_trigged();
void on_slotSobelXY_trigged();
void on_slotLaplace_trigged();
void on_slotCanny_trigged();
void on_slotHelloWorld_trigged();
void on_slotColorExchange();
void in_slotColorReset();
void on_slotHoughLine();
void in_slotHoughCircle();
void on_slotMophology_trigged();
void on_slotMophoTabChange(int cur);
void on_slotDilation();
void on_slotErosion();
void on_slotOpen();
void on_slotClose();
void on_slotThinning();
void on_slotThickening();
void on_slotSkeleton();
void on_slotSkeletonRecon();
void on_slotDistanceTrans();
void on_slotBinRecon();
void on_slotGrayRecon();
void on_slotWatershed();

void openUrl(QString url);


void on_slotMinMax();
void on_slotPseudoColor();
void on_slotSharpen();


void on_slotLadder_trigged();
void on_ladderOk_trigged();

};
