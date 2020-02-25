#include "algorithms/fft.h"
#include "utility/audio_wrapper.h"
#include <SFML/Audio/SoundBufferRecorder.hpp>
#include <SFML/Graphics.hpp>
#include <exception>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <thread>

using namespace std;

#define AUDIO_PATH "res/audio/"

void FourierAudio::calc_freq(int hz, int second, int max_amplitude, const vector<cn>& raw, sf::Int16* raw_samples) {
	double freq = 0;
	int start_pos = hz * second;
	for(int x = 0;x < hz;x++){
		// mag  = sqrt(even^2 + odd^2)
		double mag = sqrt(pow(raw[x + start_pos].real(), 2) + pow(raw[x + start_pos].imag(), 2));

		// Changes of frequencies in a given wave (Maybe make a harmonic bucket ??? )
		double current_point = sin(M_PI * 2 * freq * (second+1));
		int value = max_amplitude * current_point;

		// Calculation for the actual frequency value given in the sin
		freq += mag / hz;
		raw_samples[x] = value;
		//cout << mag << endl;
		//cout << current_point << endl;
		//cout << value << endl << endl;;

	}
}

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
void FourierAudio::makeOgg(){

}

FourierAudio::FourierAudio(){}

void FourierAudio::playAndDraw(std::vector<cn> raw_buffer, int hz, int max_amplitude, pair<int, int> window_size){
		int seconds = raw_buffer.size() / hz;		
		int N = hz * seconds;
		int current_second = 0;

		
		// Basic preparation for SFML display
		sf::RenderWindow window(sf::VideoMode(window_size.first, window_size.second), "Soundwave");
		sf::VertexArray vert(sf::LineStrip, window_size.second);

		// Drawing loop that iterates over the data in the seconds
		while(window.isOpen()){
			sf::Event event;
			while(window.pollEvent(event)){
				switch(event.type){
					case sf::Event::Closed:
							window.close();
							break;
				}
			}

			// Break if the seconds of sampling run out
			if(current_second >= seconds)
				break;

			sf::Int16* raw_samples = new sf::Int16[hz];

			// Calculate sample data based on frequencies
			calc_freq(hz, current_second, max_amplitude, ref(raw_buffer), ref(raw_samples));

			// Load sample data into graphical buffer
			int rate = hz / window_size.first;
			for(int i = 0;i < window_size.first;i++){
				int samp = raw_samples[i * rate];
				vert[i].position = sf::Vector2f(i, window_size.second/2 + samp / 10);
				//cout << current_sample << endl;
				//cout << raw_samples[0][i] << endl << endl;
			}

			// Load data into sound buffer (TODO CHANGE TO sf::Music)
			sf::SoundBuffer current_buffer;
			current_buffer.loadFromSamples(raw_samples, hz, 1, hz);
			sf::Sound sound;
			sound.setBuffer(current_buffer);
			sound.setLoop(false);

			// Clear window draw and play audio
			window.clear();
			window.draw(vert);
			window.display();
			sound.play();

			while (sound.getStatus() == sf::Music::Playing);

			current_second++;
		}
}

void FourierAudio::readBuffer(std::vector<cn> raw){
	int hz = raw.size();
	int seconds = 1;
	int N = hz * seconds;
	sf::Int16 ** raw_samples = new sf::Int16*[seconds];
	
	for (int x = 0;x < seconds;x++){
		raw_samples[x] = new sf::Int16[hz];
		for (int y = 0;y < hz;y++){
			raw_samples[x][y] = 0;
		}
	}

	double freq = 0;
	int max_amplitude =	1000;
	
	vector<thread> workers;
	for(int i = 0;i < seconds;i++){
		workers.push_back(thread(calc_freq, i, hz, max_amplitude, ref(raw), raw_samples[i]));
		cout << "Exec thread: " << i << endl;
	}

	for(auto & t : workers){
		t.join();
		cout << "Thread finished" << endl;
	}
	
	sf::RenderWindow window(sf::VideoMode(800, 800), "Soundwave");
	sf::VertexArray vert(sf::LineStrip, 800);

	int rate = raw.size() / 800;

	for(int i = 0;i < 800;i++){
		int current_sample = raw_samples[0][i * rate];
		vert[i].position = sf::Vector2f(i, 800/2 + current_sample / 10);
		//cout << current_sample << endl;
		//cout << raw_samples[0][i] << endl << endl;
	}
	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			switch(event.type){
				case sf::Event::Closed:
						window.close();
						break;
			}
			window.clear();
			window.draw(vert);
			window.display();
		}
	}

	for(int x = 0;x < seconds;x++){
		if(!buffer.loadFromSamples(raw_samples[x], hz, 1, hz)){
			cout << "error reading samples" << endl;
		}
    sf::Sound sound;
		sound.setBuffer(buffer);
		sound.setLoop(false);
    sound.play();

    while (sound.getStatus() == sf::Music::Playing);
	}
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

