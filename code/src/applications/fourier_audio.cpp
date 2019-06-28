#include "utility/audio_wrapper.h"

void test_audio(void) {
    FourierAudio FA;
    FA.readAudio("linares.ogg");
    FA.printBuffer();
    FA.playAudio();
}
