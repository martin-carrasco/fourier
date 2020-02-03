#include "algorithms/fft.h"
#include "utility/audio_wrapper.h"
//#include "utility/matplotlibcpp.h"
#include <SFML/Audio/SoundBufferRecorder.hpp>
//#include <boost/python.hpp>
//#include <pygtk/pygtk.h>
#include <exception>
//#include <gtkmm.h>
#include <iostream>
#include <string>

#define AUDIO_PATH "res/audio/"
using namespace std;

FourierAudio::FourierAudio(vector<cn> raw){
	ofstream f("test_audio.wav", ios::binary);
	double hz = 44100; //Sample per second from the function
	f << "RIFF----WAVEfmt "; //Fill ---- with size

	/* Data format
	 * 4 bytes - extension data
	 * 2 bytes - PCM integer samples (default: 1)
	 * 2 bytes - Channels (default: 2)
	 * 4 bytes - Sample per second (HZ)
	 * 4 bytes - (Sample Rate * Bits per sample *Channels ) / 8
	 * 2 bytes - Data block size (size of 2 integer samples, one for each channel)
	 * 2 bytes - Number of bits per samble (multiple of 8 so as to use bytes)
	*/
	f << "data----"; // Fill ---- with size


	//Fill size with raw data 
	

	//Fill ---- with the chunk size

}

void FourierAudio::readAudio(const std::string path) {
    std::cout << "Reading audio file from: " << AUDIO_PATH << path << "\n";
    if (not buffer.loadFromFile(AUDIO_PATH + path))
        throw std::runtime_error("File " AUDIO_PATH + path +
                                 " couldn't be found.");
}

void FourierAudio::playAudio(void) const {
    if (buffer.getSampleCount() == 0)
        throw std::runtime_error("No audio to play.");

    sf::Sound sound(buffer);
    sound.play();
    while (sound.getStatus() == sf::Music::Playing);
}

void FourierAudio::printBuffer(void) const {
    auto samples = buffer.getSamples();
    auto count = buffer.getSampleCount();

    for (int i = 0; i < count; ++i) std::cout << samples[i] << " ";
    std::cout << std::endl;
}
/*
 * void FourierAudio::plotSignal(void) const {
 *     namespace plt = matplotlibcpp;
 *
 *     auto raw_samples = buffer.getSamples();
 *     auto count = buffer.getSampleCount();
 *     vector<auto> samples(raw_samples, raw_samples + count);
 *     plt::plot(samples);
 *     plt::show();
 * }
 */

/*
int main(int argc, const char* argv[]) {
  // first check if an input audio device is available on the system
  std::string cmd;
  bool recorded = false;
  if (!sf::SoundBufferRecorder::isAvailable()) {
  }  // create the recorder
  sf::SoundBufferRecorder recorder;

  // start the capture
  while (true) {
    cout << ">> ";
    cin >> cmd;

    if (cmd.compare("exit") == 0) break;
    if (cmd.compare("record") == 0) {
      cout << "Recording...\n";
      recorder.start();
      cmd.clear();
      while (true) {
        cout << ">> ";
        cin >> cmd;
        if (cmd.compare("stop") == 0) {
          recorder.stop();
          cout << "Stopped recording...\n";
          recorded = true;
          break;
        }
      }
      cmd.clear();
      cout << ">> ";
      cin >> cmd;
    }

    if (cmd.compare("play") == 0 and recorded) {
      cout << "Playing recorded\n";
      const sf::SoundBuffer& buffer = recorder.getBuffer();
      sf::Sound sound;
      sound.setBuffer(buffer);
      sound.stop();
      sound.play();
      sf::Sound::Status Status = sound.getStatus();
      const sf::Int16* Samples = buffer.getSamples();
      std::size_t Count = buffer.getSampleCount();
      cout << "played\n";
    }
    if (cmd.compare("save") == 0 and recorded) {
      cout << "Saving recorded\n";
      const sf::SoundBuffer& buffer = recorder.getBuffer();
      buffer.saveToFile("my_record.ogg");
    }
    cmd.clear();
  }

  return 0;
}
*/
