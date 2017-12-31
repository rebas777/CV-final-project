#include "miniPS.h"



miniPS::miniPS(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	showMaximized();

	// Hide some components
	ui.hsvWidget->setVisible(false);
	ui.doubleThreshodWidget->setVisible(false);
	ui.addWidget->setVisible(false);
	ui.subtractionWidget->setVisible(false);
	ui.multiplicationWidget->setVisible(false);
	ui.divisionWidget->setVisible(false);
	ui.resizeWidget->setVisible(false);
	ui.filterWidget->setVisible(false);
	ui.rotateWidget->setVisible(false);
	ui.GSAWidget->setVisible(false);
	ui.UGSAWidget->setVisible(false);
	ui.selfFilterWidget->setVisible(false);
	ui.MophologyWidget->setVisible(false);

	//init focused layer
	focusedLayer = 0;
	mophoCurTab = 0;

	// Initialize picked color
	color1 = { 0,0,0 };
	color2 = { 255,255,255 };

	//init 5 views
	myViews[0] = new MyView();
	myViews[0]->setParentUI(ui);
	ui.scrollArea->setWidget(myViews[0]);
	myViews[1] = new MyView();
	myViews[1]->setParentUI(ui);
	ui.scrollArea_2->setWidget(myViews[1]);
	myViews[2] = new MyView();
	myViews[2]->setParentUI(ui);
	ui.scrollArea_3->setWidget(myViews[2]);
	myViews[3] = new MyView();
	myViews[3]->setParentUI(ui);
	ui.scrollArea_4->setWidget(myViews[3]);
	myViews[4] = new MyView();
	myViews[4]->setParentUI(ui);
	ui.scrollArea_5->setWidget(myViews[4]);

	//init 5 images
	for (int i = 0; i < NLAYERS; i++) {
		//this->images[i] = new QImage();
		this->imagesDirtyFlag[i] = 0;
	}

	//init picked color
	ui.picked_color1->setStyleSheet("QLabel { background-color : white; color : blue; }");
	ui.picked_color2->setStyleSheet("QLabel { background-color : black; color : blue; }");

	//connect button control
	connect(ui.tabWidget, SIGNAL(currentChanged(int)), this, SLOT(on_slotTabChang_trigged(int)));
	connect(ui.tabWidget_2, SIGNAL(currentChanged(int)), this, SLOT(on_slotMophoTabChange(int)));
	connect(ui.actionopen_image, SIGNAL(triggered()), this, SLOT(on_slotLoadImage_trigged()));
	connect(ui.actionexit,SIGNAL(triggered()),this,SLOT(on_slotExit_trigged()));
	connect(ui.actionminimize, SIGNAL(triggered()), this, SLOT(on_slotMin_trigged()));
	connect(ui.actionfull_screen, SIGNAL(triggered()), this, SLOT(on_slotWinModeFull_trigged()));
	connect(ui.actionwindowed, SIGNAL(triggered()), this, SLOT(on_slotWinModeWined_trigged()));
	connect(ui.actionsave_image, SIGNAL(triggered()), this, SLOT(on_slotSave_trigged()));
	connect(ui.zoomOutBtn, SIGNAL(clicked()), this, SLOT(on_slotZoomOut_trigged()));
	connect(ui.zoomInBtn, SIGNAL(clicked()), this, SLOT(on_slotZoomIn_trigged()));
	connect(ui.horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(on_slotZoomSlid(int)));
	connect(ui.horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(on_slotFreshScalVal()));
	connect(ui.zoomOutBtn, SIGNAL(clicked()), this, SLOT(on_slotFreshScalVal()));
	connect(ui.zoomInBtn, SIGNAL(clicked()), this, SLOT(on_slotFreshScalVal()));
	connect(ui.normalModeBtn, SIGNAL(clicked()), this, SLOT(on_slotNormMode_trigged()));
	connect(ui.slctModeBtn, SIGNAL(clicked()), this, SLOT(on_slotSlctMode_trigged()));
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(on_slotPenMode_trigged()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(on_slotEraserMode_trigged()));
	connect(ui.getColorBtn, SIGNAL(clicked()), this, SLOT(on_slotPickMode_trigged()));
	connect(ui.cutBtn, SIGNAL(clicked()), this, SLOT(on_slotCutBtn_trigged()));
	connect(ui.actionclean_all_layers, SIGNAL(triggered()), this, SLOT(on_slotClean_trigged()));
	connect(ui.actionRed, SIGNAL(triggered()), this, SLOT(on_channelSplitR_trigged()));
	connect(ui.actionGreen, SIGNAL(triggered()), this, SLOT(on_channelSplitG_trigged()));
	connect(ui.actionBlue, SIGNAL(triggered()), this, SLOT(on_channelSplitB_trigged()));
	connect(ui.actionundo, SIGNAL(triggered()), this, SLOT(on_slotUndo_trigged()));
	connect(ui.actionRGB2GrayScale, SIGNAL(triggered()), this, SLOT(on_rgb2gry_trigged()));
	connect(ui.actionHSB, SIGNAL(triggered()), this, SLOT(on_slotHSV_trigged()));
	connect(ui.HSVokBtn, SIGNAL(clicked()), this, SLOT(on_slotHSVok_trigged()));
	connect(ui.horizontalSlider_h, SIGNAL(valueChanged(int)), this, SLOT(on_slotHSVslidH_trigged(int)));
	connect(ui.horizontalSlider_s, SIGNAL(valueChanged(int)), this, SLOT(on_slotHSVslidS_trigged(int)));
	connect(ui.horizontalSlider_v, SIGNAL(valueChanged(int)), this, SLOT(on_slotHSVslidV_trigged(int)));
	connect(ui.actionOtus_Algo, SIGNAL(triggered()), this, SLOT(on_slotOtsu_trigged()));
	connect(ui.actiondouble_threshod, SIGNAL(triggered()), this, SLOT(on_slotDbTh_trigged()));
	connect(ui.doubleThreshodOkBtn, SIGNAL(clicked()), this, SLOT(on_slotDbThok_trigged()));
	connect(ui.addBtn, SIGNAL(clicked()), this, SLOT(on_slotAdd_trigged()));
	connect(ui.subtractionBtn, SIGNAL(clicked()), this, SLOT(on_slotSubtraction_trigged()));
	connect(ui.multiplicationBtn, SIGNAL(clicked()), this, SLOT(on_slotMultiplication_trigged()));
	//connect(ui.divisionBtn, SIGNAL(clicked()), this, SLOT(on_slotDivision_trigged()));
	connect(ui.addOkBtn, SIGNAL(clicked()), this, SLOT(on_addOk_trigged()));
	connect(ui.substractionOkBtn, SIGNAL(clicked()), this, SLOT(on_subOk_trigged()));
	connect(ui.multiplicationOkBtn, SIGNAL(clicked()), this, SLOT(on_multiOk_trigged()));
	//connect(ui.divisionOkBtn, SIGNAL(clicked()), this, SLOT(on_dvdOk_trigged()));
	connect(ui.actionresize, SIGNAL(triggered()), this, SLOT(on_slotResize_trigged()));
	connect(ui.resizeOkBtn, SIGNAL(clicked()), this, SLOT(on_resizeOk_trigged()));
	connect(ui.spinBtn, SIGNAL(clicked()), this, SLOT(on_slotSpin_trigged()));
	connect(ui.actionR_hist, SIGNAL(triggered()), this, SLOT(on_slotRHist_trigged()));
	connect(ui.actionG_hist, SIGNAL(triggered()), this, SLOT(on_slotGHist_trigged()));
	connect(ui.actionB_hist, SIGNAL(triggered()), this, SLOT(on_slotBHist_trigged()));
	connect(ui.actionEqualization, SIGNAL(triggered()), this, SLOT(on_slotHistEqualization()));
	connect(ui.actionfilter_2, SIGNAL(triggered()), this, SLOT(on_slotFilter_trigged()));
	connect(ui.filterOkBtn, SIGNAL(clicked()), this, SLOT(on_filterOk_trigged()));
	connect(ui.actionrotate, SIGNAL(triggered()), this, SLOT(on_slotRotate_trigged()));
	connect(ui.rotateOkBtn, SIGNAL(clicked()), this, SLOT(on_rotateOk_trigged()));
	connect(ui.actionlinear, SIGNAL(triggered()), this, SLOT(on_slotGSALinear_trigged()));
	connect(ui.GSALinearOkBtn, SIGNAL(clicked()), this, SLOT(on_GSAOk_trigged()));
	connect(ui.GSASliderA, SIGNAL(valueChanged(int)), this, SLOT(on_GSALinearSlid(int)));
	connect(ui.GSASliderB, SIGNAL(valueChanged(int)), this, SLOT(on_GSALinearSlid(int)));
	connect(ui.GSASliderC, SIGNAL(valueChanged(int)), this, SLOT(on_GSALinearSlid(int)));
	connect(ui.GSASliderD, SIGNAL(valueChanged(int)), this, SLOT(on_GSALinearSlid(int)));
	connect(ui.UGSAOkBtn, SIGNAL(clicked()), this, SLOT(on_UGSAOk_trigged()));
	connect(ui.actionexp_log, SIGNAL(triggered()), this, SLOT(on_slotGSAExpLog_trigged()));
	connect(ui.action3_3_self_define, SIGNAL(triggered()), this, SLOT(on_selfFilter_trigged()));
	connect(ui.selfFilterOkBtn, SIGNAL(clicked()), this, SLOT(on_selfFilterOk_trigged()));
	connect(ui.actionsobelX, SIGNAL(triggered()), this, SLOT(on_slotSobelX_trigged()));
	connect(ui.actionsobelY, SIGNAL(triggered()), this, SLOT(on_slotSobelY_trigged()));
	connect(ui.actionsobelXY, SIGNAL(triggered()), this, SLOT(on_slotSobelXY_trigged()));
	connect(ui.actionlaplace, SIGNAL(triggered()), this, SLOT(on_slotLaplace_trigged()));
	connect(ui.actioncanny, SIGNAL(triggered()), this, SLOT(on_slotCanny_trigged()));
	connect(ui.helloWorldBtn, SIGNAL(clicked()), this, SLOT(on_slotHelloWorld_trigged()));
	connect(ui.colorSwitchBtn, SIGNAL(clicked()), this, SLOT(on_slotColorExchange()));
	connect(ui.colorResetBtn, SIGNAL(clicked()), this, SLOT(in_slotColorReset()));
	connect(ui.actionhoughLine, SIGNAL(triggered()), this, SLOT(on_slotHoughLine()));
	connect(ui.actionhoughCircle, SIGNAL(triggered()), this, SLOT(in_slotHoughCircle()));
	connect(ui.actionmophology, SIGNAL(triggered()), this, SLOT(on_slotMophology_trigged()));
	connect(ui.dilationBtn, SIGNAL(clicked()), this, SLOT(on_slotDilation()));
	connect(ui.erosionBtn, SIGNAL(clicked()), this, SLOT(on_slotErosion()));
	connect(ui.openBtn, SIGNAL(clicked()), this, SLOT(on_slotOpen()));
	connect(ui.closeBtn, SIGNAL(clicked()), this, SLOT(on_slotClose()));
	connect(ui.thinningBtn, SIGNAL(clicked()), this, SLOT(on_slotThinning()));
	connect(ui.thickeningBtn, SIGNAL(clicked()), this, SLOT(on_slotThickening()));
	connect(ui.distanceBtn, SIGNAL(clicked()), this, SLOT(on_slotDistanceTrans()));
	connect(ui.skeletonBtn, SIGNAL(clicked()), this, SLOT(on_slotSkeleton()));
	connect(ui.SkeletonReconBtn, SIGNAL(clicked()), this, SLOT(on_slotSkeletonRecon()));
	connect(ui.binReconBtn, SIGNAL(clicked()), this, SLOT(on_slotBinRecon()));
	connect(ui.reconstructionBtn, SIGNAL(clicked()), this, SLOT(on_slotGrayRecon()));
	connect(ui.watershedBtn, SIGNAL(clicked()), this, SLOT(on_slotWatershed));


	// Set shortcut for menu
	ui.actionsave_image->setShortcut(Qt::CTRL | Qt::Key_S);
	ui.actionopen_image->setShortcut(Qt::CTRL | Qt::Key_L);
	ui.actionundo->setShortcut(Qt::CTRL | Qt::Key_Z);

	// Set zoom slider
	ui.horizontalSlider->setOrientation(Qt::Horizontal);
	ui.horizontalSlider->setMaximum(ZOOM_MAX);
	ui.horizontalSlider->setMinimum(ZOOM_MIN);
	ui.horizontalSlider->setSingleStep(ZOOM_STEP);
	ui.horizontalSlider->setTickInterval(50);
	ui.horizontalSlider->setTickPosition(QSlider::TicksAbove);

	// Set GSA linear dslider
	ui.GSASliderA->setMaximum(254);
	ui.GSASliderA->setMinimum(1);
	ui.GSASliderA->setSingleStep(10);
	ui.GSASliderB->setMaximum(254);
	ui.GSASliderB->setMinimum(1);
	ui.GSASliderB->setSingleStep(10);
	ui.GSASliderC->setMaximum(254);
	ui.GSASliderC->setMinimum(1);
	ui.GSASliderC->setSingleStep(10);
	ui.GSASliderD->setMaximum(254);
	ui.GSASliderD->setMinimum(1);
	ui.GSASliderD->setSingleStep(10);

	// Set HSV slider
	ui.horizontalSlider_h->setOrientation(Qt::Horizontal);
	ui.horizontalSlider_s->setOrientation(Qt::Horizontal);
	ui.horizontalSlider_v->setOrientation(Qt::Horizontal);
	ui.horizontalSlider_h->setMaximum(HSV_H_MAX);
	ui.horizontalSlider_h->setMinimum(HSV_H_MIN);
	ui.horizontalSlider_h->setSingleStep(HSV_STEP);
	ui.horizontalSlider_s->setMaximum(HSV_S_MAX);
	ui.horizontalSlider_s->setMinimum(HSV_S_MIN);
	ui.horizontalSlider_s->setSingleStep(HSV_STEP);
	ui.horizontalSlider_v->setMaximum(HSV_V_MAX);
	ui.horizontalSlider_v->setMinimum(HSV_V_MIN);
	ui.horizontalSlider_v->setSingleStep(HSV_STEP);
	ui.horizontalSlider_h->setTickInterval(30);
	ui.horizontalSlider_h->setTickPosition(QSlider::TicksAbove);
	ui.horizontalSlider_s->setTickInterval(30);
	ui.horizontalSlider_s->setTickPosition(QSlider::TicksAbove);
	ui.horizontalSlider_v->setTickInterval(30);
	ui.horizontalSlider_v->setTickPosition(QSlider::TicksAbove);

	// Initialize edge detection kernel
	double **kernel;
	sobelX = (double **)malloc(3 * sizeof(double*));
	sobelY = (double **)malloc(3 * sizeof(double*));
	laplace = (double **)malloc(3 * sizeof(double*));
	for (int i = 0; i < 3; i++) {
		sobelX[i] = (double *)malloc(3 * sizeof(double));
		sobelY[i] = (double *)malloc(3 * sizeof(double));
	    laplace[i] = (double *)malloc(3 * sizeof(double));
	}
	sobelX[0][0] = -1;
	sobelX[0][1] = 0;
	sobelX[0][2] = 1;
	sobelX[1][0] = -2;
	sobelX[1][1] = 0;
	sobelX[1][2] = 2;
	sobelX[2][0] = -1;
	sobelX[2][1] = 0;
	sobelX[2][2] = 1;
	sobelY[0][0] = 1;
	sobelY[0][1] = 2;
	sobelY[0][2] = 1;
	sobelY[1][0] = 0;
	sobelY[1][1] = 0;
	sobelY[1][2] = 0;
	sobelY[2][0] = -1;
	sobelY[2][1] = -2;
	sobelY[2][2] = -1;
	laplace[0][0] = 0;
	laplace[0][1] = 1;
	laplace[0][2] = 0;
	laplace[1][0] = 1;
	laplace[1][1] = -4;
	laplace[1][2] = 1;
	laplace[2][0] = 0;
	laplace[2][1] = 1;
	laplace[2][2] = 0;

	setMouseTracking(true);
	ui.centralWidget->setMouseTracking(true);
}

