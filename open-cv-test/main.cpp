#include <fstream>

// Open CV
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iomanip>

#define FILENAME "input/lenna.png"
#define OUTPUTFILE "output/output.txt"

typedef cv::Mat Img;

int main() {
  Img image = cv::imread(FILENAME, cv::IMREAD_GRAYSCALE);
  std::fstream file(OUTPUTFILE, std::ios::out);
  file << cv::format(image, cv::Formatter::FMT_CSV);

  return 0;
}
