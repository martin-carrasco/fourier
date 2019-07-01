#ifndef __IMAGE_MANAGER_H__
#define __IMAGE_MANAGER_H__

#include "algorithms/fft.h"
#include <cmath>
#include <sstream>
#include <vector>

typedef typename std::vector<std::vector<cn>> CompMatrix;

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
    CompMatrix complex_matrix;

   public:
    ImageTransform(CompMatrix matrix);

    void transform(bool direction);  // False = Forward, True = Backwards

    void convolute_kernel(const CompMatrix& kernel);
    void convolute_whole(const CompMatrix& filter);

    void pad(void);
    void center(void);
    void shift(void);
    void crop(void);

    CompMatrix get_matrix(void);

    std::pair<int, int> get_dimentions(void);
};

class FilterFactory {
   public:
};
class Filters {
   public:
    static CompMatrix low_pass(int height, int width, double fc);
    static CompMatrix high_pass(int height, int width, double fc);
    static CompMatrix gaussian_low_pass(int height, int width, double fc);
};

class FilterTransform {
   public:
};
#endif
