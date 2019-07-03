#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#define INPUT_PATH "res/image/input/"
#define OUTPUT_PATH "res/image/output/"
#define DEGREE_PRECISION 180

using namespace cv;
using namespace std;

/// Global variables

Mat src;
Mat dst, detected_edges;

int ratio = 3;
int kernel_size = 3;
int* H[DEGREE_PRECISION + 1];
int tota_rho;
int max_v = 0;

// y=((x-min)*255/(max-min)).
// y = (x * 255) / max

bool isEdge(int row, int col) {
    // return dst.at()
    return (int)dst.at<uchar>(row, col) != 0;
}

void initRhoH(void) {
    int rows = (int)dst.rows;
    int cols = (int)dst.cols;
    tota_rho = (int)ceil(sqrt(pow(dst.rows, 2) + pow(dst.cols, 2)));
    tota_rho *= 2;
    for (int i = 0; i <= DEGREE_PRECISION; ++i) {
        H[i] = (int*)calloc(tota_rho, sizeof(int));
    }
}

// vector<pair<int, int>> local_maxima() {
// vector<pair<int, int>> local_max;
// int before, after;
// before = after = 0;

// for (int y = 0; y <= DEGREE_PRECISION; y++) {
// for (int x = 0; x < total_rho; x++) {
// if (H[y][x] >= before && H[y][x] >= after) {
// before = H[y - 1][x];
// after = H[y + 1][x];
// local_max.push(local_max[y][x])
//}
//}
//}
// return local_max;
//}

void compute_hough(void) {
    int rows = (int)dst.rows;
    int cols = (int)dst.cols;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (not isEdge(row, col)) continue;
            int step = DEGREE_PRECISION / 180;
            for (int deg = 0; deg <= 180; deg += step) {
                double rad = (double)(deg * M_PI / 180.0);
                int rho = (int)(col * cos(rad) + row * sin(rad));
                max_v = (++H[deg][rho + (int)(tota_rho / 2)]) > max_v
                            ? H[deg][rho + (int)(tota_rho / 2)]
                            : max_v;
            }
        }
    }
}

/** @function main */
int main(int argc, char** argv) {
    /// Load an image
    std::cout << "loading image\n\n";
    src = imread(std::string(INPUT_PATH) + std::string("pentagon.png"),
                 cv::IMREAD_GRAYSCALE);

    if (!src.data) {
        std::cout << "dead image\n\n";
        return -1;
    }

    /// Create a matrix of the same type and size as src (for dst)
    dst.create(src.size(), src.type());

    std::cout << "creating window\n\n";

    namedWindow("original", CV_WINDOW_AUTOSIZE);
    namedWindow("hough space", CV_WINDOW_AUTOSIZE);
    namedWindow("lines", CV_WINDOW_AUTOSIZE);

    std::cout << "blurring\n\n";
    /// Reduce noise with a kernel 3x3
    blur(src, detected_edges, Size(3, 3));

    std::cout << "applying canny\n\n";
    /// Canny detector
    // Canny(detected_edges, detected_edges, lowThreshold, lowThreshold *
    // ratio,kernel_size);
    Canny(detected_edges, detected_edges, 50, 200, kernel_size);

    /// Using Canny's output as a mask, we display our result
    dst = Scalar::all(0);

    src.copyTo(dst, detected_edges);

    std::cout << "init rho\n\n";
    initRhoH();
    // working with dst

    std::cout << "hough\n\n\n";
    compute_hough();
    std::cout << "finished computing hough\n\n";

    int hough_rows = DEGREE_PRECISION;
    int hough_cols = tota_rho;

    std::cout << "hough to cv\n";
    Mat hough = Mat::zeros(hough_rows, hough_cols + 2, CV_8UC1);

    std::cout << "filling mat\n";
    std::cout << "RANGE RHO: " << tota_rho
              << "\tRANGE DEG: " << DEGREE_PRECISION << std::endl;
    std::cout << "MAX VALUE: " << max_v << std::endl;

    vector<pair<int, int>> coords;
    int max = 0;
    for (int row = 0; row < hough_rows; ++row) {
        for (int col = 0; col < hough_cols; ++col) {
            // cout << H[row][col] << endl;
            if (H[row][col] >= 20) {
                double theta_rad = col * M_PI / 180;
                // int y = row / sin(theta_rad);
                // int x = row / cos(theta_rad);
                pair<int, int> current_pair = make_pair(row, theta_rad);
                coords.push_back(current_pair);
            }
        }
    }

    cout << coords.size() << endl;
    Mat l(dst.rows, dst.cols, CV_8UC1);
    for (auto& [rho, theta] : coords) {
        cv::Point p1, p2;

        double x = rho / cos(theta);
        double y = rho / sin(theta);

        p1.x = 0;
        p1.y = y;
        p2.x = x;
        p2.y = 0;
        line(dst, p1, p2, Scalar(255, 255, 255), 3, LINE_AA);
    }
    for (int row = 0; row < hough_rows; ++row) {
        for (int col = 0; col < hough_cols; ++col) {
            hough.at<uchar>(row, col) = (int)(20.0 * log2(H[row][col]));
        }
    }

    // MAX VALUE: 191
    // row: 0, col: 0 -->	row: 0, col: -400

    std::cout << "showing hough space\n";
    imshow("hough space", hough);

    cout << "Showing lines\n";
    imshow("lines", l);

    std::cout << "showing original space\n";
    imshow("original", dst);

    /// Wait until user exit program by pressing a key
    waitKey(0);

    return 0;
}
