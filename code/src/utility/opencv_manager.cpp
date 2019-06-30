#include "utility/opencv_manager.h"
#include <cmath>

using namespace std;

unsigned int nextPowerOf2(unsigned int n) {
    unsigned count = 0;

    // First n in the below condition
    // is for the case where n is 0
    if (n && !(n & (n - 1))) return n;

    while (n != 0) {
        n >>= 1;
        count += 1;
    }

    return 1 << count;
}

vector<vector<cn>> read_img(const std::string filename) {
    Img image = cv::imread(INPUT_PATH + filename, cv::IMREAD_GRAYSCALE);
    int rows, cols, mod_rows, mod_cols;
    rows = image.rows;
    cols = image.cols;

    // Creating of zero padded matrix
    mod_rows = nextPowerOf2(rows) == rows ? rows : nextPowerOf2(rows);
    mod_cols = nextPowerOf2(cols) == cols ? cols : nextPowerOf2(cols);

    vector<vector<cn>> matrix(mod_rows, vector<cn>(mod_cols));

    // Copy image to matrix buffer
    uchar* ptr;
    for (int x = 0; x < rows; x++) {
        ptr = image.ptr<uchar>(x);
        for (int y = 0; y < cols; y++) {
            matrix[x][y] = ptr[y];
        }
    }
    return matrix;
}

void display_csv(vector<vector<cn>> matrix) {
    // Now add all the data into a Mat element
    Img vect = Img::zeros((int)matrix.size(), (int)matrix[0].size(), CV_8UC1);

    // Loop over vectors and add the data
    for (int rows = 0; rows < matrix.size(); rows++) {
        for (int cols = 0; cols < matrix[0].size(); cols++) {
            vect.at<uchar>(rows, cols) =
                sqrt(pow(matrix[rows][cols].real(), 2) +
                     pow(matrix[rows][cols].imag(), 2));
        }
    }
    // Show image
    cv::namedWindow("Image", cv::WINDOW_NORMAL);
    cv::imshow("Image", vect);
    cv::waitKey(0);
}

void to_csv(std::string filename, const std::vector<std::vector<cn>>& matrix) {
    // FORMAT: (-116759.57090511809-27922.44814168373j)

    std::ofstream out(OUTPUT_PATH + filename);
    for (auto& row : matrix) {
        for (auto col : row)
            out << "(" << col.real() << (col.imag() < 0 ? "-" : "+")
                << abs(col.imag()) << "j)" << ',';
        out << '\n';
    }
}
