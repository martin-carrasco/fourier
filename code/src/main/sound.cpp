#include "utility/image_manager.h"
#include "utility/audio_wrapper.h"
#include "utility/opencv_manager.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#define INPUT_PATH "res/image/input/"
#define OUTPUT_PATH "res/audio/output/"
#define _FILE "calato.JPG"

int main(void) {
    auto matrix = read_img(std::string(INPUT_PATH) + std::string(_FILE));

    ImageTransform q(matrix);
		
    q.pad();
    q.center();
    q.transform(false);
		
		auto out_freq_img = display_img(q.get_matrix(), 1);
		FourierAudio fa(FourierAudio::transform2DTo1D(q.get_matrix()));

		fa.playAudio();	

    cv::waitKey(0);
    return 0;
}
