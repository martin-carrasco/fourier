#include "algorithms/fft.h"
#include "utility/audio_wrapper.h"
#include <SFML/Audio/SoundBufferRecorder.hpp>
#include <exception>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

#define AUDIO_PATH "res/audio/"

namespace little_endian_io
{
  template <typename Word>
  std::ostream& write_word( std::ostream& outs, Word value, unsigned size = sizeof( Word ) )
  {
    for (; size; --size, value >>= 8)
      outs.put( static_cast <char> (((int)value) & 0xFF) );
    return outs;
  }
}

void rot(int n, int *x, int *y, int rx, int ry) {
    if (ry == 0) {
        if (rx == 1) {
            *x = n-1 - *x;
            *y = n-1 - *y;
        }

        //Swap x and y
        int t  = *x;
        *x = *y;
        *y = t;
    }
}
/**
 * r_max/min Denotes the extremes of the actual range
 * t_max/min Denotes the extremes of the target meassure
 * m Number to be evaluated
 */
int scale_range(int r_max, int r_min, int t_max, int t_min, int m){
	return (int)((m - r_min) / (r_max - r_min ) ) * (t_max - t_min) + t_min;
}

int xy2d (int n, int x, int y) {
    int rx, ry, s, d=0;
    for (s=n/2; s>0; s/=2) {
        rx = (x & s) > 0;
        ry = (y & s) > 0;
        d += s * s * ((3 * rx) ^ ry);
        rot(n, &x, &y, rx, ry);
    }
    return d;
}
using namespace std;
using namespace little_endian_io;

double magn(vector<double> v) {
    double sum = 0;

    for (auto x : v) sum += pow(x, 2);

    return sqrt(sum);
}
void FourierAudio::makeWav(vector<cn> raw){
	ofstream f(AUDIO_PATH + string("test_audio.wav"), ios::binary);
	double hz = 44100; //Sample per second from the function
	double bits_per_sample = 1000;
	double sample_rate =10;
	double channels = 2;
	f << "RIFF";
	f << "----"; // Fill with the size of input data
	f << "WAVE";
	f << "fmt ";
	write_word<int>(f, 16, 4); // Chunk data size
	write_word<int>(f, 1, 2); // Format (compression code)
	write_word<int>(f, 2, 2); // 2 bytes - Channels (default: 2)
	write_word<int>(f, hz, 4); // 4 bytes - Sample per second (HZ)
	write_word<int>(f, 176400, 4);
//	write_word<int>(f, (int)(sample_rate * bits_per_sample * channels) / 8, 4); // 4 bytes - (Sample Rate * Bits per sample *Channels ) / 8
	write_word<int>(f, 4, 2); // 2 bytes - Data block size (size of 2 integer samples, one for each channel)
	write_word<int>(f, 16, 2);  // 2 bytes - Number of bits per samble (multiple of 8 so as to use bytes)
	
	size_t data_chunk_pos = f.tellp();
  f << "data---";


	double frequency = 261.626;
	double seconds = 10;


/*
	int N = hz * seconds;
	for(int x = 0;x < N;x++){
		double amplitude = (double) x / N * max_amplitude;
		double value = sin( (two_pi * x * frequency) / hz);
		write_word(f, (int)(amplitude * value), 2);
		write_word(f, (int)((max_amplitude - amplitude) * value), 2);
	}*/

	size_t file_len = f.tellp();
	f.seekp(data_chunk_pos + 4);
	write_word<int>(f, file_len - data_chunk_pos + 8);

	f.seekp(4);
	write_word<int>(f, file_len -8, 4);
	f.close();
}

FourierAudio::FourierAudio(){}

void FourierAudio::readBufferFromVec(std::vector<cn> raw){
	sf::Int16 * raw_samples = new sf::Int16[raw.size()];

  int volume_constant = 5;
	//int sample_rate = static_cast<int>(sqrt(raw.size()));
	int sample_rate = sqrt(raw.size());
	for (int x = 0; x < raw.size(); x++){
		int mag = sqrt(pow(raw[x].real(), 2) + pow(raw[x].imag(), 2));
		cout << mag;
		for (int oct = start_octave; oct <= end_octave;oct++){
			unsigned int note = pow(2, oct) * start_note;
			if(mag >= note and mag < pow(2, oct+1) * start_note){
				raw_samples[x] = static_cast<sf::Int16>(note);
			}
		}
	}

	if(!buffer.loadFromSamples(raw_samples, raw.size(), 1, 20)){
		cout << "error reading samples" << endl;
		return;
	}
	
	buffer.saveToFile("res/audio/output/beep_boop_3.ogg");

	cout << "Finished saving";
	
	/*int hz = raw.size();
	int sample_size = hz * 2;
	int seconds = 10;
	int N = hz * seconds;
	sf::Int16 ** raw_samples = new sf::Int16*[seconds];
	

	for (int x = 0;x < 10;x++){
		raw_samples[x] = new sf::Int16[sample_size];
		for (int y = 0;y < sample_size;y++){
			raw_samples[x][y] = 0;
		}
	}

	int max_amplitude = 	15000;
	for(int x = 0;x < sample_size * seconds;x+= 2){
		int mag = sqrt(pow(raw[x].real(), 2) + pow(raw[x].imag(), 2));
		double amplitude = (double) x / (sample_size * seconds);
		double value = sin( ((M_PI * 2) * x * (mag / seconds )) / hz);
		cout << value;
		raw_samples[static_cast<int>(x / hz)][x % hz] = amplitude * value;
		raw_samples[static_cast<int>(x / hz)][(x % hz) + 1] = (max_amplitude - amplitude) * 2;
	}
	
	for(int x = 0;x < 10;x++){
		if(!buffer.loadFromSamples(raw_samples[x], sample_size(), 1, sample_size)){
			cout << "error reading samples" << endl;
			return;
		}
	}*/
}

vector<cn> FourierAudio::hilbert_curve(CMatrix mat){
	vector<cn> freq_repre(mat.size() * mat.size(), 0); // Create the 1D representation size

	for(int x = 0;x < mat.size();x++){
		for(int y = 0; y < mat.size();y++){
			freq_repre[xy2d(mat.size(), x, y)] =  mat[x][y];
		}
	}
	return freq_repre;
}
vector<cn> FourierAudio::transform2DTo1D(CMatrix mat){
	//TODO: Do hilbert curve or peanno curve
	return hilbert_curve(mat);
}
void FourierAudio::readAudio(const string path) {

		string abs_path = AUDIO_PATH + path;
    cout << "Reading audio file from: " << abs_path << "\n";
    if (!buffer.loadFromFile(abs_path)){
        throw std::runtime_error("File "+ abs_path+" couldn't be found.");
		}
}

void FourierAudio::playAudio(void) const {
    if (buffer.getSampleCount() == 0)
        throw std::runtime_error("No audio to play.");

    sf::Sound sound;
		sound.setBuffer(buffer);
		sound.setLoop(false);
		sound.setVolume(100);
    sound.play();
    while (sound.getStatus() == sf::Music::Playing);
}

void FourierAudio::printBuffer(void) const {
    auto samples = buffer.getSamples();
    auto count = buffer.getSampleCount();

    for (int i = 0; i < count; ++i) std::cout << samples[i] << " ";
    std::cout << std::endl;
}

/*void FourierAudio::plotSignal(void) const {
		namespace plt = matplotlibcpp;

		auto raw_samples = buffer.getSamples();
		auto count = buffer.getSampleCount();
		vector<auto> samples(raw_samples, raw_samples + count);
		plt::plot(samples);
		plt::show();
}*/



/*int main(int argc, const char* argv[]) {
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
}*/

