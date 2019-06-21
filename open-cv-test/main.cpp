#include <fstream>

// Open CV
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#define FILENAME "input/lenna.png"
#define OUTPUTFILE "output/output.txt"

typedef cv::Mat Img;

int main() {
  // Generate CSV
  Img image = cv::imread(FILENAME, cv::IMREAD_GRAYSCALE);
  std::fstream file(OUTPUTFILE, std::ios::out);
  file << cv::format(image, cv::Formatter::FMT_CSV);

  // Read CSV
  // Source: https://answers.opencv.org/question/55210/reading-csv-file-in-opencv/
  std::fstream inputfile(OUTPUTFILE, std::ios::in);
  std::string current_line;
  // vector allows you to add data without knowing the exact size beforehand
  std::vector<std::vector<int>> all_data;
  // Start reading lines as long as there are lines in the file
  while (getline(inputfile, current_line)) {
    // Now inside each line we need to seperate the cols
    std::vector<int> values;
    std::stringstream temp(current_line);
    std::string single_value;
    while (getline(temp, single_value, ',')) {
      // convert the string element to a integer value
      values.push_back(atoi(single_value.c_str()));
    }

    // add the row to the complete data vector
    all_data.push_back(values);
  }

  // Now add all the data into a Mat element
  Img vect = Img::zeros((int) all_data.size(), (int) all_data[0].size(), CV_8UC1);
  // Loop over vectors and add the data
  for (int rows = 0; rows < all_data.size(); rows++) {
    for (int cols = 0; cols < all_data[0].size(); cols++) {
      vect.at<uchar>(rows, cols) = all_data[rows][cols];
    }
  }

  // Show image
  cv::namedWindow("Image", cv::WINDOW_NORMAL);
  cv::imshow("Image", vect);
  cv::waitKey(0);

  return 0;
}
