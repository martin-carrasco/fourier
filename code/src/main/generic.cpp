#include "algorithms/hough.h"
#include "utility/image_manager.h"
#include "utility/opencv_manager.h"
#include <cmath>
#include <iostream>
#define INPUT_PATH "res/image/input/"
#define OUTPUT_PATH "res/image/output/"

using namespace std;

int main(int argc, const char* argv[]) {
    vector<vector<int>> mat{{0, 1, 0, 0, 0},
                            {0, 0, 1, 1, 0},
                            {1, 0, 1, 0, 0},
                            {1, 0, 1, 0, 0},
                            {0, 0, 0, 0, 0}

    };
    auto hough_lines = hough_transform(mat);
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            for (int rho = hough_lines.size(); rho++) {
                for (int theta = hough_lines[0].size(); theta++) {
                    if (x) }
            }
        }
    }
    for (auto : hough_lines) {
        cout << rho.first << ", " << rho.second;
        cout << endl;
    }

    // Img im = Img::zeros(hough_lines.size(), hough_lines[0].size(), CV_8UC1);

    // for (int x = 0; x < im.rows; x++) {
    // for (int y = 0; y < im.cols; y++) {
    // im.at<uchar>(x, y) = hough_lines[x][y] * 20;
    //}
    //}

    // cv::namedWindow("Image", cv::WINDOW_NORMAL);
    // cv::imshow("Image", im);
    // cv::waitKey(0);
}
