#include "imageProcessor.h"


ImageProcessor::ImageProcessor() {
	Mat defaultMat;
	images = { defaultMat , defaultMat , defaultMat , defaultMat , defaultMat };
}

void ImageProcessor::loadImage(const char* name, int idx) {
	images[idx] = imread(name);
}

void ImageProcessor::saveImage(const char* name, int idx) {
	imwrite(name, images[idx]);
}

void ImageProcessor::showImage(int idx) {
	Mat van = imread("van.jpg");
	namedWindow("Õ¥ø‡VAN∑÷");
	imshow("Õ¥ø‡VAN∑÷", van);
}

std::vector<int> ImageProcessor::getPixelVal(int x, int y, int idx) {

	std::vector<int> ans;
	QString xStr, yStr;
	xStr.sprintf("%d", x);
	yStr.sprintf("%d", y);
	qDebug("x = %s", qPrintable(xStr));
	qDebug("y = %s", qPrintable(yStr));

	int iChannels = images[idx].channels();
	int iRows = images[idx].rows;
	int iCols = images[idx].cols;

	switch (iChannels) {
	// Grayscale
	case 1: {
		int grayScaleVal = images[idx].at<uchar>(y, x);
		ans = { grayScaleVal, grayScaleVal, grayScaleVal, 0 };
	}
    // RGB
	case 3: {
		Vec3b rgbVal = images[idx].at<Vec3b>(y, x);
		ans = { rgbVal[2], rgbVal[1], rgbVal[0], 1 };
	}
	}
	return ans;
}