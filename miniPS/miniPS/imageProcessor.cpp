#include "imageProcessor.h"
#include <algorithm>


ImageProcessor::ImageProcessor() {
	Mat defaultMat;
	images = { defaultMat , defaultMat , defaultMat , defaultMat , defaultMat };
	imageBackups = { defaultMat , defaultMat , defaultMat , defaultMat , defaultMat };
}

void ImageProcessor::loadImage(const char* name, int idx) {
	// Default format: RGB
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

void ImageProcessor::bilinearInter(float x0, float y0, Mat img, int &rVal, int &gVal, int &bVal) {
	int iRows = img.rows, iCols = img.cols;
	int x1, x2, y1, y2;
	float w1, w2, w3, w4;
	Vec3b p1, p2, p3, p4;
	x1 = (int)x0;
	y1 = (int)y0;
	if (x1 < 0)
		x1 = 0;
	if (y1 < 0)
		y1 = 0;
	if (x1 == iCols - 1) {
		x2 = x1;
	}
	else {
		x2 = x1 + 1;
	}
	if (y1 == iRows - 1) {
		y2 = y1;
	}
	else {
		y2 = y1 + 1;
	}
	w1 = (x0 - x1)*(y0 - y1);
	w2 = (x2 - x0)*(y0 - y1);
	w3 = (x2 - x0)*(y2 - y0);
	w4 = (x0 - x1)*(y2 - y0);
	p1 = img.at<Vec3b>(y1, x1);
	p2 = img.at<Vec3b>(y1, x2);
	p3 = img.at<Vec3b>(y2, x2);
	p4 = img.at<Vec3b>(y2, x1);
	rVal = int(w1*p1[2] + w2*p2[2] + w3*p3[2] + w4*p4[2]);
	gVal = int(w1*p1[1] + w2*p2[1] + w3*p3[1] + w4*p4[1]);
	bVal = int(w1*p1[0] + w2*p2[0] + w3*p3[0] + w4*p4[0]);
}

void ImageProcessor::resize(int width, int height, int choiceNum, int idx) {
	commit(idx);
	Mat newImg(height, width, images[idx].type());
	int srcHeight = images[idx].rows;
	int srcWidth = images[idx].cols;
	float hRate = (float)srcHeight / height;
	float wRate = (float)srcWidth / width;
	if (choiceNum == NN) { // Use NN
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
		float srcX0, srcY0;
		int rVal, gVal, bVal;
		Vec3b pVal = { 0,0,0 };
		for (int i = 0; i < height; i++) {
			srcY0 = (i * hRate);
			for (int j = 0; j < width; j++) {
				srcX0 = (j * wRate);
				bilinearInter(srcX0, srcY0, images[idx], rVal, gVal, bVal);
				pVal[0] = bVal;  pVal[1] = gVal; pVal[2] = rVal;
				newImg.at<Vec3b>(i, j) = pVal;
			}
		}
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

void ImageProcessor::rotateCW(float theta, int choiceNum, int idx) {
	commit(idx);
	Mat imgOut;
	int oldWidth = images[idx].cols;
	int oldHeight = images[idx].rows;
 
	float fSrcX1, fSrcY1, fSrcX2, fSrcY2, fSrcX3, fSrcY3, fSrcX4, fSrcY4;
	fSrcX1 = (float)(-(oldWidth - 1) / 2);
	fSrcY1 = (float)((oldHeight - 1) / 2);
	fSrcX2 = (float)((oldWidth - 1) / 2);
	fSrcY2 = (float)((oldHeight - 1) / 2);
	fSrcX3 = (float)(-(oldWidth - 1) / 2);
	fSrcY3 = (float)(-(oldHeight - 1) / 2);
	fSrcX4 = (float)((oldWidth - 1) / 2);
	fSrcY4 = (float)(-(oldHeight - 1) / 2);

	float fDstX1, fDstY1, fDstX2, fDstY2, fDstX3, fDstY3, fDstX4, fDstY4;
	fDstX1 = cos(theta) * fSrcX1 + sin(theta) * fSrcY1;
	fDstY1 = -sin(theta) * fSrcX1 + cos(theta) * fSrcY1;
	fDstX2 = cos(theta) * fSrcX2 + sin(theta) * fSrcY2;
	fDstY2 = -sin(theta) * fSrcX2 + cos(theta) * fSrcY2;
	fDstX3 = cos(theta) * fSrcX3 + sin(theta) * fSrcY3;
	fDstY3 = -sin(theta) * fSrcX3 + cos(theta) * fSrcY3;
	fDstX4 = cos(theta) * fSrcX4 + sin(theta) * fSrcY4;
	fDstY4 = -sin(theta) * fSrcX4 + cos(theta) * fSrcY4;

	int newWidth = (max(fabs(fDstX4 - fDstX1), fabs(fDstX3 - fDstX2)) + 0.5);
	int newHeight = (max(fabs(fDstY4 - fDstY1), fabs(fDstY3 - fDstY2)) + 0.5);

	imgOut.create(newHeight, newWidth, images[idx].type());

	float dx = -0.5*newWidth*cos(theta) - 0.5*newHeight*sin(theta) + 0.5*oldWidth;
	float dy = 0.5*newWidth*sin(theta) - 0.5*newHeight*cos(theta) + 0.5*oldHeight;

	int x, y;
	for (int i = 0; i<newHeight; i++)
	{
		for (int j = 0; j<newWidth; j++)
		{
			x = float(j)*cos(theta) + float(i)*sin(theta) + dx;
			y = float(-j)*sin(theta) + float(i)*cos(theta) + dy;

			if ((x<0) || (x >= oldWidth) || (y<0) || (y >= oldHeight))
			{
				imgOut.at<cv::Vec3b>(i, j) = cv::Vec3b(255, 255, 255);
			}
			else
			{
				if (choiceNum == LINEAR) { // Use BILINEAR
					int rVal, gVal, bVal;
					bilinearInter(x, y, images[idx], rVal, gVal, bVal);
					Vec3b pVal = { 0,0,0 };
					pVal[0] = bVal; pVal[1] = gVal; pVal[2] = rVal;
					imgOut.at<cv::Vec3b>(i, j) = pVal;
				}
				else { // Use NN
					imgOut.at<cv::Vec3b>(i, j) = images[idx].at<cv::Vec3b>(y, x);
				}
			}
		}
	}
	images[idx] = imgOut;
}

void ImageProcessor::linearGSA(int A, int B, int C, int D, int channelNum, int idx) {
	int iRows = images[idx].rows;
	int iCols = images[idx].cols;

	for (int i = 0; i < iRows; i++) {
		for (int j = 0; j < iCols; j++) {
			Vec3b tmp = GSABackup.at<Vec3b>(i, j);
			//Vec3b tmp = images[idx].at<Vec3b>(i, j);
			int value = tmp[2 - channelNum];
			if (value >= B) {
				value = (value - B)*(255 - D) / (255 - B) + D;
			}
			else if (value >= A && value < B) {
				value = (value - A)*(D - C) / (B - A) + C;
			}
			else {
				value = value * C / A;
			}
			tmp[2 - channelNum] = value;
			images[idx].at<Vec3b>(i, j) = tmp;
		}
	}
}

void ImageProcessor::expGSA(int A, int B, int C, int channelNum, int idx) {
	int iRows = images[idx].rows;
	int iCols = images[idx].cols;

	for (int i = 0; i < iRows; i++) {
		for (int j = 0; j < iCols; j++) {
			Vec3b tmp = images[idx].at<Vec3b>(i, j);
			double value = tmp[2 - channelNum]*1.00;
			value = pow(B, (C*(value - A))) - 1;
			if (value > 255)
				value = 255;
			if (value < 0)
				value = 0;
			tmp[2 - channelNum] =(int)value;
			images[idx].at<Vec3b>(i, j) = tmp;
		}
	}
}

void ImageProcessor::logGSA(int A, int B, int C, int channelNum, int idx) {
	int iRows = images[idx].rows;
	int iCols = images[idx].cols;

	for (int i = 0; i < iRows; i++) {
		for (int j = 0; j < iCols; j++) {
			Vec3b tmp = images[idx].at<Vec3b>(i, j);
			double value = tmp[2 - channelNum] * 1.00;
			value = A + (log(value + 1)) / (B*log(C));
			if (value > 255)
				value = 255;
			if (value < 0)
				value = 0;
			tmp[2 - channelNum] = (int)value;
			images[idx].at<Vec3b>(i, j) = tmp;
		}
	}
}

void ImageProcessor::makeGSABackup(int idx) {
	GSABackup = images[idx].clone();
}

Mat ImageProcessor::drawLinearFunction(int A, int B, int C, int D) {
	Mat res = Mat::zeros(256,  256, CV_8UC3);
	CvScalar color = CV_RGB(0, 255, 0);
	int y;
	for (int x = 0; x < 255; x++) {
		if (x >= B) {
			y = (x - B)*(255 - B) / (255 - D) + D;
		}
		else if (x >= A && x < B) {
			y = (x - A)*(D - C) / (B - A) + C;
		}
		else {
			y = x * C / A;
		}
		Point p(x, 256-y);
		circle(res, p, 2, color);
	}
	return res;
}

void ImageProcessor::filter2D(double **kernel, int ksize, int idx) {  // 卷积函数(默认 anchor 在卷积核中间)
	commit(idx);
	Mat newImg = images[idx].clone();
	int iRows = newImg.rows;
	int iCols = newImg.cols;
	for (int i = ksize / 2; i < iRows - ksize / 2; i++) {
		for (int j = ksize / 2; j < iCols - ksize / 2; j++) {
			Vec3b tmp = images[idx].at<Vec3b>(i, j);
			double rVal = 0, gVal = 0, bVal = 0;
			for (int m = 0; m < ksize; m++) {
				for (int n = 0; n < ksize; n++) {
					int i_t = i - (ksize / 2) + m;
					int j_t = j - (ksize / 2) + n;
					Vec3b tmp1 = images[idx].at<Vec3b>(i_t, j_t);
					rVal += kernel[m][n] * tmp1[2];
					gVal += kernel[m][n] * tmp1[1];
					bVal += kernel[m][n] * tmp1[0];
				}
			}
			if (rVal < 0)
				rVal = 0;
			if (gVal < 0)
				gVal = 0;
			if (bVal < 0)
				bVal = 0;
			if (rVal > 255)
				rVal = 255;
			if (gVal > 255)
				gVal = 255;
			if (bVal > 255)
				bVal = 255;
			tmp[0] = bVal;
			tmp[1] = gVal;
			tmp[2] = rVal;
			newImg.at<Vec3b>(i, j) = tmp;
		}
	}
	images[idx] = newImg;
}

void ImageProcessor::boxFilter(int ksize, int idx) {
	double val = 1.0 / (ksize*ksize);
	double **kernel;
	kernel = (double **)malloc(ksize * sizeof(double*));
	for (int i = 0; i < ksize; i++) {
		kernel[i] = (double *)malloc(ksize * sizeof(double));
		for (int j = 0; j < ksize; j++) {
			kernel[i][j] = val;
		}
	}
	filter2D(kernel, ksize, idx);
	for (int i = 0; i < ksize; i++) {
		delete kernel[i];
	}
	delete kernel;
}

void getGaussianKernel(double **gaus, const int size, const double sigma)
{
	const double PI = 4.0*atan(1.0);
	int center = size / 2;
	double sum = 0;
	for (int i = 0; i<size; i++)
	{
		for (int j = 0; j<size; j++)
		{
			gaus[i][j] = (1 / (2 * PI*sigma*sigma))*exp(-((i - center)*(i - center) + (j - center)*(j - center)) / (2 * sigma*sigma));
			sum += gaus[i][j];
		}
	}

	for (int i = 0; i<size; i++)
	{
		for (int j = 0; j<size; j++)
		{
			gaus[i][j] /= sum;
		}
	}
	return;
}

void ImageProcessor::gaussianFilter(int ksize, int idx) {
	double **kernel;
	kernel = (double **)malloc(ksize * sizeof(double*));
	for (int i = 0; i < ksize; i++) {
		kernel[i] = (double *)malloc(ksize * sizeof(double));
	}
	getGaussianKernel(kernel, ksize, SIGMA);
	filter2D(kernel, ksize, idx);
	for (int i = 0; i < ksize; i++) {
		delete kernel[i];
	}
	delete kernel;
}

void ImageProcessor::medianFilter(int ksize, int idx) {
	//commit(idx);
	//Mat newImg = images[idx].clone();
	//int iRows = newImg.rows;
	//int iCols = newImg.cols;
	//int *orderR = (int *)malloc(sizeof(int)*ksize ^ 2);
	//int *orderG = (int *)malloc(sizeof(int)*ksize ^ 2);
	//int *orderB = (int *)malloc(sizeof(int)*ksize ^ 2);
	//for (int i = ksize / 2; i < iRows - ksize / 2; i++) {
	//	for (int j = ksize / 2; j < iCols - ksize / 2; j++) {
	//		Vec3b tmp = images[idx].at<Vec3b>(i, j);
	//		for (int m = 0; m < ksize; m++) {
	//			for (int n = 0; n < ksize; n++) {
	//				int i_t = i - (ksize / 2) + m;
	//				int j_t = j - (ksize / 2) + n;
	//				Vec3b tmp1 = images[idx].at<Vec3b>(i_t, j_t);
	//				orderR[m*ksize + n] = tmp1[2];
	//				orderG[m*ksize + n] = tmp1[1];
	//				orderB[m*ksize + n] = tmp1[0];
	//			}
	//		}
	//		// sort
	//		std::sort(orderR, &orderR[ksize^2]);
	//		std::sort(orderG, &orderG[ksize ^ 2]);
	//		std::sort(orderB, &orderB[ksize ^ 2]);
	//		tmp[0] = orderB[(ksize ^ 2) / 2];
	//		tmp[1] = orderG[(ksize ^ 2) / 2];
	//		tmp[2] = orderR[(ksize ^ 2) / 2];
	//		newImg.at<Vec3b>(i, j) = tmp;
	//	}
	//}
	//images[idx] = newImg;
}

// Part of Canny filter
void SobelGradDirction(const Mat imageSource, Mat &imageSobelX, Mat &imageSobelY, double *&pointDrection)
{
	pointDrection = new double[(imageSource.rows - 1)*(imageSource.cols - 1)];
	for (int i = 0; i<(imageSource.rows - 1)*(imageSource.cols - 1); i++)
	{
		pointDrection[i] = 0;
	}
	imageSobelX = Mat::zeros(imageSource.size(), CV_32SC1);
	imageSobelY = Mat::zeros(imageSource.size(), CV_32SC1);
	uchar *P = imageSource.data;
	uchar *PX = imageSobelX.data;
	uchar *PY = imageSobelY.data;

	int step = imageSource.step;
	int stepXY = imageSobelX.step;
	int k = 0;
	int m = 0;
	int n = 0;
	for (int i = 1; i<(imageSource.rows - 1); i++)
	{
		for (int j = 1; j<(imageSource.cols - 1); j++)
		{
			//通过指针遍历图像上每一个像素   
			double gradY = P[(i - 1)*step + j + 1] + P[i*step + j + 1] * 2 + P[(i + 1)*step + j + 1] - P[(i - 1)*step + j - 1] - P[i*step + j - 1] * 2 - P[(i + 1)*step + j - 1];
			PY[i*stepXY + j*(stepXY / step)] = abs(gradY);
			double gradX = P[(i + 1)*step + j - 1] + P[(i + 1)*step + j] * 2 + P[(i + 1)*step + j + 1] - P[(i - 1)*step + j - 1] - P[(i - 1)*step + j] * 2 - P[(i - 1)*step + j + 1];
			PX[i*stepXY + j*(stepXY / step)] = abs(gradX);
			if (gradX == 0)
			{
				gradX = 0.00000000000000001;  //防止除数为0异常  
			}
			pointDrection[k] = atan(gradY / gradX)*57.3;//弧度转换为度  
			pointDrection[k] += 90;
			k++;
		}
	}
	convertScaleAbs(imageSobelX, imageSobelX);
	convertScaleAbs(imageSobelY, imageSobelY);
}

// Part of Canny filter
void SobelAmplitude(const Mat imageGradX, const Mat imageGradY, Mat &SobelAmpXY)
{
	SobelAmpXY = Mat::zeros(imageGradX.size(), CV_32FC1);
	for (int i = 0; i<SobelAmpXY.rows; i++)
	{
		for (int j = 0; j<SobelAmpXY.cols; j++)
		{
			float tmp = sqrt(imageGradX.at<uchar>(i, j)*imageGradX.at<uchar>(i, j) + imageGradY.at<uchar>(i, j)*imageGradY.at<uchar>(i, j));
			if (tmp > 255)
				tmp = 255;
			SobelAmpXY.at<float>(i, j) = tmp;
		}
	}
	convertScaleAbs(SobelAmpXY, SobelAmpXY);
}

// Part of Canny filter
void LocalMaxValue(const Mat imageInput, Mat &imageOutput, double *pointDrection)
{
	//imageInput.copyTo(imageOutput);  
	imageOutput = imageInput.clone();
	int k = 0;
	for (int i = 1; i<imageInput.rows - 1; i++)
	{
		for (int j = 1; j<imageInput.cols - 1; j++)
		{
			int value00 = imageInput.at<uchar>((i - 1), j - 1);
			int value01 = imageInput.at<uchar>((i - 1), j);
			int value02 = imageInput.at<uchar>((i - 1), j + 1);
			int value10 = imageInput.at<uchar>((i), j - 1);
			int value11 = imageInput.at<uchar>((i), j);
			int value12 = imageInput.at<uchar>((i), j + 1);
			int value20 = imageInput.at<uchar>((i + 1), j - 1);
			int value21 = imageInput.at<uchar>((i + 1), j);
			int value22 = imageInput.at<uchar>((i + 1), j + 1);

			if (pointDrection[k]>0 && pointDrection[k] <= 45)
			{
				if (value11 <= (value12 + (value02 - value12)*tan(pointDrection[(i-1)*imageOutput.rows + j])) || (value11 <= (value10 + (value20 - value10)*tan(pointDrection[(i-1)*imageOutput.rows + j]))))
				{
					imageOutput.at<uchar>(i, j) = 0;
				}
			}
			if (pointDrection[k]>45 && pointDrection[k] <= 90)

			{
				if (value11 <= (value01 + (value02 - value01) / tan(pointDrection[(i - 1)*imageOutput.cols + j])) || value11 <= (value21 + (value20 - value21) / tan(pointDrection[(i - 1)*imageOutput.cols + j])))
				{
					imageOutput.at<uchar>(i, j) = 0;

				}
			}
			if (pointDrection[k]>90 && pointDrection[k] <= 135)
			{
				if (value11 <= (value01 + (value00 - value01) / tan(180 - pointDrection[(i - 1)*imageOutput.cols + j])) || value11 <= (value21 + (value22 - value21) / tan(180 - pointDrection[(i - 1)*imageOutput.cols + j])))
				{
					imageOutput.at<uchar>(i, j) = 0;
				}
			}
			if (pointDrection[k]>135 && pointDrection[k] <= 180)
			{
				if (value11 <= (value10 + (value00 - value10)*tan(180 - pointDrection[(i-1)*imageOutput.cols + j])) || value11 <= (value12 + (value22 - value11)*tan(180 - pointDrection[(i-1)*imageOutput.cols + j])))
				{
					imageOutput.at<uchar>(i, j) = 0;
				}
			}
			k++;
		}
	}
}

// Part of Canny filter
void DoubleThreshold(Mat &imageIput, double lowThreshold, double highThreshold)
{
	for (int i = 0; i<imageIput.rows; i++)
	{
		for (int j = 0; j<imageIput.cols; j++)
		{
			if (imageIput.at<uchar>(i, j)>highThreshold)
			{
				imageIput.at<uchar>(i, j) = 255;
			}
			if (imageIput.at<uchar>(i, j)<lowThreshold)
			{
				imageIput.at<uchar>(i, j) = 0;
			}
		}
	}
}

// Part of Canny filter
void DoubleThresholdLink(Mat &imageInput, double lowThreshold, double highThreshold)
{
	for (int i = 1; i<imageInput.rows - 1; i++)
	{
		for (int j = 1; j<imageInput.cols - 1; j++)
		{
			if (imageInput.at<uchar>(i, j)>lowThreshold&&imageInput.at<uchar>(i, j)<255)
			{
				if (imageInput.at<uchar>(i - 1, j - 1) == 255 || imageInput.at<uchar>(i - 1, j) == 255 || imageInput.at<uchar>(i - 1, j + 1) == 255 ||
					imageInput.at<uchar>(i, j - 1) == 255 || imageInput.at<uchar>(i, j) == 255 || imageInput.at<uchar>(i, j + 1) == 255 ||
					imageInput.at<uchar>(i + 1, j - 1) == 255 || imageInput.at<uchar>(i + 1, j) == 255 || imageInput.at<uchar>(i + 1, j + 1) == 255)
				{
					imageInput.at<uchar>(i, j) = 255;
					DoubleThresholdLink(imageInput, lowThreshold, highThreshold); //递归调用  
				}
				else
				{
					imageInput.at<uchar>(i, j) = 0;
				}
			}
		}
	}
}

void ImageProcessor::canny(int idx) {
	commit(idx);
	// STEP1: Gaussian filter
	gaussianFilter(5, idx);
	Mat copyImg = images[idx].clone();
	int iRows = copyImg.rows;
	int iCols = copyImg.cols;
	if (copyImg.channels() != 1) {
		// convert the image into grayscale
		cvtColor(copyImg, copyImg, CV_RGB2GRAY);
	}
	// copyImg now is a 1channel grayscale image, do operation to this image.
	Mat imageSobelY;
	Mat imageSobelX;
	double *pointDirection = new double[(imageSobelX.cols - 1)*(imageSobelX.rows - 1)];  //定义梯度方向角数组  
	SobelGradDirction(copyImg, imageSobelX, imageSobelY, pointDirection);  //计算X、Y方向梯度和方向角  
	Mat SobelGradAmpl;
	SobelAmplitude(imageSobelX, imageSobelY, SobelGradAmpl);   //计算X、Y方向梯度融合幅值  
	Mat imageLocalMax;
	LocalMaxValue(SobelGradAmpl, imageLocalMax, pointDirection);  //局部非极大值抑制  
	Mat cannyImage;
	cannyImage = Mat::zeros(imageLocalMax.size(), CV_8UC1);
	DoubleThreshold(imageLocalMax, 40, 100);        //双阈值处理  
	DoubleThresholdLink(imageLocalMax, 40, 100);   //双阈值中间阈值滤除及连接  

	// then recover the 3 channels image
	for (int i = 0; i < iRows; i++) {
		for (int j = 0; j < iCols; j++) {
			unsigned char tmp = imageLocalMax.at<uchar>(i, j);
			Vec3b tmpVec = { tmp, tmp, tmp };
			images[idx].at<Vec3b>(i, j) = tmpVec;
		}
	}
}

void ImageProcessor::initPara() {
	Theta1 = Mat(25, 401, CV_64FC1);
	Theta2 = Mat(10, 26, CV_64FC1);
	FILE *fp1, *fp2;
	double tmp;

	// Load Theta1
	fp1 = fopen("theta1.txt", "r");
	if (!fp1)
	{
		qDebug("Can not open the file.\n");
		return;
	}
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 401; j++) {
			fscanf(fp1, "%lf", &tmp);
			Theta1.at<double>(i, j) = tmp;
		}
	}
	fclose(fp1);

	// Load Theta2
	fp2 = fopen("theta2.txt", "r");
	if (!fp2) {
		qDebug("Can not open the file.\n");
		return;
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 26; j++) {
			fscanf(fp2, "%lf", &tmp);
			Theta2.at<double>(i, j) = tmp;
		}
	}
	fclose(fp2);

	/*double s1 = Theta1.at<double>(0, 0);
	double s2 = Theta2.at<double>(0, 0);
	double d1 = Theta1.at<double>(24, 400);
	double d2 = Theta2.at<double>(9, 25);*/
}

