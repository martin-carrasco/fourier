#ifndef __AUDIO_WRAPPER_H__
#define __AUDIO_WRAPPER_H__

#include <SFML/Audio.hpp>
#include <string>
#include <vector>

class FourierAudio {
    sf::SoundBuffer buffer;

   public:
		FourierAudio(std::vector<cn> raw);
    void readAudio(const std::string path);
    void playAudio(void) const;
    void printBuffer(void) const;
    void plotSignal(void) const;
		static std::vector<cn> transform2DTo1D(CMatrix mat);
};
#endif
