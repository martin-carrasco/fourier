#include "utility/image_manager.h"
#include "utility/opencv_manager.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#define INPUT_PATH "res/image/input/"
#define OUTPUT_PATH "res/image/output/"
#define _FILE "lena_128.png"

int main(void) {
    auto matrix = read_img(std::string(INPUT_PATH) + std::string(_FILE));

    ImageTransform q(matrix);

		display_img(q.get_matrix(), 0);

    q.pad();
    q.center();
    q.transform(false);

    auto [height, width] = q.get_dimentions();
		auto out_freq_img = display_img(q.get_matrix(), 1);

    Filters f0;
    ImageTransform f(f0.gaussian_low_pass(height, width, 11));
		auto out_freq_filter = display_filter(f.get_matrix(), 0);


    q.apply(f.get_matrix());
		auto out_transformed_freq = display_img(q.get_matrix(), 1);
    q.transform(true);
    q.center();
    q.crop();

    auto out_mat = display_img(q.get_matrix(), 0);
		cv::imwrite(std::string(OUTPUT_PATH) + "transformed_freq_" + std::string(_FILE), out_transformed_freq);
		cv::imwrite(std::string(OUTPUT_PATH) + "filter_freq_" + std::string(_FILE), out_freq_filter);
		cv::imwrite(std::string(OUTPUT_PATH) + "transformed_" + std::string(_FILE), out_mat);	
		cv::imwrite(std::string(OUTPUT_PATH) + "image_freq_" + std::string(_FILE), out_freq_img);	
    cv::waitKey(0);
    return 0;

}