miniPS::~miniPS() {
	for (int i = 0; i < NLAYERS; i++) {
		delete this->myViews[i];
	}
}


QImage cvMat2QImage(const Mat& mat)
{
	// 8-bits unsigned, NO. OF CHANNELS = 1  
	if (mat.type() == CV_8UC1)
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		// Set the color table (used to translate colour indexes to qRgb values)  
		image.setColorCount(256);
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		// Copy input Mat  
		uchar *pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
	// 8-bits unsigned, NO. OF CHANNELS = 3  
	else if (mat.type() == CV_8UC3)
	{
		// Copy input Mat  
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat  
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if (mat.type() == CV_8UC4)
	{
		//qDebug() << "CV_8UC4";
		// Copy input Mat  
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat  
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
		//qDebug() << "ERROR: Mat could not be converted to QImage.";
		return QImage();
	}
}

Mat QImage2cvMat(QImage image)
{
	cv::Mat mat;
	//qDebug() << image.format();
	switch (image.format())
	{
	case QImage::Format_ARGB32:
	case QImage::Format_RGB32:
	case QImage::Format_ARGB32_Premultiplied:
		mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
		break;
	case QImage::Format_RGB888:
		mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
		cv::cvtColor(mat, mat, CV_BGR2RGB);
		break;
	case QImage::Format_Indexed8:
		mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
		break;
	}
	return mat;
}

// When load image
void miniPS::on_slotLoadImage_trigged() {
	if (imagesDirtyFlag[focusedLayer] == 1) {
		QMessageBox::StandardButton rb = QMessageBox::question(NULL,
			"Unsaved Image", "Do you want to load new image without saving the old one ?",
			QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
		if (rb == QMessageBox::No)
			return;
	}
	QString fileName = QFileDialog::getOpenFileName(
		this, "open image file",
		".",
		"Image files (*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)");
	if (fileName != "")
	{
		    
			myProcessor.loadImage(qPrintable(fileName), focusedLayer);
			refreshImg();
	}
}

// Whenever need to refresh image
void miniPS::refreshImg() {
	int width = myProcessor.images[focusedLayer].cols;
	int height = myProcessor.images[focusedLayer].rows;
	QImage tmp = cvMat2QImage(myProcessor.images[focusedLayer]);
	MyScene *scene = new MyScene();
	connect(scene, SIGNAL(mouseMove(int, int)),
		this, SLOT(on_viewMouseMove_trigged(int, int)));
	connect(scene, SIGNAL(penMove(int, int)),
		this, SLOT(on_viewPenMove_trigged(int, int)));
	connect(scene, SIGNAL(eraserMove(int, int)),
		this, SLOT(on_viewEraserMove_trigged(int, int)));
	connect(scene, SIGNAL(colorClick(int, int)),
		this, SLOT(on_viewColorClick_trigged(int, int)));
	scene->setParentView(*myViews[focusedLayer]);
	scene->addPixmap(QPixmap::fromImage(tmp));
	myViews[focusedLayer]->setScene(scene);
	myViews[focusedLayer]->resetSize();
	ui.horizontalSlider->setValue(100);
	myViews[focusedLayer]->resize(width + 10,
		height + 10);
	myViews[focusedLayer]->show();
	QString sizeStr;
	sizeStr.sprintf("%d * %d px", width, height);
	ui.label_imagesize->setText(sizeStr);
}

// When save image
void miniPS::on_slotSave_trigged() {
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"),
		"stickYourFinger", tr("Images (*.png *.bmp *.jpg)"));
	if (fileName != "") {
		myProcessor.saveImage(qPrintable(fileName), focusedLayer);
		QMessageBox::about(NULL, "Saved", "Your current image is saved.");
	}
}

// When exit the application
void miniPS::on_slotExit_trigged() {
	/*QCloseEvent *event = new QCloseEvent();
	this->closeEvent(event);*/
	//TODO: how to close the app in window level ??
}

// When minimize the window
void miniPS::on_slotMin_trigged() {
	showMinimized();
}

// When set the window to FULLSCREEN mode
void miniPS::on_slotWinModeFull_trigged() {
	showFullScreen();
}

// When set the window to WINDOWED mode
void miniPS::on_slotWinModeWined_trigged() {
	showNormal();
	showMaximized();
}

// When the + (zoom in) button is pressed
void miniPS::on_slotZoomIn_trigged() {
	myViews[focusedLayer]->zoomInOut(ZOOM_IN_RATE);
	double scaleVal = myViews[focusedLayer]->getScaleVal();
	ui.horizontalSlider->setValue((int)(scaleVal * 100));
}

// When the - (zoom out) button is pressed
void miniPS::on_slotZoomOut_trigged() {
	myViews[focusedLayer]->zoomInOut(ZOOM_OUT_RATE);
	double scaleVal = myViews[focusedLayer]->getScaleVal();
	ui.horizontalSlider->setValue((int)(scaleVal * 100));
}

// When tab changed
// 切换 tab 的时候自动把模式切回 normal ，并且把相关的UI显示的数据置为0
void miniPS::on_slotTabChang_trigged(int cur) {
	focusedLayer = cur;
	myViews[focusedLayer]->mode = 0;
	QString sizeStr;
	int imageWidth = myProcessor.images[focusedLayer].cols;
	int imageHeight = myProcessor.images[focusedLayer].rows;
	sizeStr.sprintf("%d * %d px", imageWidth, imageHeight);
	ui.label_imagesize->setText(sizeStr);
	ui.label_height->setText("0");
	ui.label_width->setText("0");
	ui.label_posX->setText("0");
	ui.label_posY->setText("0");
	ui.doubleThreshodWidget->setVisible(false);
}

// When the zoom slider is touched
void miniPS::on_slotZoomSlid(int cur) {
	float scaleVal = cur / 100.0;
	myViews[focusedLayer]->resetSize();
	myViews[focusedLayer]->zoomInOut(scaleVal);
}

// When the zoom slider is touched, also need to update the displayed value
void miniPS::on_slotFreshScalVal() {
	double scaleVal = myViews[focusedLayer]->getScaleVal();
	QString scaleValStr;
	scaleValStr.sprintf("%d%%", (int)(scaleVal * 100));
	ui.label_scaleVal->setText(scaleValStr);
}

// When the "norm" button is pressed(change to the normal mode)
void miniPS::on_slotNormMode_trigged() {
	myViews[focusedLayer]->mode = 0;
	//TODO:remove the rectangle
	//TODO:change cursor
	ui.label_height->setText("0");
	ui.label_width->setText("0");
	myViews[focusedLayer]->freshView();
	qDebug("Now in the normal mode \n");
}

// When the "slct" button is pressed(change to the selection mode)
void miniPS::on_slotSlctMode_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "Load Image First", "Please load an image before selection");
		return;
	}
	myViews[focusedLayer]->mode = 1;
	qDebug("Now in the selection mode \n");
	//TODO:change cursor
}

