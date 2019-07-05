#include "utility/opencv_manager.h"
#include <cmath>
#include <iostream>

using namespace std;

int nextPowerOf2(int n) {
    int count = 0;

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

double magnitude(vector<double> v) {
    double sum = 0;

    for (auto x : v) sum += pow(x, 2);

    return sqrt(sum);
}

// time = 0
// frequency = 1
Img display_img(vector<vector<cn>> matrix, bool domain = false) {
    // Now add all the data into a Mat element
    int rows = matrix.size();
    int cols = matrix[0].size();
    Img vect = Img::zeros(rows, cols, CV_8UC1);
    // int c = 255 / log(1 + 255);
    int c = 20;
    // Loop over vectors and add the data
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int temp = 0;
            auto elem = matrix[row][col];
            if (domain) {
                std::cout << "magnitude: "
                          << magnitude({elem.real(), elem.imag()});
                temp = c * log(1 + magnitude({elem.real(), elem.imag()}));
                std::cout << " power: ";
                std::cout << temp << "\n";
            } else {
                temp = floor(matrix[row][col].real());
            }

            vect.at<uchar>(row, col) = temp < 0 ? 0 : temp > 255 ? 255 : temp;
        }
    }

    cout << "Finished adding data\n";
    // Show image
    cv::namedWindow("Image", cv::WINDOW_NORMAL);
    cv::imshow("Image", vect);
    cv::waitKey(0);
    return vect;
}
