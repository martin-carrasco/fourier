#ifndef __IMAGE_MANAGER_H__
#define __IMAGE_MANAGER_H__

#include "algorithms/2dfft.h"
#include <sstream>
#include <vector>

class ImageFilter {
 public:
  virtual std::vector<std::vector<cn>> make_filter(
      std::vector<std::vector<cn>> matrix, int width, int height, int d0) = 0;
};

class ImageMedianFilter : public ImageFilter {
 public:
  std::vector<std::vector<cn>> make_filter(std::vector<std::vector<cn>> matrix,
                                           int width, int height, int d0);
};

std::vector<std::vector<cn>> low_pass_filter(int width, int height, int d0);
class ImageLowFilter : public ImageFilter {
 public:
  std::vector<std::vector<cn>> make_filter(std::vector<std::vector<cn>> matrix,
                                           int width, int height, int d0);
};

class ImageUtils {
 public:
  static bool cmp_complex(cn a, cn b) { return real(a) < real(b); }
  static std::vector<std::vector<cn>> pad0_complex(
      std::vector<std::vector<cn>>& matrix, int width, int height) {
    std::vector<std::vector<cn>> rows(width * 2,
                                      std::vector<cn>(height * 2, 0));
    for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
        rows[x][y] = matrix[x][y];
      }
    }
    return rows;
  }
  static void center_matrix(std::vector<std::vector<cn>>& matrix) {
    int width = matrix.size();
    int height = matrix[0].size();
    for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
        matrix[x][y] = matrix[x][y] * pow(-1, x + y);
      }
    }
  }
  static float dist_euclid(int cx, int cy, int px, int py) {
    return sqrt(pow(cx - px, 2) + pow(cy - py, 2));
  }
};

class ImageTransform {
 private:
  std::vector<std::vector<cn>> complex_matrix;

 public:
  ImageTransform(void);
  ImageTransform(std::vector<std::vector<cn>> matrix);
  ImageTransform(std::vector<std::vector<double>> matrix);

  void apply_transform(ImageFilter* filter);

  void set_matrix(std::vector<std::vector<cn>> matrix);
  void set_matrix(std::vector<std::vector<double>> matrix);

  std::vector<std::vector<cn>> get_matrix(void);
};
#endif
