/********************************************************************************
** Form generated from reading UI file 'miniPS.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINIPS_H
#define UI_MINIPS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_miniPSClass
{
public:
    QAction *actionopen_image;
    QAction *actionsave_image;
    QAction *actionminimize;
    QAction *actionundo;
    QAction *actionfull_screen;
    QAction *actionwindowed;
    QAction *actionexit;
    QAction *actionclean_all_layers;
    QAction *actionRGB2GrayScale;
    QAction *actionRed;
    QAction *actionGreen;
    QAction *actionBlue;
    QAction *actionHSB;
    QAction *actionOtus_Algo;
    QAction *actiondouble_threshod;
    QWidget *centralWidget;
    QPushButton *exitBtn;
    QGroupBox *groupBox;
    QFrame *line;
    QFrame *line_2;
    QSlider *horizontalSlider;
    QPushButton *zoomOutBtn;
    QPushButton *zoomInBtn;
    QLabel *label_scaleVal;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_posX;
    QLabel *label_posY;
    QLabel *label_width;
    QLabel *label_height;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_rVal;
    QLabel *label_gVal;
    QLabel *label_bVal;
    QLabel *label_8;
    QLabel *label_gsVal;
    QTabWidget *tabWidget;
    QWidget *layer1;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *layer2;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QWidget *layer3;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_3;
    QWidget *layer4;
    QScrollArea *scrollArea_4;
    QWidget *scrollAreaWidgetContents_4;
    QWidget *layer5;
    QScrollArea *scrollArea_5;
    QWidget *scrollAreaWidgetContents_5;
    QLabel *label_imagesize;
    QWidget *leftToolBar;
    QPushButton *normalModeBtn;
    QPushButton *slctModeBtn;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QFrame *line_3;
    QLabel *picked_color1;
    QLabel *picked_color2;
    QPushButton *colorSwitchBtn;
    QPushButton *colorResetBtn;
    QPushButton *getColorBtn;
    QPushButton *cutBtn;
    QFrame *line_4;
    QFrame *line_6;
    QFrame *line_7;
    QFrame *line_5;
    QWidget *containerWidget;
    QWidget *hsvWidget;
    QSlider *horizontalSlider_h;
    QSlider *horizontalSlider_s;
    QSlider *horizontalSlider_v;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QPushButton *HSVokBtn;
    QWidget *doubleThreshodWidget;
    QSpinBox *inputThreshod1;
    QLabel *label_12;
    QLabel *label_13;
    QSpinBox *inputThreshod2;
    QPushButton *doubleThreshodOkBtn;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menucolor_operation;
    QMenu *menuchannel_split;
    QMenu *menubinary_analysis;
    QMenu *menuSettings;
    QMenu *menuWindow_mode;
    QMenu *menuHelp;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *miniPSClass)
    {
        if (miniPSClass->objectName().isEmpty())
            miniPSClass->setObjectName(QStringLiteral("miniPSClass"));
        miniPSClass->resize(1920, 980);
        actionopen_image = new QAction(miniPSClass);
        actionopen_image->setObjectName(QStringLiteral("actionopen_image"));
        actionsave_image = new QAction(miniPSClass);
        actionsave_image->setObjectName(QStringLiteral("actionsave_image"));
        actionminimize = new QAction(miniPSClass);
        actionminimize->setObjectName(QStringLiteral("actionminimize"));
        actionundo = new QAction(miniPSClass);
        actionundo->setObjectName(QStringLiteral("actionundo"));
        actionfull_screen = new QAction(miniPSClass);
        actionfull_screen->setObjectName(QStringLiteral("actionfull_screen"));
        actionwindowed = new QAction(miniPSClass);
        actionwindowed->setObjectName(QStringLiteral("actionwindowed"));
        actionexit = new QAction(miniPSClass);
        actionexit->setObjectName(QStringLiteral("actionexit"));
        actionclean_all_layers = new QAction(miniPSClass);
        actionclean_all_layers->setObjectName(QStringLiteral("actionclean_all_layers"));
        actionRGB2GrayScale = new QAction(miniPSClass);
        actionRGB2GrayScale->setObjectName(QStringLiteral("actionRGB2GrayScale"));
        actionRed = new QAction(miniPSClass);
        actionRed->setObjectName(QStringLiteral("actionRed"));
        actionGreen = new QAction(miniPSClass);
        actionGreen->setObjectName(QStringLiteral("actionGreen"));
        actionBlue = new QAction(miniPSClass);
        actionBlue->setObjectName(QStringLiteral("actionBlue"));
        actionHSB = new QAction(miniPSClass);
        actionHSB->setObjectName(QStringLiteral("actionHSB"));
        actionOtus_Algo = new QAction(miniPSClass);
        actionOtus_Algo->setObjectName(QStringLiteral("actionOtus_Algo"));
        actiondouble_threshod = new QAction(miniPSClass);
        actiondouble_threshod->setObjectName(QStringLiteral("actiondouble_threshod"));
        centralWidget = new QWidget(miniPSClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        exitBtn = new QPushButton(centralWidget);
        exitBtn->setObjectName(QStringLiteral("exitBtn"));
        exitBtn->setGeometry(QRect(2340, 0, 112, 34));
        exitBtn->setCheckable(false);
        exitBtn->setAutoDefault(false);
        exitBtn->setFlat(false);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(1430, 70, 461, 331));
        groupBox->setCursor(QCursor(Qt::ArrowCursor));
        line = new QFrame(groupBox);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(17, 240, 431, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(groupBox);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(330, 30, 20, 201));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        horizontalSlider = new QSlider(groupBox);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(80, 280, 301, 22));
        horizontalSlider->setCursor(QCursor(Qt::ClosedHandCursor));
        horizontalSlider->setOrientation(Qt::Horizontal);
        zoomOutBtn = new QPushButton(groupBox);
        zoomOutBtn->setObjectName(QStringLiteral("zoomOutBtn"));
        zoomOutBtn->setGeometry(QRect(50, 273, 34, 34));
        zoomOutBtn->setCursor(QCursor(Qt::PointingHandCursor));
        zoomInBtn = new QPushButton(groupBox);
        zoomInBtn->setObjectName(QStringLiteral("zoomInBtn"));
        zoomInBtn->setGeometry(QRect(380, 273, 34, 34));
        zoomInBtn->setCursor(QCursor(Qt::PointingHandCursor));
        label_scaleVal = new QLabel(groupBox);
        label_scaleVal->setObjectName(QStringLiteral("label_scaleVal"));
        label_scaleVal->setGeometry(QRect(210, 300, 81, 18));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(350, 60, 31, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(350, 90, 21, 18));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(350, 140, 21, 18));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(350, 170, 16, 18));
        label_posX = new QLabel(groupBox);
        label_posX->setObjectName(QStringLiteral("label_posX"));
        label_posX->setGeometry(QRect(370, 60, 81, 18));
        label_posY = new QLabel(groupBox);
        label_posY->setObjectName(QStringLiteral("label_posY"));
        label_posY->setGeometry(QRect(370, 90, 81, 18));
        label_width = new QLabel(groupBox);
        label_width->setObjectName(QStringLiteral("label_width"));
        label_width->setGeometry(QRect(370, 140, 81, 18));
        label_height = new QLabel(groupBox);
        label_height->setObjectName(QStringLiteral("label_height"));
        label_height->setGeometry(QRect(370, 170, 81, 18));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(70, 60, 41, 18));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(70, 100, 31, 18));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(70, 140, 31, 18));
        label_rVal = new QLabel(groupBox);
        label_rVal->setObjectName(QStringLiteral("label_rVal"));
        label_rVal->setGeometry(QRect(100, 60, 81, 18));
        label_gVal = new QLabel(groupBox);
        label_gVal->setObjectName(QStringLiteral("label_gVal"));
        label_gVal->setGeometry(QRect(100, 100, 81, 18));
        label_bVal = new QLabel(groupBox);
        label_bVal->setObjectName(QStringLiteral("label_bVal"));
        label_bVal->setGeometry(QRect(100, 140, 81, 18));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(70, 180, 111, 18));
        label_gsVal = new QLabel(groupBox);
        label_gsVal->setObjectName(QStringLiteral("label_gsVal"));
        label_gsVal->setGeometry(QRect(170, 180, 81, 18));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(170, 40, 1212, 863));
        layer1 = new QWidget();
        layer1->setObjectName(QStringLiteral("layer1"));
        scrollArea = new QScrollArea(layer1);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(0, 0, 1212, 834));
        scrollArea->setMinimumSize(QSize(0, 0));
        scrollArea->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1184, 806));
        scrollArea->setWidget(scrollAreaWidgetContents);
        tabWidget->addTab(layer1, QString());
        layer2 = new QWidget();
        layer2->setObjectName(QStringLiteral("layer2"));
        scrollArea_2 = new QScrollArea(layer2);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setGeometry(QRect(0, 0, 1212, 834));
        scrollArea_2->setMinimumSize(QSize(0, 0));
        scrollArea_2->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
        scrollArea_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 1184, 806));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);
        tabWidget->addTab(layer2, QString());
        layer3 = new QWidget();
        layer3->setObjectName(QStringLiteral("layer3"));
        scrollArea_3 = new QScrollArea(layer3);
        scrollArea_3->setObjectName(QStringLiteral("scrollArea_3"));
        scrollArea_3->setGeometry(QRect(0, 0, 1212, 834));
        scrollArea_3->setMinimumSize(QSize(0, 0));
        scrollArea_3->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
        scrollArea_3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea_3->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QStringLiteral("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 1184, 806));
        scrollArea_3->setWidget(scrollAreaWidgetContents_3);
        tabWidget->addTab(layer3, QString());
        layer4 = new QWidget();
        layer4->setObjectName(QStringLiteral("layer4"));
        scrollArea_4 = new QScrollArea(layer4);
        scrollArea_4->setObjectName(QStringLiteral("scrollArea_4"));
        scrollArea_4->setGeometry(QRect(0, 0, 1212, 834));
        scrollArea_4->setMinimumSize(QSize(0, 0));
        scrollArea_4->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
        scrollArea_4->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea_4->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea_4->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QStringLiteral("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 1184, 806));
        scrollArea_4->setWidget(scrollAreaWidgetContents_4);
        tabWidget->addTab(layer4, QString());
        layer5 = new QWidget();
        layer5->setObjectName(QStringLiteral("layer5"));
        scrollArea_5 = new QScrollArea(layer5);
        scrollArea_5->setObjectName(QStringLiteral("scrollArea_5"));
        scrollArea_5->setGeometry(QRect(0, 0, 1212, 834));
        scrollArea_5->setMinimumSize(QSize(0, 0));
        scrollArea_5->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
        scrollArea_5->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea_5->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea_5->setWidgetResizable(true);
        scrollAreaWidgetContents_5 = new QWidget();
        scrollAreaWidgetContents_5->setObjectName(QStringLiteral("scrollAreaWidgetContents_5"));
        scrollAreaWidgetContents_5->setGeometry(QRect(0, 0, 1184, 806));
        scrollArea_5->setWidget(scrollAreaWidgetContents_5);
        tabWidget->addTab(layer5, QString());
        label_imagesize = new QLabel(centralWidget);
        label_imagesize->setObjectName(QStringLiteral("label_imagesize"));
        label_imagesize->setGeometry(QRect(1230, 48, 151, 18));
        leftToolBar = new QWidget(centralWidget);
        leftToolBar->setObjectName(QStringLiteral("leftToolBar"));
        leftToolBar->setGeometry(QRect(30, 70, 131, 691));
        normalModeBtn = new QPushButton(leftToolBar);
        normalModeBtn->setObjectName(QStringLiteral("normalModeBtn"));
        normalModeBtn->setGeometry(QRect(10, 10, 51, 34));
        slctModeBtn = new QPushButton(leftToolBar);
        slctModeBtn->setObjectName(QStringLiteral("slctModeBtn"));
        slctModeBtn->setGeometry(QRect(70, 10, 51, 34));
        pushButton = new QPushButton(leftToolBar);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 60, 51, 34));
        pushButton_2 = new QPushButton(leftToolBar);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(70, 60, 51, 34));
        line_3 = new QFrame(leftToolBar);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(0, 550, 131, 20));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        picked_color1 = new QLabel(leftToolBar);
        picked_color1->setObjectName(QStringLiteral("picked_color1"));
        picked_color1->setGeometry(QRect(20, 570, 51, 51));
        picked_color2 = new QLabel(leftToolBar);
        picked_color2->setObjectName(QStringLiteral("picked_color2"));
        picked_color2->setGeometry(QRect(60, 610, 51, 51));
        colorSwitchBtn = new QPushButton(leftToolBar);
        colorSwitchBtn->setObjectName(QStringLiteral("colorSwitchBtn"));
        colorSwitchBtn->setGeometry(QRect(80, 570, 31, 34));
        colorResetBtn = new QPushButton(leftToolBar);
        colorResetBtn->setObjectName(QStringLiteral("colorResetBtn"));
        colorResetBtn->setGeometry(QRect(10, 630, 31, 34));
        getColorBtn = new QPushButton(leftToolBar);
        getColorBtn->setObjectName(QStringLiteral("getColorBtn"));
        getColorBtn->setGeometry(QRect(10, 510, 112, 34));
        cutBtn = new QPushButton(leftToolBar);
        cutBtn->setObjectName(QStringLiteral("cutBtn"));
        cutBtn->setGeometry(QRect(10, 110, 51, 34));
        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(30, 60, 131, 20));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_6 = new QFrame(centralWidget);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(30, 750, 131, 16));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);
        line_7 = new QFrame(centralWidget);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setGeometry(QRect(150, 70, 16, 691));
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(centralWidget);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(18, 70, 20, 691));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);
        containerWidget = new QWidget(centralWidget);
        containerWidget->setObjectName(QStringLiteral("containerWidget"));
        containerWidget->setGeometry(QRect(1430, 430, 461, 471));
        hsvWidget = new QWidget(containerWidget);
        hsvWidget->setObjectName(QStringLiteral("hsvWidget"));
        hsvWidget->setGeometry(QRect(10, 10, 441, 241));
        horizontalSlider_h = new QSlider(hsvWidget);
        horizontalSlider_h->setObjectName(QStringLiteral("horizontalSlider_h"));
        horizontalSlider_h->setGeometry(QRect(80, 30, 291, 22));
        horizontalSlider_h->setOrientation(Qt::Horizontal);
        horizontalSlider_s = new QSlider(hsvWidget);
        horizontalSlider_s->setObjectName(QStringLiteral("horizontalSlider_s"));
        horizontalSlider_s->setGeometry(QRect(80, 90, 291, 22));
        horizontalSlider_s->setOrientation(Qt::Horizontal);
        horizontalSlider_v = new QSlider(hsvWidget);
        horizontalSlider_v->setObjectName(QStringLiteral("horizontalSlider_v"));
        horizontalSlider_v->setGeometry(QRect(80, 150, 291, 22));
        horizontalSlider_v->setOrientation(Qt::Horizontal);
        label_9 = new QLabel(hsvWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(50, 30, 31, 18));
        label_10 = new QLabel(hsvWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(50, 90, 16, 18));
        label_11 = new QLabel(hsvWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(50, 150, 16, 18));
        HSVokBtn = new QPushButton(hsvWidget);
        HSVokBtn->setObjectName(QStringLiteral("HSVokBtn"));
        HSVokBtn->setGeometry(QRect(280, 190, 112, 34));
        doubleThreshodWidget = new QWidget(containerWidget);
        doubleThreshodWidget->setObjectName(QStringLiteral("doubleThreshodWidget"));
        doubleThreshodWidget->setGeometry(QRect(10, 10, 441, 171));
        inputThreshod1 = new QSpinBox(doubleThreshodWidget);
        inputThreshod1->setObjectName(QStringLiteral("inputThreshod1"));
        inputThreshod1->setGeometry(QRect(120, 30, 49, 25));
        inputThreshod1->setMaximum(255);
        label_12 = new QLabel(doubleThreshodWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(20, 33, 101, 18));
        label_13 = new QLabel(doubleThreshodWidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(200, 33, 111, 18));
        inputThreshod2 = new QSpinBox(doubleThreshodWidget);
        inputThreshod2->setObjectName(QStringLiteral("inputThreshod2"));
        inputThreshod2->setGeometry(QRect(310, 30, 49, 25));
        inputThreshod2->setMaximum(255);
        doubleThreshodOkBtn = new QPushButton(doubleThreshodWidget);
        doubleThreshodOkBtn->setObjectName(QStringLiteral("doubleThreshodOkBtn"));
        doubleThreshodOkBtn->setGeometry(QRect(310, 100, 112, 34));
        miniPSClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(miniPSClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1920, 30));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menucolor_operation = new QMenu(menuEdit);
        menucolor_operation->setObjectName(QStringLiteral("menucolor_operation"));
        menuchannel_split = new QMenu(menucolor_operation);
        menuchannel_split->setObjectName(QStringLiteral("menuchannel_split"));
        menubinary_analysis = new QMenu(menuEdit);
        menubinary_analysis->setObjectName(QStringLiteral("menubinary_analysis"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        menuWindow_mode = new QMenu(menuSettings);
        menuWindow_mode->setObjectName(QStringLiteral("menuWindow_mode"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        miniPSClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(miniPSClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        miniPSClass->setStatusBar(statusBar);
        mainToolBar = new QToolBar(miniPSClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        miniPSClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionopen_image);
        menuFile->addSeparator();
        menuFile->addAction(actionsave_image);
        menuFile->addSeparator();
        menuFile->addAction(actionminimize);
        menuFile->addAction(actionexit);
        menuEdit->addAction(actionundo);
        menuEdit->addAction(actionclean_all_layers);
        menuEdit->addAction(menucolor_operation->menuAction());
        menuEdit->addAction(menubinary_analysis->menuAction());
        menucolor_operation->addAction(menuchannel_split->menuAction());
        menucolor_operation->addAction(actionRGB2GrayScale);
        menucolor_operation->addAction(actionHSB);
        menuchannel_split->addAction(actionRed);
        menuchannel_split->addAction(actionGreen);
        menuchannel_split->addAction(actionBlue);
        menubinary_analysis->addAction(actionOtus_Algo);
        menubinary_analysis->addAction(actiondouble_threshod);
        menuSettings->addSeparator();
        menuSettings->addAction(menuWindow_mode->menuAction());
        menuWindow_mode->addAction(actionfull_screen);
        menuWindow_mode->addAction(actionwindowed);

        retranslateUi(miniPSClass);
        QObject::connect(exitBtn, SIGNAL(clicked()), miniPSClass, SLOT(close()));
        QObject::connect(tabWidget, SIGNAL(tabBarClicked(int)), miniPSClass, SLOT(update()));

        exitBtn->setDefault(true);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(miniPSClass);
    } // setupUi

    void retranslateUi(QMainWindow *miniPSClass)
    {
        miniPSClass->setWindowTitle(QApplication::translate("miniPSClass", "miniPS", Q_NULLPTR));
        actionopen_image->setText(QApplication::translate("miniPSClass", "load image", Q_NULLPTR));
#ifndef QT_NO_STATUSTIP
        actionopen_image->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        actionsave_image->setText(QApplication::translate("miniPSClass", "save", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        actionsave_image->setWhatsThis(QApplication::translate("miniPSClass", "to save image", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        actionminimize->setText(QApplication::translate("miniPSClass", "minimize", Q_NULLPTR));
        actionundo->setText(QApplication::translate("miniPSClass", "undo", Q_NULLPTR));
        actionfull_screen->setText(QApplication::translate("miniPSClass", "full screen", Q_NULLPTR));
        actionwindowed->setText(QApplication::translate("miniPSClass", "windowed", Q_NULLPTR));
        actionexit->setText(QApplication::translate("miniPSClass", "exit", Q_NULLPTR));
        actionclean_all_layers->setText(QApplication::translate("miniPSClass", "clean all layers", Q_NULLPTR));
        actionRGB2GrayScale->setText(QApplication::translate("miniPSClass", "RGB2GrayScale", Q_NULLPTR));
        actionRed->setText(QApplication::translate("miniPSClass", "Red", Q_NULLPTR));
        actionGreen->setText(QApplication::translate("miniPSClass", "Green", Q_NULLPTR));
        actionBlue->setText(QApplication::translate("miniPSClass", "Blue", Q_NULLPTR));
        actionHSB->setText(QApplication::translate("miniPSClass", "HSB", Q_NULLPTR));
        actionOtus_Algo->setText(QApplication::translate("miniPSClass", "Otus Algo", Q_NULLPTR));
        actiondouble_threshod->setText(QApplication::translate("miniPSClass", "double threshod", Q_NULLPTR));
        exitBtn->setText(QApplication::translate("miniPSClass", "QUIT", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("miniPSClass", "Inpector", Q_NULLPTR));
        zoomOutBtn->setText(QApplication::translate("miniPSClass", "-", Q_NULLPTR));
        zoomInBtn->setText(QApplication::translate("miniPSClass", "+", Q_NULLPTR));
        label_scaleVal->setText(QApplication::translate("miniPSClass", "100%", Q_NULLPTR));
        label->setText(QApplication::translate("miniPSClass", "X:", Q_NULLPTR));
        label_2->setText(QApplication::translate("miniPSClass", "Y:", Q_NULLPTR));
        label_3->setText(QApplication::translate("miniPSClass", "W:", Q_NULLPTR));
        label_4->setText(QApplication::translate("miniPSClass", "H:", Q_NULLPTR));
        label_posX->setText(QApplication::translate("miniPSClass", "0", Q_NULLPTR));
        label_posY->setText(QApplication::translate("miniPSClass", "0", Q_NULLPTR));
        label_width->setText(QApplication::translate("miniPSClass", "0", Q_NULLPTR));
        label_height->setText(QApplication::translate("miniPSClass", "0", Q_NULLPTR));
        label_5->setText(QApplication::translate("miniPSClass", "R:", Q_NULLPTR));
        label_6->setText(QApplication::translate("miniPSClass", "G:", Q_NULLPTR));
        label_7->setText(QApplication::translate("miniPSClass", "B:", Q_NULLPTR));
        label_rVal->setText(QApplication::translate("miniPSClass", "0", Q_NULLPTR));
        label_gVal->setText(QApplication::translate("miniPSClass", "0", Q_NULLPTR));
        label_bVal->setText(QApplication::translate("miniPSClass", "0", Q_NULLPTR));
        label_8->setText(QApplication::translate("miniPSClass", "GrayScale:", Q_NULLPTR));
        label_gsVal->setText(QApplication::translate("miniPSClass", "0", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(layer1), QApplication::translate("miniPSClass", "Image1", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(layer2), QApplication::translate("miniPSClass", "Image2", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(layer3), QApplication::translate("miniPSClass", "Image3", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(layer4), QApplication::translate("miniPSClass", "Image4", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(layer5), QApplication::translate("miniPSClass", "Image5", Q_NULLPTR));
        label_imagesize->setText(QApplication::translate("miniPSClass", "0 * 0 px", Q_NULLPTR));
        normalModeBtn->setText(QApplication::translate("miniPSClass", "norm", Q_NULLPTR));
        slctModeBtn->setText(QApplication::translate("miniPSClass", "slct", Q_NULLPTR));
        pushButton->setText(QApplication::translate("miniPSClass", "pen", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("miniPSClass", "erase", Q_NULLPTR));
        picked_color1->setText(QString());
        picked_color2->setText(QString());
#ifndef QT_NO_WHATSTHIS
        colorSwitchBtn->setWhatsThis(QApplication::translate("miniPSClass", "Exchange two gethered color", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        colorSwitchBtn->setText(QApplication::translate("miniPSClass", "ex", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        colorResetBtn->setWhatsThis(QApplication::translate("miniPSClass", "Reset the gethered color to black and white", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        colorResetBtn->setText(QApplication::translate("miniPSClass", "re", Q_NULLPTR));
        getColorBtn->setText(QApplication::translate("miniPSClass", "get color", Q_NULLPTR));
        cutBtn->setText(QApplication::translate("miniPSClass", "cut", Q_NULLPTR));
        label_9->setText(QApplication::translate("miniPSClass", "H\357\274\232", Q_NULLPTR));
        label_10->setText(QApplication::translate("miniPSClass", "S\357\274\232", Q_NULLPTR));
        label_11->setText(QApplication::translate("miniPSClass", "V:", Q_NULLPTR));
        HSVokBtn->setText(QApplication::translate("miniPSClass", "OK", Q_NULLPTR));
        label_12->setText(QApplication::translate("miniPSClass", "Threshod 1:", Q_NULLPTR));
        label_13->setText(QApplication::translate("miniPSClass", "Threshod 2:", Q_NULLPTR));
        doubleThreshodOkBtn->setText(QApplication::translate("miniPSClass", "OK", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("miniPSClass", "File", Q_NULLPTR));
        menuEdit->setTitle(QApplication::translate("miniPSClass", "Edit", Q_NULLPTR));
        menucolor_operation->setTitle(QApplication::translate("miniPSClass", "color operation", Q_NULLPTR));
        menuchannel_split->setTitle(QApplication::translate("miniPSClass", "channel split", Q_NULLPTR));
        menubinary_analysis->setTitle(QApplication::translate("miniPSClass", "binary analysis", Q_NULLPTR));
        menuSettings->setTitle(QApplication::translate("miniPSClass", "Settings", Q_NULLPTR));
        menuWindow_mode->setTitle(QApplication::translate("miniPSClass", "window mode", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("miniPSClass", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class miniPSClass: public Ui_miniPSClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINIPS_H
