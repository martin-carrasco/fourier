#ifndef __AUDIO_WRAPPER_H__
#define __AUDIO_WRAPPER_H__

#include <SFML/Audio.hpp>
#include "utility/image_manager.h"
#include <string>
#include <vector>

class FourierAudio {
    sf::SoundBuffer buffer;
		unsigned int start_note = 110;
		unsigned int start_octave = 1;
		static constexpr unsigned int end_octave = 8;
		static void calc_freq(int hz, int seconds, int max_amplitude, const std::vector<cn> & raw, sf::Int16* raw_samples);
   public:
		FourierAudio();
		void makeOgg(const std::string& path);
		void playAndDraw(std::vector<cn> raw_buffer, int hz, int max_amplitude, std::pair<int, int> window_size);
		void readBuffer(std::vector<cn> raw);
    void readAudio(const std::string path);
    void playAudio(void) const;
    void printBuffer(void) const;
    void plotSignal(void) const;

		static std::vector<cn> hilbert_curve(CMatrix mat);
		static std::vector<cn> transform2DTo1D(CMatrix mat);
};
#endif
