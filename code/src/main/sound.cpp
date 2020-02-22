#include "utility/image_manager.h"
#include "utility/audio_wrapper.h"
#include "utility/opencv_manager.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#define INPUT_PATH "res/image/input/"
#define OUTPUT_PATH "./res/audio/output/"
#define _FILE "kene_small_3.JPG"

using namespace std;

int main(void) {
    auto matrix = read_img(std::string(INPUT_PATH) + std::string(_FILE));

    ImageTransform q(matrix);
		cout << "Image loaded" << endl;		
		q.pad();
    q.center();
    q.transform(false);

		cout << "Transformation" << endl;
		auto out_freq_img = display_img(q.get_matrix(), 1);

		cv::waitKey(0);
		FourierAudio fa;
		//fa.makeWav(FourierAudio::transform2DTo1D(q.get_matrix()));
		fa.readBufferFromVec(FourierAudio::transform2DTo1D(q.get_matrix()));
		cout << "Audio" <<endl;
		//fa.printBuffer();
		fa.playAudio();	
		cout << "Finished" << endl;

    cv::waitKey(0);
    return 0;
}
