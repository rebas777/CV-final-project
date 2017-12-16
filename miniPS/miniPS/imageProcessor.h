#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>
#include <QtWidgets/QMainWindow>
#include <QGraphicsScene>  
#include <QGraphicsView>  
#include <vector>

using namespace cv;

class ImageProcessor {
	 
public:

	std::vector<Mat> images;

	ImageProcessor();
	void loadImage(const char *name, int idx);
	void saveImage(const char *name, int idx);
	void showImage(int idx); // For debug only
	std::vector<int> getPixelVal(int x, int y, int idx);

	void channelSplit(int rgbNum, int idx);
};
