#include "algorithms/fft.h"
#include "utility/audio_wrapper.h"
#include "utility/matplotlibcpp.h"
#include <SFML/Audio/SoundBufferRecorder.hpp>
#include <boost/python.hpp>
#include <pygtk/pygtk.h>
#include <exception>
#include <gtkmm.h>
#include <iostream>
#include <string>

#define AUDIO_PATH "res/audio/"

namespace little_endian_io
{
  template <typename Word>
  std::ostream& write_word( std::ostream& outs, Word value, unsigned size = sizeof( Word ) )
  {
    for (; size; --size, value >>= 8)
      outs.put( static_cast <char> (value & 0xFF) );
    return outs;
  }
}
using namespace std;

FourierAudio::FourierAudio(vector<cn> raw){
	ofstream f("test_audio.wav", ios::binary);
	double hz = 44100; //Sample per second from the function
	double bits_per_sample = 1000;
	double sample_rate =10;
	double channels = 2;
	f << "RIFF";
	f << "----"; // Fill with the size of input data
	f << "WAVE";
	f << "fmt";
	write_word(f, 16, 4); // Chunk data size
	write_word(f, 1, 2); // Format (compression code)
	write_word(f, 2, 2); // 2 bytes - Channels (default: 2)
	write_word(f, hz, 4); // 4 bytes - Sample per second (HZ)
	write_word(f, (sample_rate * bits_per_sample * channels) / 8, 4); // 4 bytes - (Sample Rate * Bits per sample *Channels ) / 8
	write_word(f, 4, 2); // 2 bytes - Data block size (size of 2 integer samples, one for each channel)
	write_word(f, 16, 2);  // 2 bytes - Number of bits per samble (multiple of 8 so as to use bytes)
	
	size_t data_chunk_pos = f.tellp();
  stream.write("data", 4);
	f << ""; // Data buffer size
	f << ""; //Data buffer 

	constexpr double two_pi = 6.283185307179586476925286766559;
	constexpr double max_amplitude = 32760;

	double frequency = 261.626;
	double seconds = 2.5;

	int N = hz * seconds;
	for(int x = 0;x < N;x++){
		double amplitude = (double) x / N * max_amplitude;
		double value = sin( (two_pi * x * frequency) / hz);
		write_word(f, (int)(amplitude * value), 2);
		write_word(f, (int)((max_amplitude - amplitude) * value), 2);
	}

	size_t file_len = f.tellp();
	f.seekp(data_chunk_pos + 4);
	write_word(f, file_len - data_chunk_pos + 8);

	f.seekp(4);
	write_word(f, file_len -8, 4)
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

void FourierAudio::plotSignal(void) const {
		namespace plt = matplotlibcpp;

		auto raw_samples = buffer.getSamples();
		auto count = buffer.getSampleCount();
		vector<auto> samples(raw_samples, raw_samples + count);
		plt::plot(samples);
		plt::show();
}



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

