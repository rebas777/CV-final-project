#include "miniPS.h"



miniPS::miniPS(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	showMaximized();

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
		this->images[i] = new QImage();
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
	
	//set shortcut for menu
	ui.actionsave_image->setShortcut(Qt::CTRL | Qt::Key_S);
	ui.actionopen_image->setShortcut(Qt::CTRL | Qt::Key_L);

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
		delete this->images[i];
		delete this->myViews[i];
	}
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
		if (images[focusedLayer]->load(fileName))
		{
			//QGraphicsScene *scene = new QGraphicsScene;
			MyScene *scene = new MyScene();
			scene->setParentView(*myViews[focusedLayer]);
			scene->addPixmap(QPixmap::fromImage(*images[focusedLayer]));
			myViews[focusedLayer]->setScene(scene);
			//myViews[focusedLayer]->scene();
			myViews[focusedLayer]->resetSize();
			ui.horizontalSlider->setValue(100);
			myViews[focusedLayer]->resize(images[focusedLayer]->width() + 10,
				images[focusedLayer]->height() + 10);
			myViews[focusedLayer]->show();
			QString sizeStr;
			int imageWidth = images[focusedLayer]->width();
			int imageHeight = images[focusedLayer]->height();
			sizeStr.sprintf("%d * %d px", imageWidth, imageHeight);
			ui.label_imagesize->setText(sizeStr);
		}
	}
}

void miniPS::on_slotSave_trigged() {
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"),
		"stickYourFinger", tr("Images (*.png *.bmp *.jpg)"));
	if (fileName != "") {
		images[focusedLayer]->save(fileName);
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
	int imageWidth = images[focusedLayer]->width();
	int imageHeight = images[focusedLayer]->height();
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
	QImage newImage = images[focusedLayer]->copy(minX, minY, (maxX - minX), (maxY - minY));
	// Find the first layer whose image is already saved, and put the copy into that layer
	int j = focusedLayer;
	for (int i = 0; i < NLAYERS; i++) {
		j = (j + 1) % NLAYERS;
		if (imagesDirtyFlag[j] == 0)
			break;
	}

	*images[j] = newImage;
	MyScene *scene = new MyScene();
	scene->setParentView(*myViews[j]);
	scene->addPixmap(QPixmap::fromImage(newImage));
	myViews[j]->setScene(scene);
	myViews[j]->resetSize();
	ui.horizontalSlider->setValue(100);
	myViews[j]->resize(newImage.width() + 10,
		newImage.height() + 10);
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
