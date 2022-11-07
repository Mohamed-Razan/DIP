#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

using namespace cv;
using namespace std;

int countGxy(Mat image, int i, int j) {
	int Gxy = -image.at<uchar>(i - 1, j - 1) - image.at<uchar>(i - 1, j) - image.at<uchar>(i - 1, j + 1) -
		image.at<uchar>(i, j - 1) + 8 * image.at<uchar>(i, j) - image.at<uchar>(i, j + 1) -
		image.at<uchar>(i + 1, j - 1) - image.at<uchar>(i + 1, j) - image.at<uchar>(i + 1, j + 1);

	/*int Gxy = -image.at<uchar>(y - 1, x - 1) - image.at<uchar>(y - 1, x) - image.at<uchar>(y - 1, x + 1) -
		image.at<uchar>(y, x - 1) + 8 * image.at<uchar>(y, x) - image.at<uchar>(y, x + 1) -
		image.at<uchar>(y + 1, x - 1) - image.at<uchar>(y + 1, x) - image.at<uchar>(y + 1, x + 1);*/

	/*int Gxy = 0 * image.at<uchar>(i - 1, j - 1) + image.at<uchar>(i - 1, j) + 0 * image.at<uchar>(i - 1, j + 1) +
		image.at<uchar>(i, j - 1) - 4 * image.at<uchar>(i, j) + image.at<uchar>(i, j + 1) +
		0 * image.at<uchar>(i + 1, j - 1) + image.at<uchar>(i + 1, j) + 0 * image.at<uchar>(i + 1, j + 1);*/
	return Gxy;
}

int main(int argc, char* argv[]) {

	Mat image = imread(argv[1], IMREAD_GRAYSCALE);

	if (!image.data) {
		cout << "Could not find the image! " << endl;
		return -1;
	}

	Mat output = image.clone();
	int Gxy;

	for (int i = 2; i < image.rows - 2; i++) {
		for (int j = 2; j < image.cols - 2; j++) {

			Gxy = countGxy(image, i, j);

			if (Gxy < 0) {
				Gxy = 0;
			}
			else if (Gxy > 255) {
				Gxy = 255;
			}

			output.at<uchar>(i, j) = Gxy;

			/*Gxy = 0 * image.at<uchar>(i - 1, j - 1) + image.at<uchar>(i - 1, j) + 0 * image.at<uchar>(i - 1, j + 1) +
				image.at<uchar>(i, j - 1) - 4 * image.at<uchar>(i, j) + image.at<uchar>(i, j + 1) +
				0 * image.at<uchar>(i + 1, j - 1) + image.at<uchar>(i + 1, j) + 0 * image.at<uchar>(i + 1, j + 1);*/

			/*if (Gxy == 0) {
				if (
					(countGxy(image, x - 1, y - 1) * countGxy(image, x + 1, y + 1)) < 0 ||
					(countGxy(image, x - 1, y) * countGxy(image, x + 1, y)) < 0 ||
					(countGxy(image, x - 1, y + 1) * countGxy(image, x + 1, y - 1)) < 0 ||
					(countGxy(image, x, y - 1) * countGxy(image, x, y + 1)) < 0
					) {
					output.at<uchar>(y, x) = 255;
				}
				else {
					output.at<uchar>(y, x) = 0;
				}
			}
			else {
				output.at<uchar>(y, x) = 0;
			}*/

			/*if (Gxy == 0) {
				if (
					(countGxy(image, i - 1, j - 1) * countGxy(image, i + 1, j + 1)) < 0 ||
					(countGxy(image, i, j - 1) * countGxy(image, i, j + 1)) < 0 ||
					(countGxy(image, i + 1, j - 1) * countGxy(image, i - 1, j + 1)) < 0 ||
					(countGxy(image, i - 1, j) * countGxy(image, i + 1, j)) < 0
					) {
					output.at<uchar>(i, j) = 255;
				}
				else {
					output.at<uchar>(i, j) = 0;
				}
			}
			else {
				output.at<uchar>(i, j) = 0;
			}*/

			/*if (Gxy > 50)
				output.at<uchar>(i, j) = 255;
			else
				output.at<uchar>(i, j) = 0;*/
		}
	}

	namedWindow("Image");
	imshow("Image", image);
	namedWindow("Output Image");
	imshow("Output Image", output);
	waitKey(0);

	return 0;

}