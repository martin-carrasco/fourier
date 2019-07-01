#include "utility/image_manager.h"
#include "utility/opencv_manager.h"
#include <cmath>
#include <iostream>
#include <vector>
#define INPUT_PATH "res/image/input/"
#define OUTPUT_PATH "res/image/output/"

int main(int argc, const char* argv[]) {
    auto matrix = read_img(argv[1]);

    ImageTransform image(matrix);
    image.pad();
    image.center();

    auto filter_h = FilterTransform::high_pass(
        image.get_matrix().size(), image.get_matrix()[0].size(), 20);
    auto filter_l = FilterTransform::low_pass(
        image.get_matrix().size(), image.get_matrix()[0].size(), 120);
    image.transform(false);

    image.convolute_whole(filter_l);
    image.convolute_whole(filter_h);

    image.transform(true);
    image.center();

    image.crop();

    auto result = image.get_matrix();
    // if (!atoi(argv[2])) {
    // ct_in_fft2d(img, false);
    // shift_fft2d(img);
    //} else {
    // ct_in_fft2d(img, false);
    // shift_fft2d(img);
    // ct_in_fft2d(img, true);
    //}
    //
    display_img(result, atoi(argv[2]));
    return 0;
}
