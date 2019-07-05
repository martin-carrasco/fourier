#include "utility/image_manager.h"
#include "utility/opencv_manager.h"
#include <cmath>
#include <iostream>
#include <vector>
#define INPUT_PATH "res/image/input/"
#define OUTPUT_PATH "res/image/output/"

int main(int argc, const char* argv[]) {
    auto matrix = read_img(argv[1]);

    ImageTransform t(matrix);

    t.transform(false);
    t.shift();

    auto result = t.get_matrix();
    auto mat = display_img(result, atoi(argv[2]));
    cv::imwrite("res/image/output/yo_freq.jpeg", mat);
    return 0;
}
