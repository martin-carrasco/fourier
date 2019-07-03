#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "utility/matplotlibcpp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#define INPUT_PATH "res/image/input/"
#define OUTPUT_PATH "res/image/output/"

int** H0;

cv::Mat detect_edges(cv::Mat img) {
    using namespace cv;

    Mat dst, detected_edges;
    dst.create(img.size(), img.type());

    /// Reduce noise with a kernel 3x3
    blur(img, detected_edges, Size(3, 3));

    /// Canny detector
    Canny(detected_edges, detected_edges, 50, 200, 3 /* kernel_size*/);
    dst = Scalar::all(0);

    img.copyTo(dst, detected_edges);

    return dst.clone();
}

/*
 * H: voting matrix
 * rows: rows of matrix
 * cols: cols of matrix
 */
std::pair<int, int> init_acc_array(int**& H, int rows, int cols) {
    int n_rho, n_theta;

    // n_rho will will be the number of pixels in the diagonal
    // >> [-sqrt(rows^2, cols^2), sqrt(rows^2, cols^2)]
    // n_theta goes [-pi/2, pi/2]
    n_rho = ceil(sqrt(pow(rows, 2) + pow(cols, 2)) + 1);
    n_theta = 90;

    H = (int**)malloc(sizeof(int*) * (2 * n_rho + 2));
    for (int i = -n_rho; i <= n_rho; ++i)
        H[i + n_rho] = (int*)calloc(2 * n_theta + 1, sizeof(int));

    H0 = (int**)malloc(sizeof(int*) * (2 * n_rho + 2));
    for (int i = -n_rho; i <= n_rho; ++i)
        H0[i + n_rho] = (int*)calloc(2 * n_theta + 1, sizeof(int));

    std::cout << "rho_max: " << 2 * n_rho << "\tn_theta: " << 2 * n_theta
              << std::endl;
    return {n_rho, n_theta};
}

bool is_edge(const cv::Mat& img, int row, int col) {
    return (int)img.at<uchar>(row, col) != 0;
}

void fill_acc_array(const cv::Mat& img, int** H, int n_rho, int n_theta) {
    int rows = img.rows;
    int cols = img.cols;
    bool first = true;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (not is_edge(img, row, col)) continue;
            for (int deg = -n_theta; deg <= n_theta; ++deg) {
                double rad = (double)(deg * M_PI / 180.0);
                int rho = (int)(col * cos(rad) + row * sin(rad));
                ++H[rho + n_rho][deg + n_theta];
                if (first and not(row == 0 or col == 0)) {
                    std::cout << "(" << col << ", " << row << ")\n";
                    ++H0[rho + n_rho][deg + n_theta];
                }
                // std::cout << H[rho + n_rho][deg + n_theta] << std::endl;
            }
            if (not(row == 0 or col == 0)) first = false;
        }
    }
}

void plot_3d(int** H, int n_rho, int n_theta) {
    namespace plt = matplotlibcpp;

    std::vector<std::vector<double>> x, y, z;
    for (int row = -n_rho; row <= n_rho; ++row) {
        std::vector<double> x_row, y_row, z_row;
        for (int col = -n_theta; col <= n_theta; ++col) {
            x_row.push_back(col);
            y_row.push_back(row);
            z_row.push_back((20.0 * log2(1 + H[row + n_rho][col + n_theta])));
        }

        x.push_back(x_row);
        y.push_back(y_row);
        z.push_back(z_row);
    }

    plt::plot_surface(x, y, z);
    plt::show();
}

cv::Mat hough(cv::Mat img) {
    using namespace cv;

    int** H;
    int rows = img.rows;
    int cols = img.cols;

    std::cout << "Initializing Accumulator array\n\n";
    auto [n_rho, n_theta] = init_acc_array(H, rows, cols);

    std::cout << "Filling Accumulator array\n\n";
    fill_acc_array(img, H, n_rho, n_theta);

    std::cout << "Finished. Copying to CV::Mat\n\n";
    Mat hough =
        Mat::zeros(2 * n_rho + 1 /*rows*/, 2 * n_theta + 1 /*cols*/, CV_8UC1);

    /*
    plot_3d(H0, n_rho, n_theta);
    std::ofstream out(std::string(OUTPUT_PATH) + std::string("hcsv.csv"));

    for (int row = -n_rho; row <= n_rho; ++row) {
        for (int col = -n_theta; col <= n_theta; ++col) {
            out << 20.0 * log2(1 + H0[row + n_rho][col + n_theta]) << ',';
        }
        out << std::endl;
    }
    */

    for (int row = -n_rho; row <= n_rho; ++row) {
        for (int col = -n_theta; col <= n_theta; ++col) {
            hough.at<uchar>(row + n_rho, col + n_theta) =
                (int)(20.0 * log2(H[row + n_rho][col + n_theta]));
        }
    }

    return hough.clone();
}
