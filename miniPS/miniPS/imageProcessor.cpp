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
				images[idx].at<Vec3b>(i, j)[k] = images[idx].at<Vec3b>(i, j)[2-rgbNum];
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

	memset(ihist, 0, sizeof(int)*256);
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
				Vec3b tmp = img.at<Vec3b>(i, j);
				ihist[tmp[2 - channelNum]]++;
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

void ImageProcessor::addOper(int idx1, int idx2, double weight1, double weight2, int posX, int posY) {
	commit(idx1);
	int iRows1 = images[idx1].rows;
	int iCols1 = images[idx1].cols;
	int iRows2 = images[idx2].rows;
	int iCols2 = images[idx2].cols;
	int adjX = (posX >= iCols1) ? 0 : posX;// Check (posX, posY) in the range of images[idx1]
	int adjY = (posY >= iRows1) ? 0 : posY;
	int rangeX = (adjX + iCols2 >= iCols1) ? (iCols1 - adjX) : iCols2;// If images[idx2] is bigger, truncate it.
	int rangeY = (adjY + iRows2 >= iRows1) ? (iRows1 - adjY) : iRows2;
	Mat imageROI;
	imageROI = images[idx1](Rect(posX, posY, rangeX, rangeY));
	for (int i = 0; i < rangeY; i++) {
		for (int j = 0; j < rangeX; j++) {
			Vec3b left = imageROI.at<Vec3b>(i, j);
			Vec3b right = images[idx2].at<Vec3b>(i, j);
			Vec3b ans = weight1*left + weight2*right;
			for (int k = 0; k < 3; k++) {
				if (ans[k] > 255)
					ans[k] = 255;
			}
			imageROI.at<Vec3b>(i, j) = ans;
		}
	}
}

void ImageProcessor::subtractionOper(int idx1, int idx2, int posX, int posY) {
	commit(idx1);
	int iRows1 = images[idx1].rows;
	int iCols1 = images[idx1].cols;
	int iRows2 = images[idx2].rows;
	int iCols2 = images[idx2].cols;
	int adjX = (posX >= iCols1) ? 0 : posX;// Check (posX, posY) in the range of images[idx1]
	int adjY = (posY >= iRows1) ? 0 : posY;
	int rangeX = (adjX + iCols2 >= iCols1) ? (iCols1 - adjX) : iCols2;// If images[idx2] is bigger, truncate it.
	int rangeY = (adjY + iRows2 >= iRows1) ? (iRows1 - adjY) : iRows2;
	Mat imageROI;
	imageROI = images[idx1](Rect(posX, posY, rangeX, rangeY));
	for (int i = 0; i < rangeY; i++) {
		for (int j = 0; j < rangeX; j++) {
			Vec3b left = imageROI.at<Vec3b>(i, j);
			Vec3b right = images[idx2].at<Vec3b>(i, j);
			Vec3b ans = left - right;
			for (int k = 0; k < 3; k++) {
				if (ans[k] < 0)
					ans[k] = 0;
			}
			imageROI.at<Vec3b>(i, j) = ans;
		}
	}
}

bool ImageProcessor::multiplicationOper(int idx1, int idx2) {
	commit(idx1);
	int iRows1 = images[idx1].rows;
	int iCols1 = images[idx1].cols;
	int iRows2 = images[idx2].rows;
	int iCols2 = images[idx2].cols;
	if (iRows1 != iRows2 || iCols1 != iCols2)
		return false;
	for (int i = 0; i < iRows1; i++) {
		for (int j = 0; j < iCols1; j++) {
			Vec3b left = images[idx1].at<Vec3b>(i, j);
			Vec3b right = images[idx2].at<Vec3b>(i, j);
			uchar tmp0 = left[0] * right[0]/255;
			uchar tmp1 = left[1] * right[1] / 255;
			uchar tmp2 = left[2] * right[2] / 255;
			Vec3b ans = {tmp0, tmp1, tmp2};
			images[idx1].at<Vec3b>(i, j) = ans;
		}
	}
}

