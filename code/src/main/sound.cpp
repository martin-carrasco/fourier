#include "utility/image_manager.h"
#include "utility/audio_wrapper.h"
#include "utility/opencv_manager.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#define INPUT_PATH "res/image/input/"
#define OUTPUT_PATH "./res/audio/output/"
#define _FILE "kene_5.jpg"

using namespace std;

int main(void) {
    auto matrix = read_img(std::string(INPUT_PATH) + std::string(_FILE));

    ImageTransform q(matrix);
		cout << "Image loaded" << endl;		
		q.pad();
    q.center();
    q.transform(false);

		auto [height, width] = q.get_dimentions();

		Filters f;
		ImageTransform filter(f.gaussian_low_pass(height, width, 12));
		
		//q.apply(filter.get_matrix());

		cout << "Transformation" << endl;

		//auto out_freq_img = display_img(q.get_matrix(), 1);

		FourierAudio fa;
		//fa.makeWav(FourierAudio::transform2DTo1D(q.get_matrix()));
		vector<cn> freq_array = FourierAudio::hilbert_curve(q.get_matrix());
		fa.playAndDraw(freq_array, freq_array.size(), 1000, make_pair(800, 800));
		cout << "Audio" <<endl;
		//fa.printBuffer();
		//fa.playAudio();	
		//fa.makeOgg(string(OUTPUT_PATH) + "kene_5.ogg");
		cout << "Finished" << endl;

    return 0;
}