// When the "pen" button is pressed(change to the pen mode)
void miniPS::on_slotPenMode_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "Load Image First", "Please load an image before selection");
		return;
	}
	myViews[focusedLayer]->mode = 2;
	qDebug("Now in the pen mode \n");
}

// When the "eraser" button is pressed(change to the eraser mode)
void miniPS::on_slotEraserMode_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "Load Image First", "Please load an image before selection");
		return;
	}
	myViews[focusedLayer]->mode = 3;
	qDebug("Now in the eraser mode \n");
}

// When the "color" label is pressed(change to the color pick mode)
void miniPS::on_slotPickMode_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "Load Image First", "Please load an image before selection");
		return;
	}
	myViews[focusedLayer]->mode = 4;
	qDebug("Now in the color pick mode \n");
}

// When the "cut" button is pressed
void miniPS::on_slotCutBtn_trigged() {
	if (myViews[focusedLayer]->mode != 1) {
		QMessageBox::about(NULL, "Need Select First", "Please press slct button and select an area before cutting.");
		return;
	}
	QPointF beginPoint = ((MyScene *)(myViews[focusedLayer]->scene()))->m_beginPoint;
	QPointF endPoint = ((MyScene *)(myViews[focusedLayer]->scene()))->m_endPoint;
	int minX = (beginPoint.x() <= endPoint.x()) ? beginPoint.x() : endPoint.x();
	int maxX = (beginPoint.x() >= endPoint.x()) ? beginPoint.x() : endPoint.x();
	int minY = (beginPoint.y() <= endPoint.y()) ? beginPoint.y() : endPoint.y();
	int maxY = (beginPoint.y() >= endPoint.y()) ? beginPoint.y() : endPoint.y();
	if (minX < 0)  minX = 0;
	if (minY < 0)  minY = 0;
	if (maxX >= myProcessor.images[focusedLayer].cols)
		maxX = myProcessor.images[focusedLayer].cols - 1;
	if (maxY >= myProcessor.images[focusedLayer].rows)
		maxY = myProcessor.images[focusedLayer].rows - 1;
	// Find the first layer whose image is already saved, and put the copy into that layer
	int j = focusedLayer;
	for (int i = 0; i < NLAYERS; i++) {
		j = (j + 1) % NLAYERS;
		if (imagesDirtyFlag[j] == 0)
			break;
	}
	myProcessor.images[j] = myProcessor.images[focusedLayer](Rect(minX, minY, (maxX - minX), (maxY - minY)));
	QImage tmp = cvMat2QImage(myProcessor.images[j]);
	MyScene *scene = new MyScene();
	scene->setParentView(*myViews[j]);
	scene->addPixmap(QPixmap::fromImage(tmp));
	myViews[j]->setScene(scene);
	myViews[j]->resetSize();
	ui.horizontalSlider->setValue(100);
	myViews[j]->resize(myProcessor.images[j].cols + 10,
		myProcessor.images[j].rows + 10);
	myViews[j]->show();
	imagesDirtyFlag[j] = 1;
}

