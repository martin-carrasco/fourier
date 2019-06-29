#include "utility/image_manager.h"
#include <algorithm>

using namespace std;

ImageTransform::ImageTransform(void) {}

ImageTransform::ImageTransform(CompMatrix& matrix) {
  this->complex_matrix(matrix);
}

void ImageTransform::convolute_filter(CompMatrix& mask, int width, int height) {
  // 2D FFT
  fft2d(complex_matrix, width, height);

  // Apply the filter H(x, y) to F(x, y) (multiply)
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      complex_matrix[x][y] = complex_matrix[x][y] * mask[x][y];
    }
  }

  // Inverse 2D FFT
  ifft2d(complex_matrix, width, height);

  // Crop back ????
  // for (int x = 0; x < width; x++) {
  // for (int y = 0; y < height; y++) {
  // this->complex_matrix[x][y] = rows[x][y];
  //}
  //}
}

void ImageTransform::apply_lp(double d0) {
  int width = this->complex_matrix.size();
  int height = this->complex_matrix[0].size();

  CompMatrix image_filter(width, vector<cn>(height, 0));

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      double m = (static_cast<double>(x) - static_cast<double>(width) / 2.D) /
                 static_cast<double>(width);
      double n = (y - height / 2.D) / static_cast<double>(height);

      double total = sqrt(pow(m, 2) + pow(n, 2));

      if (total < d0)
        image_filter[x][y] = 1;
      else
        image_filter[x][y] = 0;
    }
  }

  this->convolute_filter(image_filter, width, height);
}

void ImageTransform::apply_bp(double fc1, double fc2) {
  int width = this->complex_matrix.size();
  int height = this->complex_matrix[0].size();

  CompMatrix image_filter(width, vector<cn>(height, 0));

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      double m = (static_cast<double>(x) - static_cast<double>(width) / 2.D) /
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

void ImageTransform::set_matrix(CompMatrix& matrix) {
  this->complex_matrix = matrix;
}
