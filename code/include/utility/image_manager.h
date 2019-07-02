#ifndef __IMAGE_MANAGER_H__
#define __IMAGE_MANAGER_H__

#include "algorithms/fft.h"
#include <cmath>
#include <sstream>
#include <vector>

typedef typename std::vector<std::vector<cn>> CMatrix;

class ImageUtils {
   public:
    static bool cmp_complex(cn a, cn b) { return real(a) < real(b); }
    static double dist_euclid(int px, int py, int cx, int cy) {
        return sqrt(pow(px - cx / 2, 2) + pow(py - cy / 2, 2));
    }
};

class ImageTransform {
   private:
    int original_height, original_width;
    CMatrix complex_matrix;

   public:
    ImageTransform(const CMatrix& matrix);

    void transform(bool direction);  // False = Forward, True = Backwards

    void apply(const CMatrix& filter);

    void pad(void);
    void center(void);
    void shift(void);
    void crop(void);

    CMatrix get_matrix(void);

    std::pair<int, int> get_dimentions(void);
};

// class FilterFactory {
// public:
//};

class Filters {
   public:
    static CMatrix low_pass(int height, int width, double fc);
    static CMatrix high_pass(int height, int width, double fc);
    static CMatrix gaussian_low_pass(int height, int width, double fc);
};

#endif