// Whenever need to clear one of the images
void miniPS::on_slotClean_trigged() {
	for (int i = 0; i < NLAYERS; i++) {
		MyScene *scene = new MyScene();
		scene->setParentView(*myViews[i]);
		myViews[i]->setScene(scene);
		imagesDirtyFlag[i] = 0;
	}
}

// Self-defined SLOT triggered by a SIGNAL from MyScene
void miniPS::on_viewMouseMove_trigged(int x, int y) {
	//qDebug("don't stop!");
	if (x < 0)  x = 0;
	if (y < 0)  y = 0;
	if (x >= myProcessor.images[focusedLayer].cols)
		x = myProcessor.images[focusedLayer].cols - 1;
	if (y >= myProcessor.images[focusedLayer].rows)
		y = myProcessor.images[focusedLayer].rows - 1;
	std::vector<int> ans = myProcessor.getPixelVal(x, y, focusedLayer);
	QString tmp;
	if (ans[3] == 1) {
		tmp.sprintf("%d", ans[0]);
		ui.label_rVal->setText(tmp);
		tmp.sprintf("%d", ans[1]);
		ui.label_gVal->setText(tmp);
		tmp.sprintf("%d", ans[2]);
		ui.label_bVal->setText(tmp);
		//ui.label_gsVal->setText("-");
	}	
}

