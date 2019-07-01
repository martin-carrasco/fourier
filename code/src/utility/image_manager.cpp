#include "utility/image_manager.h"
#include <algorithm>
#include <assert.h>
#include <iostream>

using namespace std;

ImageTransform::ImageTransform(CompMatrix matrix) {
    this->original_height = matrix.size();
    this->original_width = matrix[0].size();
    this->complex_matrix = matrix;
}

void ImageTransform::transform(bool direction) {
    ct_in_fft2d(complex_matrix, direction);
}

void ImageTransform::convolute_kernel(const CompMatrix& kernel) {
    assert(kernel.size() % 2 == 1 && kernel.size() == kernel[0].size());

    int height = complex_matrix.size();
    int width = complex_matrix[0].size();

    int size = kernel.size();
    int radius = floor(kernel.size() / 2);

    for (int x = radius; x < height; x += radius + 1) {
        for (int y = radius; y < width; y += radius + 1) {
            for (int z = -radius; z <= radius; z++) {
                pair<int, int> fwd = make_pair(z, -1 * z);
                pair<int, int> bwd = make_pair(-1 * z, z);

                if (fwd.first + x < height && fwd.second + y < width) {
                    cn result = complex_matrix[x + fwd.first][y + fwd.second] *
                                kernel[fwd.first + radius][fwd.second + radius];
                    complex_matrix[x + fwd.first][y + fwd.second] = result;
                }

                if (bwd.first + x < height && bwd.second + y < width) {
                    cn result = complex_matrix[x + bwd.first][y + bwd.second] *
                                kernel[bwd.first + radius][bwd.second + radius];
                    complex_matrix[x + bwd.first][y + bwd.second] = result;
                }
            }
        }
    }
}
void ImageTransform::convolute_whole(const CompMatrix& filter) {
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
void ImageTransform::shift(void) { shift_fft2d(complex_matrix); }

pair<int, int> ImageTransform::get_dimentions() {
    return make_pair(complex_matrix.size(), complex_matrix[0].size());
}
void ImageTransform::crop(void) {
    complex_matrix.resize(original_height);
    for (auto& row : complex_matrix) {
        row.resize(original_width);
    }
}

CompMatrix ImageTransform::get_matrix(void) { return complex_matrix; }

void ImageTransform::pad(void) {
    int height = complex_matrix.size();
    int width = complex_matrix[0].size();

    CompMatrix rows(height * 2, std::vector<cn>(width * 2, 0));
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            rows[x][y] = complex_matrix[x][y];
        }
    }
    complex_matrix = rows;
}
void ImageTransform::center(void) {
    int width = complex_matrix.size();
    int height = complex_matrix[0].size();

    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            complex_matrix[x][y] *= pow(-1, x + y);
        }
    }
}

CompMatrix Filters::gaussian_low_pass(int height, int width, double fc) {
    CompMatrix filter(height, std::vector<cn>(height, 0));
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

CompMatrix Filters::high_pass(int height, int width, double fc) {
    CompMatrix filter(height, std::vector<cn>(height, 0));
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
CompMatrix Filters::low_pass(int height, int width, double fc) {
    CompMatrix filter(height, std::vector<cn>(height, 0));
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