// Part of handwriting recognizing procedure
Mat ImageProcessor::sigmoid(Mat src) {
	Mat dst = Mat(src.size(), src.type());
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			double tmp = src.at<double>(i, j);
			tmp = 1.0 / (1.0 + exp(-tmp));
			dst.at<double>(i, j) = tmp;
		}
	}
	return dst;
}

// Recognize handwriting with trained NN
int ImageProcessor::helloWorld(int idx) {
	Mat imgVec = Mat(400, 1, CV_64FC1);
	int iRows = images[idx].rows;
	int iCols = images[idx].cols;
	if (iRows != 20 || iCols != 20) {
		qDebug("Bad image size !\n");
		return -1;
	}
	initPara();
	
	// Vectorization of image[idx]
	int cur = 0;
	for (int i = 0; i < iRows; i++) {
		for (int j = 0; j < iCols; j++) {
			imgVec.at<double>(cur, 0) = (double)images[idx].at<Vec3b>(i, j)[0];
			cur++;
		}
	}

	// Map grayscale 0~255 to 0.0~1.0
	for (int i = 0; i < 400; i++) {
		double tmp = imgVec.at<double>(i, 0);
		tmp = tmp / 255.0;
		imgVec.at<double>(i, 0) = tmp;
	}

	Mat a1 = Mat(401, 1, CV_64FC1);
	a1.at<double>(0, 0) = 1;
	for (int k = 0; k < 400; k++) {
		a1.at<double>(k + 1, 0) = imgVec.at<double>(k, 0);
	}

	Mat z2 = Theta1 * a1;
	Mat z2_sig = sigmoid(z2);
	Mat a2 = Mat(z2_sig.rows + 1, z2_sig.cols, CV_64FC1);
	a2.at<double>(0, 0) = 1;
	for (int k = 0; k < z2_sig.rows; k++) {
		a2.at<double>(k + 1, 0) = z2_sig.at<double>(k, 0);
	}
	Mat z3 = Theta2 * a2;
	Mat h0x = sigmoid(z3);
	double h0, h1, h2, h3, h4, h5, h6, h7, h8, h9;
	h0 = h0x.at<double>(0, 0);
	h1 = h0x.at<double>(1, 0);
	h2 = h0x.at<double>(2, 0);
	h3 = h0x.at<double>(3, 0);
	h4 = h0x.at<double>(4, 0);
	h5 = h0x.at<double>(5, 0);
	h6 = h0x.at<double>(6, 0);
	int maxPos = 0;
	double maxVal = h0x.at<double>(0, 0);
	for (int k = 0; k < h0x.rows; k++) {
		double tmp = h0x.at<double>(k, 0);
		if (tmp > maxVal) {
			maxVal = tmp;
			maxPos = k;
		}
	}
	return maxPos;
}