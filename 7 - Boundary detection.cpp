#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"


using namespace cv;
using namespace std;
int main(int argc, char* argv[]) {

	Mat image = imread(argv[1], IMREAD_GRAYSCALE);

	if (!image.data) {
		cout << "Could not find thye image " << endl;
		return -1;
	}

	//Guassian smoothing
	Mat output = image.clone();

	int k[5][5] = { 
		{2, 4, 5, 4 , 2},
		{4, 9, 12, 9, 4},
		{5, 12, 15, 12, 5},
		{4, 9, 12, 9, 4 },
		{2, 4, 5, 4 , 2 } 
	};

	double val;


	for (int i = 2; i < image.rows - 2; i++) {
		for (int j = 2; j < image.cols - 2; j++) {

			val = 0.0;

			for (int m = -2; m <= 2; m++) {
				for (int n = -2; n <= 2; n++) {
					val = val + double(k[m + 2][n + 2] * image.at<uchar>(i + m, j + n)) / 159;
				}
			}
			output.at<uchar>(i, j) = cvRound(val);
		}
	}

	Mat newImage = output.clone();

	int Gx, Gy, g;

	for (int i = 0; i < output.rows - 1; i++) {
		for (int j = 0; j < output.cols - 1; j++) {

			Gx = 1 * output.at<uchar>(i, j) - 1 * output.at<uchar>(i, j + 1);
			Gy = 1 * output.at<uchar>(i, j) - 1 * output.at<uchar>(i + 1, j);

			g = abs(Gx) + abs(Gy);

			if (g > 15)
				newImage.at<uchar>(i, j) = 255;
			else
				newImage.at<uchar>(i, j) = 0;
		}
	}

	namedWindow("Image");
	imshow("Image", image);

	namedWindow("Output Image");
	imshow("Output Image", output);

	namedWindow("New Image");
	imshow("New Image", newImage);


	waitKey(0);
	return 0;
}