#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;

Mat contrastCondition(Mat gray, int a, int b, int c, int d) {

    Mat constrastImg = gray.clone();
    int x;
    int out;

    for (int i = 0; i < gray.rows; i++) {
        for (int j = 0; j < gray.cols; j++) {
            x = (int)gray.at<uchar>(i, j);
            if (x >= 0 && x <= a)
                out = int((c / a) * x);
            else if (a < x && x <= b)
                out = int(((d - c) / (b - a)) * (x - a) + 5);
            else if (x > b && x <= 255)
                out = int(((255 - d) / (255 - b)) * (x - b) + 250);

            //convert the int value to uchar and apply it to the high contrast image
            constrastImg.at<uchar>(i, j) = uchar(out);
        }
    }
    return constrastImg;
}

int main(int argc, char* argv[]) {
    Mat image = imread(argv[1]); //get image from command line, if 0 - exe file, if 1 - image name

    if (!image.data) {
        cout << "couldn't find the image!" << endl; //endl in use to print new line in mat
        return -1;
    }

    Mat gray(image.rows, image.cols, CV_8UC1, Scalar(0)); //CV_8UC1 - because gray scale, 1 scale image
    //convert BGR image to gray using opencv function, without using loops
    cvtColor(image, gray, COLOR_BGR2GRAY); //1st param - input image, 2nd - output image, 3rd - conversion method

    //draw histogram
    int histogram[256]; //array to allocate memory for all the intensity values

    //initialize 0 to all the array elements
    for (int i = 0; i < 256; i++)
        histogram[i] = 0;

    for (int x = 0; x < image.rows; x++) {
        for (int y = 0; y < image.cols; y++) {
            int pix_in = (int)gray.at<uchar>(x, y); //1 channel - so, usue uchar
            int cnt = histogram[(int)gray.at<uchar>(x, y)]; //find how many no.of pixels for each intensity currently
            histogram[(int)gray.at<uchar>(x, y)] = cnt + 1; //that value increment by 1 and assign to relevant intensity of the histogram
            //histogram[(int)gray.at<uchar>(y, x)]++ : instead of above 3 line you can replace this
        }
    }

    //Print number of pixels for each intensity value
    for (int i = 0; i < 256; i++)
        cout << i << ":" << histogram[i] << endl;

    int histogram_height = 400;
    int histogram_width = 512; //use any value you wish
    int bin_w = cvRound((double)histogram_width / 256);


    //Draw the histogram for B,G and R
    Mat histImage(histogram_height, histogram_width, CV_8UC1, Scalar(255, 255, 255)); //create a window to draw the histogram

    //Find the maximum number of pixels from histogram array
    int max = histogram[0];
    for (int i = 1; i < 256; i++) {
        if (max < histogram[i]) {
            max = histogram[i];
        }
    }

    //Normalize the histogram between 0 and histogram height
    for (int i = 0; i < 256; i++) {
        histogram[i] = ((double)histogram[i] / max) * histogram_height;
        //cout << histogram[i] << endl;
    }

    //Draw the lines of histogram
    for (int i = 0; i < 256; i++) {
        //line ( histImage, Point pt1, Point pt2,color , thickness, lineType, shift)
        line(histImage, Point(bin_w * (i), histogram_height), Point(bin_w * (i), histogram_height - histogram[i]), Scalar(0, 0, 0), 1, 8, 0);
    }

    //Mat constrastImg = gray.clone();

    int a = atoi(argv[2]); //get from command line
    int b = atoi(argv[3]);
    int c = 5;
    int d = 250;
    //int the command line - Project1 low_contrast_girl.jpg 103 234 - pass like this
    //int x;
    //int out;

    //for (int i = 0; i < gray.rows; i++) {
    //    for (int j = 0; j < gray.cols; j++) {
    //        x = (int)gray.at<uchar>(i, j);
    //        if (x >= 0 && x <= a)
    //            out = int((c / a) * x);
    //        else if (a < x && x <= b)
    //            out = int(((d - c) / (b - a)) * (x - a) + 5);
    //        else if (x > b && x <= 255)
    //            out = int(((255 - d) / (255 - b)) * (x - b) + 250);

    //        //convert the int value to uchar and apply it to the high contrast image
    //        constrastImg.at<uchar>(i, j) = uchar(out);
    //    }
    //}


    Mat constrastImg = contrastCondition(gray, a, b, c, d);

    namedWindow("Gray"); //give a name to window
    imshow("Gray", gray); //show the image on window
    namedWindow("Histogram"); //give a name to window
    imshow("Histogram", histImage); //show the image on window
    namedWindow("Contrast Image"); //give a name to window
    imshow("Contrast Image", constrastImg); //show the image on window

    imwrite("output.jpg", constrastImg);
    waitKey(0);

    return 0;
}