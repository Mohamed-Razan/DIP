#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2//core/core.hpp"

using namespace cv;
using namespace std;


int main(int argc, char* argv[])
{
	Mat image = imread(argv[1]);

	if (!image.data) {
		cout << "Couldn't find the image" << endl;
		return -1;
	}

	int height = image.rows;
	int width = image.cols; 
	int ws = image.step;
	int channel = image.channels();

	printf("Heigt: %d\n", height);
	printf("Width: %d\n", width);
	printf("Width Step: %d\n", ws);
	printf("No of Channel: %d\n", channel);

	printf("1st pixel blue: %d\n", image.at<Vec3b>(0, 0)[0]);

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			image.at<Vec3b>(i, j)[0] = 0;
			image.at<Vec3b>(i, j)[1] = 0;
			image.at<Vec3b>(i, j)[2] = 0;
		}
	}

	Mat image2;
	image2.create(height, width, CV_8UC1);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			image2.at<uchar>(i, j) = 0.1140 * image.at<Vec3b>(i, j)[0] + 0.5870 * image2.at<Vec3b>(i, j)[1] + 0.2989 * image2.at<Vec3b>(i, j)[2];
		}
	}

	namedWindow("Image");
	imshow("Image", image);

	namedWindow("Image2");
	imshow("Image2", image2);

	waitKey(0);
	return 0;
}