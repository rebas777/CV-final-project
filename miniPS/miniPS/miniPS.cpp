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

	//init focused layer
	focusedLayer = 0;

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
	connect(ui.actionfilter, SIGNAL(triggered()), this, SLOT(on_slotFilter_trigged()));
	connect(ui.filterOkBtn, SIGNAL(clicked()), this, SLOT(on_filterOk_trigged()));
	connect(ui.actionrotate, SIGNAL(triggered()), this, SLOT(on_slotRotate_trigged()));
	connect(ui.rotateOkBtn, SIGNAL(clicked()), this, SLOT(on_rotateOk_trigged()));
	
	
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

	setMouseTracking(true);
	ui.centralWidget->setMouseTracking(true);
}

miniPS::~miniPS() {
	for (int i = 0; i < NLAYERS; i++) {
		//delete this->images[i];
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
}

// When the "slct" button is pressed(change to the selection mode)
void miniPS::on_slotSlctMode_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "Load Image First", "Please load an image before selection");
		return;
	}
	myViews[focusedLayer]->mode = 1;
	//TODO:change cursor
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
	ui.hsvWidget->setVisible(false);
}

// When HSV slider h is touched
void miniPS::on_slotHSVslidH_trigged(int cur) {
	myProcessor.changeHSV(0, cur, focusedLayer);
	refreshImg();
}

// When HSV slider s is touched
void miniPS::on_slotHSVslidS_trigged(int cur) {
	myProcessor.changeHSV(1, cur, focusedLayer);
	refreshImg();
}

// When HSV slider v is touched
void miniPS::on_slotHSVslidV_trigged(int cur) {
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

// Do filter operation
void miniPS::on_filterOk_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "No Image", "Please load an image before operation");
		ui.filterWidget->setVisible(false);
		return;
	}
	//
	refreshImg();
	ui.filterWidget->setVisible(false);
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
		return;
	}
	float theta = ui.inputRotateTheta->value();
	if (theta == 0) {
		return;
	}
	//myProcessor.rotateCW(theta, focusedLayer);
	if (ui.inputRotateChoiceNN->checkState() == Qt::Checked) {
		if (ui.inputRotateChoiceLINEAR->checkState() == Qt::Checked) {// Both are checked
			QMessageBox::about(NULL, "Oooops", "You can only check one choice");
			ui.resizeWidget->setVisible(false);
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
		ui.resizeWidget->setVisible(false);
		return;
	}
	refreshImg();
	ui.rotateWidget->setVisible(false);
}