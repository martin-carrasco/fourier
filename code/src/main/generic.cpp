#include "utility/image_manager.h"
#include "utility/opencv_manager.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#define INPUT_PATH "res/image/input/"
#define OUTPUT_PATH "res/image/output/"
#define _FILE "yo.jpeg"

int main(void) {
    auto matrix = read_img(std::string(INPUT_PATH) + std::string(_FILE));
    display_img(matrix, 0);

    ImageTransform t(matrix);

    t.transform(false);
    t.shift();

    auto result = t.get_matrix();
    auto mat = display_img(result, 1);
    cv::imwrite(std::string(OUTPUT_PATH) + "freq_" + std::string(_FILE), mat);

    // -----------------------------------------------------------------------

    auto matrix2 = read_img(std::string(INPUT_PATH) + std::string(_FILE));

    ImageTransform q(matrix2);

    q.pad();
    q.center();
    q.transform(false);

    auto [height, width] = q.get_dimentions();

    Filters f0;
    ImageTransform f(f0.gaussian_low_pass(height, width, 10));

    q.apply(f.get_matrix());
    q.transform(true);
    q.center();
    q.crop();

    display_img(q.get_matrix(), 0);

    cv::waitKey(0);
    return 0;
}