// Self-defined SLOT triggered by a SIGNAL from MyScene
void miniPS::on_viewPenMove_trigged(int x, int y) {
	if (x < 0)  x = 0;
	if (y < 0)  y = 0;
	if (x >= myProcessor.images[focusedLayer].cols)
		x = myProcessor.images[focusedLayer].cols - 1;
	if (y >= myProcessor.images[focusedLayer].rows)
		y = myProcessor.images[focusedLayer].rows - 1;
	//qDebug("paint paint paint \n");
	CvScalar color = CV_RGB(color1[0], color1[1], color1[2]);
	Point p(x, y);
	circle(myProcessor.images[focusedLayer], p, 5, color, -1);
	refreshImg();
}

// Self-defined SLOT triggered by a SIGNAL from MyScene
void miniPS::on_viewEraserMove_trigged(int x, int y) {
	if (x < 0)  x = 0;
	if (y < 0)  y = 0;
	if (x >= myProcessor.images[focusedLayer].cols)
		x = myProcessor.images[focusedLayer].cols - 1;
	if (y >= myProcessor.images[focusedLayer].rows)
		y = myProcessor.images[focusedLayer].rows - 1;
	//qDebug("erase erase erase \n");
	CvScalar color = CV_RGB(255,255,255);
	Point p(x, y);
	circle(myProcessor.images[focusedLayer], p, 10, color, -1);
	refreshImg();
}

// Self-defined SLOT triggered by a SIGNAL from MyScene
void miniPS::on_viewColorClick_trigged(int x, int y) {
	if (x < 0)  x = 0;
	if (y < 0)  y = 0;
	if (x >= myProcessor.images[focusedLayer].cols)
		x = myProcessor.images[focusedLayer].cols - 1;
	if (y >= myProcessor.images[focusedLayer].rows)
		y = myProcessor.images[focusedLayer].rows - 1;
	//qDebug("pick pick pick \n");
	std::vector<int> ans = myProcessor.getPixelVal(x, y, focusedLayer);
	color1[0] = ans[0];
	color1[1] = ans[1];
	color1[2] = ans[2];
	// Change displayed color
	QString css;
	css.sprintf("QLabel { background-color : rgb(%d,%d,%d); color : blue; }", color1[0], color1[1], color1[2]);
	ui.picked_color1->setStyleSheet(css);
}

// When "color ex" button is pressed
void miniPS::on_slotColorExchange() {
	std::vector<int> tmp = { color1[0], color1[1], color1[2] };
	color1 = {color2[0], color2[1], color2[2]};
	color2 = { tmp[0], tmp[1], tmp[2] };
	QString css;
	css.sprintf("QLabel { background-color : rgb(%d,%d,%d); color : blue; }", color1[0], color1[1], color1[2]);
	ui.picked_color1->setStyleSheet(css);
	css.sprintf("QLabel { background-color : rgb(%d,%d,%d); color : blue; }", color2[0], color2[1], color2[2]);
	ui.picked_color2->setStyleSheet(css);
}

// When "color reset" button is pressed
void miniPS::in_slotColorReset() {
	color1 = { 255,255,255 };
	color2 = { 0,0,0 };
	ui.picked_color1->setStyleSheet("QLabel { background-color : white; color : blue; }");
	ui.picked_color2->setStyleSheet("QLabel { background-color : black; color : blue; }");
}

// Do channel split(R)
void miniPS::on_channelSplitR_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	myProcessor.channelSplit(CHANNEL_R, focusedLayer);
	refreshImg();
}

// Do channel split(G)
void miniPS::on_channelSplitG_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	myProcessor.channelSplit(CHANNEL_G, focusedLayer);
	refreshImg();
}

// Do channel split(B)
void miniPS::on_channelSplitB_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	myProcessor.channelSplit(CHANNEL_B, focusedLayer);
	refreshImg();
}

// When "undo" button is pressed
void miniPS::on_slotUndo_trigged() {
	if (myProcessor.undo(focusedLayer)) {
		refreshImg();
	}
	else {
		QMessageBox::about(NULL, "Ooops", "No more history operation has been saved.");
	}
}

// Change an rgb-image into grayscale one
void miniPS::on_rgb2gry_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	myProcessor.rgb2gry(focusedLayer);
	refreshImg();
}

// When "HSB" button is pressed(show hsv info)
void miniPS::on_slotHSV_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	ui.hsvWidget->setVisible(true);
	myProcessor.commit(focusedLayer);
	myProcessor.makeHsvBackup(focusedLayer);
	ui.horizontalSlider_s->setValue(0);
	ui.horizontalSlider_v->setValue(0);
}

// When "HSV ok" button is pressed(hide hsv info)
void miniPS::on_slotHSVok_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	ui.hsvWidget->setVisible(false);
}