bool ImageProcessor::divisionOper(int idx1, int idx2) {
	commit(idx1);
	int iRows1 = images[idx1].rows;
	int iCols1 = images[idx1].cols;
	int iRows2 = images[idx2].rows;
	int iCols2 = images[idx2].cols;
	if (iRows1 != iRows2 || iCols1 != iCols2)
		return false;
	for (int i = 0; i < iRows1; i++) {
		for (int j = 0; j < iCols1; j++) {
			Vec3b left = images[idx1].at<Vec3b>(i, j);
			Vec3b right = images[idx2].at<Vec3b>(i, j);
			uchar tmp0 = left[0] / right[0]  * 255;
			uchar tmp1 = left[1] / right[1] * 255;
			uchar tmp2 = left[2] / right[2] * 255;
			Vec3b ans = { tmp0, tmp1, tmp2 };
			images[idx1].at<Vec3b>(i, j) = ans;
		}
	}
}

void ImageProcessor::resize(int width, int height, int choiceNum, int idx) {
	commit(idx);
	Mat newImg(height, width, images[idx].type());
	if (choiceNum == NN) { // Use NN
		int srcHeight = images[idx].rows;
		int srcWidth = images[idx].cols;
		float hRate = (float)srcHeight / height;
		float wRate = (float)srcWidth / width;
		int srcX, srcY;
		for (int i = 0; i < height; i++) {
			srcY = int(i * hRate);
			for (int j = 0; j < width; j++) {
				srcX = int(j * wRate);
				newImg.at<Vec3b>(i, j) = images[idx].at<Vec3b>(srcY, srcX);
			}
		}
	}
	else if(choiceNum == LINEAR){ // Use LINEAR
	
	}
	images[idx] = newImg;
}

void ImageProcessor::spinCW(int idx) {
	commit(idx);
	int iRows = images[idx].rows;
	int iCols = images[idx].cols;
	Mat newImg(iCols, iRows, images[idx].type());
	for (int i = 0; i < iRows; i++) {
		for (int j = 0; j < iCols; j++) {
			newImg.at<Vec3b>(j, iRows -1 - i) = images[idx].at<Vec3b>(i,j);
		}
	}
	images[idx] = newImg;
}

void ImageProcessor::drawHist(int channelNum, int idx) {
	int ihist[256];
	makeHist(ihist, channelNum, images[idx]);
	Mat histImg = Mat::zeros(256, 512, CV_8UC3);
	int maxHistVal = 0;
	for (int k = 0; k < 256; k++) {
		if (ihist[k] > maxHistVal) {
			maxHistVal = ihist[k];
		}
	}
	CvScalar color;
	switch (channelNum) {
	case CHANNEL_R:
		color = CV_RGB(255, 0, 0);
		break;
	case CHANNEL_G:
		color = CV_RGB(0, 255, 0);
		break;
	case CHANNEL_B:
		color = CV_RGB(0, 0, 255);
		break;
	}
	for (int i = 0; i < 512; i++) {
		int drawVal = ihist[i/2] * 256 / maxHistVal;
		line(histImg, Point(i, 256), Point(i, 256- drawVal), color);
	}
	imshow("histogram", histImg);
}

void ImageProcessor::histEqualization(int idx) {
	commit(idx);
	int iRows = images[idx].rows;
	int iCols = images[idx].cols;
	Mat newImg(iCols, iRows, images[idx].type());
	int rHist[256], gHist[256], bHist[256];
	makeHist(rHist, CHANNEL_R, images[idx]);
	makeHist(gHist, CHANNEL_G, images[idx]);
	makeHist(bHist, CHANNEL_B, images[idx]);
	int numberOfPixel = images[idx].rows*images[idx].cols;
	int rLUT[256], gLUT[256], bLUT[256];
	rLUT[0] = 1.0*rHist[0] / numberOfPixel * 255;
	gLUT[0] = 1.0*gHist[0] / numberOfPixel * 255;
	bLUT[0] = 1.0*bHist[0] / numberOfPixel * 255;
	int rSum = rHist[0], gSum = gHist[0], bSum = bHist[0];
	for (int i = 1; i < 256; i++) {
		rSum += rHist[i];
		rLUT[i] = 1.0 * rSum / numberOfPixel * 255;
		gSum += gHist[i];
		gLUT[i] = 1.0 * gSum / numberOfPixel * 255;
		bSum += bHist[i];
		bLUT[i] = 1.0 * bSum / numberOfPixel * 255;
	}
	for (int i = 0; i < iRows; i++) {
		for (int j = 0; j < iCols; j++) {
			Vec3b srcTmp = images[idx].at<Vec3b>(i, j), dstTmp;
			dstTmp[0] = bLUT[srcTmp[0]];
			dstTmp[1] = gLUT[srcTmp[1]];
			dstTmp[2] = rLUT[srcTmp[2]];
			images[idx].at<Vec3b>(i, j) = dstTmp;
		}
	}
}