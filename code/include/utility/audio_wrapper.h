#ifndef __AUDIO_WRAPPER_H__
#define __AUDIO_WRAPPER_H__

#include <SFML/Audio.hpp>
#include <string>

class FourierAudio {
    sf::SoundBuffer buffer;

   public:
    void readAudio(const std::string path);
    void playAudio(void) const;
    void printBuffer(void) const;
    void plotSignal(void) const;
};
#endif
