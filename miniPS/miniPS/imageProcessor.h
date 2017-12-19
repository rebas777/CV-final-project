#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>
#include <QtWidgets/QMainWindow>
#include <QGraphicsScene>  
#include <QGraphicsView>  
#include <vector>

using namespace cv;

class ImageProcessor {

private:
	std::vector<bool> undoMarks = { false, false, false, false, false };

	int otsu(Mat img);
	void makeHist(int *ihist, int channelNum, Mat img);
	 
public:

	std::vector<Mat> images;
    std::vector<Mat> imageBackups;
	Mat hsvBackup;

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
};
