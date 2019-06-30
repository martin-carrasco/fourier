#include "utility/image_manager.h"
#include <algorithm>

using namespace std;

ImageTransform::ImageTransform(void) {}

ImageTransform::ImageTransform(const CompMatrix& matrix) {
    this->complex_matrix = matrix;
}

void ImageTransform::convolute_filter(CompMatrix& mask, int width, int height) {
    // 2D FFT
    fft2d(complex_matrix, width, height);

    // 2D FFT of filter
    fft2d(mask, width, height);

    // Apply the filter H(x, y) to F(x, y) (multiply)
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            complex_matrix[x][y] = complex_matrix[x][y] * mask[x][y];
        }
    }

    // Inverse 2D FFT
    ifft2d(complex_matrix, width, height);
}

void ImageTransform::apply_lp(double d0) {
    int height = this->complex_matrix.size();
    int width = this->complex_matrix[0].size();

    ImageUtils::pad0_complex(complex_matrix);
    ImageUtils::center_matrix(complex_matrix);

    int Q = complex_matrix.size();
    int P = complex_matrix[0].size();

    CompMatrix image_filter(P, vector<cn>(Q, 0));
    for (int x = d0 / 2; x < P; x += d0 / 2 + 1) {
        for (int y = d0 / 2; y < Q; d0 / 2 + 1) {
            for (int z1 = -d0 / 2, z2 = d0 / 2; z1 <= d0 / 2 || z2 >= -d0 / 2;
                 z1++, z2--) {
                int px_1, py_1, px_2, py_2;
                double val_1, val_2;

                px_1 = x + z1;
                py_1 = y + z2;
                px_2 = x + z2;
                py_2 = y + z1;

                if (px_1 < P && px_1 > 0 && py_1 < Q && py_1 > 0) {
                    val_1 = ImageUtils::dist_euclid(x, y, px_1, py_1);
                    image_filter[px_1][py_1] = val_1 < d0 ? 1 : 0;
                    cout << "Threshold: " << val_1 << endl;
                    cout << "H(x,y): " << image_filter[px_1][py_1] << endl;
                }
                if (px_2 < P && px_2 > 0 && py_2 < Q && py_2 > 0) {
                    val_2 = ImageUtils::dist_euclid(x, y, px_2, py_2);
                    image_filter[px_2][py_2] = val_2 < d0 ? 1 : 0;
                    cout << "Threshold: " << val_2 << endl;

                    cout << "H(x,y): " << image_filter[px_2][py_2] << endl;
                }
            }
        }
    }
    ImageUtils::center_matrix(image_filter);
    cout << endl;
    cout << "Convolution starting..." << endl;
    cout << endl;

    this->convolute_filter(image_filter, P, Q);
}

void ImageTransform::apply_bp(double fc1, double fc2) {
    int width = this->complex_matrix.size();
    int height = this->complex_matrix[0].size();

    CompMatrix image_filter(width, vector<cn>(height, 0));

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            double m =
                (static_cast<double>(x) - static_cast<double>(width) / 2.D) /
                static_cast<double>(width);
            double n = (y - height / 2.D) / static_cast<double>(height);

            double total = sqrt(pow(m, 2) + pow(n, 2));

            if (fc1 <= total && total <= fc2)
                image_filter[x][y] = 0;
            else
                image_filter[x][y] = 1;
        }
    }
    this->convolute_filter(image_filter, width, height);
}

CompMatrix ImageTransform::get_matrix(void) { return this->complex_matrix; }
void ImageTransform::set_matrix(CompMatrix& matrix) {
    this->complex_matrix = matrix;
}
