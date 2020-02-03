#include "utility/image_manager.h"
#include "utility/opencv_manager.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#define INPUT_PATH "res/audio/input/"
#define OUTPUT_PATH "res/audio/output/"
#define _FILE "test_image.png"

int main(void) {
    auto matrix = read_img(std::string(INPUT_PATH) + std::string(_FILE));

    ImageTransform q(matrix);

		display_img(q.get_matrix(), 0);

			
		auto out_freq_img = display_img(q.get_matrix(), 1);

		FourierAudio fa(FourierAudio::transform2DTo1D(out_freq_img));

		fa.playAudio();	

    cv::waitKey(0);
    return 0;
}