// When HSV slider h is touched
void miniPS::on_slotHSVslidH_trigged(int cur) {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	myProcessor.changeHSV(0, cur, focusedLayer);
	refreshImg();
}

// When HSV slider s is touched
void miniPS::on_slotHSVslidS_trigged(int cur) {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	myProcessor.changeHSV(1, cur, focusedLayer);
	refreshImg();
}

// When HSV slider v is touched
void miniPS::on_slotHSVslidV_trigged(int cur) {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	myProcessor.changeHSV(2, cur, focusedLayer);
	refreshImg();
}

// When "double threshod" button is pressed(show dbth info)
void miniPS::on_slotDbTh_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	ui.doubleThreshodWidget->setVisible(true);
}

// When "dbthOK" button is pressed
void miniPS::on_slotDbThok_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
    //call function
	int threshod1 = ui.inputThreshod1->value();
	int threshod2 = ui.inputThreshod2->value();
	myProcessor.toBinary(false, threshod1, threshod2, focusedLayer);
	refreshImg();
	ui.doubleThreshodWidget->setVisible(false);
}

// When "otsu" button is pressed
void miniPS::on_slotOtsu_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	myProcessor.toBinary(true, 0, 0, focusedLayer);
	refreshImg();
}

// When "add" button is pressed
void miniPS::on_slotAdd_trigged() {
	ui.addWidget->setVisible(true);
}

// When "sub" button is pressed
void miniPS::on_slotSubtraction_trigged() {
	ui.subtractionWidget->setVisible(true);
}

// When "multi" button is pressed
void miniPS::on_slotMultiplication_trigged(){
	ui.multiplicationWidget->setVisible(true);
}

// When "dvd" button is pressed
void miniPS::on_slotDivision_trigged() {
	ui.divisionWidget->setVisible(true);
}

// Do add operation
void miniPS::on_addOk_trigged() {
	int idx1 = ui.inputAddImg1->value() - 1;
	int idx2 = ui.inputAddImg2->value() - 1;
	double weight1 = ui.inputAddWeight1->value();
	double weight2 = ui.inputAddWeight2->value();
	int posX = ui.inputAddX->value();
	int posY = ui.inputAddY->value();
	if (myViews[idx1]->scene() == NULL || myViews[idx2]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		ui.addWidget->setVisible(false);
		return;
	}
	myProcessor.addOper(idx1, idx2, weight1, weight2, posX, posY);
	refreshImg();
	ui.addWidget->setVisible(false);
	refreshImg();
}

// Do subtraction operation
void miniPS::on_subOk_trigged() {
	int idx1 = ui.inputSubImg1->value() - 1;
	int idx2 = ui.inputSub2->value() - 1;
	int posX = ui.inputSubX->value();
	int posY = ui.inputSubY->value();
	if (myViews[idx1]->scene() == NULL || myViews[idx2]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		ui.subtractionWidget->setVisible(false);
		return;
	}
	myProcessor.subtractionOper(idx1, idx2, posX, posY);
	refreshImg();
	ui.subtractionWidget->setVisible(false);
	refreshImg();
}

// Do multiplication operation
void miniPS::on_multiOk_trigged() {
	int idx1 = ui.inputMultiImg1->value() - 1;
	int idx2 = ui.inputMultiImg2->value() - 1;
	if (myViews[idx1]->scene() == NULL || myViews[idx2]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		ui.multiplicationWidget->setVisible(false);
		return;
	}
	if (!myProcessor.multiplicationOper(idx1, idx2)) {
		QMessageBox::about(NULL, "Images not in the same size", "Images must be in the same size to do multiplication");
		ui.multiplicationWidget->setVisible(false);
	}
	refreshImg();
	ui.multiplicationWidget->setVisible(false);
	refreshImg();
}

// Do division operation
void miniPS::on_dvdOk_trigged() {
	int idx1 = ui.inputDvdImg1->value() - 1;
	int idx2 = ui.inputDvdImg2->value() - 1;
	if (myViews[idx1]->scene() == NULL || myViews[idx2]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		ui.divisionWidget->setVisible(false);
		return;
	}
	if (!myProcessor.divisionOper(idx1, idx2)) {
		QMessageBox::about(NULL, "Images not in the same size", "Images must be in the same size to do division");
		ui.divisionWidget->setVisible(false);
	}
	refreshImg();
	ui.divisionWidget->setVisible(false);
	refreshImg();
}

// When "resize" button is pressed
void miniPS::on_slotResize_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	ui.resizeWidget->setVisible(true);
}

// Do resize operation
void miniPS::on_resizeOk_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		ui.resizeWidget->setVisible(false);
		return;
	}
	int height = ui.inputResizeHeight->value();
	int width = ui.inputResizeWidth->value();
	if (ui.inputChoiceNN->checkState() == Qt::Checked) {
		if (ui.inputChoiceLINEAR->checkState() == Qt::Checked) {// Both are checked
			QMessageBox::about(NULL, "Oooops", "You can only check one choice");
			ui.resizeWidget->setVisible(false);
			return;
		}
		else {// use NN
			myProcessor.resize(width, height, NN, focusedLayer);
		}
	}
	else if (ui.inputChoiceLINEAR->checkState() == Qt::Checked) {// use LINEAR
		myProcessor.resize(width, height, LINEAR, focusedLayer);
	}
	else {// None are checked
		QMessageBox::about(NULL, "Oooops", "You must take one choice");
		ui.resizeWidget->setVisible(false);
		return;
	}
	refreshImg();
	ui.resizeWidget->setVisible(false);
}

// Do spin PI/2 clockwize
void miniPS::on_slotSpin_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	myProcessor.spinCW(focusedLayer);
	refreshImg();
}

// Draw R channel histogram
void miniPS::on_slotRHist_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	myProcessor.drawHist(CHANNEL_R, focusedLayer);
}

// Draw G channel histogram
void miniPS::on_slotGHist_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	myProcessor.drawHist(CHANNEL_G, focusedLayer);
}

// Draw B channel histogram
void miniPS::on_slotBHist_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	myProcessor.drawHist(CHANNEL_B, focusedLayer);
}

// Do histogram equalization
void miniPS::on_slotHistEqualization() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	myProcessor.histEqualization(focusedLayer);
	refreshImg();
}

// When "filter" button is pressed
void miniPS::on_slotFilter_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	ui.filterWidget->setVisible(true);
}

// When "self define filter" button is pressed
void miniPS::on_selfFilter_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	ui.selfFilterWidget->setVisible(true);
}

