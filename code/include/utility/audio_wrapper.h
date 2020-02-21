#ifndef __AUDIO_WRAPPER_H__
#define __AUDIO_WRAPPER_H__

#include <SFML/Audio.hpp>
#include "utility/image_manager.h"
#include <string>
#include <vector>

class FourierAudio {
    sf::SoundBuffer buffer;
		std::vector<unsigned int> buckets{55, 110, 220, 440, 880};

   public:
		FourierAudio();
		void makeWav(std::vector<cn> raw);
		void readBufferFromVec(std::vector<cn> raw);
    void readAudio(const std::string path);
    void playAudio(void) const;
    void printBuffer(void) const;
    void plotSignal(void) const;

		static std::vector<cn> hilbert_curve(CMatrix mat);
		static std::vector<cn> transform2DTo1D(CMatrix mat);
};
#endif
