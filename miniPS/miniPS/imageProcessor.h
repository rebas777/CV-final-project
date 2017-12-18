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
	 
public:

	std::vector<Mat> images;
    std::vector<Mat> imageBackups;

	ImageProcessor();
	void loadImage(const char *name, int idx);
	void saveImage(const char *name, int idx);
	void showImage(int idx); // For debug only
	std::vector<int> getPixelVal(int x, int y, int idx);
	void commit(int idx);
	bool undo(int idx);
	void rgb2gry(int idx);
	void changeHSV(int hsvNum, int val, int idx);

	void channelSplit(int rgbNum, int idx);
};
