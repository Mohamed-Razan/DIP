#include "cv.h" //main opencv header
#include "highgui.h" //GUI header
int main(int argc, char* argv[])
{
	IplImage* img;
	img = cvLoadImage(argv[1]);
	if (!img)
		printf("Could not load image file: %s\n", argv[1]);

	int height = img->height;
	int width = img->width;
	int nChannels = img->nChannels;
	int ws = img->widthStep;

	/*printf("Height: %d\n", height);
	printf("width: %d\n", width);
	printf("nChannels: %d\n", nChannels);
	printf("widthStep: %d\n", ws);*/

	uchar* data = (uchar*) img->imageData;

	/*printf("1st pixel's blue: %d\n", data[0]);
	printf("1st pixel's green: %d\n", data[1]);
	printf("1st pixel's red: %d\n", data[2]);*/

	/*int i = 100;
	int j = 100;

	printf("100th pixel's blue: %d\n", data[i*ws + j*nChannels]);
	printf("100th pixel's green: %d\n", data[i * ws + j * nChannels + 1]);
	printf("100th pixel's red: %d\n", data[i * ws + j * nChannels + 2]);*/

	/*for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			data[i * ws + j * nChannels] = 0;
			data[i * ws + j * nChannels + 1] = 0;
			data[i * ws + j * nChannels + 2] = 0;
		}
	}*/

	IplImage* gray = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	uchar* dataGray = (uchar*)gray->imageData;

	int nChannelsGray = gray->nChannels;
	int wsGray = gray->widthStep;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			dataGray[i * wsGray + j * nChannelsGray] = 0.1140 * data[i * ws + j * nChannels] + 0.5870 * data[i * ws + j * nChannels + 1] + 0.2989 * data[i * ws + j * nChannels + 2];
		}
	}

	IplImage* binary = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	uchar* dataBinary = (uchar*)binary->imageData;

	int nChannelsBinary = binary->nChannels;
	int wsBinary = binary->widthStep;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (dataGray[i * wsBinary + j * nChannelsBinary] > 100) {
				dataBinary[i * wsBinary + j * nChannelsBinary] = 255;
			}
			else {
				dataBinary[i * wsBinary + j * nChannelsBinary] = 0;
			}
		}
	}

	IplImage* invertBGR = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
	uchar* dataInvertBGR = (uchar*)invertBGR->imageData;

	int nChannelsInvertBGR = invertBGR->nChannels;
	int wsInvertBGR = invertBGR->widthStep;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			dataInvertBGR[i * wsInvertBGR + j * nChannelsInvertBGR] = 255 - data[i * ws + j * nChannels];
			dataInvertBGR[i * wsInvertBGR + j * nChannelsInvertBGR + 1] = 255 - data[i * ws + j * nChannels + 1];
			dataInvertBGR[i * wsInvertBGR + j * nChannelsInvertBGR + 2] = 255 - data[i * ws + j * nChannels + 2];
		}
	}

	IplImage* blue = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
	uchar* dataBlue = (uchar*)blue->imageData;

	int nChannelsBlue = blue->nChannels;
	int wsBlue = blue->widthStep;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			dataBlue[i * wsBlue + j * nChannelsBlue] = data[i * ws + j * nChannels];
			dataBlue[i * wsBlue + j * nChannelsBlue + 1] = 0;
			dataBlue[i * wsBlue + j * nChannelsBlue + 2] = 0;
		}
	}

	IplImage* green = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
	uchar* dataGreen = (uchar*)green->imageData;

	int nChannelsGreen = green->nChannels;
	int wsGreen = green->widthStep;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			dataGreen[i * wsGreen + j * nChannelsGreen] = 0;
			dataGreen[i * wsGreen + j * nChannelsGreen + 1] = data[i * wsGreen + j * nChannelsGreen + 1];
			dataGreen[i * wsGreen + j * nChannelsGreen + 2] = 0;
		}
	}

	IplImage* red = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
	uchar* dataRed = (uchar*)red->imageData;

	int nChannelsRed = red->nChannels;
	int wsRed = red->widthStep;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			dataRed[i * wsRed + j * nChannelsRed] = 0;
			dataRed[i * wsRed + j * nChannelsRed + 1] = 0;
			dataRed[i * wsRed + j * nChannelsRed + 2] = data[i * wsRed + j * nChannelsRed + 2];
		}
	}

	cvNamedWindow("Image");
	cvShowImage("Image", img);
	cvNamedWindow("Gray");
	cvShowImage("Gray", gray);
	cvNamedWindow("Binary");
	cvShowImage("Binary", binary);
	cvNamedWindow("InvertBGR");
	cvShowImage("InvertBGR", invertBGR);
	cvNamedWindow("Blue");
	cvShowImage("Blue", blue);
	cvNamedWindow("Green");
	cvShowImage("Green", green);
	cvNamedWindow("Red");
	cvShowImage("Red", red);

	cvWaitKey(0);

	cvDestroyWindow("Image");
	cvReleaseImage(&img);
	cvDestroyWindow("Gray");
	cvReleaseImage(&gray);
	cvDestroyWindow("Binary");
	cvReleaseImage(&binary);
	cvDestroyWindow("InvertBGR");
	cvReleaseImage(&invertBGR);
	cvDestroyWindow("Blue");
	cvReleaseImage(&blue);
	cvDestroyWindow("Green");
	cvReleaseImage(&green);
	cvDestroyWindow("Red");
	cvReleaseImage(&red);

	return 0;
}