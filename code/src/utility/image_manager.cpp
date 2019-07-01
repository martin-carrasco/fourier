#include "utility/image_manager.h"
#include <algorithm>
#include <assert.h>
#include <iostream>

using namespace std;

ImageTransform::ImageTransform(CMatrix matrix) {
    this->original_height = matrix.size();
    this->original_width = matrix[0].size();
    this->complex_matrix = matrix;
}

pair<int, int> ImageTransform::get_dimentions(void) {
    return make_pair(complex_matrix.size(), complex_matrix[0].size());
}
CMatrix ImageTransform::get_matrix(void) { return complex_matrix; }

ImageTransform& ImageTransform::transform(bool direction) {
    ct_in_fft2d(complex_matrix, direction);
}

CMatrix ImageTransform::apply(const CMatrix& filter) {
    int height = filter.size();
    int width = filter[0].size();

    // Make sure that a multiplication by a filter has same size as the matrix
    assert(height == complex_matrix.size() &&
           width == complex_matrix[0].size());

    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            complex_matrix[x][y] = complex_matrix[x][y] * filter[x][y];
        }
    }
}
ImageTransform ImageTransform::shift(void) {
    shift_fft2d(complex_matrix);
    return *this;
}

ImageTransform& ImageTransform::crop(void) {
    complex_matrix.resize(original_height);
    for (auto& row : complex_matrix) {
        row.resize(original_width);
    }
    return *this;
}
ImageTransform& ImageTransform::pad(void) {
    int height = complex_matrix.size();
    int width = complex_matrix[0].size();

    for (auto& row : complex_matrix) row.resize(width * 2, 0);

    complex_matrix.resize(height * 2, vector<cn>(width * 2, 0));

    return *this;
}
ImageTransform& ImageTransform::center(void) {
    int width = complex_matrix.size();
    int height = complex_matrix[0].size();

    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            complex_matrix[x][y] *= pow(-1, x + y);
        }
    }
    return *this;
}

CMatrix Filters::gaussian_low_pass(int height, int width, double fc) {
    CMatrix filter(height, std::vector<cn>(height, 0));
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            double dist =
                -1 * pow(ImageUtils::dist_euclid(x, y, height, width), 2);
            double func = 2 * pow(2, fc);
            double val = exp(dist / func);

            filter[x][y] = val;
        }
    }
    return filter;
}

CMatrix Filters::high_pass(int height, int width, double fc) {
    CMatrix filter(height, std::vector<cn>(height, 0));
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            double val = ImageUtils::dist_euclid(x, y, height, width);
            if (val <= fc)
                filter[x][y] = 0;
            else
                filter[x][y] = 1;
        }
    }
    return filter;
}
CMatrix Filters::low_pass(int height, int width, double fc) {
    CMatrix filter(height, std::vector<cn>(height, 0));
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            double val = ImageUtils::dist_euclid(x, y, height, width);
            if (val <= fc)
                filter[x][y] = 1;
            else
                filter[x][y] = 0;
        }
    }
    return filter;
}