// Do filter operation
void miniPS::on_filterOk_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		ui.filterWidget->setVisible(false);
		return;
	}
	int kernelSize = ui.inputKernelSize->value();
	if (kernelSize % 2 == 0) // Make sure kernelSize is odd
		kernelSize++;
	int boxFlag = 0, gaussianFlag = 0, medianFlag = 0;
	if (ui.inputFilterChoiceBox->checkState() == Qt::Checked) {
		boxFlag = 1;
	}
	if (ui.inputFilterChoiceGaussian->checkState() == Qt::Checked) {
		gaussianFlag = 1;
	}
	if (ui.inputFilterChoiceMedian->checkState() == Qt::Checked) {
		medianFlag = 1;
	}
	if ((boxFlag + gaussianFlag + medianFlag) != 1) {
		QMessageBox::about(NULL, "Oooops", "You can only check one choice");
		ui.filterWidget->setVisible(false);
		return;
	}
	if (boxFlag == 1) { // Box filtering
		myProcessor.boxFilter(kernelSize, focusedLayer);
	}
	else if (gaussianFlag == 1) { // Gaussian filtering
		myProcessor.gaussianFilter(kernelSize, focusedLayer);
	}
	else { // Median filtering
		myProcessor.medianFilter(kernelSize, focusedLayer);
	}
	refreshImg();
	ui.filterWidget->setVisible(false);
}

// Do self-defined filter operation
void miniPS::on_selfFilterOk_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		ui.selfFilterWidget->setVisible(false);
		return;
	}
	double **kernel;  // Get user-designed kernel
	kernel = (double **)malloc(3 * sizeof(double*));
	for (int i = 0; i < 3; i++) {
		kernel[i] = (double *)malloc(3 * sizeof(double));
	}
	kernel[0][0] = ui.inputSelfFilter1->value();
	kernel[0][1] = ui.inputSelfFilter2->value();
	kernel[0][2] = ui.inputSelfFilter3->value();
	kernel[1][0] = ui.inputSelfFilter4->value();
	kernel[1][1] = ui.inputSelfFilter5->value();
	kernel[1][2] = ui.inputSelfFilter6->value();
	kernel[2][0] = ui.inputSelfFilter7->value();
	kernel[2][1] = ui.inputSelfFilter8->value();
	kernel[2][2] = ui.inputSelfFilter9->value();

	// call function
	myProcessor.filter2D(kernel, 3, focusedLayer);
	refreshImg();
	for (int i = 0; i < 3; i++) {
		delete kernel[i];
	}
	delete kernel;
	ui.selfFilterWidget->setVisible(false);
}

// When "rotate" button is pressed
void miniPS::on_slotRotate_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	ui.rotateWidget->setVisible(true);
}

// Do rotate operation
void miniPS::on_rotateOk_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		ui.rotateWidget->setVisible(false);
		return;
	}
	float theta = ui.inputRotateTheta->value();
	if (theta == 0) {
		ui.rotateWidget->setVisible(false);
		return;
	}
	//myProcessor.rotateCW(theta, focusedLayer);
	if (ui.inputRotateChoiceNN->checkState() == Qt::Checked) {
		if (ui.inputRotateChoiceLINEAR->checkState() == Qt::Checked) {// Both are checked
			QMessageBox::about(NULL, "Oooops", "You can only check one choice");
			ui.rotateWidget->setVisible(false);
			return;
		}
		else {// use NN
			myProcessor.rotateCW(theta, NN, focusedLayer);
		}
	}
	else if (ui.inputRotateChoiceLINEAR->checkState() == Qt::Checked) {// use LINEAR
		myProcessor.rotateCW(theta, LINEAR, focusedLayer);
	}
	else {// None are checked
		QMessageBox::about(NULL, "Oooops", "You must take one choice");
		ui.rotateWidget->setVisible(false);
		return;
	}
	refreshImg();
	ui.rotateWidget->setVisible(false);
}

// When "grayscale adjustment->linear" button is pressed
void miniPS::on_slotGSALinear_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	ui.GSAWidget->setVisible(true);
	myProcessor.commit(focusedLayer);
	myProcessor.makeGSABackup(focusedLayer);
	ui.GSASliderA->setValue(127);
	ui.GSASliderB->setValue(127);
	ui.GSASliderC->setValue(127);
	ui.GSASliderD->setValue(127);
}

// When any of GSA linear sliders is touched
void miniPS::on_GSALinearSlid(int cur) {
	if (myViews[focusedLayer]->scene() == NULL) {
		return;
	}
	int A, B, C, D;
	int a, b, c, d;
	A = ui.GSASliderA->value();
	B = ui.GSASliderB->value();
	C = ui.GSASliderC->value();
	D = ui.GSASliderD->value();
	if (A > B) {  // make sure a < b
		a = B;
		b = A;
	}
	else {
		a = A;
		b = B;
	}
	if (C > D) {  // make sure c < d
		c = D;
		d = C;
	}
	else {
		c = C;
		d = D;
	}

	// call paint event and draw function picture in real-time
	
	Mat functionDisplay = myProcessor.drawLinearFunction(a, b, c, d);
	QImage tmp = cvMat2QImage(functionDisplay);
	ui.label_40->setPixmap(QPixmap::fromImage(tmp));

	// check choice and call GSA function
	if (ui.inputLinearGSAChoiceRGB->checkState() == Qt::Checked) { // RGB
		myProcessor.linearGSA(a, b, c, d, CHANNEL_R, focusedLayer);
		myProcessor.linearGSA(a, b, c, d, CHANNEL_G, focusedLayer);
		myProcessor.linearGSA(a, b, c, d, CHANNEL_B, focusedLayer);
	}
	else {
		if (ui.inputLinearGSAChoiceR->checkState() == Qt::Checked) { // only R
			myProcessor.linearGSA(a, b, c, d, CHANNEL_R, focusedLayer);
		}
		if (ui.inputLinearGSAChoiceG->checkState() == Qt::Checked) {  // only G
			myProcessor.linearGSA(a, b, c, d, CHANNEL_G, focusedLayer);
		}
		if (ui.inputLinearGSAChoiceB->checkState() == Qt::Checked) {  // only B
			myProcessor.linearGSA(a, b, c, d, CHANNEL_B, focusedLayer);
		}
	}

	refreshImg();
}

// When any of "GSA OK" buttons is pressed
void miniPS::on_GSAOk_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	ui.GSAWidget->setVisible(false);
}

// When "grayscale adjustment->exp/log" button is pressed
void miniPS::on_slotGSAExpLog_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	ui.UGSAWidget->setVisible(true);
}

