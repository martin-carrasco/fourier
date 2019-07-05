#include "algorithms/hough.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

#define INPUT_PATH "res/image/input/"
#define OUTPUT_PATH "res/image/output/"
using namespace cv;

int main(int argc, const char* argv[]) {
    std::cout << "loading image\n\n";
    Mat img = imread(std::string(INPUT_PATH) + std::string("pentagon.png"),
                     cv::IMREAD_GRAYSCALE);

    namedWindow("original", CV_WINDOW_AUTOSIZE);
    namedWindow("hough space", CV_WINDOW_AUTOSIZE);

    Mat hough_space = hough(img);

    std::cout << "showing hough space\n";
    imshow("hough space", hough_space);

    std::cout << "showing original space\n";
    imshow("original", img);

    /// Wait until user exit program by pressing a key
    waitKey(0);

    return 0;
}
