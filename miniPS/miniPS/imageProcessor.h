#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>
#include <QtWidgets/QMainWindow>
#include <QGraphicsScene>  
#include <QGraphicsView>  
#include <vector>

#define NN 0
#define LINEAR 1
#define CHANNEL_R 0
#define CHANNEL_G 1
#define CHANNEL_B 2
#define SIGMA 1.2

using namespace cv;

class ImageProcessor {

private:
	std::vector<bool> undoMarks = { false, false, false, false, false };
	Mat Theta1;
	Mat Theta2;

	int otsu(Mat img);
	void makeHist(int *ihist, int channelNum, Mat img);
	void bilinearInter(float x0, float y0, Mat img, int &rVal, int &gVal, int &bVal);
	void initPara();
	Mat sigmoid(Mat src);

	 
public:

	std::vector<Mat> images;
    std::vector<Mat> imageBackups;
	Mat hsvBackup;
	Mat GSABackup;

	ImageProcessor();
	void loadImage(const char *name, int idx);
	void saveImage(const char *name, int idx);
	void showImage(int idx); // For debug only
	std::vector<int> getPixelVal(int x, int y, int idx);
	void commit(int idx);
	bool undo(int idx);
	void rgb2gry(int idx);
	void makeHsvBackup(int idx);
	void changeHSV(int hsvNum, int val, int idx);
	void channelSplit(int rgbNum, int idx);
	void toBinary(bool useOtsu, int th1, int th2, int idx);
	void addOper(int idx1, int idx2, double weight1, double weight2, int posX, int posY);
	void subtractionOper(int idx1, int idx2, int posX, int posY);
	bool multiplicationOper(int idx1, int idx2);
	bool divisionOper(int idx1, int idx2);
	void resize(int width, int height, int choiceNum, int idx);
	void spinCW(int idx);
	void drawHist(int channelNum, int idx);
	void histEqualization(int idx);
	void rotateCW(float theta, int choiceNum, int idx);
	void linearGSA(int A, int B, int C, int D, int channelNum, int idx);
	void expGSA(int A, int B, int C, int channelNum, int idx);
	void logGSA(int A, int B, int C, int channelNum, int idx);
	void makeGSABackup(int idx);
	Mat drawLinearFunction(int a, int b, int c, int d);

	void filter2D(double **kernel, int ksize, int idx);
	void boxFilter(int ksize, int idx);
	void gaussianFilter(int ksize, int idx);
	void medianFilter(int ksize, int idx);

	void canny(int idx);

	void houghLine(int idx);

	void houghCircle(int idx);

	int helloWorld(int idx);

	void test(int idx);

	void dilation(Mat B,int anchorRow, int anchorCol, int idx);
	void dilation(Mat &A, Mat B, int anchorRow, int anchorCol);
	void erosion(Mat B, int anchorRow, int anchorCol, int idx);
	void open(Mat B, int anchorRow, int anchorCol, int idx);
	void close(Mat B, int anchorRow, int anchorCol, int idx);

	void hitOrMiss(Mat B, int anchorRow, int anchorCol, int idx);
	void thinning(Mat B, int anchorRow, int anchorCol, int idx);
	void thickening(Mat B, int anchorRow, int anchorCol, int idx);

	void distanceTrans(int algo, int idx);

	void binRecon(Mat K, int anchorRow, int anchorCol, int idx);

	void reconstruction(Mat &marker, Mat mask);

	Mat skeleton(Mat &srcin);
	void extractSkeleton(int idx);

};
