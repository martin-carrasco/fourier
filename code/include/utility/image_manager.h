#ifndef __IMAGE_MANAGER_H__
#define __IMAGE_MANAGER_H__

#include "algorithms/fft.h"
#include <sstream>
#include <vector>

typedef typename std::vector<std::vector<cn>> CompMatrix;

std::vector<std::vector<cn>> lpf(std::vector<std::vector<cn>> f);

class ImageTransform {
   private:
    CompMatrix complex_matrix;
    void convolute_filter(CompMatrix& mask, int width, int height);

   public:
    ImageTransform(void);
    ImageTransform(CompMatrix& matrix);

    void apply_hp(double d0);
    void apply_lp(double d0);
    void apply_bp(double fc1, double fc2);

    void set_matrix(CompMatrix& matrix);
};

class ImageUtils {
   public:
    static bool cmp_complex(cn a, cn b) { return real(a) < real(b); }
    static CompMatrix pad0_complex(CompMatrix& matrix, int width, int height) {
        CompMatrix rows(width * 2, std::vector<cn>(height * 2, 0));
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                rows[x][y] = matrix[x][y];
            }
        }
        return rows;
    }
    static void center_matrix(CompMatrix& matrix) {
        int width = matrix.size();
        int height = matrix[0].size();
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                matrix[x][y] = matrix[x][y] * pow(-1, x + y);
            }
        }
    }
    static double dist_euclid(int cx, int cy, int px, int py) {
        return sqrt(pow(cx - px, 2) + pow(cy - py, 2));
    }
};
#endif
