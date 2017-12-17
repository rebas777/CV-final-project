#include "miniPS.h"



miniPS::miniPS(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	showMaximized();

	// Initialize image processor
	//myProcessor.showImage(3);

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
	
	
	//set shortcut for menu
	ui.actionsave_image->setShortcut(Qt::CTRL | Qt::Key_S);
	ui.actionopen_image->setShortcut(Qt::CTRL | Qt::Key_L);
	ui.actionundo->setShortcut(Qt::CTRL | Qt::Key_Z);

	//set zoom slider
	ui.horizontalSlider->setOrientation(Qt::Horizontal);
	ui.horizontalSlider->setMaximum(ZOOM_MAX);
	ui.horizontalSlider->setMinimum(ZOOM_MIN);
	ui.horizontalSlider->setSingleStep(ZOOM_STEP);
	ui.horizontalSlider->setTickInterval(50);
	ui.horizontalSlider->setTickPosition(QSlider::TicksAbove);

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

void miniPS::on_slotSave_trigged() {
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"),
		"stickYourFinger", tr("Images (*.png *.bmp *.jpg)"));
	if (fileName != "") {
		myProcessor.saveImage(qPrintable(fileName), focusedLayer);
		QMessageBox::about(NULL, "Saved", "Your current image is saved.");
	}
}

void miniPS::on_slotExit_trigged() {
	/*QCloseEvent *event = new QCloseEvent();
	this->closeEvent(event);*/
	//TODO: how to close the app in window level ??
}

void miniPS::on_slotMin_trigged() {
	showMinimized();
}

void miniPS::on_slotWinModeFull_trigged() {
	showFullScreen();
}

void miniPS::on_slotWinModeWined_trigged() {
	showNormal();
	showMaximized();
}

void miniPS::on_slotZoomIn_trigged() {
	myViews[focusedLayer]->zoomInOut(ZOOM_IN_RATE);
	double scaleVal = myViews[focusedLayer]->getScaleVal();
	ui.horizontalSlider->setValue((int)(scaleVal * 100));
}

void miniPS::on_slotZoomOut_trigged() {
	myViews[focusedLayer]->zoomInOut(ZOOM_OUT_RATE);
	double scaleVal = myViews[focusedLayer]->getScaleVal();
	ui.horizontalSlider->setValue((int)(scaleVal * 100));
}

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
}

void miniPS::on_slotZoomSlid(int cur) {
	float scaleVal = cur / 100.0;
	myViews[focusedLayer]->resetSize();
	myViews[focusedLayer]->zoomInOut(scaleVal);
}

void miniPS::on_slotFreshScalVal() {
	double scaleVal = myViews[focusedLayer]->getScaleVal();
	QString scaleValStr;
	scaleValStr.sprintf("%d%%", (int)(scaleVal * 100));
	ui.label_scaleVal->setText(scaleValStr);
}

void miniPS::on_slotNormMode_trigged() {
	myViews[focusedLayer]->mode = 0;
	//TODO:remove the rectangle
	//TODO:change cursor
	ui.label_height->setText("0");
	ui.label_width->setText("0");
	myViews[focusedLayer]->freshView();
}

void miniPS::on_slotSlctMode_trigged() {
	if (myViews[focusedLayer]->scene() == NULL) {
		QMessageBox::about(NULL, "Load Image First", "Please load an image before selection");
		return;
	}
	myViews[focusedLayer]->mode = 1;
	//TODO:change cursor
}

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

void miniPS::on_slotClean_trigged() {
	for (int i = 0; i < NLAYERS; i++) {
		MyScene *scene = new MyScene();
		scene->setParentView(*myViews[i]);
		myViews[i]->setScene(scene);
		imagesDirtyFlag[i] = 0;
	}
}

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
		ui.label_gsVal->setText("-");
	}
	else if(ans[3] == 0) {
		ui.label_rVal->setText("-");
		ui.label_gVal->setText("-");
		ui.label_bVal->setText("-");
		tmp.sprintf("%d", ans[0]);
		ui.label_gsVal->setText(tmp);
	}
	
}

void miniPS::on_channelSplitR_trigged() {
	myProcessor.channelSplit(2, focusedLayer);
	refreshImg();
}

void miniPS::on_channelSplitG_trigged() {
	myProcessor.channelSplit(1, focusedLayer);
	refreshImg();
}

void miniPS::on_channelSplitB_trigged() {
	myProcessor.channelSplit(0, focusedLayer);
	refreshImg();
}

void miniPS::on_slotUndo_trigged() {
	if (myProcessor.undo(focusedLayer)) {
		refreshImg();
		QMessageBox::about(NULL, "Ooops", "Undo successfully.");
	}
	else {
		QMessageBox::about(NULL, "Ooops", "No more history operation has been saved.");
	}
}

void miniPS::on_rgb2gry_trigged() {
	myProcessor.rgb2gry(focusedLayer);
	refreshImg();
}