// Do exp/log GSA
void miniPS::on_UGSAOk_trigged() {
	myProcessor.commit(focusedLayer);
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		ui.UGSAWidget->setVisible(false);
		return;
	}
	double A = ui.inputUGSAA->value();
	double B = ui.inputUGSAB->value();
	double C = ui.inputUGSAC->value();
	if (ui.inputUGSAexp->checkState() == Qt::Checked) {
		if (ui.inputUGSAlog->checkState() == Qt::Checked) {
			QMessageBox::about(NULL, "Oooops", "You can only check one choice");
			ui.UGSAWidget->setVisible(false);
			return;
		}
		else { // exp
			myProcessor.expGSA(A, B, C, CHANNEL_R, focusedLayer);
			myProcessor.expGSA(A, B, C, CHANNEL_G, focusedLayer);
			myProcessor.expGSA(A, B, C, CHANNEL_B, focusedLayer);
		}
	}
	else {
		if (ui.inputUGSAlog->checkState() == Qt::Checked) { // log
			myProcessor.logGSA(A, B, C, CHANNEL_R, focusedLayer);
			myProcessor.logGSA(A, B, C, CHANNEL_G, focusedLayer);
			myProcessor.logGSA(A, B, C, CHANNEL_B, focusedLayer);
		}
		else {
			QMessageBox::about(NULL, "Oooops", "You must take one choice");
			ui.UGSAWidget->setVisible(false);
			return;
		}
	}
	refreshImg();
	ui.UGSAWidget->setVisible(false);
}

// Do sobel edge detection
void miniPS::on_slotSobelX_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	myProcessor.filter2D(sobelX, 3, focusedLayer);
	refreshImg();
}

void miniPS::on_slotSobelY_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	myProcessor.filter2D(sobelY, 3, focusedLayer);
	refreshImg();
}

void miniPS::on_slotSobelXY_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	myProcessor.filter2D(sobelX, 3, focusedLayer);
	myProcessor.filter2D(sobelY, 3, focusedLayer);
	refreshImg();
}

// Do laplace edge detection
void miniPS::on_slotLaplace_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	myProcessor.filter2D(laplace, 3, focusedLayer);
	refreshImg();
}

// Do canny edge detection
void miniPS::on_slotCanny_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	myProcessor.canny(focusedLayer);
	refreshImg();
}

// Do handwriting recognizing 
void miniPS::on_slotHelloWorld_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	myProcessor.resize(20, 20, NN, focusedLayer);
	int res = myProcessor.helloWorld(focusedLayer);
	refreshImg();
	QString report;
	report.sprintf("Handwriting recognized : %d", res);
	QMessageBox::about(NULL, "HelloWorld", report);
}

// Do hough line detection
void miniPS::on_slotHoughLine() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	myProcessor.houghLine(focusedLayer);
	refreshImg();
}

// Do hough circle detection
void miniPS::in_slotHoughCircle() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	myProcessor.houghCircle(focusedLayer);
	refreshImg();
}

// When the "mophology" button is pressed
void miniPS::on_slotMophology_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	ui.MophologyWidget->setVisible(true);
}

// When the mophology input approach tab changed
void miniPS::on_slotMophoTabChange(int cur) {
	mophoCurTab = cur;
}



/*************************************   Mophology   ****************************************************/

Mat parseMat(QString inputStr) {
	std::vector<std::vector<int>> set = {};
	int j = 0;
	for (int i = 0; i < inputStr.length(); i++) {
		if (inputStr[i] == ';' && j != i) {
			std::vector<int> tmpVec = {};
			for (int k = j; k < i; k++) {
				tmpVec.push_back(inputStr[k].digitValue());
			}
			set.push_back(tmpVec);
			j = i + 1;
		}
		if (inputStr[i] == ';' && j == i) {
			j++;
		}
	}
	int iRows = set.size();
	int iCols = set[0].size();
	Mat B = Mat(iRows, iCols, CV_32FC1);
	for (int i = 0; i < iRows; i++) {
		for (int j = 0; j < iCols; j++) {
			B.at<int>(i, j) = set[i][j];
		}
	}
	return B;
}

// When the "dilation" btn is pressed
void miniPS::on_slotDilation() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	int anchorRow = ui.inputAnchorRow->value();
	int anchorCol = ui.inputAnchorCol->value();
	Mat B;
	switch (this->mophoCurTab) {
	case 0: { // 3*3
	    
		break;
	}
	case 1: { // 5*5

		break;
	}
	case 2: { // m*n
		QString text = ui.textEdit->toPlainText();
	    B = parseMat(text);
		myProcessor.dilation(B, anchorRow, anchorCol, focusedLayer);
	}
	}
	//myProcessor.dilation(B, focusedLayer);
	refreshImg();
	ui.MophologyWidget->setVisible(false);
}

// When the "erosion" btn is pressed
void miniPS::on_slotErosion(){
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}

	refreshImg();
	ui.MophologyWidget->setVisible(false);
}

// When the "open" btn is pressed
void miniPS::on_slotOpen() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}

	refreshImg();
	ui.MophologyWidget->setVisible(false);
}

// When the "close" btn is pressed
void miniPS::on_slotClose() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}

	refreshImg();
	ui.MophologyWidget->setVisible(false);
}

// When the "thinning" button is pressed
void miniPS::on_slotThinning() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}

	refreshImg();
	ui.MophologyWidget->setVisible(false);
}

// When the "thickening" button is pressed
void miniPS::on_slotThickening() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}

	refreshImg();
	ui.MophologyWidget->setVisible(false);
}

// When the "skeleton" button is pressed
void miniPS::on_slotSkeleton() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}

	refreshImg();
	ui.MophologyWidget->setVisible(false);
}

// When the "distance" button is pressed
void miniPS::on_slotDistanceTrans() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}

	refreshImg();
	ui.MophologyWidget->setVisible(false);
}

// When the "skeleton reconstruction" button is pressed
void miniPS::on_slotSkeletonRecon() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}

	refreshImg();
	ui.MophologyWidget->setVisible(false);
}

// When the "binary reconstruction" button is pressed
void miniPS::on_slotBinRecon() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}

	refreshImg();
	ui.MophologyWidget->setVisible(false);
}

// When the "reconstruction" button is pressed
void miniPS::on_slotGrayRecon() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}
	myProcessor.test(focusedLayer);
	refreshImg();
	ui.MophologyWidget->setVisible(false);
}

// When the "watershed" button is pressed
void miniPS::on_slotWatershed() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		return;
	}

	refreshImg();
	ui.MophologyWidget->setVisible(false);
}