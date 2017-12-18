#include "imageProcessor.h"


ImageProcessor::ImageProcessor() {
	Mat defaultMat;
	images = { defaultMat , defaultMat , defaultMat , defaultMat , defaultMat };
	imageBackups = { defaultMat , defaultMat , defaultMat , defaultMat , defaultMat };
}

void ImageProcessor::loadImage(const char* name, int idx) {
	images[idx] = imread(name);
}

void ImageProcessor::saveImage(const char* name, int idx) {
	imwrite(name, images[idx]);
}

void ImageProcessor::showImage(int idx) {
	Mat van = imread("van.jpg");
	namedWindow("痛苦VAN分");
	imshow("痛苦VAN分", van);
}

std::vector<int> ImageProcessor::getPixelVal(int x, int y, int idx) {

	std::vector<int> ans;

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

void ImageProcessor::commit(int idx) {
	imageBackups[idx] = images[idx].clone();
	undoMarks[idx] = true;
}

bool ImageProcessor::undo(int idx) {
	if (! undoMarks[idx]) {
		return false;
	}
	else {
		images[idx] = imageBackups[idx];
		undoMarks[idx] = false;
		return true;
	}
}

void ImageProcessor::channelSplit(int rgbNum, int idx) {
	commit(idx);
	qDebug("channel split called.");
	int iChannels = images[idx].channels();
	int iRows = images[idx].rows;
	int iCols = images[idx].cols;
	if (rgbNum != 0 && rgbNum != 1 && rgbNum != 2) {
		qDebug("channel split fail: rgbNum not in {0,1,2}\n");
		return;
	}
	if (iChannels != 3) {
		qDebug("channel split fail: channel != 3\n");
		return;
	}
	for (int i = 0; i < iRows; i++) {
		for (int j = 0; j < iCols; j++) {
			for (int k = 0; k < 3; k++) {
				if (k == rgbNum)
					continue;
				images[idx].at<Vec3b>(i, j)[k] = images[idx].at<Vec3b>(i, j)[rgbNum];
			}
		}
	}
}

void ImageProcessor::rgb2gry(int idx) {
	commit(idx);
	int iChannels = images[idx].channels();
	int iRows = images[idx].rows;
	int iCols = images[idx].cols;
	if (iChannels != 3) {
		qDebug("RGB to grayvalue fail: channel != 3\n");
		return;
	}
	for (int i = 0; i < iRows; i++) {
		for (int j = 0; j < iCols; j++) {
			int r = images[idx].at<Vec3b>(i, j)[2];
			int g = images[idx].at<Vec3b>(i, j)[1];
			int b = images[idx].at<Vec3b>(i, j)[0];
			int gray = (r * 299 + g * 587 + b * 114 + 500) / 1000;
			images[idx].at<Vec3b>(i, j)[0] = gray;
			images[idx].at<Vec3b>(i, j)[1] = gray;
			images[idx].at<Vec3b>(i, j)[2] = gray;
		}
	}
}

void ImageProcessor::makeHsvBackup(int idx) {
	cvtColor(images[idx], hsvBackup, CV_RGB2HSV);
}

void ImageProcessor::changeHSV(int hsvNum, int val, int idx) {

	Mat hsvImg(images[idx].size(), CV_8U, Scalar(0));
	cvtColor(images[idx], hsvImg, CV_RGB2HSV);
	int iRows = hsvImg.rows;
	int iCols = hsvImg.cols;
	for (int i = 0; i < iRows; i++) {
		for (int j = 0; j < iCols; j++) {
			if (hsvNum == 0) {
				hsvImg.at<Vec3b>(i, j)[hsvNum] = val;
			}
			else {
				//hsvImg.at<Vec3b>(i, j)[hsvNum] = hsvBackup.at<Vec3b>(i, j)[hsvNum] + val;
				int adjVal = hsvBackup.at<Vec3b>(i, j)[hsvNum] + val;
				if (adjVal > 255) {
					adjVal = 255;
				}
				if (adjVal < 0) {
					adjVal = 0;
				}
				hsvImg.at<Vec3b>(i, j)[hsvNum] = adjVal;
			}
		}
	}
	cvtColor(hsvImg, images[idx], CV_HSV2BGR);
}

/*Generate histogram of a grayscale image or one channel of an RGB image.
 * Memory for ihist MUST be allocated outside the funtion.
 * channelNum = {0, 1, 2} ---- red, green, blue
 */
void ImageProcessor::makeHist(int *ihist, int channelNum, Mat img) {

	memset(ihist, 0, sizeof(ihist));
	int iChannels = img.channels();
	int iRows = img.rows;
	int iCols = img.cols;
	if (iChannels == 1) { // grayscale image
		for (int i = 0; i < iRows; i++) {
			for (int j = 0; j < iCols; j++) {
				int tmp = img.at<uchar>(i, j);
				ihist[tmp]++;
			}
		}
	}
	else {  // RGB image
		for (int i = 0; i < iRows; i++) {
			for (int j = 0; j < iCols; j++) {
				int tmp = img.at<Vec3b>(i, j)[2-channelNum];
				ihist[tmp]++;
			}
		}
	}
}

/* Convert an image into binary image 
 * Otsu and double-threshod suported
 */
void ImageProcessor::toBinary(bool useOtsu, int th1, int th2, int idx) {
	commit(idx);
	Mat copyImg = images[idx].clone();
	int iRows = copyImg.rows;
	int iCols = copyImg.cols;
	if (copyImg.channels() != 1) {
		// convert the image into grayscale
		cvtColor(copyImg, copyImg, CV_RGB2GRAY);
	}
	if (useOtsu) {
		int threshod = otsu(copyImg);
		for (int i = 0; i < iRows; i++) {
			for (int j = 0; j < iCols; j++) {
				int tmp = copyImg.at<uchar>(i, j);
				copyImg.at<uchar>(i, j) = (tmp > threshod) ? 255 : 0;
			}
		}
	}
	else {
		for (int i = 0; i < iRows; i++) {
			for (int j = 0; j < iCols; j++) {
				int tmp = copyImg.at<uchar>(i, j);
				if (tmp > th1 && tmp < th2) {
					copyImg.at<uchar>(i, j) = 255;
				}
				else {
					copyImg.at<uchar>(i, j) = 0;
				}
			}
		}
	}
	for (int i = 0; i < iRows; i++) {
		for (int j = 0; j < iCols; j++) {
			unsigned char tmp = copyImg.at<uchar>(i, j);
			Vec3b tmpVec = { tmp, tmp, tmp };
			images[idx].at<Vec3b>(i, j) = tmpVec;
		}
	}
}

int ImageProcessor::otsu(Mat img) {
	unsigned char *np; 
	int thresholdValue = 1;
	int ihist[256]; 
	int i, j, k; // various counters
	int n, n1, n2, gmin, gmax;
	double m1, m2, sum, csum, fmax, sb;
	gmin = 255; gmax = 0;
	makeHist(ihist, 0, img);
	// set up everything
	sum = csum = 0.0;
	n = 0;
	for (k = 0; k <= 255; k++)
	{
		sum += (double)k * (double)ihist[k]; // x*f(x) 质量矩
		n += ihist[k]; //f(x) 质量
	}
	if (!n)
	{
		// if n has no value, there is problems
		fprintf(stderr, "NOT NORMAL thresholdValue = 160\n");
		return (160);
	}
	// do the otsu global thresholding method
	fmax = -1.0;
	n1 = 0;
	for (k = 0; k < 255; k++)
	{
		n1 += ihist[k];
		if (!n1) { continue; }
		n2 = n - n1;
		if (n2 == 0) { break; }
		csum += (double)k *ihist[k];
		m1 = csum / n1;
		m2 = (sum - csum) / n2;
		sb = (double)n1 *(double)n2 *(m1 - m2) * (m1 - m2);
		/**//* bbg: note: can be optimized. */
		if (sb > fmax) {
			fmax = sb;
			thresholdValue = k;
		}
	}
	return(thresholdValue);
}